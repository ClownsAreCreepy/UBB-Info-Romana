#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int s;
void handler(int sig) {
	(void) sig;
	close(s);
	exit(0);
}

int main() {
	struct sockaddr_in server, client;
	int c;
	socklen_t l;

	// Semnal ca sa putem redeschide serveru fix dupa ce il inchidem
	signal(SIGCHLD, SIG_IGN);
	signal(SIGINT, handler);

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		printf("Eroare la crearea socket-ului server\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la bind\n");
		return 1;
	}

	listen(s, 5);

	l = sizeof(client);
	memset(&client, 0, sizeof(client));

	while(1) {
		c = accept(s, (struct sockaddr *) &client, &l);
		printf("S-a conectat un client.\n");

		if (fork() == 0) {
			uint16_t n;
			char* sir = malloc(sizeof(char) * 100);
			char* oglindit = malloc(sizeof(char) * 100);

			// primim lungimea sirului
			recv(c, &n, sizeof(n), 0);
			n = ntohs(n);

			// calculam oglinditul
			recv(c, sir, sizeof(char) * n, MSG_WAITALL);

			for (int i = 0; i < n; ++i)
				oglindit[i] = sir[n - i -1];

			// trimitem oglinditul
			send(c, oglindit, sizeof(char) * n, 0);
			free(sir);
			free(oglindit);

			// sfarsitul deservirii clientului
			printf("S-a deconectat un client.\n");
			close(c);
		}
	}
}
