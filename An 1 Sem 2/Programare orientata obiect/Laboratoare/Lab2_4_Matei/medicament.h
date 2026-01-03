#pragma once

/*
  Structura Medicament retine cod, nume, concentratie, cantitate.
*/
typedef struct {
  int cod;
  char* nume;
  float concentratie;
  int cantitate;
} Medicament;

/*
  Creeaza un medicament pe heap.
*/
Medicament* creeaza_medicament(const int cod, const char* nume,const float conc,const int cant);

/*
  Distruge un medicament alocat dinamic.
*/
void* distruge_medicament(void* m);

/*
  Returneaza codul medicamentului.
*/
int get_cod(const Medicament* m);

/*
  Returneaza numele medicamentului.
*/
char* get_nume(const Medicament* m);

/*
  Returneaza concentratia medicamentului.
*/
float get_concentratie(const Medicament* m);

/*
  Returneaza cantitatea medicamentului.
*/
int get_cantitate(const Medicament* m);

/*
  Seteaza numele medicamentului.
*/
void set_nume(Medicament* m,const char* nume_nou);

/*
  Seteaza concentratia medicamentului.
*/
void set_concentratie(Medicament* m,const float concentratie_noua);

/*
  Seteaza cantitatea medicamentului.
*/
void set_cantitate(Medicament* m,const int cantitate_noua);

/*
 Creeaza o copie a unui medicament
*/
Medicament* copiaza_medicament(const Medicament* m);