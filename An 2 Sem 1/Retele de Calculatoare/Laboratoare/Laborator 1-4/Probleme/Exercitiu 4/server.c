#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <signal.h>
#include <string.h>

int s;

void handler(int sig) {
	(void) sig;
	close(s);
	exit(0);
}

int main() {
	// Semnal ca sa putem redeschide serveru fix dupa ce il inchidem
	signal(SIGINT, handler);

	// Declaram variabilele pentru server si socket
	int c;
	struct sockaddr_in server, client;
	socklen_t l;

	// Stabilirea socket-ului server
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		printf("Eroare la crearea socket-ului server\n");
		return 1;
	}

	// Stabilirea serverului
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	// Legarea socket-ului de server
	if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la bind\n");
		return 2;
	}

	// Ascultam dupa clienti ig
	listen(s, 5);

	// Luam lungimea clientului
	l = sizeof(client);

	// Golim clientul
	memset(&client, 0, sizeof(client));

	while(1) {
		// Conectam un client
		c = accept(s, (struct sockaddr *) &client, &l);
		printf("S-a conectat un client\n");

		// Primim sirurile pe care le interclasam
		uint16_t l1, l2;
		int* sir1 = malloc(sizeof(int) * 256);
		int* sir2 = malloc(sizeof(int) * 256);

		recv(c, &l1, sizeof(l1), MSG_WAITALL);
		recv(c, &l2, sizeof(l2), MSG_WAITALL);

		l1 = ntohs(l1);
		l2 = ntohs(l2);

		recv(c, sir1, sizeof(int) * l1, MSG_WAITALL);
		recv(c, sir2, sizeof(int) * l2, MSG_WAITALL);

		// Inerclasam
		int i = 0, j = 0, k = 0;
		int* sir3 = malloc(sizeof(int) * 512);

		while (i < l1 && j < l2) {
			if (sir1[i] < sir2[j]){
				sir3[k] = sir1[i];
				i++;
			} else {
				sir3[k] = sir2[j];
				j++;
			}
			k++;
		}

		while (i < l1) {
			sir3[k] = sir1[i];
			i++;
			k++;
		}

		while (j < l2) {
			sir3[k] = sir2[j];
			j++;
			k++;
		}

		// Trimitem sirul interclasat
		send(c, sir3, sizeof(int) * k, 0);

		// Curatam
		free(sir1);
		free(sir2);
		free(sir3);

		printf("S-a deconectat un client\n");
		close(c);
	}
}
