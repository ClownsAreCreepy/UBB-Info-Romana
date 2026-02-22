#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
	int c;
	struct sockaddr_in server;

	c = socket(AF_INET, SOCK_STREAM, 0);
	if (c < 0) {
		printf("Eroare la crearea socket-ului client\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
		printf("Eroare la connect\n");
		return 2;
	}

	uint16_t dlen;
	recv(c, &dlen, sizeof(dlen), MSG_WAITALL);
	dlen = ntohs(dlen);

	char* desc = malloc(sizeof(char) * (dlen + 1));
	recv(c, desc, sizeof(char) * dlen, MSG_WAITALL);
	desc[dlen] = '\0';

	printf("%s\n", desc);

	uint16_t n;
	recv(c, &n, sizeof(n), MSG_WAITALL);
	n = ntohs(n);

	int* sir1 = malloc(sizeof(int) * n);
	recv(c, sir1, sizeof(int) * n, MSG_WAITALL);

	for (int i = 0; i < n; ++i)
		sir1[i] = ntohl(sir1[i]);

	for (int i = 0; i < n - 1; ++i) {
		int schimbat = 0;
		for (int j = 0; j < n - i - 1; ++j)
			if (sir1[j] > sir1[j + 1]) {
				int temp = sir1[j];
				sir1[j] = sir1[j + 1];
				sir1[j + 1] = temp;
				schimbat = 1;
			}
		if (schimbat == 0)
			break;
	}

	uint16_t m;
	recv(c, &m, sizeof(m), MSG_WAITALL);
	m = ntohs(m);

	int* sir2 = malloc(sizeof(int) * m);
	recv(c, sir2, sizeof(int) * m, MSG_WAITALL);

	for (int i = 0; i < m; ++i)
		sir2[i] = ntohl(sir2[i]);

	for (int i = 0; i < m - 1; ++i) {
		int schimbat = 0;
		for (int j = 0; j < m - i - 1; ++j)
			if (sir2[j] > sir2[j + 1]) {
				int temp = sir2[j];
				sir2[j] = sir2[j + 1];
				sir2[j + 1] = temp;
				schimbat = 1;
			}
		if (schimbat == 0)
			break;
	}

	printf("\n%hu\n", n);
	for(int i = 0; i < n; ++i)
		printf("%d ", sir1[i]);

	printf("\n");

	printf("\n%hu\n", m);
	for(int i = 0; i < m; ++i)
		printf("%d ", sir2[i]);

	printf("\n");

	uint16_t i = 0, j = 0, k = 0;
	int* sir3 = malloc(sizeof(int) * (n + m));
	while (i < n && j < m) {
		int a = sir1[i];
		int b = sir2[j];	
		if (a < b) {
			if (k == 0 || sir3[k-1] != a)
				sir3[k++] = a;
			i++;
		} else if (a > b) {
			if (k == 0 || sir3[k-1] != b)
				sir3[k++] = b;
			j++;
		} else {
			if (k == 0 || sir3[k - 1] != a)
				sir3[k++] = a;

			while (i < n && sir1[i] == a) ++i;
			while (j < m && sir2[j] == a) ++j;
		}
	}

	while (i < n) {
		if (k == 0 || sir3[k - 1] != sir1[i])
			sir3[k++] = sir1[i];
		int val = sir1[i];
		while (i < n && sir1[i] == val) ++i;
	}
	
	while (j < m) {
		if (k == 0 || sir3[k - 1] != sir2[j])
			sir3[k++] = sir2[j];
		int val = sir2[j];
		while (j < m && sir2[j] == val) ++j;
	}


	printf("\n%hu\n", k);
	for(int i = 0; i < k; ++i)
		printf("%d ", sir3[i]);


	for (i = 0; i < k; ++i)
		sir3[i] = htonl(sir3[i]);

	k = htons(k);
	send(c, &k, sizeof(k), 0);
	
	k = ntohs(k);
	send(c, sir3, sizeof(int) * k, 0);

	free(sir1);
	free(sir2);
	free(sir3);
	close(c);
	return 0;
}
