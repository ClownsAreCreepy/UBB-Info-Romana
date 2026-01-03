#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	char *args[] = {"ls", "-l", NULL};

	int pid = fork();

	if (pid == -1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) //in copil
	{
		//creez fisierul
		int fd = open("lista_fisiere", O_CREAT | O_TRUNC | O_RDWR, 0644);
		if (fd == -1)
		{
			perror("open()");
			exit(EXIT_FAILURE);
		}

		//redirectez fluxul de iesire (stdout) in fisier
		dup2(fd, STDOUT_FILENO);
		close(fd);

		if (execvp(args[0], args) < 0){
			perror("execvp()");
			exit(EXIT_FAILURE);
		}
	}

	else 
	{
		int status;
		wait(&status);
	}
	return 0;
}
