#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int is_prim(int n)
{
	if (n < 2) return 0;
	for (int i = 2; i * i <= n; ++i)
		if (n % i == 0)
			return 0;
	return 1;
}


int main(int argc, char *argv[])
{
	// VERIFICAM PENTRU PROCESUL COPIL
	if (argc == 2)
	{
		int num = atoi(argv[1]);
		if (is_prim(num))
			exit(0);
		else
			exit(1);
	}

	// PARINTE
	int n;
	printf("Introduceti un numar: ");
	scanf("%d", &n);

	for (int i = 2; i <= n; ++i)
	{
		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork()");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			// copil: chemam acelasi program cu i
			
			char num_str[20];
			sprintf(num_str, "%d", i);	// printf but saves it in a string
		
			execl("./ex_11", "./ex_11", num_str, NULL);

			// daca exec pica:
			perror("execl()");
			exit(EXIT_FAILURE);
		}
		else
		{
			// parintele asteapta si verifica
			int status;
			wait(&status);

			if (WIFEXITED(status) != 0 && WEXITSTATUS(status) == 0)
				printf("%d ", i); // afisam numarul prim
		}
	}

	printf("\n");
	return 0;
}
