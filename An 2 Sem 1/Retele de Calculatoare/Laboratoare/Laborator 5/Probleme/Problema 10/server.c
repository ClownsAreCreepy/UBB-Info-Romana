#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <signal.h>

#define NR_LITERE 53

int s;
void handler(int sig) {
	(void) sig;
	close(s);
	exit(0);
}

int main() {
	// Functie ca sa se inchida frumos cu Ctrl+C
	signal(SIGCHLD, SIG_IGN);
	signal(SIGINT, handler);

	// Declaram variabilele importante
	int c;
	struct sockaddr_in server, client;
	socklen_t l;

	// Creem socket-ul server
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		printf("Eroare la crearea socket-ului server\n");
		return 1;
	}

	// Configuram server-ul
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	// Legam server-ul de socket
	if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la bind\n");
		return 2;
	}

	// Ascultam pentru clienti
	listen(s, 5);

	// Pregam pentru client
	memset(&client, 0, sizeof(client));
	l = sizeof(client);

	while(1) {
		// Acceptam clientul
		c = accept(s, (struct sockaddr *) &client, &l);
		printf("S-a conectat un client\n");

		if (fork() == 0) {

			// Lucram
			// Primim sirurile
			uint16_t l1, l2;
			recv(c, &l1, sizeof(l1), MSG_WAITALL);
			recv(c, &l2, sizeof(l2), MSG_WAITALL);

			l1 = ntohs(l1);
			l2 = ntohs(l2);

			char* sir1 = malloc(sizeof(char) * l1);
			char* sir2 = malloc(sizeof(char) * l2);

			recv(c, sir1, sizeof(char) * l1, MSG_WAITALL);
			recv(c, sir2, sizeof(char) * l2, MSG_WAITALL);

			// Gasim caracterul maxim si frecventa sa
			int* freq = malloc(sizeof(int) * NR_LITERE);
			memset(freq, 0, sizeof(int) * NR_LITERE);
			char max = '0';
			uint16_t freq_max = 0;

			for (int i = 0; i < l1; ++i)
				if (sir1[i] == sir2[i]) {
					int car = sir1[i] - 'A';
					freq[car] ++;
					if (freq[car] > freq_max) {
						max = sir1[i];
						freq_max = freq[car];
					}
				}
		
			// Trimitem caracterul maxim si frecventa sa
			freq_max = htons(freq_max);

			send(c, &freq_max, sizeof(freq_max), 0);
			send(c, &max, sizeof(char), 0);

			// Inchidem clientul si curatam
			free(sir1);
			free(sir2);
			free(freq);
			close(c);
			printf("S-a deconectat un client\n");
		}
	}

	return 0;
}
