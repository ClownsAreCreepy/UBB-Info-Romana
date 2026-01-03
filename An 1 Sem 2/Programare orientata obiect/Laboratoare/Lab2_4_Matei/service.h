#pragma once
#include "repo.h"

/*
  Service contine un Repo si ofera operatii pe medicamente.
*/
typedef struct {
  Repo* repo;
  ListaDinamica* undo_list;
} Service;

/*
  Creeaza service si adauga 10 medicamente initiale.
*/
Service* creeaza_service();

/*
  Distruge service.
*/
void distruge_service(Service* service);

/*
  Adauga medicament. Daca exista deja codul, actualizeaza cantitatea.
  return 1, adaugare noua
  return 2, actualizare cantitate
*/
int adauga_medicament(Service* service,const int cod,const char* nume,const float conc,const int cant);

/*
  Actualizeaza nume si concentratie.
  Returneaza 1 daca reuseste, 0 daca nu exista.
*/
int actualizeaza_medicament(Service* service,const int cod,const char* nume_nou,const float concentratie_noua);

/*
  Sterge medicament dupa cod.
  Returneaza 1 daca reuseste, 0 daca nu exista.
*/
int sterge_medicament(Service* service,const int cod);

/*
  Compara a si b dupa nume
  return -1 daca a < b
  return 0 daca a = b
  return 1 daca a > b
*/
int compara_nume(Medicament* a, Medicament* b);

/*
  Compara a si b dupa cantitate
  return -1 daca a < b
  return 0 daca a = b
  return 1 daca a > b
*/
int compara_cantitate(Medicament* a, Medicament* b);

/*
  Returneaza 1 daca a este inaintea lui b in ordinea numelui, 0 altfel.
*/
int cmp_nume_crescator(Medicament* a, Medicament* b);

/*
  Returneaza 1 daca a dupa b in ordinea numelui, 0 altfel.
*/
int cmp_nume_descrescator( Medicament* a, Medicament* b);

/*
  Returneaza 1 daca a este inaintea lui b in ordinea cantitatii, 0 altfel.
*/
int cmp_cantitate_crescator( Medicament* a, Medicament* b);

/*
  Returneaza 1 daca a dupa b in ordinea cantitatii, 0 altfel.
*/
int cmp_cantitate_descrescator( Medicament* a, Medicament* b);

/*
  Sorteaza medicamentele dupa un criteriu stabilit de functia cmp din apel.
  Returneaza functia sortata.
*/
ListaDinamica* sorteaza_medicamente(const Service* service, int (*cmp)(Medicament*, Medicament*));

/*
  Sorteaza medicamentele dupa un criteriu (1 - nume, 2 - cantitate),
  intr-o ordine (1 - crescator, 2 - descrescator).
  Returneaza functia sortata.
*/
ListaDinamica* sorteaza_medicamente_criteriu(const Service* service,const int criteriu,const int ordine);

/*
  Filtreaza medicamentele cu stoc < val data.
  Returneaza o lista noua.
*/
ListaDinamica* filtreaza_dupa_stoc(const Service* service,const int val);

/*
  Filtreaza medicamentele al caror nume incepe cu litera data.
  Returneaza o lista noua.
*/
ListaDinamica* filtreaza_dupa_litera(const Service* service,const char litera);

/*
 Filtreaza medicamentele ale caror concentratii sunt mai mari decat un procent dat.
 Returneaza o lista noua
 */
ListaDinamica* filtreaza_dupa_concentratie(const Service* service,const float val);

/*
 Salveaza in lista de undo lista curenta de medicamente
*/
void salveaza_undo(const Service* service);

/*
 Restabileste lista la o iteratie anterioara
*/
int undo(Service* service);