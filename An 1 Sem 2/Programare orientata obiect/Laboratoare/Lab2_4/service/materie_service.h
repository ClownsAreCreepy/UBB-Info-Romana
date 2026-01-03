#ifndef MATERIE_SERVICE_H
#define MATERIE_SERVICE_H

#include "../repository/lista_materii.h"

/**
 * Tip nou de data pentru a folosi o functie care compara doua aspecte a doua materii
 */
typedef int (*Compare)(MateriePrima, MateriePrima);


/**
 * Functia adauga o noua materie prima in lista, sau mareste cantitatea unei materii prime deja existente, daca materia e valida
 * @param lista o lista de materii
 * @param m o materie prima
 */
void adaugare_validata(ListaMaterii* lista, MateriePrima m);


/**
 * Functia modifica o materie prima existenta in ea, daca materia e valida si daca exista o materie de acel index
 * @param lista o lista de materii
 * @param index un identificator pentru materii
 * @param m o materie prima
 */
void modificare_validata(ListaMaterii* lista, int index, MateriePrima m);


/**
 * Functia sterge o materie din lista, daca exista o materie de acel index
 * @param lista o lista de materii
 * @param index un identificator pentru materii
 */
void stergere_validata(ListaMaterii* lista, int index);


/**
 * Functia returneaza o lista de materii filtrata, astfel incat sunt afisate doar materiile ale caror nume incep cu litera litera
 * @param lista o lista de materii
 * @param litera litera dupa care se realizeaza filtrarea
 * @return lista filtrata
 */
ListaMaterii filtrare_dupa_nume(ListaMaterii lista, char litera);


/**
 * Functia returneaza o lista de materii filtrata, astfel incat sunt afisate doar materiile ale caror cantitati sunt mai mici decat numarul prag
 * @param lista o lista de materii
 * @param prag numarul dupa care se face filtrarea
 * @return lista filtrata
 */
ListaMaterii filtrare_dupa_cantitate(ListaMaterii lista, int prag);


/**
 * Functia compara alfabetic numele a doua materii
 * @param a o materie prima
 * @param b o materie prima
 * @return diferenta lexicala dintre numele materiilor
 */
int cmpDupaNume(MateriePrima a, MateriePrima b);


/**
 * Functia compara numeric cantitatiile a doua materii
 * @param a o materie prima
 * @param b o materie prima
 * @return diferenta dintre cantitatile materiilor
 */
int cmpDupaCantitate(MateriePrima a, MateriePrima b);


/**
 * Functia returneaza o lista de materii sortata crescator dupa un criteriu
 * @param lista o lista de materii
 * @param dupa_camp un numar, reprezentand criteriul dupa care se face sortarea (1 pentru nume, 2 pentru cantitate)
 * @return lista sortata
 */
void sortare(ListaMaterii* lista, Compare dupa_camp);


#endif
