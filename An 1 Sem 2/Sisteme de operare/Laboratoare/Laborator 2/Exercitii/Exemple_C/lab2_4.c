#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10

int main(int argc, char* argv[])
{
	// using static memory allocation
	char s1[MAX_SIZE] = "abcde";
	// char s1[MAX_SIZE] = {'a','b','c','d','e'};
	
	// using dynamic memory allocation
	char* s2 = malloc(MAX_SIZE*sizeof(char));
	if (s2 == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	
	// copy s1 to s2
	strcpy(s2, s1);
	
	// print s1, s2
	printf("s1: %s\n", s1);
	printf("s2: %s\n", s2);
	
	// print s2 char by char
	printf("s2:");
	for (int i = 0; i < strlen(s2); i++)
		printf(" %c", s2[i]);
	
	// deallocate the dynamic allocated memory
	free(s2);

	return 0;
}
