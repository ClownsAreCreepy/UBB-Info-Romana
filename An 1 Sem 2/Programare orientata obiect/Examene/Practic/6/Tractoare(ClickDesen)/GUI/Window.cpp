#include "Window.h"

MainWindow::MainWindow(ServiceTractoare &s, QWidget *parent) : QWidget(parent), service(s) {
    table = new QTableView();
    tableModel = new ModelTabelTractoare(service, this);
    table->setModel(tableModel);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    const auto formLayout = new QFormLayout();
    formLayout->addRow("Id", idEdit = new QLineEdit());
    formLayout->addRow("Denumire", denumireEdit = new QLineEdit());
    formLayout->addRow("Tip", tipEdit = new QLineEdit());
    formLayout->addRow("Nr. Roti", rotiEdit = new QLineEdit());
    formLayout->addWidget(addBtn = new QPushButton("Adauga"));

    filterBox = new QComboBox();

    const auto funcLayout = new QVBoxLayout();
    funcLayout->addLayout(formLayout);
    funcLayout->addWidget(filterBox);

    const auto mainLayout = new QHBoxLayout();
    mainLayout->addWidget(table);
    mainLayout->addLayout(funcLayout);

    roti = new DesenareRoti();
    roti->setFixedHeight(100);

    const auto fullLayout = new QVBoxLayout(this);
    fullLayout->addLayout(mainLayout);
    fullLayout->addWidget(roti);

    connect(addBtn, &QPushButton::clicked, this, &MainWindow::adaugare);
    connect(filterBox, &QComboBox::currentTextChanged, this, &MainWindow::filtrare);
    connect(table->selectionModel(), &QItemSelectionModel::currentChanged, this, &MainWindow::paintRoti);
    connect(roti, &DesenareRoti::roataClick, this, &MainWindow::clickOnRoata);

    reloadTable();

}

void MainWindow::reloadTable() {
    tableModel->updateModel(service.getAll());

    filterBox->clear();
    filterBox->addItem("");

    set<string> tipuri;
    service.getTipuri(tipuri);
    for (const string &tip: tipuri) {
        filterBox->addItem(QString::fromStdString(tip));
    }
}

void MainWindow::adaugare() {
    int id = idEdit->text().toInt();
    const string &denumire = denumireEdit->text().toStdString();
    const string &tip = tipEdit->text().toStdString();
    int nrRoti = rotiEdit->text().toInt();

    try {
        service.adaugare_service(id, denumire, tip, nrRoti);
        reloadTable();
    } catch (const exception &e) {
        QMessageBox::warning(this, "Eroare Validare", e.what());
    }
}

void MainWindow::filtrare() {
    const string &tip = filterBox->currentText().toStdString();
    tableModel->setTipFiltrat(tip);
}

void MainWindow::paintRoti() {
    const QModelIndex index = table->selectionModel()->currentIndex();
    if (!index.isValid()) return;

    const Tractor &tractor = tableModel->getTractorAtRow(index.row());
    roti->setNrRoti(tractor.getRoti());
}

void MainWindow::clickOnRoata() {
    const auto index = table->selectionModel()->currentIndex();
    if (!index.isValid()) return;

    int row = index.row();
    const Tractor &tractor = tableModel->getTractorAtRow(row);

    if (tractor.getRoti() <= 2)
        return;

    service.decrementare(tractor.getId());
    reloadTable();

    QModelIndex newIndex = tableModel->index(row, 3);
    table->selectRow(row);
    table->selectionModel()->setCurrentIndex(newIndex, QItemSelectionModel::SelectCurrent);

    roti->setNrRoti(tractor.getRoti());
}
