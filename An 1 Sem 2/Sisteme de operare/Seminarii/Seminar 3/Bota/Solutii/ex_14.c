#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX 256

int main(int argc, char *argv[])
{
	if (argc == 4)
	{
		// in copil
		
		int a = atoi(argv[1]);
		int b = atoi(argv[2]);
		FILE *f = fopen(argv[3], "w");
		if (!f)
		{
			perror("fopen (write)");
			exit(EXIT_FAILURE);
		}

		fprintf(f, "%d", a + b);
		fclose(f);
		exit(0);
	}

	// parinte
	char buffer[MAX], file[] = "caca";
	int nums[100], count = 0;

	printf("Introduceti un sir de numere: ");
	fgets(buffer, MAX, stdin);

	char *tok = strtok(buffer, " ");
	while (tok != NULL)
	{
		nums[count++] = atoi(tok);
		tok = strtok(NULL, " ");
	}

	if (count < 2)
	{
		printf("Trebuie sa introduceti minim 2 numere\n");
		return 1;
	}

	// suma initiala a primelor 2 numere
	char a_str[20], b_str[20];
	sprintf(a_str, "%d", nums[0]);
	sprintf(b_str, "%d", nums[1]);

	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		execl("./ex_14", "./ex_14", a_str, b_str, file, NULL);
		perror("execl");
		exit(EXIT_FAILURE);
	}

	wait(NULL);

	// apoi dam loop prin restul numerelor
	for (int i = 2; i < count; ++i)
	{
		// citim suma curenta din fisier
		FILE *f = fopen(file, "r");
		if (!f)
		{
			perror("fopen (read)");
			exit(EXIT_FAILURE);
		}

		int sum;
		fscanf(f, "%d", &sum);
		fclose(f);

		// fork din nou si adaugam numarul urmator
		sprintf(a_str, "%d", sum);
		sprintf(b_str, "%d", nums[i]);

		pid = fork();
		if (pid == -1)
		{
			perror("fork()");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			execl("./ex_14", "./ex_14", a_str, b_str, file, NULL);
			perror("execl()");
			exit(EXIT_FAILURE);
		}

		wait(NULL);
	}

	// afisare finala
	FILE *f = fopen(file, "r");
	int total;
	fscanf(f, "%d", &total);
	fclose(f);

	printf("Suma este: %d\n", total);
	return 0;
}
