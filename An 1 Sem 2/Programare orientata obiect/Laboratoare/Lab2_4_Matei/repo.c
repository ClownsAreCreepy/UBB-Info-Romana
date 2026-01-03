#include <stdlib.h>
#include "repo.h"

Repo* creeaza_repo() {
  Repo* repo = malloc(sizeof(Repo));
  repo->lista = creeaza_lista();
  repo->medicamente_sterse = creeaza_lista();
  return repo;
}

void distruge_repo(Repo* repo) {
  if (repo == NULL) return;
  distruge_lista(repo->lista,distruge_medicament);
  distruge_lista(repo->medicamente_sterse, distruge_medicament);
  free(repo);
}

int gaseste_medicament(const Repo* repo,const int cod) {
  for (int i = 0; i < dimensiune_lista(repo->lista); i++) {
    const Medicament* m = get_element_lista(repo->lista, i);
    if (get_cod(m) == cod)
      return i;
  }
  return -1;
}

int repo_adauga(Repo* repo,const Medicament* m) {
  int const index = gaseste_medicament(repo, get_cod(m));
  if (index == -1) {
    adauga_in_lista(repo->lista, copiaza_medicament(m));
    return 1;
  } else {
    Medicament* existent = get_element_lista(repo->lista, index);
    int cantitate_noua = get_cantitate(existent) + get_cantitate(m);
    set_cantitate(existent, cantitate_noua);
    return 2;
  }
}

int repo_actualizeaza(Repo* repo,const int cod,const char* nume_nou,const float concentratie_noua) {
  const int index = gaseste_medicament(repo, cod);
  if (index == -1)
    return 0;

  Medicament* m = get_element_lista(repo->lista, index);
  set_nume(m, nume_nou);
  set_concentratie(m, concentratie_noua);
  return 1;
}

int repo_sterge(Repo* repo,const int cod) {
  int index = gaseste_medicament(repo, cod);
  if (index == -1)
    return 0;
  Medicament* m = get_element_lista(repo->lista, index);
  Medicament* copie = copiaza_medicament(m);
  adauga_in_lista(repo->medicamente_sterse, copie);

  return sterge_din_lista(repo->lista, index, distruge_medicament);
}

int repo_dimensiune(const Repo* repo) {
  return dimensiune_lista(repo->lista);
}

Medicament* repo_get_medicament(const Repo* repo,const int index) {
  return get_element_lista(repo->lista, index);
}

ListaDinamica* repo_get_lista_de_sters(Repo* repo) {
  return repo->medicamente_sterse;
}

void repo_clear_lista_de_sters(Repo* repo) {
  if (dimensiune_lista(repo->medicamente_sterse) >0)
    sterge_din_lista(repo->medicamente_sterse, dimensiune_lista(repo->medicamente_sterse) - 1, distruge_medicament);
}