#include "DesenareRoti.h"

void DesenareRoti::setNrRoti(int nr) {
    nrRoti = nr;
    update();
}

void DesenareRoti::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setBrush(Qt::green);
    rotiRects.clear();

    int radius = 20;
    int margin = 10;
    int x = margin, y = height() / 2 - radius;

    for (int i = 0; i < nrRoti; ++i) {
        QRect rect(x, y, 2 * radius, 2 * radius);
        p.drawEllipse(rect);
        rotiRects.push_back(rect);
        x += 2 * radius + margin;
    }
}

void DesenareRoti::mousePressEvent(QMouseEvent *event) {
    for (const auto &rect : rotiRects)
        if (rect.contains(event->pos())) {
            emit roataClick();
            break;
        }
}
