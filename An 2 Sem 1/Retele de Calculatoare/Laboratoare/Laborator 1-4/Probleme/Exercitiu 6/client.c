#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main() {
	// Declaram variabilele pentru server si client
	int c;
	struct sockaddr_in server;

	// Creem socket-ul client
	c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0) {
		printf("Eroare la crearea socket-ului client\n");
		return 1;
	}

	// Configuram serverul
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Connectam socket-ul la server
	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la connectare\n");
		return 2;
	}

	// Lucram
	// Luam sirul si caracterul
	printf("Introduceti un sir: ");
	uint16_t size = 0;
	char caracter = 'a';
	char* sir = malloc(sizeof(char) * 256);

	while (caracter != '\n') {
		scanf("%c", &caracter);
		sir[size++] = caracter;
	}

	printf("Introduceti caracterul al carei pozitie vreti sa il aflati: ");
	scanf("%c", &caracter);

	// Trimitem sirul si caracterul
	size = htons(size);
	send(c, &size, sizeof(size), 0);

	size = ntohs(size);
	send(c, sir, sizeof(char) * size, 0);
	send(c, &caracter, sizeof(char), 0);

	// Primim sirul de pozitii
	uint16_t count;
	recv(c, &count, sizeof(count), 0);
	count = ntohs(count);

	int* poz = malloc(sizeof(int) * count);
	recv(c, poz, sizeof(int) * count, MSG_WAITALL);

	// Tiparim sirul de pozitii
	for (int i = 0; i < count; ++i)
		printf("%d ", poz[i]);
	
	printf("\n");

	// Curatam si inchidem socket-ul
	free(sir);
	free(poz);
	close(c);
	return 0;
}
