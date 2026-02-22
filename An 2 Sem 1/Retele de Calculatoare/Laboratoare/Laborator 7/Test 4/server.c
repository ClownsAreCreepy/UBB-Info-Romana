// server.c — practice server (sorted union of two int arrays, dedup)
// Protocol:
// 1) uint16 desc_len (net) + desc bytes
// 2) uint16 N (net) + N * int32 (net)  // A
// 3) uint16 M (net) + M * int32 (net)  // B
// Client -> Server:
//    uint16 K (net) + K * int32 (net) = sorted ascending union(A ∪ B) without duplicates
// Server -> Client:
//    uint16 status (net): 1=OK, 0=ERR
//
// Build: gcc -Wall -Wextra -pedantic server.c -o server
// Run:   ./server  (127.0.0.1:1234)

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

static int sfd = -1;

static void on_sigint(int sig) {
    (void)sig;
    if (sfd >= 0) close(sfd);
    exit(0);
}

static int send_all(int fd, const void *buf, size_t len) {
    const uint8_t *p = (const uint8_t *)buf;
    size_t off = 0;
    while (off < len) {
        ssize_t n = send(fd, p + off, len - off, 0);
        if (n <= 0) return -1;
        off += (size_t)n;
    }
    return 0;
}

static int recv_all(int fd, void *buf, size_t len) {
    uint8_t *p = (uint8_t *)buf;
    size_t off = 0;
    while (off < len) {
        ssize_t n = recv(fd, p + off, len - off, 0);
        if (n <= 0) return -1;
        off += (size_t)n;
    }
    return 0;
}

