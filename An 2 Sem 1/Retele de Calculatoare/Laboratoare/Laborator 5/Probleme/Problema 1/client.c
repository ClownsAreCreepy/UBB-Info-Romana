#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
 
int main() {
  int c;
  struct sockaddr_in server;
  uint16_t n, x, suma;
  
  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }
  
  // luam lungimea sirului
  printf("Lungimea sirului: ");
  scanf("%hu", &n);

  // trimitem n
  uint16_t n_net = htons(n);
  send(c, &n_net, sizeof(n_net), 0);


  // trimitem n numere
  for(int i = 0; i < n; ++i) {
  	printf("x[%d] = ", i);
	scanf("%hu", &x);
	x = htons(x);
	send(c, &x, sizeof(x), 0);
  }

  // primim suma
  recv(c, &suma, sizeof(suma), 0);
  suma = ntohs(suma);
  printf("Suma este %hu\n", suma);
  close(c);

}

