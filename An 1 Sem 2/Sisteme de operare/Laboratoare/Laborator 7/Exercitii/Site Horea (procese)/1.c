#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv){ 

	if (argc != 2) {
		printf("Usage: %s <number>\n", argv[0]);
		return 1;
	}

	int nr = atoi(argv[1]);

	for (int i = 0; i < nr; ++i) {
		int pid = fork();
		if (pid == -1) {
			printf("Error at fork()\n");
			return 2;
		}

		if (pid == 0) {
			//getpid pentru id-ul copilului
			//getppid pentru id-ul parintelui
			printf("[CHILD] My id is %d, my dad's id is %d\n", getpid(), getppid());
			exit(0);
		}
		wait(NULL);
		printf("[PARENT] My id is %d, my kid's id is %d\n", getpid(), pid);
	}

	return 0;
}
