#pragma once
#include<vector>

using std::vector;

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

class IteratorMD;

struct NodValoare {
	TValoare valoare;
	NodValoare* urmator;

	NodValoare(TValoare v, NodValoare* n = nullptr) : valoare(v), urmator(n) {}
};

struct NodCheie {
	TCheie cheie;
	NodValoare*  cap_valori;
	NodCheie* urmator;

	NodCheie(TCheie k, NodCheie* n = nullptr) :  cheie(k), cap_valori(nullptr), urmator(n) {}
};

class MD
{
	friend class IteratorMD;

private:

	NodCheie* cap;
	int dimensiune;

public:
	// constructorul implicit al MultiDictionarului
	MD();

	// adauga o pereche (cheie, valoare) in MD	
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MD 
	int dim() const;

	//verifica daca MultiDictionarul e vid 
	bool vid() const;

	// se returneaza iterator pe MD
	IteratorMD iterator();

	// destructorul MultiDictionarului	
	~MD();

};

