#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
 
int main() {
  int c;
  struct sockaddr_in server;
  
  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(8889);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("10.51.1.20");
  
  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }

  uint16_t id = 3817;
  id = htons(id);
  send (c, &id, sizeof(id), 0);

  uint16_t dlen;
  recv(c, &dlen, sizeof(dlen), MSG_WAITALL);
  dlen = ntohs(dlen);

  char* desc = malloc(sizeof(char) * (dlen + 1));
  recv(c, desc, sizeof(char) * dlen, MSG_WAITALL);
  desc[dlen] = '\0';

  printf("%s\n", desc);

  uint8_t* sir_b = malloc(sizeof(uint8_t) * 150);
  uint16_t* sir_s = malloc(sizeof(uint16_t) * 150);
  uint32_t* sir_i = malloc(sizeof(uint32_t) * 150);
  uint8_t b = 0, s = 0, i = 0;
  

  while (1) {
  	char ch;
	recv(c, &ch, sizeof(char), 0);

	if (ch == 'b') {
		recv(c, sir_b + b, sizeof(uint8_t), MSG_WAITALL); 
		b++;
	}
	if (ch == 's') {
		recv(c, sir_s + s, sizeof(uint16_t), MSG_WAITALL);
		s++;
	}
	if (ch == 'i') {
		recv(c, sir_i + i, sizeof(uint32_t), MSG_WAITALL);
		i++;
	}
	if (ch == 'g')
		break;
  }


  send(c, &b, sizeof(b), 0);
  send(c, &s, sizeof(b), 0);
  send(c, &i, sizeof(b), 0);


  int sum = 0;
  for (int j = 0; j < b; ++j) {
  	uint8_t a = sir_b[j];
	while (a) {
		sum += a % 10;
		a /= 10;
	}
  }

  for (int j = 0; j < s; ++j) {
  	uint16_t a = sir_s[j];
	a = ntohs(a);
	while (a) {
		sum += a % 10;
		a /= 10;
	}
  }

  for (int j = 0; j < i; ++j) {
  	uint32_t a = sir_i[j];
	a = ntohl(a);
	while (a) {
		sum += a % 10;
		a /= 10;
	}
  }


  uint8_t cod;
  if (sum % 3 == 0)
	  cod = 1;
  else
	  cod = 0;
  
  send(c, &cod, sizeof(cod), 0);

  free(desc);
  free(sir_b);
  free(sir_s);
  free(sir_i);
  return 0;
}
