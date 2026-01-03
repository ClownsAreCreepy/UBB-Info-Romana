#include <stdio.h>
/*
  Scopul acestui typedef este sa facilitam schimbarea usoara
  a tipului elementelor din lista
*/
typedef int ElementType;
/*
Structura de date pentru lista
*/
typedef struct {
	int lg;
	ElementType elems[20];
} Vector;
/*
  Adauga element in capatul listei
  v- lista
  elem - elementul de adaugat
  pre: capacitatea totala alocata listei permite adaugarea
*/
void append(Vector* v, ElementType elem) {
	v->elems[v->lg] = elem;
	v->lg++;
}
/*
  Creaza o lista vida
  Asigura initializarea corecta a listei
*/
Vector creaza() {
	Vector rez;
	rez.lg = 0;
	return rez;
}
/*
  returneaza numarul de elemente in lista
*/
int len(Vector* v) {
	return v->lg;
}
/*
  returneaza elementul de pe pozitia data
  v - lista
  poz - pozitie in lista
  pre: poz este o pozitie valida in lista
*/
ElementType get(Vector* v, int poz) {
	return v->elems[poz];
}
/*
   Returneaza lista de cifre a numarului dat
   nr - numar, pre: nr>0
*/
Vector getCifre(int nr) {
	Vector rez = creaza();
	while (nr > 0) {
		int cifra = nr % 10;
		nr = nr / 10;
		append(&rez, cifra);
	}
	return rez;
}
/*
  Functie apelata la pornire pentru orice aplicatie C
*/
int main() {
	while (1)
	{
		printf("\n1 cifre\n0 Iesire\nDati comanda:");
		int cmd = 0;
		int nrCharRead = scanf("%d", &cmd);
		if (nrCharRead < 0) continue;
		if (cmd == 0) break;
		int nr = 0;
		nrCharRead = scanf("%d", &nr);
		if (nrCharRead < 0) continue;
		Vector cifre = getCifre(nr);
		printf("Numar cifre %d\n", len(&cifre));
		for (int i = 0; i < len(&cifre); i++) {
			printf("%d,", get(&cifre, i));
		}
	}
	return 0;
}