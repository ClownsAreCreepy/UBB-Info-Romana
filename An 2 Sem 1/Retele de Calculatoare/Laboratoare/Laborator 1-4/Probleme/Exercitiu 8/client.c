#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

int main() {
	// Declaram variabilele importante
	int c;
	struct sockaddr_in server;

	// Creem socket-ul client
	c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0) {
		printf("Eroare la crearea socket-ului client\n");
		return 1;
	}

	// Configuram server-ul
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Conectam socket-ul la server
	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la conectare\n");
		return 2;
	}

	// Lucram
	// Luam sirurile de numere
	uint16_t l1, l2;
	printf("Introduceti lungimile sirurilor: ");
	scanf("%hu", &l1);
	scanf("%hu", &l2);

	int* sir1 = malloc(sizeof(int) * l1);
	int* sir2 = malloc(sizeof(int) * l2);
	printf("Introduceti sirurile: \n");
	
	printf("sir1: ");
	for (int i = 0; i < l1; ++i)
		scanf("%d", &sir1[i]);

	printf("sir2: ");
	for (int i = 0; i < l2; ++i)
		scanf("%d", &sir2[i]);

	// Trimitem sirurile de numere
	l1 = htons(l1);
	l2 = htons(l2);

	send(c, &l1, sizeof(l1), 0);
	send(c, &l2, sizeof(l2), 0);

	l1 = ntohs(l1);
	l2 = ntohs(l2);

	send(c, sir1, sizeof(int) * l1, 0);
	send(c, sir2, sizeof(int) * l2, 0);

	// Primim sirul rezultat si il afisam
	uint16_t count;
	recv(c, &count, sizeof(count), MSG_WAITALL);
	count = ntohs(count);

	int* sir3 = malloc(sizeof(int) * count);
	recv(c, sir3, sizeof(int) * count, MSG_WAITALL);

	for (int i = 0; i < count; ++i)
		printf("%d ", sir3[i]);
	printf("\n");

	// Inchiderea socket-ului si curatare
	free(sir1);
	free(sir2);
	free(sir3);
	close(c);
	return 0;
}
