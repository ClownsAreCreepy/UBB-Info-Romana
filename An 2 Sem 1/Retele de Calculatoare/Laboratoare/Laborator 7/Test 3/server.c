// server.c — practice server (letter frequency a..z, case-insensitive)
// Protocol:
// 1) uint16 desc_len (net) + desc bytes
// 2) uint16 n (net) + n bytes string (no NUL)
// 3) client -> server: 26 * uint16 (net) counts for 'a'..'z' (case-insensitive)
// 4) server -> client: uint16 status (net): 1=OK, 0=ERR
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
#include <ctype.h>

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

    puts("server ready on 127.0.0.1:1234 — task: letter frequency a..z (case-insensitive)");

    for (;;) {
        struct sockaddr_in cli;
        socklen_t l = (socklen_t)sizeof(cli);
        int cfd = accept(sfd, (struct sockaddr *)&cli, &l);
        if (cfd < 0) { perror("accept"); continue; }
        puts("client connected");

        /* ---- generate test payload ---- */
        uint16_t n = (uint16_t)(40 + (rand() % 41)); /* 40..80 */
        char *sbuf = (char *)malloc(n);
        if (!sbuf) { perror("malloc"); close(cfd); continue; }

        const char *pool =
            "abcdefghijklmnopqrstuvwxyz"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "0123456789       ,.;:-_!?@#";
        const size_t plen = strlen(pool);
        for (uint16_t i = 0; i < n; ++i) {
            sbuf[i] = pool[(size_t)(rand() % (int)plen)];
        }

        uint16_t correct[26];
        for (int i = 0; i < 26; ++i) correct[i] = 0;

        for (uint16_t i = 0; i < n; ++i) {
            unsigned char ch = (unsigned char)sbuf[i];
            if (isalpha(ch)) {
                int idx = (int)(tolower(ch) - (unsigned char)'a');
                if (idx >= 0 && idx < 26) {
                    if (correct[idx] < UINT16_MAX) correct[idx]++;
                }
            }
        }

        const char *desc =
            "TASK: Return counts of letters 'a'..'z' in the provided ASCII string, case-insensitive.\n"
            "Only letters count; ignore digits, spaces, punctuation.\n"
            "Response must be 26 * uint16 (network byte order), in order 'a'..'z'.\n"
            "Protocol:\n"
            " 1) uint16 desc_len (net) + desc bytes\n"
            " 2) uint16 n (net) + n bytes string (no NUL)\n"
            " 3) client -> server: 26 * uint16 (net) counts\n"
            " 4) server -> client: uint16 status (net): 1=OK, 0=ERR\n";

        const uint16_t dlen = (uint16_t)strlen(desc);
        const uint16_t dlen_net = htons(dlen);
        if (send_all(cfd, &dlen_net, sizeof(dlen_net)) < 0 ||
            send_all(cfd, desc, dlen) < 0) {
            perror("send desc");
            free(sbuf); close(cfd); continue;
        }

        const uint16_t n_net = htons(n);
        if (send_all(cfd, &n_net, sizeof(n_net)) < 0 ||
            send_all(cfd, sbuf, n) < 0) {
            perror("send data");
            free(sbuf); close(cfd); continue;
        }

        uint16_t recv_counts[26];
        if (recv_all(cfd, recv_counts, sizeof(recv_counts)) < 0) {
            perror("recv counts");
            free(sbuf); close(cfd); continue;
        }

        int ok = 1;
        for (int i = 0; i < 26; ++i) {
            uint16_t cnt = ntohs(recv_counts[i]);
            if (cnt != correct[i]) { ok = 0; break; }
        }

        const uint16_t status = (uint16_t)(ok ? 1 : 0);
        const uint16_t status_net = htons(status);
        if (send_all(cfd, &status_net, sizeof(status_net)) < 0) {
            perror("send status");
        }

        printf("verdict: %s\n", ok ? "OK" : "ERR");

        free(sbuf);
        close(cfd);
    }
}

