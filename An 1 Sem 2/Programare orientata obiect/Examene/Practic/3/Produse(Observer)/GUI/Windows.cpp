#include "Windows.h"

TypeWindow::TypeWindow(ServiceProdus& service, const QString& tipVal, QWidget* parent) : QWidget(parent), service(service), tip(tipVal) {
    label = new QLabel(this);
    const auto layout = new QVBoxLayout(this);
    layout->addWidget(label);

    setWindowTitle(tip);
    update();
    service.addObserver(this);

    this->setMinimumSize(200, 100);
}

void TypeWindow::update(){
    int count = 0;
    for (const auto &p : service.getAll())
        if (QString::fromStdString(p.getTip()) == tip)
            count ++;
    label->setText("Numar produse: " + QString::number(count));
}


TypeWindow::~TypeWindow() {
    service.removeObserver(this);
}
