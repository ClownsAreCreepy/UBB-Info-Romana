
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qmessagebox.h>
#include <qlist.h>
#include "petrepo.h"
#include "petcontroller.h"
#include "petgui.h"
#include <string>
#include <list>
#include "CosGUI1.h"
int main(int argc, char *argv[])
{
	testPet();
	testCtr();
	PetRepoFile rep{ "pets.txt" };
	PetController ctr{ rep };
	
	QApplication a(argc, argv);
	PetStoreGUI gui{ ctr };
	gui.show();

	CosGUICuLista cosGUI{ ctr.getCos() };
	cosGUI.move(10, 10);
	cosGUI.show();


	CosGUILabel* cosGUI2=new CosGUILabel{ ctr.getCos() };	
	cosGUI2->show();

	CosGUICuTabel cosGUI3{ ctr.getCos() };
	cosGUI3.move(600, 10);
	cosGUI3.show();

	CosGUICuTabel cosGUI4{ ctr.getCos() };
	cosGUI4.move(10, 600);
	cosGUI4.show();

	CosGUICuTabel cosGUI5{ ctr.getCos() };
	cosGUI5.move(600, 600);
	cosGUI5.show();

	return a.exec();
}
