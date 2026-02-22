#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <signal.h>

// Handler pentru a inchide serverul la Ctrl+C
int s;
void handler(int sig) {
	(void) sig;
	close(s);
	exit(0);
}

int main() {
	signal(SIGCHLD, SIG_IGN);
	signal(SIGINT, handler);
	// Declaram variabilele pentru server si client
	int c;
	struct sockaddr_in server, client;
	socklen_t l;

	// Creem socket-ul server
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		printf("Eroare la crearea socket-ului server\n");
		return 1;
	}

	// Configuram serverul
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	// Legam serverul de socket
	if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la bind\n");
		return 2;
	}

	// Ascultam pentru clienti
	listen(s, 5);

	// Pregatim venirea clientilor
	l = sizeof(client);
	memset(&client, 0, sizeof(client));
	while (1) {
		// Acceptam clientul care a venit
		c = accept(s, (struct sockaddr *) &client, &l);
		printf("S-a conectat un client\n");

		if (fork() == 0) {
			// Lucram
			// Primim caracterul, apoi sirul de caractere
			char caracter;
			char* sir = malloc(sizeof(char) * 256);
			uint16_t size = 0;

			recv(c, &size, sizeof(size), 0);
			size = ntohs(size);

			recv(c, sir, sizeof(char) * size, MSG_WAITALL);
			recv(c, &caracter, sizeof(char), MSG_WAITALL);

			// Gasim pozitiile din sir in care este caracterul
			int* poz = malloc(sizeof(int) * size);
			uint16_t count = 0;

			for (int i = 0; i < size; ++i)
				if (sir[i] == caracter)
					poz[count++] = i;

			// Trimitem sirul cu pozitii
			count = htons(count);
			send(c, &count, sizeof(count), 0);

			count = ntohs(count);
			send(c, poz, sizeof(int) * count, 0);

			// Scoatem clientul afara si curatam
			free(sir);
			free(poz);
			close(c);
			printf("S-a deconectat un client\n");
		}
	}

	return 0;
}
