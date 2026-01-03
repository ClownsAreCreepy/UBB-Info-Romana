#include "Window.h"

MainWindow::MainWindow(ServiceTask &s, QWidget *parent) : QWidget(parent), service(s) {
    table = new QTableView();
    tableModel = new ModelTabelTask(this);
    table->setModel(tableModel);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    const auto formLayout = new QFormLayout();
    formLayout->addRow("ID", idEdit = new QLineEdit());
    formLayout->addRow("Denumire", denumireEdit = new QLineEdit());
    formLayout->addRow("Programatori", programatoriEdit = new QLineEdit());
    formLayout->addRow("Stare", stareEdit = new QLineEdit());

    const auto addLayout = new QVBoxLayout();
    addLayout->addLayout(formLayout);
    addLayout->addWidget(AddBtn = new QPushButton("Adaugare"));
    addLayout->addStretch();

    const auto filterLayout = new QFormLayout();
    filterLayout->addRow("Filtrare", filterEdit = new QLineEdit());

    const auto funcLayout = new QVBoxLayout();
    funcLayout->addLayout(addLayout);
    funcLayout->addLayout(filterLayout);
    funcLayout->addStretch();


    const auto mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(table);
    mainLayout->addLayout(funcLayout);

    connect(AddBtn, &QPushButton::clicked, this, &MainWindow::adaugare);
    connect(filterEdit, &QLineEdit::textChanged, this, &MainWindow::filtrare);

    reloadTable();
    creeazaFerestreStari();
    service.addObserver(this);
}

void MainWindow::reloadTable() {
    tableModel->updateModel(service.getAll());
}

void MainWindow::adaugare() {
    int id = idEdit->text().toInt();
    const string &denumire = denumireEdit->text().toStdString();

    const string &nume = programatoriEdit->text().toStdString();
    vector<string> programatori;

    stringstream ss(nume);
    string p;
    while (ss >> p)
        programatori.push_back(p);

    const string &stare = stareEdit->text().toStdString();

    try {
        service.adaugare_service(id, denumire, programatori, stare);
        reloadTable();
    } catch (const exception &e) {
        QMessageBox::warning(this, "Eroare", QString::fromStdString(e.what()));
    }

    idEdit->clear();
    denumireEdit->clear();
    programatoriEdit->clear();
    stareEdit->clear();
}

void MainWindow::filtrare() {
    const string programator = filterEdit->text().toStdString();

    if (programator.empty()) {
        reloadTable();
        return;
    }

    vector<int> IDuri;
    service.filtrare_service(IDuri, programator);

    vector<Task> filtrate;
    const auto &all = service.getAll();
    for (const Task &t: all)
        if (std::find(IDuri.begin(), IDuri.end(), t.getId()) != IDuri.end())
            filtrate.push_back(t);

    tableModel->updateModel(filtrate);
}

void MainWindow::creeazaFerestreStari() {
    for (const auto &stare : service.getKeywords()) {
        auto *win = new WindowStare(service, stare);
        win->show();
    }
}

void MainWindow::update() {
    reloadTable();
}
