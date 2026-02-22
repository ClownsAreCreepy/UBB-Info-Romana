#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <signal.h>
#include <unistd.h>

int s;

void pentru_inchiderea_serverului(int sig) {
	(void)sig;
	close(s);
	exit(0);
}

int main() {

	int c;
	socklen_t l;
	struct sockaddr_in server, client;
	s = socket(AF_INET, SOCK_STREAM, 0);
	if ( s < 0 ) {
		printf("Eroare la crearea socketului server\n");
		return 1;
	}

        signal(SIGINT, pentru_inchiderea_serverului);
	signal(SIGCHLD, SIG_IGN);
	
	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la bind\n");
		return 2;
	}

	listen(s, 5);

	l = sizeof(client);
	memset(&client, 0, sizeof(client));

	while(1) {

		c = accept(s, (struct sockaddr *) &client, &l);
		
		if (fork() == 0) {
			short cs = 0;
			char * sir = malloc( sizeof(char) * 256);


			// primim sirul de caractere
			recv(c, sir, sizeof(char) * 256, 0);

			// numaram spatiile si le trimitem inapoi
			for (size_t i = 0; i < strlen(sir); ++i)
				if (sir[i] == ' ')
					cs++;
			cs = htons(cs);
			send(c, &cs, sizeof(short), 0);

			// curatam pe aici
			free(sir);
			close(c);
		}
	}
}
