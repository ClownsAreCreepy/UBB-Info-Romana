#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv){
	if (argc != 2) {
		printf("Usage: %s <number>\n", argv[0]);
		return 1;
	}

	int ppid=getpid(), nr=atoi(argv[1]);
	
	for (int i = 0; i < nr; ++i){
		int pid = fork();
		if (pid == -1) {
			printf("Erorr at fork()\n");
			return 2;
		}
		if (pid != 0) { 
			printf("Child #%d created, son of %d\n", i+1, getppid());
			break;
		}
	}

	if (getpid() == ppid)
		for (int i = 0; i < nr; ++i)
			wait(NULL);
	return 0;
}
