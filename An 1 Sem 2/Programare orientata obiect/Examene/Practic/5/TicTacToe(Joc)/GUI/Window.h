#pragma once

#include "Model.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVector>

class MainWindow : public QWidget{
    Q_OBJECT
private:
    QTableView *table;
    ModelTabelJoc *tableModel;

    QLineEdit *adaugaDimEdit;
    QLineEdit *adaugaTabEdit;
    QLineEdit *adaugaJocEdit;

    QLineEdit *modificaDimEdit;
    QLineEdit *modificaTabEdit;
    QLineEdit *modificaJocEdit;
    QLineEdit *modificaStareEdit;

    QPushButton *addBtn;
    QPushButton *modBtn;

    QGridLayout *gridLayout;
    QWidget *gridWrapper;
    QVector<QPushButton*> gridBtns;

    int currentGridDim = 0;
    int selectedRow = -1;

    ServiceJoc &service;

    void reloadTable();

private slots:
    void adaugare();
    void modificare();
    void joc();
    void updateGrid(const Joc &j);
    void handleCellClick(int index);

public:
    MainWindow(ServiceJoc &s, QWidget *parent = nullptr);
};