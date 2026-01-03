#include "TestScurt.h"
#include <assert.h>
#include <vector>
#include <iostream>
#include "../MultiDictionar//MD.h"
#include "../MultiDictionar//IteratorMD.h"


void testAll() {
	MD m;
	m.adauga(1, 100);
	m.adauga(2, 200);
	m.adauga(3, 300);
	m.adauga(1, 500);
	m.adauga(2, 600);
	m.adauga(4, 800);

	assert(m.dim() == 6);

	assert(m.sterge(5, 600) == false);
	assert(m.sterge(1, 500) == true);

	assert(m.dim() == 5);


	vector<TValoare> v;
	v=m.cauta(6);
	assert(v.size()==0);

	v=m.cauta(1);
	assert(v.size()==1);

	assert(m.vid() == false);

	IteratorMD im = m.iterator();
	assert(im.valid() == true);
	while (im.valid()) {
	   im.element();
	   im.urmator();
	}
	assert(im.valid() == false);
	im.prim();
	assert(im.valid() == true);
}


void testElimina() {
	MD dict;
	dict.adauga(2, 100);
	dict.adauga(1, 200);
	dict.adauga(1, 300);

	IteratorMD it = dict.iterator();

	assert(it.valid());
	TElem eliminat = it.elimina(); //Ar trebui sa scoata (1,300)
	assert(eliminat.first == 1 && eliminat.second == 300);

	assert(dict.cauta(1).size() == 1); //Mai exista doar 1 element cu cheia 1
	it.urmator();
	assert(it.valid()); //Suntem pe 100 si e valid

	it.elimina(); //eliminat (2,100), deci acum e gol
	assert(!it.valid()); //ar trebui sa fie invalid

	 try {
	 	it.elimina();
	 	assert(false);
	 }catch (std::exception&){}
}