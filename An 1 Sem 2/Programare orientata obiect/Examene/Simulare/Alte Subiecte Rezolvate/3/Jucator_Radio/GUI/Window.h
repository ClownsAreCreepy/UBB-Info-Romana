#pragma once

#include "../Service/Service.h"
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QSlider>

class MainWindow : public QWidget {
    Q_OBJECT

private:
    QListWidget *lista;

    QLineEdit *nameEdit;
    QLineEdit *pointsEdit;

    QRadioButton *sfertFinala;
    QRadioButton *semiFinala;
    QRadioButton *finala;

    QPushButton *AddBtn;
    QPushButton *UpdBtn;
    QPushButton *DelBtn;

    QSlider *slider;

    ServiceJucatori &service;

    void reloadListFromCurrent();

private slots:
    void adaugaPuncte();
    void recalibreaza();
    void stergeM();

public:
    explicit MainWindow(ServiceJucatori &service, QWidget *parent = nullptr);
};
