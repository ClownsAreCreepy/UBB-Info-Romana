#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX 256

void scriem_produs_in_file(const char *filename, int val)
{
	FILE *f= fopen(filename, "w");
	if(!f)
	{
		perror("fopen (write)");
		exit(EXIT_FAILURE);
	}

	fprintf(f, "%d\n", val);
	fclose(f);
}

int citim_produs_din_file(const char *filename)
{
	FILE *f = fopen(filename, "r");
	if(!f)
	{
		perror("fopen (read)");
		exit(EXIT_FAILURE);
	}

	int val;
	fscanf(f, "%d", &val);
	fclose(f);
	return val;
}

int main()
{
	char buffer[MAX];
	int nums[100], count = 0;

	printf("Please enter numbers: ");
	fgets(buffer, MAX, stdin);

	char *token = strtok(buffer, " ");
	while (token != NULL)
	{
		nums[count++] = atoi(token);
		token = strtok(NULL, " ");
	}

	if (count < 2)
	{
		printf("Trebuie cel putin 2 numere!\n");
		return 1;
	}

	char filename[] = "caca";
	int product = nums[0] * nums[1];
	scriem_produs_in_file(filename, product);
	printf("Parintele scrie in fiser %d * %d = %d\n", nums[0], nums[1], product);

	for(int i = 2; i < count; ++i)
	{
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
			int prev = citim_produs_din_file(filename);
			int result = prev * nums[i];
			scriem_produs_in_file(filename, result);
			printf("Copilul scrie in fiser %d * %d = %d\n", prev, nums[i], result);
			
			if (i == count - 1)
			{
				close(pipefd[0]);
				write(pipefd[1], &result, sizeof(int));
				close(pipefd[1]);
			}

			exit(0);
		}
		else
		{
			// in parinte
			wait(NULL);
			if (i == count - 1)
			{
				close(pipefd[1]);
				read(pipefd[0], &product, sizeof(int));
				close(pipefd[0]);
			}
		}

	}	

	printf("Produs final: %d\n", product);
	return 0;
}
