#include "MD.h"
#include "IteratorMD.h"

using namespace std;

//(n - nr total al valorilor de la toate cheile ; c - nr total de chei)

MD::MD() { //O(1)
	cap = nullptr;
	dimensiune = 0;
}


void MD::adauga(TCheie c, TValoare v) { //O(c)
	NodCheie* curent = cap;

	//cautam sa vedem daca cheia exista
	while (curent != nullptr && curent->cheie != c)
		curent = curent->urmator;

	//Daca nodul nu exista, il creem
	if (curent == nullptr) {
		NodCheie* cheie_noua = new NodCheie(c);
		cheie_noua->urmator = cap;
		cap = cheie_noua;
		curent = cheie_noua;
	}

	//Adaugam valoarea de la cap la lista de valori
	NodValoare* valoare_noua = new NodValoare(v, curent->cap_valori);
	curent->cap_valori = valoare_noua;

	dimensiune++;
}


bool MD::sterge(TCheie c, TValoare v) { //O(c+n)
	NodCheie* cheie_curenta = cap;
	NodCheie* cheie_anterioara = nullptr;

	//Cautam sa vedem daca exista cheia si tinem minte pozitia si cheia de dinainte
	while (cheie_curenta != nullptr && cheie_curenta->cheie != c) {
		cheie_anterioara = cheie_curenta;
		cheie_curenta = cheie_curenta->urmator;
	}

	//daca nu exista, e foarte bine si gatam
	if (cheie_curenta == nullptr)
		return false;


	//facem aceeasi chestie, dar pentru valoare
	NodValoare* valoare_curenta = cheie_curenta->cap_valori;
	NodValoare* valoare_anterioara = nullptr;

	while (valoare_curenta != nullptr && valoare_curenta->valoare != v) {
		valoare_anterioara = valoare_curenta;
		valoare_curenta = valoare_curenta->urmator;
	}

	if (valoare_curenta == nullptr)
		return false;

	//eliminam nodul de valoare
	if (valoare_anterioara == nullptr)
		//daca capul de vectorul valoare e gol, inseamna ca valoarea pe care o stergem e cea din cap, deci bagam urmatoru in cap
		cheie_curenta->cap_valori = valoare_curenta->urmator;
	else
		//daca valoarea e pe undeva prin vector, doar sarim peste ea cu urmator
		valoare_anterioara->urmator = valoare_curenta->urmator;

	delete valoare_curenta;
	dimensiune --;

	//Daca nu mai sunt valori, stergem nodul cheie
	if (cheie_curenta->cap_valori == nullptr) {
		if (cheie_anterioara == nullptr)
			cap = cheie_curenta->urmator;
		else
			cheie_anterioara->urmator=cheie_curenta->urmator;
		delete cheie_curenta;
	}

	return true;
}


vector<TValoare> MD::cauta(TCheie c) const { //O(c+n)
	vector<TValoare> resultat;
	NodCheie* curent = cap;

	while (curent != nullptr) {
		if (curent->cheie == c) {
			NodValoare* valoare = curent->cap_valori;
			while (valoare != nullptr) {
				resultat.push_back(valoare->valoare);
				valoare = valoare->urmator;
			}
			break;
		}
		curent = curent->urmator;
	}
	return resultat;
}


int MD::dim() const { //theta(1)
	return dimensiune;
}


bool MD::vid() const { //theta(1)
	return dimensiune == 0;
}

IteratorMD MD::iterator() { //theta(1)
	return IteratorMD(*this);
}


MD::~MD() { //theta(n+c)
	NodCheie* cheie_curenta = cap;
	while (cheie_curenta != nullptr) {
		NodValoare*  valoare_curenta = cheie_curenta->cap_valori;
		while (valoare_curenta != nullptr) {
			NodValoare* de_sters = valoare_curenta;
			valoare_curenta = valoare_curenta->urmator;
			delete de_sters;
		}
		NodCheie* de_sters_cheie = cheie_curenta;
		cheie_curenta = cheie_curenta->urmator;
		delete de_sters_cheie;
	}
}

