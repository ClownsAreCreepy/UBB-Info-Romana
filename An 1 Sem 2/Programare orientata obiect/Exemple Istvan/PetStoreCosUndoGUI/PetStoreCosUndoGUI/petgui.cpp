#include "petgui.h"
#include "pet.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <string>
#include <algorithm>
void PetStoreGUI::initGUICmps() {
	QHBoxLayout* ly = new QHBoxLayout;
	setLayout(ly);

	//adaug lista si sub doua butoane de sort
	QWidget* widDreapta = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widDreapta->setLayout(vl);
	lst = new QListWidget;
	vl->addWidget(lst);
	
	QWidget* widBtnDreapta = new QWidget;
	QHBoxLayout* lyBtnsDr = new QHBoxLayout;
	widBtnDreapta->setLayout(lyBtnsDr);
	btnSortByPrice = new QPushButton("Sort by price");
	lyBtnsDr->addWidget(btnSortByPrice);
	
	btnSortByType = new QPushButton("Sort by type");
	lyBtnsDr->addWidget(btnSortByType);
	vl->addWidget(widBtnDreapta);
	ly->addWidget(widDreapta);

	//fac un form pentru detalii
	QWidget* widDetalii = new QWidget;
	QFormLayout* formLDetalii = new QFormLayout;
	widDetalii->setLayout(formLDetalii);
	txtSpecies = new QLineEdit;
	formLDetalii->addRow(new QLabel("Species:"),txtSpecies);
	txtType = new QLineEdit;
	formLDetalii->addRow(new QLabel("Type:"), txtType);
	txtPrice = new QLineEdit;
	formLDetalii->addRow(new QLabel("Price:"), txtPrice);

	btnAdd = new QPushButton("Add pet");
	
	formLDetalii->addWidget(btnAdd);

	ly->addWidget(widDetalii);
}


void PetStoreGUI::connectSignalsSlots() {
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByPrice, &QPushButton::clicked, [&]() {
		reloadList(ctr.getSortByPrice());
	});
	//cand se emite semnalul clicked de pe buton reincarc lista
	QObject::connect(btnSortByType, &QPushButton::clicked, [&]() {
		reloadList(ctr.getSortByType());
	});
	//cand se selecteaza elementul din lista incarc detaliile
	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		if (lst->selectedItems().isEmpty()) {
			//nu este nimic selectat (golesc detaliile)
			txtSpecies->setText("");
			txtType->setText("");
			txtPrice->setText("");
			return;
		}
		QListWidgetItem* selItem =  lst->selectedItems().at(0);
		QString species = selItem->text();
		txtSpecies->setText(species);		
		QString type = selItem->data(Qt::UserRole).toString();
		txtType->setText(type);
		try {
			//cautam Pet
			Pet p = ctr.find(type.toStdString(), species.toStdString());
			txtPrice->setText(QString::number(p.getPrice()));
		}
		catch (PetException& ex) {
			QMessageBox::warning(nullptr, "Warning", QString::fromStdString(ex.getMsg()));
		}
	});
	QObject::connect(btnAdd, &QPushButton::clicked, this, &PetStoreGUI::addNewPet);
}

void PetStoreGUI::addNewPet() {
	try {
		ctr.add(txtType->text().toStdString(), txtSpecies->text().toStdString(), txtPrice->text().toDouble());
		reloadList(ctr.getAllPets());	
	}
	catch (PetException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMsg()));
	}
}
void PetStoreGUI::reloadList(const std::vector<Pet>& pets) {
	auto colorize = ctr.getFilterByPrice(20);
	lst->clear();
	for (const auto& p : pets) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.getSpecies()), lst);
		item->setData(Qt::UserRole,QString::fromStdString( p.getType()));//adaug in lista (invizibil) si type 
		//if (std::find(colorize.cbegin(), colorize.cend(), p) !=colorize.end()){//merge pt ca am adaugat operator== la Pet		
		    //item->setBackground(QBrush{ QColor{Qt::red},Qt::CrossPattern });		
			//item->setBackgroundColor(QColor{ Qt::red });
		//}
	}
}