#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#define MAX_LEN 200

int main(int argc, char **argv){
    (void)argc;
    (void)argv;
    int pd[2];
    if (pipe(pd) < 0){
        perror("pipe()");
        exit(1);
    }

    int pid = fork();
    int n1, n2;
    char op;
    if (pid == -1){
        perror("fork()");
        exit(1);
    }

    if (pid == 0){  // In copil
        close(pd[1]);   // Inchid descriptorul de scriere

        int cpn1, cpn2;
        char cpop;
        FILE* fd = fopen("solutie.txt", "w");
        while(1){
             read(pd[0], &cpop, sizeof(char));
             if (cpop == 'x')
                 break;
             read(pd[0], &cpn1, sizeof(int));
             read(pd[0], &cpn2, sizeof(int));
             int rez;
             if (cpop == '+')
                 rez = cpn1 + cpn2;
             if (cpop == '-')
                 rez = cpn1 - cpn2;
             if (cpop == '/')
                 rez = cpn1/cpn2;
             if (cpop == '*')
                 rez = cpn1*cpn2;
             if (cpop == '%')
                 rez = cpn1%cpn2;
             fprintf(fd,"%d %c %d = %d\n", cpn1, cpop, cpn2, rez);
        }
        fclose(fd);
        close(pd[0]);   // Inchid descriptorul de citire
        exit(0);
    }
    
    // In parinte
    close(pd[0]);   // Inchid descriptorul de citire

    while (1){
        scanf(" %c", &op);
        write(pd[1], &op, sizeof(char));
        if (op == 'x')
            break;
        scanf("%d", &n1);
        write(pd[1], &n1, sizeof(int));
        scanf("%d", &n2);
        write(pd[1], &n2, sizeof(int));
        
    }

    close(pd[1]);   // Inchid descriptorul de scriere
    wait(NULL);
    exit(0);
    return 0;
}

