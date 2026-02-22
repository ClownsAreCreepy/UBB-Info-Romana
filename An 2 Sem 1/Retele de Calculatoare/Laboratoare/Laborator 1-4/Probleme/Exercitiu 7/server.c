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
void handler(int sig) {
	(void) sig;
	close(s);
	exit(0);
}

int main() {

	// Facem functie pentru a inchide serverul cu Ctrl + C
	signal(SIGINT, handler);

	// Declaram variabilele importante
	int c;
	socklen_t l;
	struct sockaddr_in server, client;

	// Creem socket-ul serverului
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		printf("Eroare la crearea socket-ului server\n");
		return 1;
	}

	// Configuram server-ul
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

	// Pregatim pentru clienti
	l = sizeof(client);
	memset(&client, 0, sizeof(client));

	while (1) {
		// Acceptam client
		c = accept(s, (struct sockaddr *) &client, &l);
		printf("S-a conectat un client\n");

		// Lucram
		// Primim sirul de caractere si doua numere
		uint16_t size, poz, lungime;
		recv(c, &size, sizeof(size), MSG_WAITALL);
		size = ntohs(size);

		char* sir = malloc(sizeof(char) * size);
		recv(c, sir, sizeof(char) * size, MSG_WAITALL);
		
		recv(c, &poz, sizeof(poz), MSG_WAITALL);
		recv(c, &lungime, sizeof(lungime), MSG_WAITALL);

		poz = ntohs(poz);
		lungime = ntohs(lungime);

		// Aflam subsirul de lungime lungime din s care incepe la pozitia poz
		char *subsir = malloc(sizeof(char) * (lungime + 1));
		int loc = 0;

		for (int i = poz; i < poz + lungime; ++i) {
			subsir[loc++] = sir[i];
		}

		subsir[loc] = '\0';

		// Trimitem subsirul inapoi la client
		send(c, subsir, sizeof(char) * lungime, 0);

		// Inchidem cu clientul si curatam
		free(sir);
		free(subsir);
		close(c);
		printf("S-a deconectat un client\n");
	}

	return 0;
}
