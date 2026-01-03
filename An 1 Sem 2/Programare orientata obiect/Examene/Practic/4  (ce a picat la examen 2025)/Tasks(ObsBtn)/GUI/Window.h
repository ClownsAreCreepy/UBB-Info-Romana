#pragma once

#include "Model.h"
#include "Windows.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

class MainWindow : public QWidget, public Observer{
    Q_OBJECT
private:
    ModelTabelTask *tableModel;
    QTableView *table;

    QPushButton *AddBtn;

    QLineEdit *idEdit;
    QLineEdit *denumireEdit;
    QLineEdit *programatoriEdit;
    QLineEdit *stareEdit;

    QLineEdit *filterEdit;

    ServiceTask &service;

    void reloadTable();
    void creeazaFerestreStari();
    void update() override;

private slots:
    void adaugare();
    void filtrare();

public:
    MainWindow(ServiceTask &s, QWidget *parent = nullptr);
};
