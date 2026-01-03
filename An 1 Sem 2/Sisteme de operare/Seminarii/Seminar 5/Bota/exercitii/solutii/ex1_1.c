//
// ex1_1.c - Fara sincronizare
//
// Generati 100.000 de numere aleatoare si calculati suma lor utilizand 100 thread-uri.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_THR 100
#define CHUNK_SIZE 1000
#define MAX_NUM 100000

int sum = 0;
int numbers[MAX_NUM];


// Rutina de start
void* do_sum(void *a)
{
	int min = *(int *)a;
	//printf("min = %d\n", min);
	free(a);
	
	int i;
	int max = min + CHUNK_SIZE;
	for (i = min; i < max; i++)
	{
		sum += numbers[i];
	}

	return NULL;
}


int main(int argc, char *argv[])
{
	srand(time(NULL));
	
	// generam 100.000 numere aleatoare
	int i;
	for (i = 0; i < MAX_NUM; i++)
	{
		numbers[i] = rand() % 20;
	}

	// cream cele 100 thread-uri
	pthread_t tid[MAX_THR];
	for (i = 0; i < MAX_THR; i++)
	{
		int *n = (int *)malloc(sizeof(int));
		*n = i * CHUNK_SIZE;
		pthread_create(&tid[i], NULL, do_sum, n);
	}

	// asteptam terminarea thread-urilor
	for (i = 0; i < MAX_THR; i++)
	{
		pthread_join(tid[i], NULL);
	}

	// afisam rezultatul
	printf("Suma calculata:  %d\n", sum);

	// verificam suma
	int check_sum = 0;
	for (i = 0; i < MAX_NUM; i++)
	{
		check_sum += numbers[i];
	}

	printf("Suma verificata: %d\n", check_sum);

	return 0;
}
