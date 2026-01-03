#include "service.h"
#include <stdlib.h>
#include <string.h>

Service *creeaza_service() {
    Service *service = malloc(sizeof(Service));
    service->repo = creeaza_repo();
    service->undo_list = creeaza_lista();

    adauga_medicament(service, 1, "Paracetamol", 500.0, 20);
    adauga_medicament(service, 2, "Algocalmin", 250.0, 15);
    adauga_medicament(service, 3, "Ibuprofen", 200.0, 15);
    adauga_medicament(service, 4, "Nurofen", 400.0, 10);
    adauga_medicament(service, 5, "Aspirina", 100.0, 50);
    adauga_medicament(service, 6, "Panadol", 650.0, 12);
    adauga_medicament(service, 7, "Strepsils", 50.0, 25);
    adauga_medicament(service, 8, "D32000", 1000.0, 8);
    adauga_medicament(service, 9, "Lecitinpro", 750.0, 5);
    adauga_medicament(service, 10, "Supramax", 600.0, 18);

    return service;
}

void distruge_service(Service *service) {
    distruge_lista_de_liste(service->undo_list);
    distruge_repo(service->repo);
    free(service);
}

int adauga_medicament(Service *service, const int cod, const char *nume, const float conc, const int cant) {
    salveaza_undo(service);
    Medicament *m = creeaza_medicament(cod, nume, conc, cant);
    int rez = repo_adauga(service->repo, m);
    distruge_medicament(m); //??
    return rez;
}

int actualizeaza_medicament(Service *service, const int cod, const char *nume_nou, const float concentratie_noua) {
    salveaza_undo(service);
    return repo_actualizeaza(service->repo, cod, nume_nou, concentratie_noua);
}

int sterge_medicament(Service *service, const int cod) {
    salveaza_undo(service);
    return repo_sterge(service->repo, cod);
}

/*
  Interschimba medicamentele a si b.
*/
void interschimba(Medicament **a, Medicament **b) {
    Medicament *aux = *a;
    *a = *b;
    *b = aux;
}

/*
  Compara a si b dupa nume
  return -1 daca a < b
  return 0 daca a = b
  return 1 daca a > b
*/
int compara_nume(Medicament *a, Medicament *b) {
    return strcmp(get_nume(a), get_nume(b));
}

/*
  Compara a si b dupa cantitate
  return -1 daca a < b
  return 0 daca a = b
  return 1 daca a > b
*/
int compara_cantitate(Medicament *a, Medicament *b) {
    if (get_cantitate(a) < get_cantitate(b))
        return -1;
    if (get_cantitate(a) > get_cantitate(b))
        return 1;
    return 0;
}

int cmp_nume_crescator(Medicament *a, Medicament *b) {
    return compara_nume(a, b) <= 0; // a <= b -> 1
}

int cmp_nume_descrescator(Medicament *a, Medicament *b) {
    return compara_nume(a, b) >= 0; // a >= b -> 1
}

int cmp_cantitate_crescator(Medicament *a, Medicament *b) {
    return compara_cantitate(a, b) <= 0; // a <= b -> 1
}

int cmp_cantitate_descrescator(Medicament *a, Medicament *b) {
    return compara_cantitate(a, b) >= 0; // a >= b -> 1
}

/*
  Compara a si b dupa nume
  return -1 daca a < b
  return 0 daca a = b
  return 1 daca a > b
*/
ListaDinamica *sorteaza_medicamente(const Service *service, int (*cmp)(Medicament *, Medicament *)) {
    ListaDinamica *rez = creeaza_lista();
    int n = repo_dimensiune(service->repo);

    for (int i = 0; i < n; i++) {
        const Medicament *m = repo_get_medicament(service->repo, i);
        adauga_in_lista(rez, copiaza_medicament(m));
    }

    // direct selection sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            Medicament *a = rez->elems[i];
            Medicament *b = rez->elems[j];
            if (!cmp(a, b))
                interschimba((Medicament **) &rez->elems[i], (Medicament **) &rez->elems[j]); //inainte erau fara &
        }
    }
    return rez;
}

ListaDinamica *sorteaza_medicamente_criteriu(const Service *service, const int criteriu, const int ordine) {
    ListaDinamica *rez;
    if (criteriu == 1) {
        if (ordine == 1)
            rez = sorteaza_medicamente(service, cmp_nume_crescator);
        else
            rez = sorteaza_medicamente(service, cmp_nume_descrescator);
    } else {
        if (ordine == 1)
            rez = sorteaza_medicamente(service, cmp_cantitate_crescator);
        else
            rez = sorteaza_medicamente(service, cmp_cantitate_descrescator);
    }
    return rez;
}

ListaDinamica *filtreaza_dupa_stoc(const Service *service, int val) {
    ListaDinamica *rez = creeaza_lista();
    int n = repo_dimensiune(service->repo);
    for (int i = 0; i < n; i++) {
        Medicament *m = repo_get_medicament(service->repo, i);
        if (get_cantitate(m) < val) {
            adauga_in_lista(rez, copiaza_medicament(m));
        }
    }
    return rez;
}

ListaDinamica *filtreaza_dupa_litera(const Service *service, char litera) {
    ListaDinamica *rez = creeaza_lista();
    int n = repo_dimensiune(service->repo);
    for (int i = 0; i < n; i++) {
        Medicament *m = repo_get_medicament(service->repo, i);
        if (get_nume(m)[0] == litera) {
            adauga_in_lista(rez, copiaza_medicament(m));
        }
    }
    return rez;
}

ListaDinamica *filtreaza_dupa_concentratie(const Service *service, const float val) {
    ListaDinamica *rez = creeaza_lista();
    int n = repo_dimensiune(service->repo);
    for (int i = 0; i < n; ++i) {
        Medicament *m = repo_get_medicament(service->repo, i);
        if (get_concentratie(m) - val > 0) {
            adauga_in_lista(rez, copiaza_medicament(m));
        }
    }
    return rez;
}


void salveaza_undo(const Service *service) {
    ListaDinamica *copie = copiaza_lista(service->repo->lista, (CopyFunction) copiaza_medicament);
    adauga_in_lista(service->undo_list, copie);
}

int undo(Service *service) {
    if (dimensiune_lista(service->undo_list) <= 0)
        return 0;

    ListaDinamica *lista_trecuta = get_element_lista(service->undo_list, dimensiune_lista(service->undo_list) - 1);
    service->undo_list->lungime--;

    distruge_lista(service->repo->lista, distruge_medicament);
    service->repo->lista = lista_trecuta;

    repo_clear_lista_de_sters(service->repo);
    return 1;
}
