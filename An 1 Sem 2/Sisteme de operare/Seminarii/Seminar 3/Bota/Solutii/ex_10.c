#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX 256

int gcd(int a, int b)
{
	while(b != 0)
	{
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int main()
{
	int numere[MAX], count = 0, cod, toate_prime=0;
	char buffer[MAX];

	printf("Introduceti un sir de numere: ");
	fgets(buffer, MAX, stdin);

	char *tok = strtok(buffer, " ");
	while (tok != NULL)
	{
		numere[count++] = atoi(tok);
		tok = strtok(NULL, " ");
	}

	if (count % 2 != 0)
	{
		printf("Trebuie introduse un numar par de numere!\n");
		return 1;
	}

	for (int i = 0; i < count; i+= 2)
	{
		int pipefd[2];
		if (pipe(pipefd) == -1)
		{
			perror("pipe()");
			exit(EXIT_FAILURE);
		}

		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork()");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			// copil
			close(pipefd[0]);

			int cod = (gcd(numere[i], numere[i+1]) == 1) ? 0 : 1;
			write(pipefd[1], &cod, sizeof(int));

			close(pipefd[1]);
			exit(0);
		}
		else
		{
			// parent
			close(pipefd[1]);

			wait(NULL);

			read(pipefd[0], &cod, sizeof(int));
			close(pipefd[0]);

			printf("Numerele %d si %d ", numere[i], numere[i+1]);
			if (cod != 0)
			{
				printf("NU ");
				toate_prime = 1;
			}
			printf("sunt prime intre ele!\n");
		}
	}

	printf("\nDeci,");
	if (toate_prime)
		printf(" NU");
	printf(" toate numerele sunt prime intre ele!\n");

	return 0;
}
