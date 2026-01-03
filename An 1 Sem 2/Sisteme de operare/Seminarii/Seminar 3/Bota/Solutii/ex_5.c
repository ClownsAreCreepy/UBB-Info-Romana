#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int gcd(int a, int b)
{
	while (b!=0)
	{
		int r = a%b;
		a = b;
		b = r;
	}
	return a;
}

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		printf("Usage: %s num1 num2 ... <filename>\n", argv[0]);
		return 1;
	}

	const char *filename = argv[argc - 1];

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
		//in copil
		close(pipefd[1]);		//capat de scriere

		int a, b;
		read(pipefd[0], &a, sizeof(int));
		read(pipefd[0], &b, sizeof(int));
		close(pipefd[0]);

		int cmmdc = gcd(a,b);

		FILE *f = fopen(filename, "w");
		if(!f)
		{
			perror("fopen()");
			exit(EXIT_FAILURE);
		}

		fprintf(f, "%d\n", cmmdc);
		fclose(f);

		printf("Child wrote GCD(%d, %d) = %d to file %s\n", a, b, cmmdc, filename);
		exit(0);
	}
	else
	{
		close(pipefd[0]);		//inchidem citirea
		
		int result = atoi(argv[1]);
		for(int i = 2; i < argc -2; ++i)
		{
			printf("Parent calculated GCD(%d", result);
			result = gcd(result, atoi(argv[i]));
			printf(", %c) = %d \n", argv[i][0], result);
		}

		int a = atoi(argv[argc-2]);

		write(pipefd[1], &result, sizeof(int));
		write(pipefd[1], &a, sizeof(int));
		close(pipefd[1]);

		wait(NULL);
	}

	return 0;
}
