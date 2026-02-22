#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main () {
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

	dlen++;

	char* desc = malloc(sizeof(char) * dlen);
	recv(c, desc, sizeof(char) * dlen, MSG_WAITALL);

	uint16_t n;
	recv(c, &n, sizeof(n), MSG_WAITALL);
	n = ntohs(n);

	n++;

	char* string = malloc(sizeof(char) * n);
	recv(c, string, sizeof(char) * n, MSG_WAITALL);

	uint16_t pos, len;
	recv(c, &pos, sizeof(pos), MSG_WAITALL);
	recv(c, &len, sizeof(len), MSG_WAITALL);
	pos = ntohs(pos);
	len = ntohs(len);

	if (pos + len > n) {
		printf("Damn uuh vezi ca cam naspa\n");
		close(c);
		return 3;
	}

	printf("%s\n\n", desc);
	printf("%d\n%s\n%d %d\n", n, string, pos, len);

	char* substring = malloc(sizeof(char) * len);
	int j=0;
	for (int i = pos + len - 1; i >= pos; --i)
		substring[j++] = string[i];

	send(c, substring, sizeof(char) * len, 0);
		
	uint16_t status;
	recv(c, &status, sizeof(status), MSG_WAITALL);
	status = ntohs(status);

	if (status)
		printf("IUPIIII!!! E CORECT!\n");
	else
		printf("wrong lol\n");

	free(desc);
	free(string);
	free(substring);
	close(c);
	return 0;
}
