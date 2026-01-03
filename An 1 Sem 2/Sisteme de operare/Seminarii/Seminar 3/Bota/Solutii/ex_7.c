#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX 256
#define MAX_NUMS 100

void scriem_vector_in_file(const char *filename, int arr[], int n)
{
	FILE *f = fopen (filename, "w");
	if (!f)
	{
		perror("fopen (write)");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < n; ++i)
		fprintf(f, "%d ", arr[i]);
	fprintf(f, "\n");
	fclose(f);
}

int citim_vector_din_file(const char *filename, int arr[])
{
	FILE *f = fopen (filename, "r");
	if(!f)
	{
		perror("fopen (read)");
		exit(EXIT_FAILURE);
	}

	int val, count = 0;
	while (fscanf(f, "%d", &val) == 1)
		arr[count++] = val;
	fclose(f);
	return count;
}

int main()
{
	char buffer[MAX];
	int user_nums[MAX_NUMS];
	int count = 0;

	printf("Please enter numbers: ");
	fgets(buffer, MAX, stdin);

	char *tok = strtok(buffer, " ");
	while (tok != NULL)
	{
		user_nums[count++] = atoi(tok);
		tok = strtok(NULL, " ");
	}

	if (count < 2)
	{
		printf("Trebuie cel putin 2 numere!\n");
		return 1;
	}
	
	// sortam vectorul
	for (int i = 0; i < count - 1; ++i)
		for (int j = i + 1; j < count; j++)
			if (user_nums[i] > user_nums[j])
			{
				int temp = user_nums[i];
				user_nums[i] = user_nums[j];
				user_nums[j] = temp;
			}

	int mid = count / 2;
	scriem_vector_in_file("prima_jumatate.txt", user_nums, mid);
	scriem_vector_in_file("a_doua_jumatate.txt", user_nums + mid, count - mid);

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
		close(pipefd[0]);

		int a[MAX_NUMS], b[MAX_NUMS], unite[MAX_NUMS * 2];
		int na = citim_vector_din_file("prima_jumatate.txt", a);
		int nb = citim_vector_din_file("a_doua_jumatate.txt", b);
		
		int i = 0, j = 0, k = 0;
		while (i < na && j < nb)
			if (a[i] <= b[j])
				unite[k++] = a[i++];
			else
				unite[k++] = b[j++];

		while (i < na) unite[k++] = a[i++];
		while (j < nb) unite[k++] = b[j++];
		
		write(pipefd[1], &k, sizeof(int));
		write(pipefd[1], &unite, k * sizeof(int));
		close(pipefd[1]);
		
		scriem_vector_in_file("caca", unite, k);
		exit(0);
	}
	else
	{
		// in parinte
		close(pipefd[1]);

		wait(NULL);

		int unite[MAX], k;
		read(pipefd[0], &k, sizeof(int));
		read(pipefd[0], &unite, k * sizeof(int));
		close(pipefd[0]);

		for (int i = 0; i < k; ++i)
			printf("%d ", unite[i]);
	}
	
	printf("\n");

	remove("prima_jumatate.txt");
	remove("a_doua_jumatate.txt");
	return 0;
}
