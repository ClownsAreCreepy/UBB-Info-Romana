#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int s;
void handler(int sig) {
	(void) sig;
	close(s);
	exit(0);
}

int main() {
	// Semnal ca putem redeschide serverul fix dupa ce il inchidem
	signal(SIGCHLD, SIG_INT);
	signal(SIGINT, handler);

	// Declaram variabilele pentru server si socket
	int c;
	struct sockaddr_in server, client;
	socklen_t l;

	// Creem socket-ul server
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		printf("Eroare la creearea socket-ului server.\n");
		return 1;
	}

	// Configurarea server-ului
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	// Legam clientul la socket-ul serverului
	if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la bind\n");
		return 2;
	}

	// Ascultam pentru eventualii clienti
	listen(s, 5);

	// Pregatim acceptarea clientului
	l = sizeof(client);
	memset(&client, 0, sizeof(client));

	while (1) {
		// Acceptam clientul care a venit
		c = accept(s, (struct sockaddr *) &client, &l);
		printf("S-a conectat un client\n");

		if (fork() == 0) {
			// Lucram
			// Primim un numar
			uint16_t n;
			recv(c, &n, sizeof(n), MSG_WAITALL);
			n = ntohs(n);

			// Luam nr de divizori ai sirului
			uint16_t count = 1;
			int* div = malloc(sizeof(int) * n);
			div[0] = 1;

			for (uint16_t i = 2; i <= n / 2; ++i)
				if (n % i == 0)
					div[count++] = i;

			div[count] = n;

			// Trimitem nr de divizori si sirul
			count = htons(count);
			send(c, &count, sizeof(count), 0);
			count = ntohs(count);

			send(c, div, sizeof(int) * count + 1, 0);

			// Inchidem clientul si curatam
			free(div);
			close(c);
			printf("S-a deconectat clientul\n");
		}
	}
	return 0;
}
