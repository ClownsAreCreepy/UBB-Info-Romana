#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

int main() {
	int c;
	struct sockaddr_in server;

	c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0) {
		printf("Eroare la crearea socket-ului client\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la connect\n");
		return 2;
	}

	uint16_t dlen;
	recv(c, &dlen, sizeof(dlen), MSG_WAITALL);
	dlen = ntohs(dlen);

	char* desc = malloc(sizeof(char) * (dlen + 1));
	recv(c, desc, sizeof(char) * dlen, MSG_WAITALL);
	desc[dlen] = '\0';

	printf("%s\n", desc);

	uint16_t n;
	recv(c, &n, sizeof(n), MSG_WAITALL);
	n = ntohs(n);

	int* sir = malloc(sizeof(int) * n);
	recv(c, sir, sizeof(int) * n, MSG_WAITALL);

	for(int i = 0; i < n; ++i)
		sir[i] = ntohl(sir[i]);
	
	printf("%hu\n", n);
	for(int i = 0; i < n; ++i)
		printf("%d ", sir[i]);
	printf("\n");

	int sum;
	for (int i = 0; i < n; ++i)
		if (sir[i] > 0) {
			int a = sir[i];
			while (a) {
				sum += a % 10;
				a /= 10;
			}
		}

	printf("%d\n", sum);

	sum = htonl(sum);
	send(c, &sum, sizeof(sum), 0);

	free(desc);
	free(sir);
	close(c);
	return 0;
}
