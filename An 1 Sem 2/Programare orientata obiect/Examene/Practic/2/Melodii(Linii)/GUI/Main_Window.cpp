#include "Main_Window.h"

MainWindow::MainWindow(ServiceMelodii &service, QWidget *parent) : QWidget(parent), service(service) {
    table = new QTableView();
    tableModel = new ModelTableMelodii(service, this);
    table->setModel(tableModel);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    slider = new QSlider(Qt::Horizontal);
    slider->setRange(1,10);
    slider->setTickPosition(QSlider::TicksRight);
    slider->setTickInterval(1);
    slider->setValue(1);

    const auto formLayout = new QFormLayout();
    formLayout->addRow("Titlu", titluEdit = new QLineEdit());
    formLayout->addRow("Rank", slider);

    const auto btnLayout = new QVBoxLayout();
    btnLayout->addStretch();
    btnLayout->addLayout(formLayout);
    btnLayout->addWidget(ModBtn = new QPushButton("Modifica"));
    btnLayout->addWidget(DelBtn = new QPushButton("Sterge"));
    btnLayout->addStretch();

    const auto tableLayout = new QHBoxLayout();
    tableLayout->addWidget(table);
    tableLayout->addLayout(btnLayout);

    const auto mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(tableLayout);
    mainLayout->addStretch();

    connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWindow::selectare);
    connect(ModBtn, &QPushButton::clicked, this, &MainWindow::modificare);
    connect(DelBtn, &QPushButton::clicked, this, &MainWindow::stergere);

    reloadTableFromCurrent();
    this->setContentsMargins(0,0,0,200);
}

void MainWindow::reloadTableFromCurrent() const{
    tableModel->updateModel(service.getAll());
}

void MainWindow::selectare() {
    const auto selected = table->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) return;

    int row = selected.first().row();
    const auto& m = service.getAll().at(row);

    titluEdit->setText(QString::fromStdString(m.getTitlu()));
    slider->setValue(m.getRank());
}

void MainWindow::modificare() {
    const auto selected = table->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Atentie", "Nicio melodie selectata!");
        return;
    }

    int row = selected.first().row();
    int id = service.getAll().at(row).getId();

    QString new_title = titluEdit->text();
    int new_rank = slider->value();

    if (new_title.trimmed().isEmpty()) {
        QMessageBox::warning(this, "Eroare", "Titlu nu poate fi gol!");
        return;
    }

    service.modifica_service(id, new_title.toStdString(), new_rank);
    reloadTableFromCurrent();

    table->selectRow(row);
}

void MainWindow::stergere() {
    const auto selected = table->selectionModel()->selectedIndexes();
    if (selected.isEmpty()) {
        QMessageBox::warning(this, "Atentie", "Nicio melodie selectata!");
        return;
    }

    int row = selected.first().row();
    const auto m = service.getAll().at(row);
    try {
        service.sterge_service(m.getId(), m.getArtist());
        reloadTableFromCurrent();
    } catch (const exception &e) {
        QMessageBox::warning(this, "Bun simt error", e.what());
        return;
    }

    table->selectRow(row);
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);    //smooth edges

    const auto &melodii = service.getAll();

    // numaram rank-urile
    map<int, int> rank_count;
    for (const auto &m: melodii)
        rank_count[m.getRank()] ++;

    //luam cat spatiu orizontal avem
    int chart_height = 200;
    int chart_y_start = height() - chart_height;
    int chart_width = width();
    int bar_width = chart_width / 10;

    //luam un max
    int max_count = 0;
    for (const auto &[rank, count]: rank_count)
        max_count = max(max_count, count);

    for (int rank = 1; rank <= 10; ++rank) {
        int count = rank_count[rank];
        int bar_height = max_count > 0 ? static_cast<int>(count / static_cast<double>(max_count) * chart_height) : 0;

        int x = (rank - 1) * bar_width;

        QRect bar (x + 2, chart_y_start + (chart_height - bar_height), bar_width - 4, bar_height);
        p.setBrush(Qt::magenta);
        p.drawRect(bar);
        p.drawText(x + bar_width / 2 - 5, height() - 5, QString::number(rank));
    }
}
