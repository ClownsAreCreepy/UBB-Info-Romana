#include <sys/types.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
 
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
  server.sin_addr.s_addr = inet_addr("10.51.1.14");
  
  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }
  short id = 3817;
  id = htons(id);
  send (c, &id, sizeof(id), 0);

  short lungime;
  char* enunt = malloc(100 * sizeof(char));

  recv(c, &lungime, sizeof(short), 0);
  lungime = ntohs(lungime);
  printf("%d\n", lungime);
  recv(c, enunt, sizeof(char) * lungime, 0);
  printf("%s\n", enunt);

  free(enunt);

  char* sir = malloc(sizeof(char*) * 500);
  memset(sir, 0, sizeof(char*) * 500);
  short l = 0, mini_lungime = 0;

  lungime = htons(lungime);
  send(c, &lungime, sizeof(lungime), 0);

  while (1) {
	recv(c, &mini_lungime, 1, 0);
	if (mini_lungime <= 0)
		break;
	recv(c, sir + l, sizeof(char) * mini_lungime, MSG_WAITALL);
	//printf("Lungime: %d\n", primite);
	l += mini_lungime;
  }
  printf("\n%d\n", l);
  printf("%s\n\n", sir);
  l = htons(l);
  send(c, &l, sizeof(l), 0);

  int ca = 0;
  for (size_t i = 1; i <= strlen(sir); ++i)
  	if ( (sir[i] > 'a' && sir[i] < 'z') || (sir[i] > 'A' && sir[i] < 'Z'))
		ca += i;

  printf("%d\n",ca);
  //ca = htons(ca);
  send(c, &ca, sizeof(ca), 0);
  free(sir);
}
