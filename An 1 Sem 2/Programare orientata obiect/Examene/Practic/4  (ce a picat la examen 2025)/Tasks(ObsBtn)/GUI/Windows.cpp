#include "Windows.h"

WindowStare::WindowStare(ServiceTask &se, const string &st, QWidget *parent) : QWidget(parent), service(se), stare(st) {
    table = new QTableView();
    tableModel = new ModelTabelTask();
    table->setModel(tableModel);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    const auto btnLayout = new QVBoxLayout();
    btnLayout->addWidget(OpenBtn = new QPushButton("Open"));
    btnLayout->addWidget(InprogressBtn = new QPushButton("In Progress"));
    btnLayout->addWidget(ClosedBtn = new QPushButton("Closed"));

    const auto mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(table);
    mainLayout->addLayout(btnLayout);

    connect(OpenBtn, &QPushButton::clicked, this, [&]() { modifca("open"); });
    connect(InprogressBtn, &QPushButton::clicked, this, [&]() { modifca("inprogress"); });
    connect(ClosedBtn, &QPushButton::clicked, this, [&]() { modifca("closed"); });

    service.addObserver(this);
    this->setWindowTitle(QString::fromStdString(stare));

    update();
}

void WindowStare::modifca(const string &s) {
    auto index = table->currentIndex();
    if (!index.isValid()) return;

    int row = index.row();
    int id = tableModel->getTaskAt(row).getId();

    service.set_stare_service(id, s);
}

void WindowStare::update() {
    vector<Task> filtrate;
    for (const auto &t : service.getAll())
        if (t.getStare() == stare)
            filtrate.push_back(t);

    tableModel->updateModel(filtrate);
}

WindowStare::~WindowStare() {
    service.removeObserver(this);
}
