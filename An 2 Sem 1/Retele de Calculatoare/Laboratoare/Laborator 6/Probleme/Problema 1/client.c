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
	socklen_t l;

	// Creem socket-ul client
	c = socket(AF_INET, SOCK_DGRAM, 0);
	if (c < 0) {
		printf("Eroare la crearea socket-ului client\n");
		return 1;
	}

	// Configuram server-ul
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	l = sizeof(server);

	// Lucram
	// Citim 2 numere
	uint16_t a, b, sum;
	printf("Introduceti 2 numere: ");
	scanf("%hu", &a);
	scanf("%hu", &b);

	// Trimitem la server
	a = htons(a);
	b = htons(b);

	sendto(c, &a, sizeof(a), 0, (struct sockaddr *) &server, l);
	sendto(c, &b, sizeof(b), 0, (struct sockaddr *) &server, l);

	// Primim suma lor si o afisam
	recvfrom(c, &sum, sizeof(sum), MSG_WAITALL, (struct sockaddr *) &server, &l);
	sum = ntohs(sum);

	printf("Suma numerelor este: %hu\n", sum);

	return 0;

}
