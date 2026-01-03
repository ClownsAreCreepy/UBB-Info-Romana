#pragma once

#include "Model.h"
#include "DesenareRoti.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QComboBox>
#include <QPainter>

class MainWindow : public QWidget {
    Q_OBJECT
private:
    QTableView *table;
    ModelTabelTractoare *tableModel;

    DesenareRoti *roti;

    QLineEdit *idEdit;
    QLineEdit *denumireEdit;
    QLineEdit *tipEdit;
    QLineEdit *rotiEdit;

    QPushButton *addBtn;

    QComboBox *filterBox;

    ServiceTractoare &service;

    void reloadTable();

private slots:
    void adaugare();
    void filtrare();
    void paintRoti();
    void clickOnRoata();

public:
    MainWindow(ServiceTractoare &s, QWidget *parent = nullptr);
};