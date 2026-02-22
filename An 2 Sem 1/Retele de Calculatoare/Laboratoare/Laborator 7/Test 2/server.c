// server.c — single-task practice server (count vowels)
// Protocol:
// 1) uint16 desc_len (net) + desc text bytes
// 2) uint16 n (net) + n bytes string (no NUL)
// 3) client sends back uint16 cnt (net) = # of vowels in the string
// 4) server replies uint16 status (net): 1=OK, 0=ERR
//
// Build: gcc server.c -o server
// Run:   ./server   (listens on 127.0.0.1:1234)

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

static int is_vowel(unsigned char c) {
    return c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||
           c=='A'||c=='E'||c=='I'||c=='O'||c=='U';
}

static int send_all(int fd, const void *buf, size_t len) {
    const uint8_t *p = (const uint8_t*)buf;
    size_t off = 0;
    while (off < len) {
        ssize_t n = send(fd, p + off, len - off, 0);
        if (n <= 0) return -1;
        off += (size_t)n;
    }
    return 0;
}

static int recv_all(int fd, void *buf, size_t len) {
    uint8_t *p = (uint8_t*)buf;
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

    // --- socket setup ---
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

    printf("server ready on 127.0.0.1:1234 — task: count vowels\n");

    for (;;) {
        struct sockaddr_in cli;
        socklen_t l = sizeof(cli);
        int cfd = accept(sfd, (struct sockaddr*)&cli, &l);
        if (cfd < 0) { perror("accept"); continue; }
        printf("client connected\n");

        // --- generate test payload ---
        // random ascii letters (a..z, A..Z) length 20..40
        uint16_t n = (uint16_t)(20 + rand() % 21);
        char *sbuf = (char*)malloc(n);
        if (!sbuf) { perror("malloc"); close(cfd); continue; }

        for (uint16_t i = 0; i < n; ++i) {
            int upper = rand() & 1;
            if (upper)
                sbuf[i] = (char)('A' + (rand() % 26));
            else
                sbuf[i] = (char)('a' + (rand() % 26));
        }

        // precompute correct count
        uint16_t correct = 0;
        for (uint16_t i = 0; i < n; ++i) {
            if (is_vowel((unsigned char)sbuf[i])) correct++;
        }

        const char *desc =
            "TASK: Count the vowels in the given ASCII string.\n"
            "Vowels are exactly: a e i o u A E I O U.\n"
            "Protocol:\n"
            " 1) uint16 desc_len (net) + desc bytes\n"
            " 2) uint16 n (net) + n bytes string (no NUL)\n"
            " 3) client sends uint16 cnt (net) = number of vowels\n"
            " 4) server replies uint16 status (net): 1=OK, 0=ERR\n";

        uint16_t dlen = (uint16_t)strlen(desc);

        // --- send description ---
        uint16_t dlen_net = htons(dlen);
        if (send_all(cfd, &dlen_net, sizeof(dlen_net)) < 0 ||
            send_all(cfd, desc, dlen) < 0) {
            perror("send desc");
            free(sbuf); close(cfd); continue;
        }

        // --- send n + string ---
        uint16_t n_net = htons(n);
        if (send_all(cfd, &n_net, sizeof(n_net)) < 0 ||
            send_all(cfd, sbuf, n) < 0) {
            perror("send data");
            free(sbuf); close(cfd); continue;
        }

        // --- receive client's count ---
        uint16_t cnt_net = 0;
        if (recv_all(cfd, &cnt_net, sizeof(cnt_net)) < 0) {
            perror("recv cnt");
            free(sbuf); close(cfd); continue;
        }
        uint16_t cnt = ntohs(cnt_net);

        // --- verify + reply ---
        uint16_t status = (cnt == correct) ? 1 : 0;
        uint16_t status_net = htons(status);
        if (send_all(cfd, &status_net, sizeof(status_net)) < 0) {
            perror("send status");
        }

        printf("expected=%u, got=%u -> %s\n",
               (unsigned)correct, (unsigned)cnt, status ? "OK" : "ERR");

        free(sbuf);
        close(cfd);
    }
}

