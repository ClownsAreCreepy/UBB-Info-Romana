/*
se da un fisier text care contine caractere aleatoare.Determinati media aritmetica a frecventelor ale fiecarei litere a aflabetului
si sa se afiseze pe fiecare thread diferenta dintre nr de aparitii determinat de thread si media aritmetica.


*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_CHAR 26
#define MAX_SIZE 1024
pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;

char filename[50];
int total_ap=0;
void* do_work(void*arg){
	char litera=*(char*)arg;
	int fd=open(filename,O_RDONLY);
	if(fd ==-1){
		perror("open()");
		exit(1);
	}
	int citit=1;
	char buffer[MAX_SIZE+1];
	int aparitii=0;
	while(citit>0){
		citit=read(fd,buffer,MAX_SIZE);
		for(int i=0;i<citit;i++){
			if(buffer[i]==litera) aparitii++;
			if(buffer[i]==toupper(litera)) aparitii++;
		}

	}
	pthread_mutex_lock(&mtx);
	total_ap+=aparitii;
	pthread_mutex_unlock(&mtx);

	pthread_barrier_wait(&barr);

	float media=total_ap/MAX_CHAR;
	float dif=(float)abs(media-aparitii);
	printf("pentru litera %c diferenta este %f \n",litera,dif);
	close(fd);
	return NULL;


}
int main(int argc,char* argv[]){
	if (argc <2){
		printf("numar incorect de argumente! \n");
		exit(1);

	}
	strcpy(filename,argv[1]);

	pthread_barrier_init(&barr,NULL,MAX_CHAR);

	pthread_t th[MAX_CHAR];
	char letters[MAX_CHAR];

	//creez threadurile,unul pt fiecare litera
	//astept terminarea threadurilor 
	//afisez media aritm
	for(int i=0;i<MAX_CHAR;i++){
		letters[i]='a'+i;
		pthread_create(&th[i],NULL,do_work,&letters[i]);
	}
	for(int i=0;i<MAX_CHAR;i++){
		pthread_join(th[i],NULL);
	}
	//printf("media este %f \n",media);

	pthread_barrier_destroy(&barr);
	return 0;

}
