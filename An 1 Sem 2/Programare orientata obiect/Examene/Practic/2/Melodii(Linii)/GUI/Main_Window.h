#pragma once

#include "Model_Tabel.h"
#include <QApplication>
#include <QPushButton>
#include <QTableView>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <map>

class MainWindow : public QWidget {
    Q_OBJECT

private:
    ModelTableMelodii *tableModel;
    QTableView *table;

    QLineEdit *titluEdit;

    QSlider *slider;

    QPushButton *ModBtn;
    QPushButton *DelBtn;

    ServiceMelodii &service;

    void reloadTableFromCurrent() const;

private slots:
    void selectare();
    void modificare();
    void stergere();


protected:
    void paintEvent(QPaintEvent *event) override;

public:
    MainWindow(ServiceMelodii &service, QWidget *parent = nullptr);
};