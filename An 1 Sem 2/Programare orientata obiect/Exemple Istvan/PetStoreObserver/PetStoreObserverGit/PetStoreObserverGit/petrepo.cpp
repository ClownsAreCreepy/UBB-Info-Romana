#include "petrepo.h"
#include "pet.h"
#include <fstream>
void PetRepoFile::loadFromFile(){
	std::ifstream in(fName);
	if (!in.is_open()) { //verify if the stream is opened		
		throw PetException("Unable to open file:"+fName);
	}	
	while (!in.eof()) {
		std::string species;
		in >> species;
		std::string type;
		in >> type;

		int price;
		in >> price;
		if (in.eof()) {	//nu am reusit sa citesc numarul
			break;
		}
		Pet p{type.c_str(), species.c_str(), price};
		PetRepo::store(p);
	}
	in.close();
}

void PetRepoFile::writeToFile() {
	std::ofstream out(fName);
	if (!out.is_open()) { //verify if the stream is opened
		std::string msg("Unable to open file:");
		throw PetException(msg);
	}
	for (auto& p:getAll()) {		
		out << p.getSpecies();
		out << std::endl;
		out << p.getType();
		out << std::endl;
		out << p.getPrice();
		out << std::endl;
	}
	out.close();
}
