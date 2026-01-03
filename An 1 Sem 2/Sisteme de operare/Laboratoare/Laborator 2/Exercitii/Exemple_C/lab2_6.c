#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
	// open the file
	char filename[] = "test.txt";
	FILE *file = fopen(filename, "r");
	if (file == NULL)
	{
		perror("Error");
		return 1;
	}

	// read the file content char by char
	char c;
	printf("Trying to read file char by char...\n");
	while ((c = fgetc(file)) != EOF)
	{
		printf("%c", c);
	}

	rewind(file);
	//fseek(file, 0L, SEEK_SET);

	// read the file content using a buffer
	char buffer[50];
	printf("Trying to read file using a buffer...\n");
	while (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		printf("%s", buffer);
	}

	// close the file
	fclose(file);
	
	return 0;
}
