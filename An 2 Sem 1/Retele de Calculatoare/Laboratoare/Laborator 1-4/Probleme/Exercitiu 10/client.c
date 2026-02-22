#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

int main() {
	// Declaram variabilele importante
	int c;
	struct sockaddr_in server;

	// Creem server-ul client
	c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0) {
		printf("Eroare la crearea server-ului client\n");
		return 1;
	}

	// Configurarea server-ului
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Conectam clientul la server
	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la connect\n");
		return 2;
	}

	// Lucram
	// Citim sirurile
	size_t lungime = sizeof(char) * 512;
	char* sir1 = malloc(lungime);
	char* sir2 = malloc(lungime);

	printf("sir1: ");
	uint16_t l1 = getline(&sir1, &lungime, stdin);
	
	printf("sir2: ");
	uint16_t l2 = getline(&sir2, &lungime, stdin);

	l1 = htons(l1);
	l2 = htons(l2);

	send(c, &l1, sizeof(l1), 0);
	send(c, &l2, sizeof(l2), 0);

	l1 = ntohs(l1);
	l2 = ntohs(l2);

	send(c, sir1, sizeof(char) * l1, 0);
	send(c, sir2, sizeof(char) * l2, 0);

	// Primim caracterul cu frecventa maxima
	char max;
	uint16_t freq_max;

	recv(c, &freq_max, sizeof(freq_max), MSG_WAITALL);
	recv(c, &max, sizeof(char), MSG_WAITALL);

	freq_max = ntohs(freq_max);

	// Le afisam
	printf("Caracterul: %c\n", max);
	printf("Frecventa: %hu\n", freq_max);
	
	// Inchidem clientul si facem curat
	free(sir1);
	free(sir2);
	close(c);

	return 0;
}
