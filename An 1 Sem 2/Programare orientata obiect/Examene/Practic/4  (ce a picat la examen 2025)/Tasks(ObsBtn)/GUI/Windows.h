#pragma once

#include "../Service/Service.h"
#include "Model.h"
#include <QWidget>
#include <QPushButton>
#include <QTableView>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>


class WindowStare : public QWidget, public Observer {
    Q_OBJECT

private:

    QTableView *table;
    ModelTabelTask *tableModel;

    QPushButton *OpenBtn;
    QPushButton *InprogressBtn;
    QPushButton *ClosedBtn;

    string stare;
    ServiceTask &service;

private slots:
    void modifca(const string &s);
    void update() override;

public:
    WindowStare(ServiceTask &se, const string &st, QWidget *parent = nullptr);
    ~WindowStare();
};