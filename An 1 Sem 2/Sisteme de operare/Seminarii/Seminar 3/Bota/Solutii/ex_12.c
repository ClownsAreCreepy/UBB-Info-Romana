#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX 256
#define MAX_FILES 20

int main(int argc, char *argv[])
{
	// Program copil
	if (argc == 3)
	{
		FILE *in = fopen(argv[1], "r");
		if (!in)
		{
			perror("fopen (read)");
			exit(EXIT_FAILURE);
		}

		FILE *out = fopen(argv[2], "a");
		if (!out)
		{
			perror("fopen (append)");
			exit(EXIT_FAILURE);
		}

		char ch;
		while ((ch = fgetc(in)) != EOF)
			fputc(ch, out);

		fclose(in);
		fclose(out);
		exit(0);
	}

	// Parinte
	char buffer[MAX];
	char *filenames[MAX_FILES];
	int count = 0;

	printf("Introduceti cel putin 2 si cel mult 20 de nume de fisiere: ");
	fgets(buffer, MAX, stdin);

	char *tok = strtok(buffer, " ");
	while (tok != NULL && count < MAX_FILES)
	{
		filenames[count++] = strdup(tok);
		tok = strtok(NULL, " ");
	}

	if (count < 2)
	{
		printf("Trebuie minim 2 nume de fisiere\n");
		return 1;
	}

	char *output = filenames[count -1];
	output[strcspn(output, "\n")] = '\0';

	for (int i = 0; i < count - 1; ++i)
	{
		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork()");
			exit(EXIT_FAILURE);
		}

		if (pid == 0)
		{
			// copil: chemam acelasi program cu 2 nume de fisier

			execl("./ex_12", "./ex_12", filenames[i], output, NULL);

			// daca exec pica:
			perror("execl()");
			exit(EXIT_FAILURE);
		}
	}

	// parintele asteapta pentru toti copii
	for (int i = 0; i < count - 1; ++i)
		wait(NULL);

	return 0;
}
