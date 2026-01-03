#include "Window.h"

MainWindow::MainWindow(ServiceJoc &s, QWidget *parent) : QWidget(parent), service(s) {
    table = new QTableView();
    tableModel = new ModelTabelJoc(this);
    table->setModel(tableModel);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    const auto addLayout = new QFormLayout();
    addLayout->addRow("Dimensiune", adaugaDimEdit = new QLineEdit());
    addLayout->addRow("Tabla", adaugaTabEdit = new QLineEdit());
    addLayout->addRow("Jucator", adaugaJocEdit = new QLineEdit());
    addLayout->addWidget(addBtn = new QPushButton("Adauga"));

    const auto modLayout = new QFormLayout();
    modLayout->addRow("Dimensiune", modificaDimEdit = new QLineEdit());
    modLayout->addRow("Tabla", modificaTabEdit = new QLineEdit());
    modLayout->addRow("Jucator", modificaJocEdit = new QLineEdit());
    modLayout->addRow("Stare", modificaStareEdit = new QLineEdit());
    modLayout->addWidget(modBtn = new QPushButton("Modifica"));

    const auto funcLayout = new QVBoxLayout();
    funcLayout->addLayout(addLayout);
    funcLayout->addLayout(modLayout);

    gridLayout = new QGridLayout();
    gridWrapper = new QWidget();
    gridWrapper->setLayout(gridLayout);

    const auto mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(table);
    mainLayout->addLayout(funcLayout);
    mainLayout->addWidget(gridWrapper);

    connect(addBtn, &QPushButton::clicked, this, &MainWindow::adaugare);
    connect(modBtn, &QPushButton::clicked, this, &MainWindow::modificare);
    connect(table->selectionModel(), &QItemSelectionModel::currentChanged, this, &MainWindow::joc);

    reloadTable();
}

void MainWindow::reloadTable() {
    tableModel->updateModel(service.getAll());

    // Tabelul sa ramana in sync cu jocul
    if (selectedRow >= 0 && selectedRow < tableModel->rowCount({})) {
        QModelIndex idx = tableModel->index(selectedRow, 0);
        table->selectionModel()->setCurrentIndex(idx, QItemSelectionModel::Select | QItemSelectionModel::Rows);
    }
}

void MainWindow::adaugare() {
    int dim = adaugaDimEdit->text().toInt();
    const string tabla = adaugaTabEdit->text().toStdString();
    const string jucator = adaugaJocEdit->text().toStdString();

    service.adauga_service(dim, tabla, jucator);
    reloadTable();
}

void MainWindow::modificare() {
    const auto index = table->currentIndex();
    if (!index.isValid())
        return;

    int row = index.row();
    int id = tableModel->getJocAtRow(row).getId();

    int dim = modificaDimEdit->text().toInt();
    const string tabla = modificaTabEdit->text().toStdString();
    const string jucator = modificaJocEdit->text().toStdString();
    const string stare = modificaStareEdit->text().toStdString();

    try {
        service.modifica_service(id, dim, tabla, jucator, stare);
        reloadTable();
    } catch (const exception &e) {
        QMessageBox::warning(this, "Eroare Validare", e.what());
    }
}


void MainWindow::joc() {
    const QModelIndex idx = table->currentIndex();
    if (!idx.isValid()) {
        selectedRow = -1;
        return;
    }

    selectedRow = idx.row();
    const Joc &j = tableModel->getJocAtRow(selectedRow);
    updateGrid(j);
}

void MainWindow::updateGrid(const Joc &j) {
    const int dim = j.getDimensiune();
    const string &tabla = j.getTabla();

    // Curatam butoanele vechi
    QLayoutItem *copil;
    while ((copil = gridLayout->takeAt(0)) != nullptr) {
        delete copil->widget();
        delete copil;
    }
    gridBtns.clear();

    // pregatim dimensiunea noua
    currentGridDim = dim;

    // Pregatim butoanele noi
    for (int i = 0; i < dim * dim; ++i) {
        QPushButton *btn = new QPushButton(QString(tabla[i]));
        btn->setFixedSize(50, 50);
        gridLayout->addWidget(btn, i / dim, i % dim);
        gridBtns.push_back(btn);

        connect(btn, &QPushButton::clicked, this, [=]() {
            handleCellClick(i);
        });
    }
}

void MainWindow::handleCellClick(int index) {
    if (selectedRow < 0 || selectedRow >= service.getAll().size())
        return;

    const Joc &joc = service.getAll()[selectedRow]; // luam jocul actual
    string table = joc.getTabla();
    if (table[index] != '-') return;

    // facem miscarea
    table[index] = joc.getJucator()[0];

    // schimbam jucatorul
    string nextPlayer = (joc.getJucator() == "X") ? "O" : "X";

    // schimbam starea daca e cazul
    string newState = (table.find('-') == string::npos) ? "Terminat" : "In derulare";

    try {
        service.modifica_service(joc.getId(), joc.getDimensiune(), table, nextPlayer, newState);
        reloadTable();

        // Modificam butoanele cu jocul nou
        const Joc &updated = service.getAll()[selectedRow];
        updateGrid(updated);
    } catch (const exception &e) {
        QMessageBox::warning(this, "Eroare la mutare", e.what());
    }
}
