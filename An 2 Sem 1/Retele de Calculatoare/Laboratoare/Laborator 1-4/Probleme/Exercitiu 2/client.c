#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

int main() {
	int c;
	struct sockaddr_in server;
	
	c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0) {
		printf("Eroare la crearea socketului client\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la conectarea la server\n");
		return 1;
	}

	// creem si luam sirul de caractere
	char* sir = malloc(sizeof(char) * 256);
	printf("Introduceti sir de litere: ");
	fgets(sir, sizeof(char) * 256, stdin);
	
	// il trimitem la server si eliberam memoria
	send(c, sir, sizeof(char) * 256 ,0);
	free(sir);

	printf("uuuh\n");
	// primim numarul de spatii si le afisam
	short spatii;
	recv(c, &spatii, sizeof(short), 0);
	printf("Nr de spatii: %hu\n", ntohs(spatii));
}
