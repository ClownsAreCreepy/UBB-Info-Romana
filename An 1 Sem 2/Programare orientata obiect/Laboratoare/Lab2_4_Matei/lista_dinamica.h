#pragma once
#include "medicament.h"

/*
  ListaDinamica cu capacitate statica maxima 100.
  Stocheaza pointeri la TElem*.
*/
#define CAPACITATE_MAX 100

typedef void* TElem;
typedef void* (*DestroyFunction)(void*);
typedef TElem (*CopyFunction)(void*);

typedef struct {
  TElem* elems;   //Inainte era ** si typedef medicament telem
  int lungime;
  int capacitate;
} ListaDinamica;

/*
  Creeaza o lista goala.
*/
ListaDinamica* creeaza_lista();

/*
 Distruge o lista de liste de medicamente
*/
void distruge_lista_de_liste(ListaDinamica* lista);

/*
  Distruge lista, eliberand memoria pentru fiecare element.
*/
void distruge_lista(ListaDinamica* lista, DestroyFunction destFct);

/*
  Adauga elementul in lista.
*/
void adauga_in_lista(ListaDinamica* lista,const TElem m);

/*
  Sterge elementul de la o pozitie.
  Returneaza 1 daca reuseste, 0 daca index invalid.
*/
int sterge_din_lista(ListaDinamica* lista, int index, DestroyFunction destFct);

/*
  Intoarce elementul de la o anumita pozitie.
*/
TElem get_element_lista(const ListaDinamica* lista, int index);

/*
  Returneaza dimensiunea listei.
*/
int dimensiune_lista(const ListaDinamica* lista);

/*
 Copiaza o lista in original
*/
ListaDinamica* copiaza_lista(const ListaDinamica* original, CopyFunction copyF);