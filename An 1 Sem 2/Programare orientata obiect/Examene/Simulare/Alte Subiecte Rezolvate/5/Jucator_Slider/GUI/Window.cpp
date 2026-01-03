#include "Window.h"
#include "Window.h"

MainWindow::MainWindow(ServiceJucatori &service, QWidget *parent): QWidget(parent), service(service) {
    table = new QTableWidget(0,4);
    table->setHorizontalHeaderLabels({"Nume", "Tara", "Puncte", "Ranc"});
    table->setSelectionBehavior(QAbstractItemView::SelectRows);

    slider = new QSlider(Qt::Vertical);
    slider->setRange(1, 100);
    slider->setTickPosition(QSlider::TicksLeft);
    slider->setTickInterval(5);
    slider->setValue(50);

    const auto formLayout = new QFormLayout();
    formLayout->addRow("Nume", numeEdit = new QLineEdit());
    formLayout->addRow("Tara", taraEdit = new QLineEdit());
    formLayout->addRow("Puncte", slider);

    const auto buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(AddBtn = new QPushButton("Add"));
    buttonLayout->addWidget(GenBtn = new QPushButton("Generate Match"));

    const auto rightLayout = new QVBoxLayout();
    rightLayout->addLayout(formLayout);
    rightLayout->addLayout(buttonLayout);

    const auto nonFilteringLayout = new QHBoxLayout();
    nonFilteringLayout->addWidget(table,3);
    nonFilteringLayout->addLayout(rightLayout);

    const auto mainLayout = new  QVBoxLayout(this);
    mainLayout->addLayout(nonFilteringLayout);

    connect(AddBtn, &QPushButton::clicked, this, &MainWindow::adaugare);
    connect(GenBtn, &QPushButton::clicked, this, &MainWindow::alegere);

    reloadTableFromList();


    const auto radioLayout = new QHBoxLayout();
    buttonGroup = new QButtonGroup();
    buttonGroup->setExclusive(true);

    const auto tari = service.raportTara();

    for (const auto &tara: tari) {
        auto *btn = new QRadioButton(QString::fromStdString(tara));
        radioLayout->addWidget(btn);
        buttonGroup->addButton(btn);

        connect(btn, &QRadioButton::clicked, this, &MainWindow::raport);
    }

    mainLayout->addLayout(radioLayout);
}

void MainWindow::reloadTableFromList() {
    table->clearContents();
    int row = 0;
    for (const auto &j: service.getAll()) {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(j.getNume())));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(j.getTara())));
        table->setItem(row, 2, new QTableWidgetItem(QString::number(j.getPuncte())));
        table->setItem(row, 3, new QTableWidgetItem(QString::number(j.getRank())));
        row ++;
    }
}

void MainWindow::adaugare() {
    const auto nume = numeEdit->text().toStdString();
    const auto tara = taraEdit->text().toStdString();
    const int puncte = slider->value();

    service.adaugare_cu_rank(nume, tara, puncte);
    reloadTableFromList();
}

void MainWindow::raport() {
    const auto selected = buttonGroup->checkedButton();
    const auto taraSelectata = selected->text().toStdString();

    table->clearContents();
    table->setRowCount(0);

    int row = 0;
    for (const auto &j: service.getAll())
        if (j.getTara() == taraSelectata){
            table->insertRow(row);
            table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(j.getNume())));
            table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(j.getTara())));
            table->setItem(row, 2, new QTableWidgetItem(QString::number(j.getPuncte())));
            table->setItem(row, 3, new QTableWidgetItem(QString::number(j.getRank())));
            row ++;
        }
}

void MainWindow::alegere() {
    const auto jucatori = service.alegere_jucatori();
    const auto &j1 = jucatori[0];
    const auto &j2 = jucatori[1];

    const QStringList scoruri = {"6-1", "6-2", "6-3", "6-4", "7-5"};
    QString scor1 = scoruri[rand() % scoruri.size()];
    QString scor2 = scoruri[rand() % scoruri.size()];

    QString rezultat = QString("[%1] %2 vs [%3] %4\nScor: %5 %6")
            .arg(QString::number(j1.getRank()))
            .arg(QString::fromStdString(j1.getNume()))
            .arg(QString::number(j2.getRank()))
            .arg(QString::fromStdString(j2.getNume()))
            .arg(scor1)
            .arg(scor2);

    QMessageBox::information(this, "Meci Generat", rezultat);
}