static int cmp_i32(const void *a, const void *b) {
    const int32_t x = *(const int32_t *)a;
    const int32_t y = *(const int32_t *)b;
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int main(void) {
    signal(SIGINT, on_sigint);
    srand((unsigned)time(NULL));

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0) { perror("socket"); return 1; }

    int opt = 1;
    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt");
        close(sfd); return 1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(1234);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (bind(sfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) { perror("bind"); return 2; }
    if (listen(sfd, 5) < 0) { perror("listen"); return 3; }

    puts("server ready on 127.0.0.1:1234 — task: sorted union of A and B (dedup)");

    for (;;) {
        struct sockaddr_in cli;
        socklen_t l = (socklen_t)sizeof(cli);
        int cfd = accept(sfd, (struct sockaddr *)&cli, &l);
        if (cfd < 0) { perror("accept"); continue; }
        puts("client connected");

        /* --- generate test payload --- */
        uint16_t N = (uint16_t)(8 + (rand() % 9));  /* 8..16 */
        uint16_t M = (uint16_t)(8 + (rand() % 9));  /* 8..16 */

        int32_t *A = (int32_t *)malloc((size_t)N * sizeof(int32_t));
        int32_t *B = (int32_t *)malloc((size_t)M * sizeof(int32_t));
        if (!A || !B) { perror("malloc"); free(A); free(B); close(cfd); continue; }

        for (uint16_t i = 0; i < N; ++i) {
            A[i] = (int32_t)((rand() % 101) - 50); /* -50..50 */
        }
        for (uint16_t j = 0; j < M; ++j) {
            B[j] = (int32_t)((rand() % 101) - 50);
        }

        /* expected union */
        int32_t *tmp = (int32_t *)malloc((size_t)(N + M) * sizeof(int32_t));
        if (!tmp) { perror("malloc"); free(A); free(B); close(cfd); continue; }

        memcpy(tmp, A, (size_t)N * sizeof(int32_t));
        memcpy(tmp + N, B, (size_t)M * sizeof(int32_t));
        qsort(tmp, (size_t)(N + M), sizeof(int32_t), cmp_i32);

        int32_t *expected = (int32_t *)malloc((size_t)(N + M) * sizeof(int32_t));
        if (!expected) { perror("malloc"); free(tmp); free(A); free(B); close(cfd); continue; }

        uint16_t K = 0;
        for (size_t i = 0; i < (size_t)(N + M); ++i) {
            if (K == 0 || tmp[i] != expected[K - 1]) {
                expected[K++] = tmp[i];
            }
        }

        const char *desc =
            "TASK: Compute the sorted ascending union of two int arrays A and B, removing duplicates.\n"
            "Response: uint16 K (net) + K * int32 (net) of the sorted unique values.\n"
            "Protocol:\n"
            " 1) uint16 desc_len (net) + desc bytes\n"
            " 2) uint16 N (net) + N * int32 (net)  // A\n"
            " 3) uint16 M (net) + M * int32 (net)  // B\n"
            " 4) client -> server: uint16 K (net) + K * int32 (net)\n"
            " 5) server -> client: uint16 status (net): 1=OK, 0=ERR\n";

        const uint16_t dlen = (uint16_t)strlen(desc);
        const uint16_t dlen_net = htons(dlen);
        if (send_all(cfd, &dlen_net, sizeof(dlen_net)) < 0 ||
            send_all(cfd, desc, dlen) < 0) {
            perror("send desc");
            free(expected); free(tmp); free(A); free(B); close(cfd); continue;
        }

        const uint16_t N_net = htons(N);
        if (send_all(cfd, &N_net, sizeof(N_net)) < 0) {
            perror("send N"); free(expected); free(tmp); free(A); free(B); close(cfd); continue;
        }
        for (uint16_t i = 0; i < N; ++i) {
            const uint32_t v_net = htonl((uint32_t)A[i]);
            if (send_all(cfd, &v_net, sizeof(v_net)) < 0) {
                perror("send A"); free(expected); free(tmp); free(A); free(B); close(cfd); continue;
            }
        }

        const uint16_t M_net = htons(M);
        if (send_all(cfd, &M_net, sizeof(M_net)) < 0) {
            perror("send M"); free(expected); free(tmp); free(A); free(B); close(cfd); continue;
        }
        for (uint16_t j = 0; j < M; ++j) {
            const uint32_t v_net = htonl((uint32_t)B[j]);
            if (send_all(cfd, &v_net, sizeof(v_net)) < 0) {
                perror("send B"); free(expected); free(tmp); free(A); free(B); close(cfd); continue;
            }
        }

        /* receive client's answer */
        uint16_t K_recv_net = 0;
        if (recv_all(cfd, &K_recv_net, sizeof(K_recv_net)) < 0) {
            perror("recv K"); free(expected); free(tmp); free(A); free(B); close(cfd); continue;
        }
        const uint16_t K_recv = ntohs(K_recv_net);

        int ok = (K_recv == K) ? 1 : 0;

        int32_t *vals = NULL;
        if (ok && K_recv > 0) {
            vals = (int32_t *)malloc((size_t)K_recv * sizeof(int32_t));
            if (!vals) { perror("malloc"); ok = 0; }
        }

        for (uint16_t i = 0; i < K_recv && ok; ++i) {
            uint32_t v_net;
            if (recv_all(cfd, &v_net, sizeof(v_net)) < 0) {
                perror("recv values");
                ok = 0;
                break;
            }
            vals[i] = (int32_t)ntohl(v_net);
        }

        if (ok) {
            for (uint16_t i = 0; i < K; ++i) {
                if (vals[i] != expected[i]) { ok = 0; break; }
            }
        }

        const uint16_t status = (uint16_t)(ok ? 1 : 0);
        const uint16_t status_net = htons(status);
        if (send_all(cfd, &status_net, sizeof(status_net)) < 0) {
            perror("send status");
        }

        printf("verdict: %s (N=%u, M=%u, Kexp=%u, Kgot=%u)\n",
               ok ? "OK" : "ERR",
               (unsigned)N, (unsigned)M, (unsigned)K, (unsigned)K_recv);

        free(vals);
        free(expected);
        free(tmp);
        free(A);
        free(B);
        close(cfd);
    }
}

