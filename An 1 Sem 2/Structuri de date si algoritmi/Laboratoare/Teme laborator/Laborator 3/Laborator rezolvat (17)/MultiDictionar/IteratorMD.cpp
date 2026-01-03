#include "IteratorMD.h"
#include "MD.h"
#include <exception>
using std::pair;
using std::exception;
using std::make_pair;

IteratorMD::IteratorMD(MD& _md): md(_md) { //theta(1)
	cheie_curenta = md.cap;
	if (cheie_curenta != nullptr)
		valoare_curenta = cheie_curenta ->cap_valori;
	else
		valoare_curenta = nullptr;
}

TElem IteratorMD::element() const{ //theta(1)
	if (!valid()) throw exception();
	return make_pair(cheie_curenta->cheie, valoare_curenta->valoare);
}

bool IteratorMD::valid() const { //theta(1)
	return cheie_curenta != nullptr && valoare_curenta != nullptr;
}

void IteratorMD::urmator() { //O(c)
	if (!valid()) throw exception();

	valoare_curenta = valoare_curenta->urmator;

	while (valoare_curenta == nullptr && cheie_curenta != nullptr) {
		cheie_curenta = cheie_curenta->urmator;
		if (cheie_curenta != nullptr)
			valoare_curenta = cheie_curenta->cap_valori;
	}

	// if (valoare_curenta == nullptr) {
	// 	cheie_curenta = cheie_curenta->urmator;
	// 	valoare_curenta = cheie_curenta->cap_valori;
	// }

}

void IteratorMD::prim() { //theta(1)
	cheie_curenta = md.cap;
	if (cheie_curenta != nullptr)
		valoare_curenta = cheie_curenta ->cap_valori;
	else
		valoare_curenta = nullptr;
}

TElem IteratorMD::elimina() { //O(n+c)
	if (!valid()) throw exception();

	TElem elem = element();	//Salvam elementul curent ca sa ne intoarcem la el mai tarziu

	//facem aceeasi chestie, dar pentru valoare
	NodValoare* valoare = cheie_curenta->cap_valori;
	NodValoare* valoare_anterioara = nullptr;

	//Cautam de la inceput, ca sa avem valoarea valorii de dinainte
	while (valoare != nullptr && valoare->valoare != valoare_curenta->valoare) {
		valoare_anterioara = valoare;
		valoare = valoare->urmator;
	}



	//eliminam nodul de valoare
	if (valoare_anterioara == nullptr)
		//daca capul de vectorul valoare e gol, inseamna ca valoarea pe care o stergem e cea din cap, deci bagam urmatoru in cap
			cheie_curenta->cap_valori = valoare_curenta->urmator;
	else
		//daca valoarea e pe undeva prin vector, doar sarim peste ea cu urmator
			valoare_anterioara->urmator = valoare_curenta->urmator;

	//Salvam pointer-ul urmator si stergem valoarea curenta
	NodValoare* valoare_urmatoare = valoare_curenta->urmator;
	delete valoare_curenta;
	md.dimensiune --;



	//Daca nu mai sunt valori, stergem nodul cheie
	if (cheie_curenta->cap_valori == nullptr) {
		//Stergem nodul cheie
		NodCheie* cheie = md.cap;
		NodCheie* cheie_anterioara = nullptr;

		//Cautam tinem minte pozitia si cheia de dinainte
		while (cheie != nullptr && cheie_curenta != cheie) {
			cheie_anterioara = cheie;
			cheie = cheie->urmator;
		}

		if (cheie_anterioara == nullptr)
			md.cap = cheie->urmator;
		else
			cheie_anterioara->urmator=cheie->urmator;

		//Salvam pointer-ul cheie
		NodCheie* cheie_urmatoare = cheie->urmator;
		delete cheie;


		//Avansam iteratorul la cheia urmatoare
		cheie_curenta = cheie_urmatoare;
		if (cheie_curenta != nullptr)
			valoare_curenta = cheie_curenta->cap_valori;
		else
			valoare_curenta = nullptr;
	}else{
		//Daca valoarea nu e ultima din iterator, atunci doar merem pe cheia urmatoare
		//Avansam iteratorul la valoarea urmatoare
		valoare_curenta = valoare_urmatoare;
	}

	return elem;
}
