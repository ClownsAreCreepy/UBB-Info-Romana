#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

int main() {
	// Declarare pentru server si client
	int c;
	struct sockaddr_in server;
	
	// Stabilirea socket-ului client
	c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0) {
		printf("Eroare la crearea socketului client\n");
		return 1;
	}

	// Sabilirea serverului
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Conectam socket-ul la server
	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la conectarea la server\n");
		return 2;
	}

	// Lucru practic
	// Declararea variabilelor
	uint16_t n;
	char* sir = malloc(sizeof(char) * 100);
	char* oglindit = malloc(sizeof(char) * 100);

	// Luam sirul de caractere
	printf("Introduceti sir de litere: ");
	fgets(sir, sizeof(char) * 100, stdin);

	// Trimitem lungimea sirului de caractere
	n = strlen(sir);
	n = htons(n);
	send(c, &n, sizeof(n), 0);

	// Trimitem sirul
	send(c, sir, sizeof(char) * n, 0);
	free(sir);

	// Primim sirul oglindit
	recv(c, oglindit, sizeof(char) * n, 0);
	printf("Oglinditul sirului este: %s\n", oglindit);
	free(oglindit);

	// Inchidem clientul
	close(c);
}
