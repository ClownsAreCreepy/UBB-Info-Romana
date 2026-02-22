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

	// Configurarea serverului
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
	// Luam numarul de la client si il trimitem la server
	uint16_t n;
	printf("Introduceti un numar: ");
	scanf("%hu", &n);

	n = htons(n);
	send(c, &n, sizeof(n), 0);

	// Luam lungimea sirului si sirul de la server
	uint16_t count;
	int* div = malloc(sizeof(int) * n);

	recv(c, &count, sizeof(count), MSG_WAITALL);
	count = ntohs(count);
	recv(c, div, sizeof(int) * count + 1, MSG_WAITALL);
	
	// Afisam sirul
	printf("Divizorii numarului %hu sunt: ", ntohs(n));
	for (int i = 0; i <= count; ++i)
		printf("%hu; ",div[i]);
        printf("\n");	

	// Inchidem clientul si curatam
	free(div);
	close(c);
	return 0;
}
