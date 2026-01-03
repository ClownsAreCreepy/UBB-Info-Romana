#include "Window.h"

MainWindow::MainWindow(ServiceJucatori &service, QWidget *parent) : QWidget(parent), service(service) {
    list = new QListWidget();

    const auto formLayout = new QFormLayout();
    formLayout->addRow("Numele", nameEdit = new QLineEdit());
    formLayout->addRow("Tara:", taraEdit = new QLineEdit());
    formLayout->addWidget(rancSpin = new QSpinBox());
    formLayout->addWidget(addBtn = new QPushButton("Add"));

    const auto listLayout = new QHBoxLayout();
    listLayout->addWidget(list);
    listLayout->addLayout(formLayout);

    const auto buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(qualBox = new QCheckBox("Qualified"));
    buttonLayout->addWidget(sortBtn = new QPushButton("Sort by rank"));

    const auto mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(listLayout);
    mainLayout->addLayout(buttonLayout);

    connect(addBtn, QPushButton::clicked, this, &MainWindow::add);
    connect(qualBox, &QCheckBox::stateChanged, this, &MainWindow::reloadListFromCurrent);
    connect(sortBtn, QPushButton::clicked, this, &MainWindow::sort);

    reloadListFromCurrent();
}

void MainWindow::reloadListFromCurrent() {
    list->clear();
    for (const auto &j: service.getAll()) {
        auto *item = new QListWidgetItem(QString::fromStdString(
            j.getNume() + "," +
            j.getTara() + "," +
            to_string(j.getPuncte()) + "," +
            to_string(j.getRank())
            ));

        if (qualBox->isChecked() && j.getPuncte() > 250)
            item->setBackground(Qt::green);

        list->addItem(item);
    }
}


void MainWindow::add() {
    const auto nume = nameEdit->text().toStdString();
    const auto tara = taraEdit->text().toStdString();
    const auto ranc = rancSpin->value();

    try {
        service.adaugare_cu_ranc(nume, tara, ranc);
        reloadListFromCurrent();
    } catch (const exception &e) {
        QMessageBox::critical(this,"Error",QString::fromStdString(e.what()));
    }
}


void MainWindow::sort() {
    service.sortare_ranc();
    reloadListFromCurrent();
}
