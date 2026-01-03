#include "Window.h"

MainWindow::MainWindow(ServiceJucatori &service, QWidget *parent) : QWidget(parent), service(service) {
    lista = new QListWidget();

    slider = new QSlider(Qt::Horizontal);
    slider->setRange(1, 14);
    slider->setTickPosition(QSlider::TicksBelow);
    slider->setTickInterval(1);
    slider->setValue(7);

    const auto formLayout = new QFormLayout();
    formLayout->addRow("Numele:", nameEdit = new QLineEdit());
    formLayout->addRow("Points:", pointsEdit = new QLineEdit());

    const auto finalsLayout = new QVBoxLayout();
    finalsLayout->addWidget(sfertFinala = new QRadioButton("Sferturi de finala"));
    finalsLayout->addWidget(semiFinala = new QRadioButton("** Semi - Finala **"));
    finalsLayout->addWidget(finala = new QRadioButton("***** Finala *****"));

    const auto finalsfuncLayout = new QHBoxLayout();
    finalsfuncLayout->addLayout(finalsLayout);
    finalsfuncLayout->addWidget(AddBtn = new QPushButton("Adauga puncte"));

    const auto crudLayout = new QHBoxLayout();
    crudLayout->addWidget(UpdBtn = new QPushButton("Recalculeaza ranking"));
    crudLayout->addWidget(DelBtn = new QPushButton("Elimina jucatori"));

    const auto functionLayout = new QVBoxLayout();
    functionLayout->addLayout(formLayout);
    functionLayout->addLayout(finalsfuncLayout);
    functionLayout->addLayout(crudLayout);

    const auto mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(lista);
    mainLayout->addLayout(functionLayout);
    mainLayout->addWidget(slider);

    connect(AddBtn, QPushButton::clicked, this, &MainWindow::adaugaPuncte);
    connect(UpdBtn, QPushButton::clicked, this, &MainWindow::recalibreaza);
    connect(DelBtn, QPushButton::clicked, this, &MainWindow::stergeM);

    reloadListFromCurrent();
}

void MainWindow::reloadListFromCurrent() {
    lista->clear();
    for (const auto &j: service.getAll()) {
        auto *item = new QListWidgetItem(QString::fromStdString(
            j.getNume() + "," +
            j.getTara() + "," +
            to_string(j.getPuncte()) + "," +
            to_string(j.getRank())));

        lista->addItem(item);
    }
}

void MainWindow::adaugaPuncte() {
    const string nume = nameEdit->text().toStdString();
    const int puncte = pointsEdit->text().toInt();

    double factor = 1.0;
    if (semiFinala->isChecked()) factor = 0.75;
    if (sfertFinala->isChecked()) factor = 0.5;

    try {
        service.adauga_puncte(nume, static_cast<int>(puncte * factor));
        reloadListFromCurrent();
    } catch (const exception &e) {
        QMessageBox::critical(this, "Eroare", e.what());
    }
}

void MainWindow::recalibreaza() {
    service.recalculare();
    reloadListFromCurrent();
}

void MainWindow::stergeM() {
    try {
        service.sterge_service(slider->value());
        reloadListFromCurrent();
    } catch (const exception &e) {
        QMessageBox::critical(this, "Eroare", e.what());
    }
}
