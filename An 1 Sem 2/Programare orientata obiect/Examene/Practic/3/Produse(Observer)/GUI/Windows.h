#pragma once

#include "../Service/Service.h"
#include <QWidget>
#include <QTableView>
#include <QLabel>
#include <QVBoxLayout>

class TypeWindow : public QWidget, public Observer {
    Q_OBJECT
private:
    ServiceProdus &service;
    QString tip;
    QLabel *label;

public:
    explicit TypeWindow(ServiceProdus &service, const QString &tipVal, QWidget *parent = nullptr);

    ~TypeWindow() override;

    void update() override;
};