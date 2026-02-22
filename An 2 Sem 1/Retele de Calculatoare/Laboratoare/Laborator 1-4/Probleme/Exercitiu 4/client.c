#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
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
		printf("Eroare le crearea socketului client\n");
		return 1;
	}

	// Stabilirea serverului
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	// Conectam serverul la socket
	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0 ){
		printf("Eroare la conectarea la server\n");
		return 2;
	}

	// Lucru la client
	// Preluarea a 2 siruri
	uint16_t l1, l2;
	printf("Introduceti lungimea primului sir: ");
	scanf("%hu", &l1);

	int* sir1 = malloc(sizeof(int) * l1);
	for (int i = 0; i < l1; ++i) {
		printf("sir1[%d] = ", i);
		scanf("%d", sir1 + i);
	}

	printf("Introduceti lungimea celui de al doilea sir: ");
	scanf("%hu", &l2);

	int* sir2 = malloc(sizeof(int) * l2);
	for (int i = 0; i < l2; ++i) {
		printf("sir2[%d] = ", i);
		scanf("%d", sir2 + i);
	}

	// Trimitem lungimile sirurilor, apoi sirurile
	
	l1 = htons(l1);
	l2 = htons(l2);

	send(c, &l1, sizeof(l1), 0);
	send(c, &l2, sizeof(l2), 0);

	l1 = ntohs(l1);
	l2 = ntohs(l2);

	send(c, sir1, sizeof(int) * l1, 0);
	send(c, sir2, sizeof(int) * l2, 0);

	int l3 = l1 + l2;

	// Preluam sirul 3 si il afisam
	int* sir3 = malloc(sizeof(int) * l3);
	recv(c, sir3, sizeof(int) * l3, 0);

	for (int i = 0; i < l3; ++i)
		printf("%d; ", sir3[i]);
	printf("\n");

	//Curatam
	free(sir1);
	free(sir2);
	free(sir3);

	// Inchidem clientul
	close(c);
}
