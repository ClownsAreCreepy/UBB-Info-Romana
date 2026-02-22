#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>

int s;
// Handler pentru a inchide server-ul cu Ctrl+C
void handler(int sig) {
	(void) sig;
	close(s);
	exit(0);
}

int main() {
	// Conectam handler-u la Ctrl+C
	signal(SIGCHLD, SIG_IGN);
	signal(SIGINT, handler);

	// Definim variabilele importante
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
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	// Legam socket-ul de server
	if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la bind\n");
		return 2;
	}

	// Ascultam pentru posibili clienti
	listen(s, 5);

	// Pregatim pentru intampinarea clientului
	l = sizeof(client);
	memset(&client, 0, sizeof(client));

	while(1) {
		// Acceptam clientul
		c = accept(s, (struct sockaddr *) &client, &l);
		printf("S-a conectat un client\n");

		if (fork() == 0) {

			// Lucram
			// Primim cele 2 siruri
			uint16_t l1, l2;
			recv(c, &l1, sizeof(l1), MSG_WAITALL);
			recv(c, &l2, sizeof(l2), MSG_WAITALL);

			l1 = ntohs(l1);
			l2 = ntohs(l2);

			int* sir1 = malloc(sizeof(int) * l1);
			int* sir2 = malloc(sizeof(int) * l2);
			recv(c, sir1, sizeof(int) * l1, MSG_WAITALL);
			recv(c, sir2, sizeof(int) * l2, MSG_WAITALL);

			// Aflam numerele comune (versiunea cu O(n^2))
			uint16_t count = 0;
			int* sir3 = malloc(sizeof(int) * l1);
			int max = 0;

			// Aflam maximul pentru a afla lungimea maxima a vectorului de frecventa
			for (int i = 0; i < l1; ++i)
				if (sir1[i] > max)
					max = sir1[i];
			max++;

			int* verif = malloc(sizeof(int) * max);
			memset(verif, 0, sizeof(int) * max);

			for(int i = 0; i < l1; ++i)
				for(int j = 0; j < l2; ++j)
					if (sir1[i] == sir2[j] && verif[sir1[i]] == 0) {
						sir3[count++] = sir1[i];
						verif[sir1[i]]++;
						break;
					}

			// Trimitem sirul aflat
			count = htons(count);
			send(c, &count, sizeof(count), 0);

			send(c, sir3, sizeof(int) * count, 0);

			// Inchidem clientul si curatam
			free(sir1);
			free(sir2);
			free(sir3);
			close(c);
			printf("S-a deconectat un client\n");
		}
	}

	return 0;
}
