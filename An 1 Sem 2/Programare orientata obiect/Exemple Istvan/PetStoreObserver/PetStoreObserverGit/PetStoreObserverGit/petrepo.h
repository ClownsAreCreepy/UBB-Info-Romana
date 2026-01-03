#pragma once
#include "pet.h"
#include <vector>
#include <algorithm>
#include <string>
class PetRepo {
private:
	std::vector<Pet> all;
public:
	PetRepo() {}

	PetRepo(const PetRepo& ot) = delete;//nu vreau sa se copieze repo
	/*
	Salveaza pet
	*/
	virtual void store(const Pet& p) {
		//verificam sa nu mai existe un pet 
		auto found = std::find_if(all.begin(), all.end(), [p](const Pet& pp) {
			return pp.getSpecies()==p.getSpecies() && pp.getType()==p.getType(); });
		if (found != all.end()) {			
			throw PetException{ "Pet existent!!!" };
		}
		all.push_back(p);
	}
	/*
	Cauta pet
	Arunca PetException daca nu exista pet
	*/
	Pet find(const std::string& species,const std::string& type) const {
		auto found = std::find_if(all.begin(), all.end(), [&](const Pet& pp) {
			return pp.getSpecies()==species && pp.getType()==type.c_str(); });
		if (found == all.end()) {
			throw PetException{ "Pet inexistent!!!" };
		}
		return *found;
	}
	virtual void sterge(const Pet& p) {
		auto found = std::find_if(all.begin(), all.end(), [p](const Pet& pp) {
			return pp.getSpecies()== p.getSpecies() && pp.getType()== p.getType(); });
		if (found == all.end()) {
			throw PetException{ "Pet inexistent!!!" };
		}
		//stergem pet
		all.erase(found);
	}

	std::vector<Pet> getAll() const{
		return all;
	}
};

class PetRepoFile :public PetRepo {
private:
	std::string fName;
	void loadFromFile();
	void writeToFile();
public:
	PetRepoFile(std::string fName) :PetRepo(), fName{ fName } {
		loadFromFile();//incarcam datele din fisier
	}
	void store(const Pet& p) override {
		PetRepo::store(p);//apelam metoda din clasa de baza
		writeToFile();
	}
	void sterge(const Pet& p) override {
		PetRepo::sterge(p);//apelam metoda din clasa de baza
		writeToFile();
	}
};