#include <stdio.h>
#include <string.h>
#include "service.h"
#include "consola.h"
#include "lista_dinamica.h"

void ui_afiseaza_meniu() {
  printf("\n");
  printf("Alege una dintre urmatoarele optiuni:\n");
  printf("0 - Iesire\n");
  printf("1 - Adauga medicament\n");
  printf("2 - Actualizeaza medicament\n");
  printf("3 - Sterge medicament\n");
  printf("4 - Afiseaza medicamente sortate\n");
  printf("5 - Filtreaza dupa stoc\n");
  printf("6 - Filtreaza dupa prima litera\n");
  printf("7 - Filtreaza dupa concentratie\n");
  printf("8 - Refa ultima operatie\n");
}

int citeste_int(const char* mesaj) {
  char buffer[64];
  int val;
  while (1) {
    printf("%s", mesaj);
    if (!fgets(buffer, sizeof(buffer), stdin))
      continue;
    if (sscanf(buffer, "%d", &val) == 1)
      return val;
    printf("VALOARE INVALIDA!\n");
  }
}

float citeste_float(const char* mesaj) {
  char buffer[64];
  float val;
  while (1) {
    printf("%s", mesaj);
    if (!fgets(buffer, sizeof(buffer), stdin))
      continue;
    if (sscanf(buffer, "%f", &val) == 1)
      return val;
    printf("VALOARE INVALIDA!\n");
  }
}

void citeste_sir(const char* mesaj, char* dest, int size) {
  while (1) {
    printf("%s", mesaj);
    if (!fgets(dest, size, stdin))
      continue;
    int lung = strlen(dest);
    if (lung > 0 && dest[lung - 1] == '\n')
      dest[lung - 1] = 0;
    if (strlen(dest) == 0)
      printf("SIR INVALID!\n");
    else
      break;
  }
}

/*
 Afiseaza lista
*/
void ui_afiseaza_lista(ListaDinamica* lista) {
  for (int i = 0; i <dimensiune_lista(lista); ++i) {
    Medicament* m=get_element_lista(lista,i);
    printf("<%d>: %s, %.2f%%, Cantitate: %d\n", m->cod, m->nume, m->concentratie, m->cantitate);
  }
}

/*
  Adauga medicament. Daca exista cod, creste cantitatea.
*/
void ui_adauga_medicament(Service* service) {
  int cod = citeste_int("Cod: ");
  char nume[50];
  citeste_sir("Nume: ", nume, 50);
  float concentratie = citeste_float("Concentratie: ");
  int cantitate = citeste_int("Cantitate: ");
  int rez = adauga_medicament(service, cod, nume, concentratie, cantitate);
  if (rez == 1) {
    printf("Medicament adaugat.\n");
  } else if (rez == 2) {
    printf("Medicament existent. Cantitate adaugata.\n");
  } else {
    printf("SPATIU INSUFICIENT!\n");
  }
}

/*
  Actualizeaza medicament (nume, concentratie) dupa cod.
*/
void ui_actualizeaza_medicament(Service* service) {
  int cod = citeste_int("Cod: ");
  char nume_nou[50];
  citeste_sir("Nume nou: ", nume_nou, 50);
  float concentratie_noua = citeste_float("Concentratie noua: ");
  int rez = actualizeaza_medicament(service, cod, nume_nou, concentratie_noua);
  if (rez == 1) {
    printf("Medicament actualizat.\n");
  } else {
    printf("MEDICAMENT INEXISTENT!\n");
  }
}

/*
  Sterge medicament dupa cod si afiseaza lista de elemente sterse
*/
void ui_sterge_medicament(Service* service) {
  int cod = citeste_int("Cod: ");
  int rez = sterge_medicament(service, cod);
  if (rez == 1) {
    printf("Medicament sters.\n");
  } else {
    printf("MEDICAMENT INEXISTENT!\n");
  }

  printf("Medicamente sterse: \n");
  ListaDinamica* lista = repo_get_lista_de_sters(service->repo);
  ui_afiseaza_lista(lista);
}

/*
  Sorteaza medicamentele dupa un criteriu (1 - nume, 2 - cantitate),
  intr-o ordine (1 - crescator, 2 - descrescator).
*/
void ui_sorteaza_medicamente_criteriu(Service* service) {
  int criteriu = citeste_int("Criteriu (1-nume, 2-cantitate): ");
  int ordine = citeste_int("Ordine (1-cresc, 2-desc): ");
  ListaDinamica* lista = sorteaza_medicamente_criteriu(service, criteriu, ordine);
  ui_afiseaza_lista(lista);
  distruge_lista(lista, distruge_medicament);
}

/*
  Filtreaza medicamentele cu stoc < val data.
*/
void ui_filtreaza_dupa_stoc(Service* service) {
  int val = citeste_int("Valoare stoc: ");
  ListaDinamica* lista = filtreaza_dupa_stoc(service, val);
  ui_afiseaza_lista(lista);
  distruge_lista(lista, distruge_medicament);
}

/*
  Filtreaza medicamentele al caror nume incepe cu litera data.
  Returneaza o lista noua.
*/
void ui_filtreaza_dupa_litera(Service* service) {
  char buf[10];
  citeste_sir("Litera: ", buf, 10);
  char lit = buf[0];
  ListaDinamica* lista = filtreaza_dupa_litera(service, lit);
  ui_afiseaza_lista(lista);
  distruge_lista(lista,distruge_medicament);
}

/*
 Filtreaza medicamentele ale caror cantitai sunt mai mari decat procentul dat.
 Returneaza o lista noua.
*/
void ui_filtreaza_dupa_concentratie(Service* service) {
  float val = citeste_float("Valoare procent: ");
  ListaDinamica* lista = filtreaza_dupa_concentratie(service,val);
  ui_afiseaza_lista(lista);
  distruge_lista(lista,distruge_medicament);
}

void ui_undo(Service* service) {
  int rez = undo(service);
  if (rez) {
    printf("Undo efectutat cu succes\n");
  } else {
    printf("Nu mai exista operatii de undo\n");
  }
}


void ui_ruleaza_aplicatie() {
  Service* service = creeaza_service();
  int ok = 1;
  while (ok) {
    ui_afiseaza_meniu();
    int cmd = citeste_int("Optiune: ");
    switch (cmd) {
      case 0: ok = 0; break;
      case 1: ui_adauga_medicament(service); break;
      case 2: ui_actualizeaza_medicament(service); break;
      case 3: ui_sterge_medicament(service); break;
      case 4: ui_sorteaza_medicamente_criteriu(service); break;
      case 5: ui_filtreaza_dupa_stoc(service); break;
      case 6: ui_filtreaza_dupa_litera(service); break;
      case 7: ui_filtreaza_dupa_concentratie(service); break;
      case 8: ui_undo(service); break;
      default: printf("OPTIUNE INVALIDA!\n"); break;
    }
  }
  distruge_service(service);
}