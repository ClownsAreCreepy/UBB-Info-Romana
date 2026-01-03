#include "Colectie.h"
#include "IteratorColectie.h"
#include <iostream>
#include <stdexcept>

#define INITIAL_CAPACITY 2
#define ALPHA 0.7
#define BETA 0.3

using namespace std;


Colectie::Colectie() { //theta (1)

	//setam capacitatea
    capacitate = INITIAL_CAPACITY;

    //alocam spatiu de memorare pentru vectorul de pozitii
    Pozitii = new int[capacitate];

    //alocam spatiu de memorare pentru vectorul de elemente distincte
    Distincte = new TElem[capacitate];

    //setam numarul de elemente pentru ambii vectori
    dim_pozitii = 0;
    dim_distincte = 0;
}


void Colectie::redimensionare(int cap) { //theta(n)

  	//alocam un spatiu de capacitate dubla vectorilor
    int * poz_nou = new int[cap];
	TElem * dist_nou = new TElem[cap];

    //copiem vechile valori ale vectorilor in noile zone
    for (int i = 0; i < dim_pozitii; i++){
    	if(i<dim_distincte)
      		dist_nou[i] = Distincte[i];
    	poz_nou[i] = Pozitii[i];
    }

    //dublam capacitatea
    capacitate = cap;

    //eliberam vechile zone
    delete[] Pozitii;
    delete[] Distincte;

    //vectorii indica spre noile zone
    Pozitii = poz_nou;
    Distincte = dist_nou;
}


void Colectie::adauga(TElem elem) { //O(n)
	//daca s-a atins capacitatea maxima, redimensionam
    if(dim_pozitii >= ALPHA * capacitate)
      redimensionare(2 * capacitate);

    //cautam sa vedem daca elementul nou a mai aparut in colectie pana acum
    bool exista = false;
    int pozitie_elem = dim_distincte;
    for (int i = 0; i < dim_distincte && exista == false; ++i)
    	if (Distincte[i] == elem){
        	exista = true;
            pozitie_elem = i;
        }

    //daca elementul e distinct, il adaugam la finalul vectorul de elemente distincte
    if(!exista){
        Distincte[dim_distincte] = elem;
        dim_distincte ++;
    }

    //indiferent daca exista sau nu, introducem la finalul vectorului de pozitii pozitia corespunzatoare
    Pozitii[dim_pozitii] = pozitie_elem;
	dim_pozitii ++;
}


bool Colectie::sterge(TElem elem) { //theta(n)

	//Gasim prima aparitie în Pozitii + indexul în Distincte
	int pozitie_elem = -1;
	int indexP =-1;

	for (int i = 0; i < dim_pozitii; ++i) {
		if (Distincte[Pozitii[i]] == elem) {
			pozitie_elem = Pozitii[i];
			indexP = i;
			break;
		}
	}

	//Dacă nu am gasit elementul, returnam false
	if (indexP == -1)
		return false;

	//Verificam daca e singura aparitie
	bool singur = true;
	for (int i = 0; i < dim_pozitii && singur; ++i) {
		if (i != indexP && Pozitii[i] == pozitie_elem)
			singur = false;
	}

	//Stergem apariTia din Pozitii
	for (int i = indexP + 1; i < dim_pozitii; ++i)
		Pozitii[i - 1] = Pozitii[i];
	dim_pozitii --;

	//Daca era singura aparitie, stergem din Distincte
	if (singur) {
		for (int i = pozitie_elem + 1; i < dim_distincte; ++i)
			Distincte[i - 1] = Distincte[i];
		dim_distincte --;

		//Actualizam valorile din Pozitii
		for (int i = 0; i < dim_pozitii; ++i)
			if (Pozitii[i] > pozitie_elem)
				Pozitii[i] --;
	}

	//Redimensionam daca e cazul
	if (dim_pozitii <= BETA * capacitate && capacitate > INITIAL_CAPACITY)
		redimensionare(capacitate / 2);

	return true;
}

int Colectie::eliminaAparitii(int nr, TElem elem){ //theta(n)

	if (nr < 0)
		throw invalid_argument("Numarul de aparitii nu poate sa fie negativ! >:(");

	//iteram prin sir de la final, si contorizam numarul de aparitii ale elementului
	//memoram a nr-a pozitie a elementului de la finalul vectorului
	//daca gasim o aparitie, memoram pozitia elementului elem in vectorul de distincte
	//mergem pana gasim nr+1 aparitii, pentru a verifica daca elem mai are aparitii dupa ce le stergem pe astea

	int nr_aparitii = 0, pozitia_de_inceput = 0, pozitia_elem = -1;

	for (int i = dim_pozitii - 1; i >= 0 && nr_aparitii <= nr; --i) {
		if (Distincte[Pozitii[i]] == elem){
			nr_aparitii ++;
			pozitia_elem = Pozitii[i];
		}
		if (nr_aparitii == nr && pozitia_de_inceput == 0)
			pozitia_de_inceput = i;
	}

	//daca nu exista, iesim din functie
	if (pozitia_elem == -1)
		return 0;

	//Ștergem aparițiile din Pozitii
	int dim_noua = pozitia_de_inceput;
	for (int i = pozitia_de_inceput; i < dim_pozitii; ++i)
		if (Distincte[Pozitii[i]] != elem) {
			Pozitii[dim_noua] = Pozitii[i];
			dim_noua++;
		}
	dim_pozitii = dim_noua;

	//daca nr de aparitii e egal sau mai mic decat nr, atunci dupa ce stergem elementele, stergem si din vectorul de elementele distincte
	if (nr_aparitii <= nr) {
		for (int i = pozitia_elem + 1; i < dim_distincte; ++i)
			Distincte[i - 1] = Distincte[i];
		dim_distincte --;

		//Actualizăm valorile din Pozitii
		for (int i = 0; i < dim_pozitii; ++i)
			if (Pozitii[i] > pozitia_elem)
				Pozitii[i] --;
	}

	//Redimensionăm dacă e cazul
	while (dim_pozitii <= BETA * capacitate && capacitate > INITIAL_CAPACITY)
		redimensionare(capacitate / 2);

	if (nr_aparitii <= nr)
		return nr_aparitii;
	else
		return nr_aparitii - 1;
}

bool Colectie::cauta(TElem elem) const { //O(n)
	//cautam in vectorul de distincte daca exista un element
    for(int i=0; i < dim_distincte; ++i)
        if(Distincte[i] == elem)
            return true;

    //daca am iesit cu totul din for, atunci elementul nu exista
	return false;
}

int Colectie::nrAparitii(TElem elem) const { //theta(n)

	//cautam in vectorul de pozitii de cate ori apare elementul
    int freq = 0;
    for (int i=0; i < dim_pozitii; ++i)
    	if(Distincte[Pozitii[i]] == elem)
          	freq ++;

    return freq;
}


int Colectie::dim() const { //theta(1)

	//returnam dimensiunea vectorului
    return dim_pozitii;
}


bool Colectie::vida() const { //theta(1)

	if (dim_pozitii != 0)
          return false;
	return true;
}

IteratorColectie Colectie::iterator() const { //theta(1)

	return  IteratorColectie(*this);
}


Colectie::~Colectie() { //theta(1)

	//eliberam zona de memorare alocata vectorilor
    delete[] Pozitii;
    delete[] Distincte;

    //prevenim dangling pointer
    Pozitii = nullptr;
    Distincte = nullptr;
}


