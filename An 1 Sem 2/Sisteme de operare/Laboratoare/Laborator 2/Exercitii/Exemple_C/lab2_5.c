#include <stdio.h>


int main(int argc, char* argv[])
{
	// read an integer from keyboard
	int n1 = 0;
	printf("Dati un intreg: ");
	scanf("%d", &n1);
	printf("n1: %d\n", n1);
	
	// read a string from keyboard
	char s1[50];
	printf("Dati un sir: ");
	scanf("%s", s1);
	printf("s1: %s\n", s1);

	return 0;
}
