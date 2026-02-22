#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
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

	// Configurarea server-ului
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Conectarea clientului la server
	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la conectare\n");
		return 2;
	}

	// Lucram
	// Citim sirurile
	uint16_t l1, l2;
	printf("Introduceti dimensiunile sirurilor: ");
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

	l1 = htons(l1);
	l2 = htons(l2);

	send(c, &l1, sizeof(l1), 0);
	send(c, &l2, sizeof(l2), 0);

	l1 = ntohs(l1);
	l2 = ntohs(l2);

	send(c, sir1, sizeof(int) * l1, 0);
	send(c, sir2, sizeof(int) * l2, 0);
	// Primim sirul din diferenta
	uint16_t l3;
	recv(c, &l3, sizeof(l3), MSG_WAITALL);
	l3 = ntohs(l3);

	int* sir3 = malloc(sizeof(int) * l3);
	recv(c, sir3, sizeof(int) * l3, MSG_WAITALL);

	//Afisam sirul
	for (int i = 0; i < l3; ++i)
		printf("%d ", sir3[i]);
	printf("\n");

	// Inchidere client si curatare
	free(sir1);
	free(sir2);
	free(sir3);
	close(c);
	return 0;
}
