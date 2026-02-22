#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>


int main() {
	// Declaram variabilele importante
	int s;
	struct sockaddr_in server, client;
	socklen_t l;

	// Creem socket-ul server
	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
		printf("Eroare la crearea socket-ului server\n");
		return 1;
	}

	// Configuram server-ul
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	// Legam socket-ul de server
	if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la bind\n");
		return 2;
	}

	// Pregatim pentru client
	l = sizeof(client);
	memset(&client, 0, sizeof(client));

	// Lucram
	// Primim cele 2 numere
	uint16_t a, b, sum;
	recvfrom(s, &a, sizeof(a), MSG_WAITALL, (struct sockaddr *) &client, &l);
	recvfrom(s, &b, sizeof(b), MSG_WAITALL, (struct sockaddr *) &client, &l);

	a = ntohs(a);
	b = ntohs(b);

	// Trimitem suma
	sum = a + b;
	
	sum = htons(sum);
	sendto(s, &sum, sizeof(sum), 0, (struct sockaddr *) &client, l);

	// Inchidem server-ul
	close(s);

	return 0;

}
