#include "Window.h"

MainWindow::MainWindow(ServiceMelodii &service, QWidget *parent) : QWidget(parent) , service(service) {
    table = new QTableView();
    tableModel = new ModelTableMelodii(service, this);
    table->setModel(tableModel);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    const auto formLayout = new QFormLayout();
    formLayout->addRow("Titlu", titluEdit = new QLineEdit());
    formLayout->addRow("Artist", artistEdit = new QLineEdit());
    formLayout->addRow("Gen", genEdit = new QLineEdit());
    formLayout->addRow(AddBtn = new QPushButton("Adauga"));

    const auto funcLayout = new QVBoxLayout();
    funcLayout->addLayout(formLayout);
    funcLayout->addWidget(DelBtn = new QPushButton("Sterge"));

    const auto mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(table);
    mainLayout->addLayout(funcLayout);

    connect(AddBtn, &QPushButton::clicked, this, &MainWindow::adaugare);
    connect(DelBtn, &QPushButton::clicked, this, &MainWindow::stergere);

    reloadTable();
    this->setContentsMargins(50,50,50,50);
}

void MainWindow::reloadTable() const {
    tableModel->updateModel(service.getAll());
}

void MainWindow::adaugare() {
    const QString &titlu = titluEdit->text();
    const QString &artist = artistEdit->text();
    const QString &gen = genEdit->text();

    service.adauga_service(titlu.toStdString(), artist.toStdString(), gen.toStdString());
    reloadTable();
    update();
}

void MainWindow::stergere() {
    const auto selected = table->selectionModel()->selectedIndexes();
    int row = selected.first().row();
    service.stergere_service(row);
    reloadTable();
    update();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    //QWidget::paintEvent(event);     // call base so the default painting still happens
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);    //smooth edges

    const vector<string> genres = { "pop", "rock", "folk", "disco"};
    const auto &melodii = service.getAll();

    //pozitii
    // QPoint topLeft(0 + 50, 0 + 50);
    // QPoint topRight(width() - 50, 0 + 50);
    // QPoint bottomLeft(0 + 50, height() - 50);
    // QPoint bottomRight(width() - 50, height() - 50);

    map<string, QPoint> genreCenters = {
        {"pop", QPoint(50, 50)},
        {"rock", QPoint(width() - 50, 50)},
        {"folk", QPoint(50, height() - 50)},
        {"disco", QPoint(width() - 50, height() - 50)}
    };

    for (const auto &genre : genres) {
        int count = service.melodii_cu_acelasi_gen(genre) + 1;
        if (count == 0) continue;

        const QPoint center = genreCenters[genre];
        int radius = 10;

        for (int i = 0; i < count; ++i) {
            p.drawEllipse(center, radius, radius);
            radius += 5;
        }
    }
}
