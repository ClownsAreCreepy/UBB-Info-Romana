#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

#define MAX_STRINGS 10
#define MAX_LEN 100

// reverse a string in-place
void reverse(char *s)
{
	int len = strlen(s);
	for(int i = 0; i < len/2; ++i)
	{
		char temp = s[i];
		s[i] = s[len-1-i];
		s[len-1-i] = temp;
	}
}


int main(int argc, char *argv[])
{

	if(argc < 3)
	{
		printf("Usage: %s <filename> <string1> <string2> ...\n", argv[0]);
		return 1;
	}

	char *filename = argv[1];
	char buffer[1024] = "";
	for(int i = 2; i < argc; ++i) {
		char temp[256];
		strncpy(temp, argv[i], sizeof(temp));
		temp[sizeof(temp)-1] = '\0';
		reverse(temp);
		strcat(buffer, temp);
	}

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
		close(pipefd[1]); 		//inchidem capatul de scriere
		
		char msg[1024];
		int n = read(pipefd[0], msg, sizeof(msg) - 1);
		msg[n] = '\0';
		close(pipefd[0]);

		FILE *f = fopen(filename, "w");
		if(!f)
		{
			perror("fopen()");
			exit(EXIT_FAILURE);
		}

		fprintf(f, "%s\n", msg);
		fclose(f);
		exit(0);
	}
	else
	{
		// in parinte
		close(pipefd[0]);		//inchidem capatul de citire
		write(pipefd[1], buffer, strlen(buffer));
		close(pipefd[1]);		//inchidem capatul de scriere
		wait(NULL);
	}
	
	return 0;
}
