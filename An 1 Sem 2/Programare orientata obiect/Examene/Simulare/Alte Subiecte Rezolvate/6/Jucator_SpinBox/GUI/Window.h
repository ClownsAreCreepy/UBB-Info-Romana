#pragma once

#include "../Service/Service.h"
#include <QApplication>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QMessageBox>
#include <QSpinBox>

class MainWindow : public QWidget {
    Q_OBJECT

private:
    QListWidget *list;

    QLineEdit *nameEdit;
    QLineEdit *taraEdit;
    QSpinBox *rancSpin;

    QPushButton *addBtn;
    QPushButton *sortBtn;
    QCheckBox *qualBox;

    ServiceJucatori &service;

    void reloadListFromCurrent();

private slots:
    void add();
    void sort();

public:
    explicit MainWindow(ServiceJucatori &service, QWidget *parent = nullptr);
};