// server.c — single-task practice server (digit sum of positive ints)
// Protocol:
// 1) uint16 desc_len (net) + desc bytes
// 2) uint16 N (net) + N * int32 (net)
// 3) client -> server: uint32 (net) = sum of digits of all positive numbers
// 4) server -> client: uint16 (net): 1=OK, 0=ERR
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

/* sum of digits of positive int32 */
static uint32_t digit_sum_positive(int32_t x) {
    if (x <= 0) return 0;
    uint32_t s = 0;
    while (x > 0) {
        s += (uint32_t)(x % 10);
        x /= 10;
    }
    return s;
}

int main(void) {
    signal(SIGINT, on_sigint);
    srand((unsigned)time(NULL));

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd < 0) { perror("socket"); return 1; }

    int opt = 1;
    setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(1234);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (bind(sfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) { perror("bind"); return 2; }
    if (listen(sfd, 5) < 0) { perror("listen"); return 3; }

    puts("server ready on 127.0.0.1:1234 — task: digit sum of positive ints");

    for (;;) {
        struct sockaddr_in cli;
        socklen_t l = (socklen_t)sizeof(cli);
        int cfd = accept(sfd, (struct sockaddr*)&cli, &l);
        if (cfd < 0) { perror("accept"); continue; }
        puts("client connected");

        /* generate N random ints */
        uint16_t N = (uint16_t)(10 + (rand() % 11)); // 10–20
        int32_t *arr = malloc((size_t)N * sizeof(int32_t));
        if (!arr) { perror("malloc"); close(cfd); continue; }

        uint32_t correct = 0;
        for (uint16_t i = 0; i < N; ++i) {
            int sign = (rand() % 2) ? 1 : -1;
            arr[i] = (int32_t)(sign * (rand() % 10000)); // ±0..9999
            correct += digit_sum_positive(arr[i]);
        }

        const char *desc =
            "TASK: Given an array of signed 32-bit integers, compute the sum of digits\n"
            "of all positive numbers only (ignore negatives & zeros).\n"
            "Protocol:\n"
            " 1) uint16 desc_len (net) + desc bytes\n"
            " 2) uint16 N (net) + N * int32 (net)\n"
            " 3) client -> server: uint32 (net) = total digit sum of positives\n"
            " 4) server -> client: uint16 (net): 1=OK, 0=ERR\n";

        const uint16_t dlen = (uint16_t)strlen(desc);
        const uint16_t dlen_net = htons(dlen);
        if (send_all(cfd, &dlen_net, sizeof(dlen_net)) < 0 ||
            send_all(cfd, desc, dlen) < 0) {
            perror("send desc");
            free(arr); close(cfd); continue;
        }

        /* send N + numbers */
        const uint16_t N_net = htons(N);
        if (send_all(cfd, &N_net, sizeof(N_net)) < 0) {
            perror("send N");
            free(arr); close(cfd); continue;
        }
        for (uint16_t i = 0; i < N; ++i) {
            const uint32_t v_net = htonl((uint32_t)arr[i]);
            if (send_all(cfd, &v_net, sizeof(v_net)) < 0) {
                perror("send arr");
                free(arr); close(cfd); continue;
            }
        }

        /* receive uint32 result */
        uint32_t recv_sum_net = 0;
        if (recv_all(cfd, &recv_sum_net, sizeof(recv_sum_net)) < 0) {
            perror("recv sum");
            free(arr); close(cfd); continue;
        }
        const uint32_t recv_sum = ntohl(recv_sum_net);

        uint16_t status = (recv_sum == correct) ? 1 : 0;
        const uint16_t status_net = htons(status);
        send_all(cfd, &status_net, sizeof(status_net));

        printf("expected=%u, got=%u -> %s\n",
               (unsigned)correct, (unsigned)recv_sum,
               status ? "OK" : "ERR");

        free(arr);
        close(cfd);
    }
}
