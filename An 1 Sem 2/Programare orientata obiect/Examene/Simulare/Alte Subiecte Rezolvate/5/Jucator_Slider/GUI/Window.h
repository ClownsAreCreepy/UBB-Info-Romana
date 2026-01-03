#pragma once

#include "../Service/Service.h"
#include <QApplication>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox>
#include <QRadioButton>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QButtonGroup>

class MainWindow : public QWidget {
    Q_OBJECT
private:
    QTableWidget *table;

    QLineEdit *numeEdit;
    QLineEdit *taraEdit;

    QPushButton *AddBtn;
    QPushButton *GenBtn;
    QButtonGroup *buttonGroup;

    QSlider *slider;

    ServiceJucatori &service;

    void reloadTableFromList();

private slots:
    void adaugare();
    void raport();
    void alegere();

public:
    MainWindow(ServiceJucatori &service, QWidget *parent = nullptr);
};