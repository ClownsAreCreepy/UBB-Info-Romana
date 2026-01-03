#pragma once
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlistwidget.h>

class MyGUIMinunat: public QWidget {
private:
	QPushButton* btnSterge = new QPushButton{ "sterge" };
	QPushButton* btnAdauga = new QPushButton{ "adauga" };
	QListWidget* lstTractoare = new QListWidget;

	void initGUIComponents() {
		QHBoxLayout* ly = new QHBoxLayout;
		setLayout(ly);
		ly->addWidget(lstTractoare);
		ly->addWidget(btnSterge);
		ly->addWidget(btnAdauga);
	}
	void initialGUIState() {
		/*
		for (auto tr:serv.getAll()){
			lstTractoare->addItem()
		}*/
		lstTractoare->addItem("Item1");
		lstTractoare->addItem("Item2");
	}
public:
	MyGUIMinunat() {
		initGUIComponents();
		initialGUIState();
	}
};