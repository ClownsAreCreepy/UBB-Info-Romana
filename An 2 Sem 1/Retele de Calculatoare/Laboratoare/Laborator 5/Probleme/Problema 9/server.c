#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <signal.h>

int s;
// Creem functia pentru a inchide server-ul
void handler(int sig) {
	(void) sig;
	close(s);
	exit(0);
}

int main() {
	// Functie care inchide server-ul frumos cu Ctrl+C
	signal(SIGCHLD, SIG_IGN);
	signal(SIGINT, handler);

	// Decalram variabilele importante
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

	// Legam socket-ul de server
	if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la bind\n");
		return 2;
	}

	// Ascultam pentru clienti
	listen(s, 5);

	// Pregatim pentru intampinarea clientilor
	l = sizeof(client);
	memset(&client, 0, sizeof(client));

	while (1) {
		// Acceptam clientul
		c = accept(s, (struct sockaddr *) &client, &l);
		printf("S-a conectat un client\n");

		if (fork() == 0) {

			// Lucram
			// Primim sirurile de numere
			uint16_t l1, l2;
			recv(c, &l1, sizeof(l1), MSG_WAITALL);
			recv(c, &l2, sizeof(l2), MSG_WAITALL);

			l1 = ntohs(l1);
			l2 = ntohs(l2);

			int* sir1 = malloc(sizeof(int) * l1);
			int* sir2 = malloc(sizeof(int) * l2);

			recv(c, sir1, sizeof(int) * l1, MSG_WAITALL);
			recv(c, sir2, sizeof(int) * l2, MSG_WAITALL);


			// Aflam maximul pentru a sti cum sa configuram vectorul de frecventa
			int max = 0;
			for (int i = 0; i < l1; ++i)
				if(max < sir1[i])
					max = sir1[i];
			max ++;

			int* verif = malloc(sizeof(int) * max);
			memset(verif, 0, sizeof(int) * max);


			// Calculam diferenta intre siruri
			uint16_t l3 = 0;
			int* sir3 = malloc(sizeof(int) * l1);

			int exista = 0;
			for (int i = 0; i < l1; ++i) {
				exista = 0;
				for (int j = 0; j < l2; ++j)
					if (sir1[i] == sir2[j]) {
						exista = 1;
						break;
					}
				if (exista == 0 && verif[sir1[i]] == 0){
					verif[sir1[i]] = 1;
					sir3[l3++] = sir1[i];
				}
			}

			// Trimitem sirul
			l3 = htons(l3);
			send(c, &l3, sizeof(l3), 0);
			l3 = ntohs(l3);

			send(c, sir3, sizeof(int) * l3, 0);

			// Inchieiem cu clientul si curatam
			free(sir1);
			free(sir2);
			free(sir3);
			close(c);
			printf("S-a deconectat un client\n");
		}
	}

	return 0;
}
