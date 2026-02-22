#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
	// Declaram variabile importante
	int c;
	struct sockaddr_in server;

	// Creem socket-ul client
	c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0) {
		printf("Eroare la creare a socket-ului clinet\n");
		return 1;
	}

	// Configuram server-ul
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Connectam socket-ul la server
	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la conectare\n");
		return 2;
	}

	// Lucram
	// Ia un sir de caractere si 2 numere
	char* sir = malloc(sizeof(char) * 256);
	uint16_t lungime, poz, size;

	printf("Introduceti un sir: ");

	size_t bufferSize = sizeof(char) * 256;
	size = getline(&sir, &bufferSize, stdin);
	
	printf("Introduceti pozitia si lungimea subsirului: ");
	scanf("%hu", &poz);
	scanf("%hu", &lungime);

	// Trimitem sirul si cele 2 numere la server
	poz = htons(poz);
	lungime = htons(lungime);
	size = htons(size);

	send(c, &size, sizeof(size), 0);
	
	size = ntohs(size);
	send(c, sir, sizeof(char) * size, 0);

	send(c, &poz, sizeof(poz), 0);
	send(c, &lungime, sizeof(lungime), 0);

	// Primim inapoi subsirul si il afisam
	lungime = ntohs(lungime);
	char* subsir = malloc(sizeof(char) * lungime);

	recv(c, subsir, sizeof(char) * lungime, MSG_WAITALL);

	for (int i = 0; i < lungime; ++i)
		printf("%c", subsir[i]);
	printf("\n");

	// Inchidem clientul si curatam
	free(sir);
	free(subsir);
	close(c);
	return 0;
}
