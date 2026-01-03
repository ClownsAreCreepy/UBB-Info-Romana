//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#include <QtWidgets/QApplication>

#include "pet.h"

#include "petservice.h"
#include "storeui.h"
#include "petgui.h"

int main(int argc, char *argv[])
{
	testPet();
	testCtr();
	testPetRepos();
	
	{
		QApplication a(argc, argv);
		//PetRepo rep;
		PetRepoFile rep{ "pets.txt" };
		PetService ctr{ rep };
	
		PetStoreGUI gui{ ctr };
		gui.show();
		a.exec();
	}
	
	return 0;
}
