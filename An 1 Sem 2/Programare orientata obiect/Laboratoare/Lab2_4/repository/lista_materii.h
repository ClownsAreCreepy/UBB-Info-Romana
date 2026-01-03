#ifndef LISTA_MATERII_H
#define LISTA_MATERII_H

#include "../domain/materie_prima.h"


/**
 * Tip nou de data pentru a stoca mai multe materii prime
 * Contine: materii - vector dinamic care contine materiile dorite
 *          nr_elemente - cate elemente contine vectorul
 *          capacitate - numarul maxim de materii care pot fi in lista
 */
typedef struct {
    MateriePrima *materii;
    int nr_elemente;
    int capacitate;
} ListaMaterii;


/**
 * Functia creeaza o noua lista de materii
 * @return o lista de materii proaspata
 */
ListaMaterii creeare();


/**
 * Functia elibereaza complet o lista de materii
 * @param lista o lista de materii
 */
void eliberare(ListaMaterii* lista);


/**
 * Functia mareste dimensiunea vectorului
 * @param lista o lista de materii
 */
void redimensionareCrestere(ListaMaterii* lista);


/**
 * Functia micsoreaza dimensiunea vectorului
 * @param lista o lista de materii
 */
void redimensionareScadere(ListaMaterii* lista);


/**
 * Functia adauga o noua materie prima in lista, sau mareste cantitatea unei materii prime deja existente
 * Daca e cazul, functia mareste dimensiunea vectorului dinamic
 * @param lista o lista de materii
 * @param m o materie prima
 */
void adaugare(ListaMaterii* lista, MateriePrima m);


/**
 * Functia modifica o materie prima existenta in ea
 * @param lista o lista de materii
 * @param index un identificator pentru materii
 * @param m o materie prima
 */
void modificare(ListaMaterii* lista,int index, MateriePrima m);


/**
 * Functia sterge o materie din lista.
 * Daca e cazul, functia micsoreaza dimensiunea vectorului dinamic
 * @param lista o lista de materii
 * @param index un identificator pentru materii
 */
void stergere(ListaMaterii* lista,int index);

#endif
