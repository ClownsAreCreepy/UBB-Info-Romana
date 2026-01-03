#include "Window.h"

MainWindow::MainWindow(ServiceRochii &service, QWidget *parent) : QWidget{parent}, service{service} {
    list = new QListWidget();

    const auto layout = new QVBoxLayout(this);
    layout->addWidget(list, 3);
    layout->addWidget(InchiriereBtn = new QPushButton("Inchiriere"));
    layout->addWidget(SortNameBtn = new QPushButton("Sortare nume"));
    layout->addWidget(SortPriceBtn = new QPushButton("Sortare pret"));
    layout->addWidget(UnsortBtn = new QPushButton("Nesortare"));

    connect(InchiriereBtn, &QPushButton::clicked, this, &MainWindow::inchiriereRochie);
    connect(SortNameBtn, &QPushButton::clicked, this, &MainWindow::sortNume);
    connect(SortPriceBtn, &QPushButton::clicked, this, &MainWindow::sortPret);
    connect(UnsortBtn, &QPushButton::clicked, this, &MainWindow::UnSort);


    UnSort();
}

void MainWindow::reloadListFromCurrent() const {
    list->clear();
    for (const auto &d: currentView) {
        auto *item = new QListWidgetItem(QString::fromStdString(
            d.getDenumire() + "," +
            d.getMarime() + "," +
            to_string(d.getPret())
            ));

        if (d.getDisponibilitate() == "True")
            item->setBackground(Qt::green);
        else
            item->setBackground(Qt::red);

        list->addItem(item);
    }
}

void MainWindow::inchiriereRochie() {
    int row = list->currentRow();

    try {
        service.inchirieaza_service(row);
        currentView = service.getAll();
        reloadListFromCurrent();
    } catch (const exception &e) {
        QMessageBox::warning(this, "Lending error", QString::fromStdString(e.what()));
    }
}

void MainWindow::sortNume() {
    currentView = service.getAll();
    service.sorteaza_denumire(currentView);
    reloadListFromCurrent();
}

void MainWindow::sortPret() {
    currentView = service.getAll();
    service.sorteaza_pret(currentView);
    reloadListFromCurrent();
}

void MainWindow::UnSort() {
    currentView.clear();
    for (const auto &d : service.getAll())
        currentView.emplace_back(d);

    reloadListFromCurrent();
}