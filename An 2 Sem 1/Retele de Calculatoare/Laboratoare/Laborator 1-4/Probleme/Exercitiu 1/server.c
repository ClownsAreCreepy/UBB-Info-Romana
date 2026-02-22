#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int s;
void handler(int sig) {
	(void)sig;
	close(s);
	exit(0);
}

int main() {
  struct sockaddr_in server, client;
  int c;
  socklen_t l;

  // Semnal ca sa putem redeschide serveru fix dupa ce il inchidem
  signal(SIGINT, handler);
  
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    printf("Eroare la crearea socketului server\n");
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
  
  while (1) {
    uint16_t n, x, sum;

    c = accept(s, (struct sockaddr *) &client, &l);
    printf("S-a conectat un client.\n");
    
    // deservirea clientului
    // primim lungimea sirului
    recv(c, &n, sizeof(n), MSG_WAITALL);
    n = ntohs(n);

    // primim n valori si calculam suma
    for (int i = 0; i < n; ++i) {
    	recv(c, &x, sizeof(x), MSG_WAITALL);
	x = ntohs(x);
	sum += x;
    }

    // intoarcem sum
    sum = htons(sum);
    send(c, &sum, sizeof(sum), 0);

    close(c);
    signal(SIGINT, handler);
    // sfarsitul deservirii clientului;
  }
}
