#include "materie_service.h"
#include <string.h>


void adaugare_validata(ListaMaterii *lista, MateriePrima m) {
    if (validare(m))
        adaugare(lista, m);
}


void modificare_validata(ListaMaterii* lista, int index, MateriePrima m) {
    if (validare(m) && index >= 0 && index < lista->nr_elemente)
        modificare(lista, index, m);
}


void stergere_validata(ListaMaterii* lista, int index) {
    if (index >= 0 && index <= lista->nr_elemente)
         stergere(lista, index);
}


ListaMaterii filtrare_dupa_nume(ListaMaterii lista, char litera) {
    ListaMaterii filtrata = creeare();
    for (int i = 0; i < lista.nr_elemente; i++) {
        if (lista.materii[i].nume[0] == litera) {
            adaugare(&filtrata, lista.materii[i]);
        }
    }
    return filtrata;
}


ListaMaterii filtrare_dupa_cantitate(ListaMaterii lista, int prag) {
    ListaMaterii filtrata = creeare();
    for (int i = 0; i < lista.nr_elemente; i++) {
        if (lista.materii[i].cantitate < prag) {
            adaugare(&filtrata, lista.materii[i]);
        }
    }
    return filtrata;
}


int cmpDupaNume(MateriePrima a, MateriePrima b) {
    return strcmp(a.nume, b.nume);
}



int cmpDupaCantitate(MateriePrima a, MateriePrima b) {
    return a.cantitate - b.cantitate;
}


void sortare(ListaMaterii* lista, Compare dupa_camp) {
    for (int i = 0; i < lista->nr_elemente - 1; i++)
        for (int j = i + 1; j < lista->nr_elemente; j++)
            if (dupa_camp(lista->materii[i], lista->materii[j])>0){
                MateriePrima temp = lista->materii[i];
                lista->materii[i] = lista->materii[j];
                lista->materii[j] = temp;
            }
}