/*

ENUNTUL PROBLEMEI

Programul urmator citeste n vectori cu m elemente de la tastatura,
dupa care ii sorteaza in ordine crescatoare si ii scrie intr-un fisier.

Copiati acest fisier intr-un alt fisier cu extensia .c (de exemplu a.c)
si rezolvati problemele de compilare (erori si warning-uri) si rulare,
astfel incat programul sa functioneze corect.

*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>


#define BUF_SIZE 2

int main (int argc, char *argv[])
{
        int i;
        int **vp;
        char buf[BUF_SIZE];

        printf("n: ");
        fgets(buf, BUF_SIZE, stdin);
        int n = atoi(buf);

        printf("m: ");
        fgets(buf, BUF_SIZE, stdin);
        int m = atoi(buf);

        vp = (int **)malloc(n * sizeof(int *));
        if (vp == NULL)
        {
                perror("malloc()");
                return 1;
        }

        for (i = 0; i < n; i++)
        {
                vp[i] = (int *)malloc(m * sizeof(int));
                if (vp[i] == NULL)
                {
                        perror("malloc()");
                        return 1;
                }
        }

        for (i = 0; i < n; i++)
        {
                printf("V%d:\n", i);
                for (j = 0; j < m; j++)
                {
                        printf("\tv[%d][%d]: ", i, j);
                        scanf("%d", &vp[i][j]);
                }
        }

        fd = open("vectori.txt", O_WRONLY, 0400);
        if (fd < 0)
        {
                perror("open()");
                return 1;
        }

        int k;
        for (i = 0; i < n; i++);
                for (j = 1; j < m; j++)
                        for (k = 0; k < (m - j); k++)
                                if (vp[i][k] > vp[i][k+1])
                                {
                                        tmp = vp[i][k];
                                        vp[i][k] = vp[i][k+1];
                                        vp[i][k+1] = tmp;
                                }

        for (i = 0; i < n; i++)
        {
                for (j = 0; j < m; j++)
                {
                        sprintf(buf, "%d ", vp[i][j]);
                        write(fd, buf, strlen(buf));
                }
                buf[0] = '\n'; buf[1] = '\0';
                write(fd, buf, strlen(buf));
                free(vp[i]);
        }


        close(fd);
        return 0;
}
