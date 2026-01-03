#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


#define MAX 256

int main()
{
	char buffer[MAX], final[MAX] = "", filename[MAX];

	printf ("Introduceti fisierul in care vreti rezultatul: ");
	fgets(filename, MAX, stdin);
	filename[strcspn(filename, "\n")] = '\0';

	printf ("Introduceti niste siruri de caractere, separate prin spatiu: ");
	fgets(buffer, MAX, stdin);

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

		char *tok = strtok(buffer, " ");
		while (tok != NULL)
		{
			strcat(final, tok);
			tok = strtok(NULL, " ");
		}
		
		write(pipefd[1], &final, strlen(final) + 1);
		close(pipefd[1]);
		exit(0);
	}
	else
	{
		// in parinte
		close(pipefd[1]);

		wait(NULL);
		read(pipefd[0], &final, MAX);

		FILE *f = fopen(filename, "w");
		if (!f)
		{
			perror("fopen (write)");
			exit(EXIT_FAILURE);
		}

		fprintf(f, "%s", final);
		fclose(f);
	}

	return 0;
}
