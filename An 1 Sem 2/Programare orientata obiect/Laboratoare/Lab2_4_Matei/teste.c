#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "teste.h"
#include "repo.h"
#include "service.h"
#include "lista_dinamica.h"

void test_creeaza_distruge_repo() {
  Repo* repo = creeaza_repo();
  assert(repo_dimensiune(repo) == 0);
  distruge_repo(repo);
}

void test_repo_adauga() {
  Repo* repo = creeaza_repo();
  Medicament* m1 = creeaza_medicament(101, "M", 100.0, 5);
  int r = repo_adauga(repo, m1);
  assert(r == 1);
  assert(repo_dimensiune(repo) == 1);
  Medicament* m1_extra = creeaza_medicament(101, "X", 50.0, 3);
  r = repo_adauga(repo, m1_extra);
  assert(r == 2);
  assert(repo_dimensiune(repo) == 1);

  distruge_repo(repo);
  distruge_medicament(m1);
  distruge_medicament(m1_extra);
}

void test_repo_actualizeaza() {
  Repo* repo = creeaza_repo();
  Medicament* m = creeaza_medicament(100, "Test", 123.0, 10);
  repo_adauga(repo, m);
  int r = repo_actualizeaza(repo, 100, "NumeNou", 999.0);
  assert(r == 1);
  r = repo_actualizeaza(repo, 999, "X", 1.0);
  assert(r == 0);

  distruge_repo(repo);
  distruge_medicament(m);
}

void test_repo_sterge() {
  Repo* repo = creeaza_repo();
  Medicament* m = creeaza_medicament(111, "A", 1.0, 1);
  ListaDinamica* lista = creeaza_lista();
  assert(sterge_din_lista(lista, -1, distruge_medicament) == 0);
  distruge_lista(lista, distruge_medicament);
  repo_adauga(repo, m);
  int r = repo_sterge(repo, 111);
  assert(r == 1);
  r = repo_sterge(repo, 111);
  assert(r == 0);
  distruge_repo(repo);
  distruge_medicament(m);
}

void test_gaseste_medicament() {
  Repo* repo = creeaza_repo();
  Medicament* m = creeaza_medicament(101, "M", 100.0, 5);
  repo_adauga(repo, m);
  int idx = gaseste_medicament(repo, 101);
  assert(idx == 0);
  idx = gaseste_medicament(repo, 999);
  assert(idx == -1);
  distruge_repo(repo);
  distruge_medicament(m);
}

void test_repo_dimensiune() {
  Repo* repo = creeaza_repo();
  assert(repo_dimensiune(repo) == 0);
  Medicament* m1 = creeaza_medicament(11, "X", 1.0, 1);
  Medicament* m2 = creeaza_medicament(12, "Y", 2.0, 2);
  repo_adauga(repo, m1);
  repo_adauga(repo, m2);
  assert(repo_dimensiune(repo) == 2);
  distruge_repo(repo);
  distruge_medicament(m1);
  distruge_medicament(m2);
}

void test_repo_get_medicament() {
  Repo* repo = creeaza_repo();
  Medicament* m = creeaza_medicament(11, "AA", 100.0, 2);
  repo_adauga(repo, m);
  Medicament* x = repo_get_medicament(repo, 0);
  assert(x->cod == 11);
  distruge_repo(repo);
  distruge_medicament(m);
}

void test_lista_medicamente_sterse() {
  Service* service = creeaza_service();

  // initial count = 10
  assert(repo_dimensiune(service->repo) == 10);
  assert(dimensiune_lista(repo_get_lista_de_sters(service->repo)) == 0);

  // delete med #1
  int rez1 = sterge_medicament(service, 1);
  assert(rez1 == 1);
  assert(repo_dimensiune(service->repo) == 9);
  assert(dimensiune_lista(repo_get_lista_de_sters(service->repo)) == 1);

  distruge_service(service);
}


void test_creeaza_distruge_service() {
  Service* service = creeaza_service();
  assert(repo_dimensiune(service->repo) == 10);
  distruge_service(service);
}

void test_adauga_medicament() {
  Service* service = creeaza_service();
  int r = adauga_medicament(service, 1, "Paracetamol", 500.0, 5);
  assert(r == 2);
  r = adauga_medicament(service, 15, "X", 100.0, 3);
  assert(r == 1);
  distruge_service(service);
}

void test_actualizeaza_medicament() {
  Service* service = creeaza_service();
  int r = actualizeaza_medicament(service, 2, "Algocalmin", 123.0);
  assert(r == 1);
  r = actualizeaza_medicament(service, 999, "X", 1.0);
  assert(r == 0);
  distruge_service(service);
}

void test_sterge_medicament() {
  Service* service = creeaza_service();
  int r = sterge_medicament(service, 3);
  assert(r == 1);
  r = sterge_medicament(service, 3);
  assert(r == 0);
  distruge_service(service);
}

void test_comparatoare_nume() {
  Medicament* a = creeaza_medicament(1, "Aspirina", 100.0, 10);
  Medicament* b = creeaza_medicament(2, "Paracetamol", 200.0, 20);

  assert(compara_nume(a, b) < 0);
  assert(compara_nume(b, a) > 0);
  assert(compara_nume(a, a) == 0);

  assert(cmp_nume_crescator(a, b) == 1);
  assert(cmp_nume_crescator(b, a) == 0);
  assert(cmp_nume_descrescator(a, b) == 0);
  assert(cmp_nume_descrescator(b, a) == 1);
  assert(cmp_nume_descrescator(a, a) == 1);

  distruge_medicament(a);
  distruge_medicament(b);
}

