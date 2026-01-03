#include "Window.h"

MainWindow::MainWindow(ServiceProdus &service, QWidget *parent) : QWidget(parent), service(service) {
    table = new QTableView();
    tableModel = new ModelTabelProdus(service, this);
    table->setModel(tableModel);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    slider = new QSlider(Qt::Horizontal);
    slider->setRange(1, 100);
    slider->setTickPosition(QSlider::TicksRight);
    slider->setTickInterval(10);
    slider->setValue(1);

    const auto formLayout = new QFormLayout();
    formLayout->addRow("ID", idEdit = new QLineEdit());
    formLayout->addRow("Nume", nameEdit = new QLineEdit());
    formLayout->addRow("Tip", tipEdit = new QLineEdit());
    formLayout->addRow("Pret", pretEdit = new QLineEdit());
    formLayout->addWidget(AddBtn = new QPushButton("Adauga"));
    formLayout->addWidget(slider);

    const auto mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(table);
    mainLayout->addLayout(formLayout);

    connect(AddBtn, &QPushButton::clicked, this, &MainWindow::adaugare);
    connect(slider, &QSlider::sliderMoved, this, &MainWindow::filtrare);

    reloadTable();
}

void MainWindow::reloadTable() {
    tableModel->updateModel(service.getAll());
    creeazaFerestrePentruTipuriNoi();
}

void MainWindow::creeazaFerestrePentruTipuriNoi() {
    set<QString> currentTypes;
    for (const auto& p : service.getAll())
        currentTypes.insert(QString::fromStdString(p.getTip()));

    for (const auto &tip : currentTypes)
        if (!typeWindows.contains(tip)) {
            auto *win = new TypeWindow(service, tip);
            win->show();
            typeWindows[tip] = win;
        }
}


void MainWindow::adaugare() {
    int id = idEdit->text().toInt();
    const string &nume = nameEdit->text().toStdString();
    const string &tip = tipEdit->text().toStdString();
    double price = pretEdit->text().toDouble();

    try {
        service.adauga_service(id, nume, tip, price);
        reloadTable();
    } catch (const exception &e) {
        QMessageBox::warning(this, "Eroare", e.what());
    }
}

void MainWindow::filtrare() {
    int pret = slider->value();
    tableModel->setPretFiltrat(pret);
}

