#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 256

int main()
{
	char buffer[MAX];
	int numere[MAX], count = 0, sum = 0;

	printf("Introduceti numere: ");
	fgets(buffer, MAX, stdin);

	char *tok = strtok(buffer, " ");
	while (tok != NULL)
	{
		numere[count++] = atoi(tok);
		tok = strtok(NULL, " ");
	}

	if (count < 2)
	{
		printf("Trebuie introduse cel putin 2 numere!\n");
		return 1;
	}

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
		// in copil
		close(pipefd[0]);

		for (int i = 0; i < count; ++i)
			sum += numere[i];

		sum = sum % 2;

		write(pipefd[1], &sum, sizeof(int));
		close(pipefd[1]);
		exit(0);
	}
	else
	{
		// in parinte
		close(pipefd[1]);
		
		wait(NULL);
		read(pipefd[0], &sum, sizeof(int));
		close(pipefd[0]);

		if (sum == 0)
			printf("Suma numerelor este para\n");
		else
			printf("Suma numerelor este impara\n");
	}

	return 0;
}
