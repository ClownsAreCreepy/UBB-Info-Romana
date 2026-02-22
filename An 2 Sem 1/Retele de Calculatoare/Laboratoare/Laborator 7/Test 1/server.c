// server.c — single-task practice server (reverse substring)
// Protocol:
// 1) uint16 desc_len (net) + desc text bytes
// 2) uint16 n (net) + n bytes string
// 3) uint16 pos (net) + uint16 len (net)
// Client must send back len bytes: reverse of s[pos..pos+len-1]
// Server replies: uint16 status (net): 1=OK, 0=ERR

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

static int s;

static void on_sigint(int sig) {
    (void)sig;
    if (s > 0) close(s);
    exit(0);
}

int main() {
    signal(SIGINT, on_sigint);
    srand((unsigned)time(NULL));

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s < 0) { perror("socket"); return 1; }

    int opt = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr, cli;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port   = htons(1234);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) { perror("bind"); return 2; }
    if (listen(s, 5) < 0) { perror("listen"); return 3; }

    socklen_t l = sizeof(cli);
    memset(&cli, 0, sizeof(cli));

    printf("server ready on 1234: task = reverse substring\n");

    for (;;) {
        int c = accept(s, (struct sockaddr*)&cli, &l);
        if (c < 0) { perror("accept"); continue; }
        printf("client connected\n");

        // --- generate payload ---
        // random lowercase string length 20..40
        uint16_t n = (uint16_t)(20 + rand() % 21);
        char *sbuf = (char*)malloc(n);
        for (uint16_t i = 0; i < n; ++i) {
            sbuf[i] = (char)('a' + (rand() % 26));
        }

        // choose a valid pos/len
        uint16_t pos = (uint16_t)(rand() % (n - 5)); // leave some room
        uint16_t len = (uint16_t)(1 + rand() % 10);
        if (pos + len > n) len = n - pos; // clamp

        // precompute correct reversed substring
        char *rev = (char*)malloc(len);
        for (uint16_t i = 0; i < len; ++i) {
            rev[i] = sbuf[pos + (len - 1 - i)];
        }

        const char *desc =
            "TASK: Given a byte string s (length n), and two numbers pos and len,\n"
            "send back the REVERSED substring s[pos..pos+len-1].\n"
            "Protocol:\n"
            " - uint16 desc_len (net) + desc bytes\n"
            " - uint16 n (net) + n bytes s\n"
            " - uint16 pos (net) + uint16 len (net)\n"
            "Response:\n"
            " - exactly len bytes = reversed substring\n"
            "Then server returns uint16 status (net): 1=OK, 0=ERR.\n";

        uint16_t dlen = (uint16_t)strlen(desc);

        // --- send description ---
        uint16_t dlen_net = htons(dlen);
        send(c, &dlen_net, sizeof(dlen_net), 0);
        send(c, desc, dlen, 0);

        // --- send n + string ---
        uint16_t n_net = htons(n);
        send(c, &n_net, sizeof(n_net), 0);
        send(c, sbuf, n, 0);

        // --- send pos + len ---
        uint16_t pos_net = htons(pos);
        uint16_t len_net = htons(len);
        send(c, &pos_net, sizeof(pos_net), 0);
        send(c, &len_net, sizeof(len_net), 0);

        // --- receive client's answer (len bytes) ---
        char *ans = (char*)malloc(len);
        size_t got = 0;
        while (got < len) {
            ssize_t r = recv(c, ans + got, len - got, 0);
            if (r <= 0) break;
            got += (size_t)r;
        }

        // --- verify ---
        uint16_t status = 0;
        if (got == len && memcmp(ans, rev, len) == 0) status = 1;

        uint16_t status_net = htons(status);
        send(c, &status_net, sizeof(status_net), 0);

        free(ans);
        free(rev);
        free(sbuf);
        close(c);
        printf("client served (status=%u)\n", status);
    }
}

