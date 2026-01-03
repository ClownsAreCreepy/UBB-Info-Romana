#ifndef MATERIE_PRIMA_H
#define MATERIE_PRIMA_H

/**
 * Tip nou de data pentru a stoca o materie prima.
 * Contine: numele materiei, producatorul materiei, cantitatea de materie
 */
typedef struct {
    char nume[50];
    char producator[50];
    int cantitate;
} MateriePrima;

/**
 * Functia valideaza o materie prima
 * @param m o materie prima
 * @return 0 - daca numele ei sau producatorul ei este vid sau daca cantitatea e mai mica decat 0
 *         1- in caz contrar
 */
int validare(MateriePrima m);

#endif
