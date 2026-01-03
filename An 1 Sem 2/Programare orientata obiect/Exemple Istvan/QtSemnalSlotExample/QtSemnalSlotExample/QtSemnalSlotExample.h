#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtSemnalSlotExample.h"

class QtSemnalSlotExample : public QMainWindow
{
	Q_OBJECT

public:
	QtSemnalSlotExample(QWidget *parent = Q_NULLPTR);

private:
	Ui::QtSemnalSlotExampleClass ui;
};
