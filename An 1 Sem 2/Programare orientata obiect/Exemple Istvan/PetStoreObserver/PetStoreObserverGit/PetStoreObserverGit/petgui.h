#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include "petcontroller.h"
#include "pet.h"
#include <vector>


class PetStoreGUI : public QWidget{
private:
	PetController& ctr;
	QListWidget* lst;
	QPushButton* btnSortByPrice;
	QPushButton* btnSortByType;
	QLineEdit* txtSpecies;
	QLineEdit* txtType;
	QLineEdit* txtPrice;
	QPushButton* btnAdd;
	void initGUICmps();
	void connectSignalsSlots();
	void reloadList(std::vector<Pet> pets);
	void addNewPet();
public:
	PetStoreGUI(PetController& ctr) :ctr{ ctr } {
		initGUICmps();
		connectSignalsSlots();
		reloadList(ctr.getAllPets());
	}

};