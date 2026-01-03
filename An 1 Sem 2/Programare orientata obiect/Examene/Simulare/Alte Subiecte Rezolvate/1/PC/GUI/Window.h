#pragma once

#include "../Service/ServiceProcesor.h"
#include "../Service/ServicePlacaDeBaza.h"
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QFormLayout>


class MainWindow : public QWidget {
    Q_OBJECT

private:
    QListWidget *lista_procesoare;
    QListWidget *lista_placi;

    QLineEdit *nameEdit;
    QLineEdit *socluEdit;
    QLineEdit *priceEdit;

    QPushButton *AddBtn;
    QPushButton *ToalBtn;

    QLabel *totalPrice;

    ServicePlacaDeBaza &service_placa;
    ServiceProcesor &service_procesor;

    vector<Procesor> currentView_procesoare;
    vector<PlacaDeBaza> currentView_placi;

    void reloadListsFromCurrent();

private slots:
    void addPlaca();
    void filterPlaca(QListWidgetItem *item);
    void ShowTotal();

public:
    explicit MainWindow(ServiceProcesor &procesoare, ServicePlacaDeBaza &placi, QWidget *parent = nullptr);
};
