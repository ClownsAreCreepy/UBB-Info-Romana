#pragma once
#include "lista_dinamica.h"

/*
  Repo contine o lista statica de Medicament*.
*/
typedef struct {
  ListaDinamica* lista;
  ListaDinamica* medicamente_sterse;
} Repo;

/*
  Creeaza repo.
*/
Repo* creeaza_repo();

/*
  Distruge repo.
*/
void distruge_repo(Repo* repo);

/*
  Cauta medicament dupa cod, returneaza index sau -1.
*/
int gaseste_medicament(const Repo* repo,const int cod);

/*
  Adauga medicament. Daca exista deja codul, actualizeaza cantitatea.
  return 1, adaugare noua
  return 2, actualizare cantitate
*/
int repo_adauga(Repo* repo,const Medicament* m);

/*
  Actualizeaza nume si concentratie.
  Returneaza 1 daca reuseste, 0 daca nu exista.
*/
int repo_actualizeaza(Repo* repo,const int cod,const char* nume_nou,const float concentratie_noua);

/*
  Sterge medicament dupa cod.
  Returneaza 1 daca reuseste, 0 daca nu exista.
*/
int repo_sterge(Repo* repo,const int cod);

/*
  Returneaza dimensiunea repo-ului.
*/
int repo_dimensiune(const Repo* repo);

/*
  Returneaza medicamentul de la index.
*/
Medicament* repo_get_medicament(const Repo* repo,const int index);

/*
 Returneaza lista de elemente sterse
*/
ListaDinamica* repo_get_lista_de_sters(Repo* repo);

/*
 Sterge din lista de elemente sterse
*/
void repo_clear_lista_de_sters(Repo* repo);