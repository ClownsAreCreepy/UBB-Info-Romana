#include "contract_window.h"

ContractWindow::ContractWindow(ServiceDisciplina &serv, QWidget *parent) : QWidget(parent), service(serv) {
    contractTable = new QTableWidget(0, 4);
    contractTable->setHorizontalHeaderLabels({"Nume", "Ore", "Tip", "Profesor"});
    contractTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    contractTable->setSelectionMode(QAbstractItemView::SingleSelection);

    // Add-by-name field + button
    addbyname = new QLineEdit();
    addbyname->setPlaceholderText("Enter name to add...");
    Addbtn = new QPushButton("Add by name");

    // Generate field + buttons
    numGenerateEdit = new QLineEdit();
    numGenerateEdit->setPlaceholderText("How many to generate:");

    GenBtn = new QPushButton("Generate");
    ClrBtn = new QPushButton("Clear");
    ExpBtn = new QPushButton("Export");

    // layout
    auto *rightLayout = new QVBoxLayout();

    rightLayout->addWidget(addbyname);
    rightLayout->addWidget(Addbtn);
    rightLayout->addSpacing(10);

    rightLayout->addWidget(numGenerateEdit);
    rightLayout->addWidget(GenBtn);
    rightLayout->addSpacing(10);

    // final buttons
    rightLayout->addWidget(ClrBtn);
    rightLayout->addWidget(ExpBtn);

    // le unim
    auto *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(contractTable, 3);
    mainLayout->addLayout(rightLayout, 2);


    //Conectam butoanele
    connect(Addbtn, &QPushButton::clicked, this, &ContractWindow::addByName);
    connect(GenBtn, &QPushButton::clicked, this, &ContractWindow::generateRandom);
    connect(ClrBtn, &QPushButton::clicked, this, &ContractWindow::clearContract);
    connect(ExpBtn, &QPushButton::clicked, this, &ContractWindow::exportContract);

    this->setMinimumSize(767, 289);

    service.addObserver(this);
    reloadContract();
}


void ContractWindow::addByName() {
    const auto name = addbyname->text().toStdString();
    if (name.empty()) {
        QMessageBox::warning(this, "Input error", "Introduceti un nume.");
        return;
    }

    try {
        service.contract_adauga(name);
        reloadContract();
    } catch (const ContractException &ce) {
        const QString msg = QString::fromStdString(ce.getMesaj());

        if (msg.contains("Doriti un profesor anume")) {
            const QString prof = QInputDialog::getText(this, "Profesorul necesar",
                                                       "Introduceti numele profesorului (lasati gol daca nu vreti un profesor specific):");
            try {
                const string dorinta = prof.isEmpty() ? "nu" : "yeah";
                service.contract_adauga(name, prof.toStdString(), dorinta);
                reloadContract();
                return;
            } catch (const ContractException &ce2) {
                QMessageBox::warning(this, "Contract error", QString::fromStdString(ce2.getMesaj()));
                return;
            }
        }
        QMessageBox::warning(this, "Contract error", msg);
    }
}


void ContractWindow::generateRandom() {
    bool ok = false;
    const auto count = numGenerateEdit->text().toInt(&ok);

    if (!ok || count <= 0) {
        QMessageBox::warning(this, "Input error", "Introduceti un numar valid (> 0)!");
        return;
    }

    try {
        service.contract_generare(count);
        reloadContract();
    } catch (const ContractException &ce) {
        QMessageBox::warning(this, "Contract error", QString::fromStdString(ce.getMesaj()));
    }
}


void ContractWindow::clearContract() {
    try {
        service.contract_goleste();
        reloadContract();
    } catch (const ContractException &ce) {
        QMessageBox::warning(this, "Contract error", QString::fromStdString(ce.getMesaj()));
    }
}


void ContractWindow::exportContract() {
    const QString path = QFileDialog::getSaveFileName(this, "Export contract", "", "Text Files (*.txt);;All Files (*)");


    if (path.isEmpty()) return;

    try {
        service.contract_exporta(path.toStdString());
        QMessageBox::information(this, "Export", "Contract exportat cu succes!");
    } catch (const FileException &fe) {
        QMessageBox::warning(this, "File error", QString::fromStdString(fe.getMesaj()));
    }
}


void ContractWindow::reloadContract() const {
    contractTable->clearContents();
    contractTable->setRowCount(0);
    const auto &list = service.contract_getAll();

    int row = 0;
    for (const auto &d: list) {
        contractTable->insertRow(row);
        contractTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(d.getNume())));
        contractTable->setItem(row, 1, new QTableWidgetItem(QString::number(d.getOre())));
        contractTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(d.getTip())));
        contractTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(d.getProfesor())));
        row++;
    }
}


void ContractWindow::update() {
    reloadContract();
}


ContractWindow::~ContractWindow() {
    service.removeObserver(this);
}
