#include <stdlib.h>
#include "lista_dinamica.h"

ListaDinamica* creeaza_lista() {
  ListaDinamica* lista = malloc(sizeof(ListaDinamica));
  lista->lungime = 0;
  lista->capacitate = 2;
  lista->elems = malloc(lista->capacitate * sizeof(TElem));
  return lista;
}

void distruge_lista_de_liste(ListaDinamica* lista) {
  for (int i = 0; i < lista->lungime; ++i) {
    ListaDinamica* l = (ListaDinamica*) lista->elems[i];
    distruge_lista(l, distruge_medicament);
  }
  free(lista->elems);
  free(lista);
}

void distruge_lista(ListaDinamica* lista, DestroyFunction destrF) {
  if (!lista) return;
  for (int i = 0; i < lista->lungime; i++) {
    destrF(lista->elems[i]);
  }
  free(lista->elems);
  free(lista);
}

void adauga_in_lista(ListaDinamica* lista, TElem elem) {
  if (lista->lungime >= lista->capacitate) {
    int capacitate_noua = lista->capacitate * 2;
    TElem* temp = realloc(lista->elems, capacitate_noua * sizeof(TElem));
    if (temp == NULL) return;
    lista->elems = temp;
    lista->capacitate = capacitate_noua;
  }
  lista->elems[lista->lungime] = elem;
  lista->lungime++;
}

int sterge_din_lista(ListaDinamica* lista, int index, DestroyFunction destrF) {
  if (index < 0 || index >= lista->lungime)
    return 0;

  destrF(lista->elems[index]);
  for (int i = index; i < lista->lungime - 1; i++) {
    lista->elems[i] = lista->elems[i + 1];
  }
  lista->lungime--;
  return 1;
}

TElem get_element_lista(const ListaDinamica* lista, int index) {
  return lista->elems[index];
}

int dimensiune_lista(const ListaDinamica* lista) {
  return lista->lungime;
}

ListaDinamica* copiaza_lista(const ListaDinamica* original, CopyFunction copyF) {
  ListaDinamica* copie = creeaza_lista();
  for (int i = 0; i < original->lungime; ++i)
    adauga_in_lista(copie, copyF(original->elems[i]));
  return copie;
}