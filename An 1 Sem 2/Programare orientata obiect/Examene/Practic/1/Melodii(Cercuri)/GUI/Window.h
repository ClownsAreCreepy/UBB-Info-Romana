#pragma once

#include "Model.h"
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
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
    QLineEdit *artistEdit;
    QLineEdit *genEdit;

    QPushButton *AddBtn;
    QPushButton *DelBtn;

    ServiceMelodii &service;

    void reloadTable() const;

private slots:
    void adaugare();
    void stergere();

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    MainWindow(ServiceMelodii &service, QWidget *parent = nullptr);
};
