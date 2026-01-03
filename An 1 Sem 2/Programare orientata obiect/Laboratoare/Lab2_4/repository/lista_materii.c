#include "lista_materii.h"

#include <stdlib.h>
#include <string.h>

#include "../domain/materie_prima.h"


ListaMaterii creeare() {
    ListaMaterii lista;
    lista.nr_elemente = 0;
    lista.capacitate = 2;
    lista.materii = (MateriePrima*)malloc(lista.capacitate * sizeof(MateriePrima));
    return lista;
}


void eliberare(ListaMaterii* lista) {
    free(lista->materii);
    lista->materii = NULL;
    lista->nr_elemente = 0;
    lista->capacitate = 0;
}


void redimensionareCrestere(ListaMaterii* lista) {
    lista->capacitate *= 2;
    lista->materii = (MateriePrima*)realloc(lista->materii, lista->capacitate * sizeof(MateriePrima));
}


void redimensionareScadere(ListaMaterii* lista) {
    lista->capacitate /= 2;
    lista->materii = (MateriePrima*)realloc(lista->materii, lista->capacitate * sizeof(MateriePrima));
}


void adaugare(ListaMaterii* lista, MateriePrima m) {
    for (int i = 0; i < lista->nr_elemente; i++) {
        if (strcmp(lista->materii[i].nume, m.nume) == 0) {
            lista->materii[i].cantitate += m.cantitate;
            return;
        }
    }
    if (lista->nr_elemente == lista->capacitate) {
        redimensionareCrestere(lista);
    }

    lista->materii[lista->nr_elemente] = m;
    lista->nr_elemente += 1;
}


void modificare(ListaMaterii* lista, int index, MateriePrima m) {
    if (index >= 0 && index < lista->nr_elemente) {
        lista->materii[index] = m;
    }
}


void stergere(ListaMaterii* lista, int index) {
    for (int i = index; i < lista->nr_elemente - 1; i++) {
        lista->materii[i] = lista->materii[i + 1];
    }
    lista->nr_elemente--;

    if (lista->nr_elemente < lista->capacitate/4) {
        redimensionareScadere(lista);
    }
}
