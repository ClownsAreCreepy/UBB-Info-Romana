#pragma once
#include <qwidget.h>
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qboxlayout.h>
#include "petservice.h"
#include "pet.h"
#include <vector>
#include <qlabel.h>
class SmallGUI : public QWidget {
private:
	QLabel* lbl = new QLabel("Nimic");
public:
	SmallGUI() {
		QHBoxLayout* ly = new QHBoxLayout;
		setLayout(ly);
		ly->addWidget(lbl);
	}

	void setPet(const Pet&p) {
		lbl->setText(QString{ p.getSpecies().c_str() });
	}

};

class PetStoreGUI : public QWidget{
private:
	PetService& ctr;
	QListWidget* lst;
	QPushButton* btnSortByPrice;
	QPushButton* btnSortByType;
	QLineEdit* txtSpecies;
	QLineEdit* txtType;
	QLineEdit* txtPrice;
	QPushButton* btnAdd;
	void initGUICmps();
	void connectSignalsSlots();
	void reloadList(const std::vector<Pet>& pets);
	void addNewPet();
public:
	PetStoreGUI(PetService& ctr) :ctr{ ctr } {
		initGUICmps();
		connectSignalsSlots();
		reloadList(ctr.getAllPets());
	}

};