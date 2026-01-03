#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	// efinesc listele de argumente
	char *first_cmd[] = {"ls", "-l", NULL};
	char *second_cmd[] = {"wc", "-l", NULL};

	// creez un pipe
	int p[2];
	if (pipe(p) < 0)
	{
		perror("pipe()");
		exit(EXIT_FAILURE);
	}

	// creez primul proces copil
	int pid1 = fork();
	if (pid1 == -1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}

	//in procesul copil
	if(pid1 == 0)
	{
		// inchid capatul de citire din pipe
		close(p[0]);

		// conectez fluxul de iesire (stdout) la captul de scriere in pipe
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);

		// execut comanda
		if(execvp(first_cmd[0], first_cmd) < 0)
		{
			perror("execvp()");
			exit(EXIT_FAILURE);
		}
	}

	// creez al doilea proces copil
	int pid2 = fork();
	if(pid2 == -1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}

	// in procesul copil
	if (pid2 == 0)
	{
		// inchid capatul de scriere in pipe
		close(p[1]);

		// conectez capatul de citire din pipe la fluxul de intrare (stdin)
		dup2(p[0], STDIN_FILENO);
		close(p[0]);

		// executa comanda
		if (execvp(second_cmd[0], second_cmd) < 0)
		{
			perror("execvp()");
			exit(EXIT_FAILURE);
		}
	}

	// in parinte
	close(p[0]);		// inchidem capatul de citire
	close(p[1]);		// inchidem capatul de scriere
	
	int status;
	waitpid(pid1, &status, 0);		// astept terminarea primului proces copil
	printf("[PARINTE] Copil PID %d a returnat %d\n", pid1, status);
	waitpid(pid2, &status, 0);		// astept terminarea celui de-al doilea proces copil
	printf("[PARINTE] Copil PID %d a returnat %d\n", pid2, status);

	return 0;

}
