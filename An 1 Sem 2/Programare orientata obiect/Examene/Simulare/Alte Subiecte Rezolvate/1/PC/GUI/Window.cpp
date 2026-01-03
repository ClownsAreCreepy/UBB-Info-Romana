#include "Window.h"

MainWindow::MainWindow(ServiceProcesor &proc, ServicePlacaDeBaza &plac, QWidget *parent) : QWidget{parent},
    service_procesor(proc), service_placa(plac) {
    lista_placi = new QListWidget();
    lista_procesoare = new QListWidget();

    const auto proclayout = new QVBoxLayout();
    proclayout->addWidget(lista_procesoare);

    const auto formlayout = new QFormLayout();
    formlayout->addRow("Nume:", nameEdit = new QLineEdit());
    formlayout->addRow("Soclu:", socluEdit = new QLineEdit());
    formlayout->addRow("Pret:", priceEdit = new QLineEdit());

    const auto placlayout = new QVBoxLayout();
    placlayout->addWidget(lista_placi);
    placlayout->addLayout(formlayout);
    placlayout->addWidget(AddBtn = new QPushButton("Add"));

    const auto middlelayout = new QVBoxLayout();
    middlelayout->addWidget(totalPrice = new QLabel("Total: 0 lei"));
    middlelayout->addWidget(ToalBtn = new QPushButton("Total Price"));

    const auto mainlayout = new QHBoxLayout(this);
    mainlayout->addLayout(proclayout);
    mainlayout->addLayout(middlelayout);
    mainlayout->addLayout(placlayout);

    connect(AddBtn, &QPushButton::clicked, this, &MainWindow::addPlaca);
    connect(lista_procesoare, &QListWidget::itemClicked, this, &MainWindow::filterPlaca);
    connect(ToalBtn, &QPushButton::clicked, this, &MainWindow::ShowTotal);

    reloadListsFromCurrent();
}

void MainWindow::reloadListsFromCurrent() {
    currentView_placi.clear();
    currentView_procesoare.clear();

    for (const auto &p: service_procesor.getAllProcesoare())
        currentView_procesoare.emplace_back(p);

    for (const auto &p: service_placa.getAllPlaci())
        currentView_placi.emplace_back(p);

    lista_placi->clear();
    lista_procesoare->clear();
    for (const auto &p: currentView_procesoare) {
        auto *item = new QListWidgetItem(QString::fromStdString(
            p.getNume() + "," +
            to_string(p.getNrThreaduri())
        ));

        lista_procesoare->addItem(item);
    }

    for (const auto &p: currentView_placi) {
        auto *item = new QListWidgetItem(QString::fromStdString(
            p.getNume()));

        lista_placi->addItem(item);
    }
}

void MainWindow::addPlaca() {
    const auto nume = nameEdit->text().toStdString();
    const auto soclu = socluEdit->text().toStdString();
    const auto pret = priceEdit->text().toInt();

    service_placa.service_adauga_placi(nume, soclu, pret);
    reloadListsFromCurrent();
}


void MainWindow::filterPlaca(QListWidgetItem *item) {
    int index = lista_procesoare->row(item);
    const auto procesor = currentView_procesoare[index];
    string selectedSoclu = procesor.getSocluProcesor();

    vector<PlacaDeBaza> filtrat;
    service_placa.filtrareSoclu(selectedSoclu, filtrat);
    lista_placi->clear();
    for (const auto &b: filtrat)
        lista_placi->addItem(QString::fromStdString(b.getNume()));
}

void MainWindow::ShowTotal() {
    int indexProc = lista_procesoare->currentRow();
    int indexPlaca = lista_placi->currentRow();

    const auto &proc = currentView_procesoare[indexProc];
    const auto &placa = currentView_placi[indexPlaca];

    int total = proc.getPret() + placa.getPret();
    totalPrice->setText(QString::fromStdString("Total: " + to_string(total) + " lei"));
}
