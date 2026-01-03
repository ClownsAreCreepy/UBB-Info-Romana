#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


// Sa se scrie un program C care:
// - citeste un numar N de la tastatura;
// - citeste N numere intregi de la tastatura;
// - determina si afiseaza pe ecran minimul, maximul si media lor aritmetica.
int main(int argc, char* argv[])
{
	// citesc N
	int N = 0;
	printf("N: ");
	scanf("%d", &N);

	// aloc dinamic vectorul de numere intregi
	int *numere = malloc(N*sizeof(int));
	if (numere == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	// citim numerele intregi
	printf("Dati numerele:\n");
	for (int i = 0; i < N; i++)
	{
		printf("  numere[%d]: ", i);
		scanf("%d", &numere[i]);
	}

	// determin minim, maxim si suma
	int minim = INT_MAX;
	int maxim = INT_MIN;
	float suma = 0.0;
	for (int i = 0; i < N; i++)
    {
		suma += numere[i];
		if (numere[i] < minim) minim = numere[i];
		if (numere[i] > maxim) maxim = numere[i];
	}

	// afisez minimul
	printf("Minim: %d\n", minim);

	// afisez maximul
    printf("Maxim: %d\n", maxim);

	// calculez media aritmetica
	float media = suma/N;
	printf("Media aritmetica: %f\n", media);

	// eliberez spatiul de memorie alocat
	free(numere);

	return 0;
}
