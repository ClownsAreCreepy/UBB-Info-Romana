#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
	int c;
	struct sockaddr_in server;

	c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0) {
		printf("Eroare la crearea socket-ului server\n");
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
	
	printf("%s\n\n", desc);

	uint16_t n;
	recv(c, &n, sizeof(n), MSG_WAITALL);
	n = ntohs(n);

	char* sir = malloc(sizeof(char) * (n + 1));
	recv(c, sir, sizeof(char) * n, MSG_WAITALL);
	sir[n] = '\0';

	
	uint16_t* counts = malloc(sizeof(uint16_t) * 26);
	
	for(int i = 0; i < n; ++i) {
		if (sir[i] >= 'A' && sir[i] <= 'Z') 
			sir[i] = sir[i] + 32;

		if (sir[i] >= 'a' && sir[i] <= 'z')
			counts[ (uint16_t) sir[i] - 'a' ] ++;
	}


	for (int i = 0; i < 26; ++i)
		counts[i] = htons(counts[i]);

	send(c, counts, sizeof(uint16_t) * 26, 0);
	
        uint16_t status;
        recv(c, &status, sizeof(status), MSG_WAITALL);
        status = ntohs(status);

        if (status)
                printf("IUPIII YOU MADE IT!!!\n");
        else
                printf("hell nah..\n");

	free(desc);
	free(sir);
	free(counts);
	close(c);
	return 0;
}