void test_comparatoare_cantitate() {
  Medicament* a = creeaza_medicament(1, "X", 100.0, 5);
  Medicament* b = creeaza_medicament(2, "Y", 200.0, 10);

  assert(compara_cantitate(a, b) < 0);
  assert(compara_cantitate(b, a) > 0);
  assert(compara_cantitate(a, a) == 0);

  assert(cmp_cantitate_crescator(a, b) == 1);
  assert(cmp_cantitate_crescator(b, a) == 0);
  assert(cmp_cantitate_descrescator(a, b) == 0);
  assert(cmp_cantitate_descrescator(b, a) == 1);
  assert(cmp_cantitate_descrescator(a, a) == 1);

  distruge_medicament(a);
  distruge_medicament(b);
}

void test_sorteaza_medicamente() {
  Service* service = creeaza_service();

  ListaDinamica* s1 = sorteaza_medicamente_criteriu(service, 1, 1);
  for (int i = 0; i < dimensiune_lista(s1) - 1; i++) {
    Medicament* a = get_element_lista(s1, i);
    Medicament* b = get_element_lista(s1, i + 1);
    assert(cmp_nume_crescator(a, b));
  }
  distruge_lista(s1, distruge_medicament);

  ListaDinamica* s2 = sorteaza_medicamente_criteriu(service, 1, 2);
  for (int i = 0; i < dimensiune_lista(s2) - 1; i++) {
    Medicament* a = get_element_lista(s2, i);
    Medicament* b = get_element_lista(s2, i + 1);
    assert(cmp_nume_descrescator(a, b));
  }
  distruge_lista(s2, distruge_medicament);

  ListaDinamica* s3 = sorteaza_medicamente_criteriu(service, 2, 1);
  for (int i = 0; i < dimensiune_lista(s3) - 1; i++) {
    Medicament* a = get_element_lista(s3, i);
    Medicament* b = get_element_lista(s3, i + 1);
    assert(cmp_cantitate_crescator(a, b));
  }
  distruge_lista(s3, distruge_medicament);

  ListaDinamica* s4 = sorteaza_medicamente_criteriu(service, 2, 2);
  for (int i = 0; i < dimensiune_lista(s4) - 1; i++) {
    Medicament* a = get_element_lista(s4, i);
    Medicament* b = get_element_lista(s4, i + 1);
    assert(cmp_cantitate_descrescator(a, b));
  }
  distruge_lista(s4, distruge_medicament);

  distruge_service(service);
}

void test_filtreaza_dupa_stoc() {
  Service* service = creeaza_service();
  ListaDinamica* rez = filtreaza_dupa_stoc(service, 10);
  for (int i = 0; i < dimensiune_lista(rez); i++) {
    Medicament* m = rez->elems[i];
    assert(get_cantitate(m) < 10);
  }
  distruge_lista(rez, distruge_medicament);
  distruge_service(service);
}

void test_filtreaza_dupa_litera() {
  Service* service = creeaza_service();
  ListaDinamica* rez = filtreaza_dupa_litera(service, 'A');
  for (int i = 0; i < dimensiune_lista(rez); i++) {
    Medicament* m = rez->elems[i];
    assert(get_nume(m)[0] == 'A');
  }
  distruge_lista(rez, distruge_medicament);
  distruge_service(service);
}

void test_filtreaza_dupa_concentratie() {
  Service* service = creeaza_service();
  ListaDinamica* rez = filtreaza_dupa_concentratie(service, 500.0);
  for (int i = 0; i < dimensiune_lista(rez); i++) {
    Medicament* m = rez->elems[i];
    assert(get_concentratie(m) > 500.0);
  }
  distruge_lista(rez, distruge_medicament);
  distruge_service(service);
}

void test_undo() {
  Service* service = creeaza_service();
  assert(repo_dimensiune(service->repo) == 10);

  adauga_medicament(service, 999, "UndoTest", 10.5, 3);
  assert(repo_dimensiune(service->repo) == 11);
  assert(undo(service) == 1);
  assert(repo_dimensiune(service->repo) == 10);

  sterge_medicament(service, 1);
  assert(repo_dimensiune(service->repo) == 9);
  assert(undo(service) == 1);
  assert(repo_dimensiune(service->repo) == 10);

  actualizeaza_medicament(service, 2, "UpdatedMed", 1337.0);
  Medicament* m = repo_get_medicament(service->repo, 1);
  assert(strcmp(get_nume(m), "UpdatedMed") == 0);
  assert(undo(service) == 1);
  m = repo_get_medicament(service->repo, 1);
  assert(strcmp(get_nume(m), "Algocalmin") == 0);

  // clean up everything else
  while (undo(service));
  assert(undo(service) == 0);

  distruge_service(service);
}

void ruleaza_toate_testele() {
  test_creeaza_distruge_repo();
  test_repo_adauga();
  test_repo_actualizeaza();
  test_repo_sterge();
  test_gaseste_medicament();
  test_repo_dimensiune();
  test_repo_get_medicament();
  test_lista_medicamente_sterse();

  test_creeaza_distruge_service();
  test_adauga_medicament();
  test_actualizeaza_medicament();
  test_sterge_medicament();
  test_comparatoare_nume();
  test_comparatoare_cantitate();
  test_sorteaza_medicamente();
  test_filtreaza_dupa_stoc();
  test_filtreaza_dupa_litera();
  test_filtreaza_dupa_concentratie();
  test_undo();
}