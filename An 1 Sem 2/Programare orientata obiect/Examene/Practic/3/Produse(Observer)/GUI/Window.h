#pragma once

#include "Model.h"
#include "Windows.h"
#include <QApplication>
#include <QMessageBox>
#include <QWidget>
#include <QPushButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <set>
#include <map>

class MainWindow : public QWidget {
    Q_OBJECT

private:
    ModelTabelProdus *tableModel;
    QTableView *table;

    QLineEdit *idEdit;
    QLineEdit *nameEdit;
    QLineEdit *tipEdit;
    QLineEdit *pretEdit;

    QPushButton *AddBtn;

    QSlider *slider;

    ServiceProdus &service;
    map<QString, TypeWindow*> typeWindows;

    void reloadTable();
    void creeazaFerestrePentruTipuriNoi();

private slots:
    void adaugare();
    void filtrare();

public:
    MainWindow(ServiceProdus &service, QWidget *parent = nullptr);
};