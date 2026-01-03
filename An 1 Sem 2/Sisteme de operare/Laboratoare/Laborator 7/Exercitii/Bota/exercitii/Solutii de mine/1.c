#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>


int main()
{
	// definesc lista de argumente
	char *args[] = {"ls", "-l", NULL};

	// creez un proces copil
	int pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) //in copil
	{
		//exectuam comanda
		if (execvp(args[0], args) < 0)
		{
			perror("execvp()");
			exit(EXIT_FAILURE);
		}
	}
	else //in parinte
	{
		int status;
		wait(&status);
		printf("[Parinte] Copilul cu PID %d a returnat %d\n", pid, status);
	}
	return 0;
}
