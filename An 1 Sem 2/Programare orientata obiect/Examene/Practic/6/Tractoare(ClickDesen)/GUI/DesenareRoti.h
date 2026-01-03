#pragma once

#include "../Service/Service.h"
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class DesenareRoti : public QWidget {
    Q_OBJECT
private:
    int nrRoti = 0;
    vector<QRect> rotiRects;

public:
    explicit DesenareRoti(QWidget *parent = nullptr) : QWidget(parent) {}

    void setNrRoti(int nr);
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void roataClick();
};