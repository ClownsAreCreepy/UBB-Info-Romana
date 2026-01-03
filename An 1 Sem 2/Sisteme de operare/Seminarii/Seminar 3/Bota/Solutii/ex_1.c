#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

	if (argc < 3)
	{
		perror("Usage: [code_file_name] num1 num2 num3 ...\n");
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
		// procesul copil
		close(pipefd[0]); // inchidem capatul de citire
		
		int equal = 1;
		int first = atoi(argv[1]);
		for(int i = 1; i < argc; ++i)
			if(atoi(argv[i]) != first)
			{
				equal = 0;
				break;
			}

		write(pipefd[1], &equal, sizeof(int));
		close(pipefd[1]);
		exit(0);
	}
	else
	{
		close(pipefd[1]);		// inchidem capatul de scriere
		
		int result;
		read(pipefd[0], &result, sizeof(int));
		close(pipefd[0]);
		wait(NULL);

		if (result == 1)
			printf("Numerele sunt egale!\n");
		else
			printf("Numerele NU sunt egale!\n");

	}
}
