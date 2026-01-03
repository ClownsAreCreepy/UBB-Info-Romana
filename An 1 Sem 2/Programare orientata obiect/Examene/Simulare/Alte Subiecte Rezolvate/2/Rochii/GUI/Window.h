#pragma once

#include "../Service/Service.h"
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QMessageBox>

class MainWindow : public QWidget {
    Q_OBJECT

private:
    QListWidget *list;

    QPushButton *InchiriereBtn;
    QPushButton *SortNameBtn;
    QPushButton *SortPriceBtn;
    QPushButton *UnsortBtn;

    ServiceRochii &service;
    vector<Rochie> currentView;

    void reloadListFromCurrent() const;

private slots:
    void inchiriereRochie();
    void sortNume();
    void sortPret();
    void UnSort();

public:
    explicit MainWindow(ServiceRochii &service, QWidget *parent = nullptr);
};