#include <stdlib.h>
#include <string.h>
#include "medicament.h"

Medicament* creeaza_medicament(const int cod, const char* nume,const float conc,const int cant) {
  Medicament* m = malloc(sizeof(Medicament));
  m->cod = cod;
  m->nume=malloc(strlen(nume)+1);
  strcpy(m->nume,nume);
  m->concentratie = conc;
  m->cantitate = cant;
  return m;
}

void* distruge_medicament(void* m) {
  Medicament* med = m;
  if (med == NULL) return NULL;
  free(med->nume);
  free(med);
  return NULL;
}

int get_cod(const Medicament* m) {
  return m->cod;
}

char* get_nume(const Medicament* m) {
  return m->nume;
}

float get_concentratie(const Medicament* m) {
  return m->concentratie;
}

int get_cantitate(const Medicament* m) {
  return m->cantitate;
}

void set_nume(Medicament* m,const char* nume_nou) {
  if (m == NULL || m->nume == NULL) return;
  free(m->nume);
  m->nume=malloc((strlen(nume_nou) + 1));
  strcpy(m->nume,nume_nou);
}

void set_concentratie(Medicament* m,const float concentratie_noua) {
  m->concentratie = concentratie_noua;
}

void set_cantitate(Medicament* m,const int cantitate_noua) {
  m->cantitate = cantitate_noua;
}

Medicament* copiaza_medicament(const Medicament* m) {
  if (m==NULL) return NULL;
  return creeaza_medicament(m->cod, m->nume, m->concentratie, m->cantitate);
}