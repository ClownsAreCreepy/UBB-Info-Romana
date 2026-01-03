#include "pet.h"

#include <string.h>
#include <assert.h>
#include <stdlib.h>
/*
Create a new pet
*/
Pet createPet(char* type, char* species, float price) {
	Pet rez;
	int nrC = strlen(type) + 1;
	rez.type = malloc(sizeof(char)*nrC);
	strcpy_s(rez.type,nrC, type);
	nrC = strlen(species) + 1;
	rez.species = malloc(sizeof(char)*nrC);
	strcpy_s(rez.species, nrC, species);
	rez.price = price;
	return rez;
}

/*
Dealocate memory occupied by pet
*/
void destroyPet(Pet* p) {
	free(p->type);
	free(p->species);
	//mark that pet is destroyed, avoid accidental use after destroy
	p->type = NULL;
	p->species = NULL;
	p->price = -1;
}
/*
  Create a copy for the pet
  Deep copy - copy all the sub-parts 
*/
Pet copyPet(Pet* p) {
	return createPet(p->type, p->species, p->price);
}

void testCreateDestroy() {
	Pet p = createPet("dog", "buldog", 100);
	assert(strcmp(p.type, "dog") == 0);
	assert(strcmp(p.species, "buldog") == 0);
	assert(p.price == 100.0);

	destroyPet(&p);
	assert(p.type == NULL);
	assert(p.species == NULL);
	assert(p.price==-1);
}