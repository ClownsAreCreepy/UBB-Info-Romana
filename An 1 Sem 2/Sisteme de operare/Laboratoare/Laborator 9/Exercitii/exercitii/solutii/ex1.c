#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[]){
	
	int pd[2];
	if (pipe(pd) < 0){ //pd[1] = capata de sciere si pd[0] = capat de citire
		perror("eroare pipe");
		exit(1);
	}

	int pid = fork();
	if (pid == -1){
		perror("eroare fork");
		exit(2);
	}
	if(pid == 0){ //in copil
		close(pd[1]); //se poate inchide capat de scriere deoarece face doar scriere
		char cuv_copil[100];
		while(1){
			int result = read(pd[0], cuv_copil, 100);
			//printf("%s\n", cuv_copil);
			if(result == 0){
				break;
			}
			printf("%s\n", cuv_copil);
		}
		
		close(pd[0]);// inchide capat citire
		exit(0);
	}

	//in parinte
	
	close(pd[0]); // poate inchide capat de read deoarece face doar write
	FILE* fd = fopen("test", "r");
	if( fd < 0){
		perror("eroare fisier");
		exit(3);
	}
	
	char cuv[100];

	while(!feof(fd)){
		fscanf(fd, "%s", cuv);
		//printf("%s\n", cuv);
		write(pd[1], cuv, 100);
	}
	fclose(fd);
	close(pd[1]); // inchide capat de sciere 
	wait(NULL); //pentru copil
	return 0;
}
