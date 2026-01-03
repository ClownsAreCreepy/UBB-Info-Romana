#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

	if(argc < 3)
	{
		printf("Usage: %s num1 num2 num3 .. \n", argv[0]);
		return 1;
	}

	int pipefd[2];
	if(pipe(pipefd) == -1)
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
		//in copil
		close(pipefd[0]);		//inchidem capatul de scriere

		int negative = 0, produs;
		for (int i = 1; i < argc; ++i)
		{
			int nr = atoi(argv[i]);
			if (nr < 0)
				negative ++;
			if (nr == 0)
			{
				produs = 2;
				write(pipefd[1], &produs, sizeof(int));
				close(pipefd[1]);
				exit(0);
			}
		}

		if (negative % 2 == 0)
			produs = 0;
		else
			produs = 1;

		write(pipefd[1], &produs, sizeof(int));
		close(pipefd[1]);
		exit(0);
	}
	else
	{
		//in parinte
		close(pipefd[1]); 		//inchidem capatul de scriere
		
		int result;
		read(pipefd[0], &result, sizeof(int));
	        close(pipefd[0]);
      		wait(NULL);
 		printf("%d\n", result);		
	}

	return 0;
}
