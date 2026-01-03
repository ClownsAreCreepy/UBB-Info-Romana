/*
Scrieti un program C care primeste doua numere, N si M, ca argumente la linia de comanda.
Programul creeaza N thread-uri "generator" care genereaza litere mici ale alfabetului aleator
si le adauga unui sir de caractere cu 128 de pozitii.
Programul mai creeaza un thread "printer" care asteapta ca toate pozitiile sirului de caractere sa fie ocupate,
moment in care afiseaza sirul si apoi seteaza toate pozitiile sirului la NULL.
Cele N thread-uri "generator" vor genera M astfel de string-uri iar thread-ul "printer" va afisa fiecare string
imediat ce ajunge la lungimea 128.

*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 128

char buffer[SIZE+1];
int poz=0;
int count;

pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cg=PTHREAD_COND_INITIALIZER;
pthread_cond_t cp=PTHREAD_COND_INITIALIZER;

void* generate(void* arg)
{
	while(1){
		char ch='a' + rand() %('z' - 'a' + 1);

		pthread_mutex_lock(&mtx);
		if(poz==SIZE){
			pthread_cond_signal(&cp);
			while(poz==SIZE){
				pthread_cond_wait(&cg,&mtx);
			}
		}

		if( count == 0 ) break;

		buffer[poz]=ch;
		poz++;

		pthread_mutex_unlock(&mtx);
	}

	pthread_mutex_unlock(&mtx);

	return NULL;
}

void* print(void *arg)
{
	while(1){
		if(poz!=SIZE){
			pthread_cond_signal(&cg);
			while(poz!=SIZE){
				pthread_cond_wait(&cp,&mtx);
			}
		}

		printf("%s \n",buffer);
		count--;
		poz=0;
		memset(buffer,0,SIZE*sizeof(char));//initializam cu zero in buffer

		pthread_cond_broadcast(&cg);

		if (count==0) break;

		pthread_mutex_unlock(&mtx);

	}
	pthread_mutex_unlock(&mtx);
	return NULL;
}
int main(int argc,char* argv[]){

	if(argc < 3){
		printf("numar incorect de argumente \n");
		exit(1);
	}

	int N = atoi(argv[1]);
	int M = atoi(argv[2]);
	count=M;

	srand(time(NULL));

	pthread_t tg[N];
	for(int i=0;i<N;i++){
		pthread_create(&tg[i],NULL,generate,NULL);
	}

	pthread_t tp;
	pthread_create(&tp,NULL,print,NULL);

	for(int i=0;i<N;i++){
		pthread_join(tg[i],NULL);
	}

	pthread_join(tp,NULL);

	return 0;
}
