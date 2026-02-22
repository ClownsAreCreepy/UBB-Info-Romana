#include <stdio.h>
#include <stdlib.h>

int main() {
	int* a = malloc(sizeof(int) * 256);
	
	a[0] = 'z';
	printf("%d\n", a[0]);
	printf("%c\n", a[0]);

	free(a);
}
