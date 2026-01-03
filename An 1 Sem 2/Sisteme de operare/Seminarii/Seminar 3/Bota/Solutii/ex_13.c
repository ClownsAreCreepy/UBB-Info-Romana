#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int is_prime(int n)
{
	if (n < 2 || n > 2 && n % 2 == 0) 
		return 0;

	for (int i = 3; i * i <= n; i += 2)
		if (n % i == 0)
			return 0;
	return 1;
}

int main(int argc, char *argv[])
{
	if (argc == 4)
	{
		int start = atoi(argv[1]), end = atoi(argv[2]);
		FILE *f = fopen(argv[3], "a");

		for (int i = start; i <= end; ++i)
			if (is_prime(i))
				fprintf(f, "%d ", i);

		fclose(f);
		exit(0);
	}

	int n;
	printf("Introduceti un numar: ");
	scanf("%d", &n);

	char file[] = "caca";

	// Curatam fisierul
	FILE *f = fopen(file, "w");
	fclose(f);

	for (int i = 0; i < n; i += 10)
	{
		int a = i;
		int b = (i + 9 < n) ? (i + 9) : (n - 1);

		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork()");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			char a_str[20], b_str[20];
			sprintf(a_str, "%d", a);
			sprintf(b_str, "%d", b);
		
			execl("./ex_13", "./ex_13", a_str, b_str, file, NULL);
		
			perror("execl()");
			exit(EXIT_FAILURE);
		}
	}

	while (wait(NULL) > 0);	

	return 0;
}
