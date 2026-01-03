#include "main_window.h"

MainWindow::MainWindow(ServiceDisciplina &serv, QWidget *parent) : QWidget{parent}, service(serv) {
    // table
    table = new QTableView();
    tableModel = new ModelTabelDisciplina(this);
    table->setModel(tableModel);
    table->setSelectionBehavior(QAbstractItemView::SelectRows); //one cel = whole row
    table->setSelectionMode(QAbstractItemView::SingleSelection); //only one row

    // list
    list = new QListView();
    listModel = new ModelListaDisciplina(this);
    list->setModel(listModel);
    list->setSelectionMode(QAbstractItemView::SingleSelection);

    // form
    const auto formLayout = new QFormLayout();
    formLayout->addRow("Materie:", nameEdit = new QLineEdit());
    nameEdit->setPlaceholderText("Caligrafie");
    formLayout->addRow("Ore:", hoursEdit = new QLineEdit());
    hoursEdit->setPlaceholderText("6");
    formLayout->addRow("Tip:", typeEdit = new QLineEdit());
    typeEdit->setPlaceholderText("Uman / Real / ??");
    formLayout->addRow("Profesor:", profEdit = new QLineEdit());
    profEdit->setPlaceholderText("Mimi");

    // CRUD btns, under form
    const auto crudLayout = new QHBoxLayout();
    AddBtn = makeBtn("Add", "Adauga o disciplina noua", crudLayout, this);
    ModBtn = makeBtn("Update", "Modifica o disciplina existenta", crudLayout, this);
    DelBtn = makeBtn("Remove", "Sterge o disciplina", crudLayout, this);

    // le unim
    const auto formAndCrudLayout = new QVBoxLayout();
    formAndCrudLayout->addLayout(formLayout);
    formAndCrudLayout->addLayout(crudLayout);

    const auto rightFormBox = new QWidget();
    rightFormBox->setLayout(formAndCrudLayout);

    // main top layout: table left, form+crud right
    const auto topLayout = new QHBoxLayout();
    topLayout->addWidget(table, 3);
    topLayout->addWidget(rightFormBox, 2);
    topLayout->addWidget(list, 3);

    // sort btns
    const auto sortLayout = new QHBoxLayout();
    SortNameBtn = makeBtn("Sort by name", "Sorteaza disciplinele dupa nume", sortLayout, this);
    SortHoursBtn = makeBtn("Sort by hours", "Sorteaza disciplinele dupa ore", sortLayout, this);
    SortProfBtn = makeBtn("Sort by prof + type", "Sorteaza disciplinele dupa profesor, apoi dupa tip", sortLayout,
                          this);


    // filter btns
    const auto filterLayout = new QHBoxLayout();
    FilterHoursBtn = makeBtn("Filter by hours", "Filtreaza disciplinele dupa un numar de ore", filterLayout, this);
    FilterProfBtn = makeBtn("Filter by prof", "Filtreaza disciplinele dupa un numele profesorului", filterLayout, this);


    // undo left, contract right
    const auto miscLayout = new QHBoxLayout();
    UndoBtn = makeBtn("Undo", "Refa ultima operatie", miscLayout, this);
    miscLayout->addStretch();
    ContractROBtn = makeBtn("Contract: View-Only",
                            "Deschide fereastra cu atatea imagini cate discipline sunt in contractul", miscLayout,
                            this);
    miscLayout->addStretch();
    ContractBtn = makeBtn("Contract: CRUD", "Deschide fereastra pentru a vizualiza si modifica contractul", miscLayout,
                          this);


    // functionalitati pentru contract
    auto contractBarLayout = new QHBoxLayout();

    contractAddNameEdit = new QLineEdit();
    contractAddNameEdit->setPlaceholderText("Add by name...");
    contractBarLayout->addWidget(contractAddNameEdit);
    ContractAddNameBtn = makeBtn("Add", "Adauga o disciplina dupa nume in contract", contractBarLayout, this);

    contractGenerateEdit = new QLineEdit();
    contractGenerateEdit->setPlaceholderText("How many to generate");
    contractBarLayout->addWidget(contractGenerateEdit);
    ContractGenerateBtn = makeBtn("Generate", "Introduce un numar de discipline in contract", contractBarLayout, this);

    ContractClearBtn = makeBtn("Clear", "Sterge toate disciplinele din contract", contractBarLayout, this);


    // tip raport
    tipWidget = new QWidget;
    tipLayout = new QHBoxLayout(tipWidget);


    // main vertical layout
    const auto mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(sortLayout);
    mainLayout->addLayout(filterLayout);
    mainLayout->addWidget(tipWidget);
    mainLayout->addLayout(miscLayout);
    mainLayout->addLayout(contractBarLayout);


    //Tweaks pentru filtru si sort
    FilterProfBtn->setCheckable(true);
    FilterHoursBtn->setCheckable(true);
    SortNameBtn->setCheckable(true);
    SortHoursBtn->setCheckable(true);
    SortProfBtn->setCheckable(true);

    setupConnections();

    currentView.clear();
    for (const auto &d: service.getAll())
        currentView.emplace_back(d);

    reloadTableFromCurrent();
    reloadListFromCurrent();
    generateTipButtons();

    this->setMinimumSize(1166, 497);
}


void MainWindow::setupConnections() {
    connect(AddBtn, &QPushButton::clicked, this, &MainWindow::addDisciplina);
    connect(ModBtn, &QPushButton::clicked, this, &MainWindow::modDisciplina);
    connect(DelBtn, &QPushButton::clicked, this, &MainWindow::delDisciplina);
    connect(UndoBtn, &QPushButton::clicked, this, &MainWindow::undoActiune);
    connect(FilterProfBtn, &QPushButton::clicked, this, &MainWindow::filterProf);
    connect(FilterHoursBtn, &QPushButton::clicked, this, &MainWindow::filterOre);
    connect(SortNameBtn, &QPushButton::clicked, this, &MainWindow::sortNume);
    connect(SortHoursBtn, &QPushButton::clicked, this, &MainWindow::sortOre);
    connect(SortProfBtn, &QPushButton::clicked, this, &MainWindow::sortProfTip);
    connect(ContractBtn, &QPushButton::clicked, this, &MainWindow::openContractWindow);
    connect(ContractROBtn, &QPushButton::clicked, this, &MainWindow::openContractWindowROnly);
    connect(ContractAddNameBtn, &QPushButton::clicked, this, &MainWindow::addByName);
    connect(ContractGenerateBtn, &QPushButton::clicked, this, &MainWindow::generateRandom);
    connect(ContractClearBtn, &QPushButton::clicked, this, &MainWindow::clearContract);


    //conectam tabelul cu lista
    connect(table->selectionModel(), &QItemSelectionModel::currentChanged, this, &MainWindow::syncListFromTable);
    connect(list->selectionModel(), &QItemSelectionModel::currentChanged, this, &MainWindow::syncTableFromList);
}


void MainWindow::addDisciplina() {
    const auto nume = nameEdit->text().toStdString();
    const auto tip = typeEdit->text().toStdString();
    const auto prof = profEdit->text().toStdString();

    try {
        if (const auto ore = getValidNumber(hoursEdit); ore)
            service.adauga_service(nume, *ore, tip, prof);
    } catch (const ValidationException &ve) {
        QMessageBox::warning(this, "Validation error", QString::fromStdString(ve.getMesaj()));
        return;
    } catch (const RepoException &re) {
        QMessageBox::warning(this, "Repo error", QString::fromStdString(re.getMesaj()));
        return;
    }

    reapply_filters();
    reapply_sorts();
    reloadTableFromCurrent();
    reloadListFromCurrent();
    generateTipButtons();
}


void MainWindow::modDisciplina() {
    const auto nume = nameEdit->text().toStdString();
    const auto tip = typeEdit->text().toStdString();
    const auto prof = profEdit->text().toStdString();

    int row = -1;
    if (table->selectionModel()->hasSelection()) {
        if (const QModelIndex index = table->selectionModel()->currentIndex(); index.isValid())
            row = index.row();
    } else if (list->selectionModel()->hasSelection()) {
        if (const QModelIndex index = list->selectionModel()->currentIndex(); index.isValid())
            row = index.row();
    }

    if (row == -1) {
        QMessageBox::warning(this, "No selection", "Va rog selectati disciplina pe care doriti sa o modificati.");
        return;
    }

    const Disciplina &d = currentView[static_cast<size_t>(row)];

    //gasim indexul in repo-ul adevarat
    int realIndex = -1;
    const auto &all = service.getAll();
    for (size_t i = 0; i < all.size(); ++i)
        if (all[i] == d) {
            realIndex = static_cast<int>(i);
            break;
        }

    try {
        if (const auto ore = getValidNumber(hoursEdit); ore)
            service.modifica_service(realIndex, nume, *ore, tip, prof);
        reapply_filters();
        reapply_sorts();
        reloadTableFromCurrent();
        reloadListFromCurrent();
        generateTipButtons();
    } catch (const ValidationException &ve) {
        QMessageBox::warning(this, "Validation error", QString::fromStdString(ve.getMesaj()));
    } catch (const RepoException &re) {
        QMessageBox::warning(this, "Repo error", QString::fromStdString(re.getMesaj()));
    }
}


void MainWindow::delDisciplina() {
    int row = -1;
    if (table->selectionModel()->hasSelection()) {
        if (const QModelIndex index = table->selectionModel()->currentIndex(); index.isValid())
            row = index.row();
    } else if (list->selectionModel()->hasSelection()) {
        if (const QModelIndex index = list->selectionModel()->currentIndex(); index.isValid())
            row = index.row();
    }

    if (row == -1) {
        QMessageBox::warning(this, "No selection", "Va rog selectati disciplina pe care doriti sa o stergeti.");
        return;
    }

    const Disciplina &d = currentView[static_cast<size_t>(row)];

    //gasim indexul in repo-ul adevarat
    int realIndex = -1;
    const auto &all = service.getAll();
    for (size_t i = 0; i < all.size(); ++i)
        if (all[i] == d) {
            realIndex = static_cast<int>(i);
            break;
        }

    service.sterge_service(realIndex);


    reapply_filters();
    reapply_sorts();
    reloadTableFromCurrent();
    reloadListFromCurrent();
    generateTipButtons();
}


void MainWindow::undoActiune() {
    try {
        service.undo();
        reapply_filters();
        reapply_sorts();
        reloadTableFromCurrent();
        reloadListFromCurrent();
        generateTipButtons();
    } catch (const RepoException &re) {
        QMessageBox::warning(this, "Repo error", QString::fromStdString(re.getMesaj()));
    }
}


void MainWindow::filterProf() {
    if (FilterProfBtn->isChecked()) {
        //dezactivam filtru de ore si sorturile
        FilterHoursBtn->setChecked(false);
        filteringByHours = false;
        lastHoursFilter = -1;
        deactivate_sorts();

        //activam filtru de profi
        bool ok;
        const QString prof = QInputDialog::getText(this, "Filter", "Introduceti numele profesorului:",
                                                   QLineEdit::Normal, "", &ok);
        if (!ok || prof.isEmpty()) {
            FilterProfBtn->setChecked(false);
            return;
        }

        lastProfFilter = prof;
        filteringByProf = true;

        vector<Disciplina> filtrate;
        service.filtrare_profesor(prof.toStdString(), filtrate);
        currentView = std::move(filtrate);

        reapply_sorts();
        reloadTableFromCurrent();
        reloadListFromCurrent();
    } else {
        //deactivam filtru
        filteringByProf = false;
        lastProfFilter.clear();

        currentView.clear();
        for (const auto &d: service.getAll())
            currentView.emplace_back(d);

        reapply_sorts();
        reloadTableFromCurrent();
        reloadListFromCurrent();
    }
}


void MainWindow::filterOre() {
    if (FilterHoursBtn->isChecked()) {
        //dezactivam filtru de profi si sorturile
        FilterProfBtn->setChecked(false);
        filteringByProf = false;
        lastProfFilter.clear();
        deactivate_sorts();

        //activam filtru
        bool ok;
        const int ore = QInputDialog::getInt(this, "Filter", "Introduceti numarul de ore:", 0, 0, 10000, 1, &ok);
        if (!ok) {
            FilterHoursBtn->setChecked(false);
            return;
        }

        lastHoursFilter = ore;
        filteringByHours = true;

        vector<Disciplina> filtrate;
        service.filtrare_ore(ore, filtrate);
        currentView = std::move(filtrate);

        reapply_sorts();
        reloadTableFromCurrent();
        reloadListFromCurrent();
    } else {
        //deactivam filtru
        filteringByHours = false;
        lastHoursFilter = -1;

        currentView.clear();
        for (const auto &d: service.getAll())
            currentView.emplace_back(d);

        reapply_sorts();
        reloadTableFromCurrent();
        reloadListFromCurrent();
    }
}


void MainWindow::sortNume() {
    sortingByName = SortNameBtn->isChecked();

    if (sortingByName) {
        SortHoursBtn->setChecked(false);
        SortProfBtn->setChecked(false);
        sortingByHours = sortingByProfTip = false;
        deactivate_filters();

        reapply_filters();
        service.sortare_nume(currentView);
    } else
        reapply_filters();

    reloadTableFromCurrent();
    reloadListFromCurrent();
}


void MainWindow::sortOre() {
    sortingByHours = SortHoursBtn->isChecked();

    if (sortingByHours) {
        SortNameBtn->setChecked(false);
        SortProfBtn->setChecked(false);
        sortingByName = sortingByProfTip = false;
        deactivate_filters();

        reapply_filters();
        service.sortare_ore(currentView);
    } else
        reapply_filters();

    reloadTableFromCurrent();
    reloadListFromCurrent();
}


void MainWindow::sortProfTip() {
    sortingByProfTip = SortProfBtn->isChecked();

    if (sortingByProfTip) {
        SortHoursBtn->setChecked(false);
        SortNameBtn->setChecked(false);
        sortingByHours = sortingByName = false;
        deactivate_filters();

        reapply_filters();
        service.sortare_profesor_tip(currentView);
    } else
        reapply_filters();

    reloadTableFromCurrent();
    reloadListFromCurrent();
}


void MainWindow::addByName() {
    const auto name = contractAddNameEdit->text().toStdString();
    if (name.empty()) {
        QMessageBox::warning(this, "Input error", "Introduceti un nume.");
        return;
    }

    try {
        service.contract_adauga(name);
        reapply_filters();
        reapply_sorts();
        reloadTableFromCurrent();
        reloadListFromCurrent();
    } catch (const ContractException &ce) {
        const QString msg = QString::fromStdString(ce.getMesaj());

        if (msg.contains("Doriti un profesor anume")) {
            const QString prof = QInputDialog::getText(this, "Profesorul necesar",
                                                       "Introduceti numele profesorului (lasati gol daca nu vreti un profesor specific):");
            try {
                const string dorinta = prof.isEmpty() ? "nu" : "yeah";
                service.contract_adauga(name, prof.toStdString(), dorinta);
                reapply_filters();
                reapply_sorts();
                reloadTableFromCurrent();
                reloadListFromCurrent();
                return;
            } catch (const ContractException &ce2) {
                QMessageBox::warning(this, "Contract error", QString::fromStdString(ce2.getMesaj()));
                return;
            }
        }
        QMessageBox::warning(this, "Contract error", msg);
    }
}


void MainWindow::generateRandom() {
    try {
        if (const auto ore = getValidNumber(contractGenerateEdit); ore)
            service.contract_generare(*ore);
        reapply_filters();
        reapply_sorts();
        reloadTableFromCurrent();
        reloadListFromCurrent();
    } catch (const ContractException &ce) {
        QMessageBox::warning(this, "Contract error", QString::fromStdString(ce.getMesaj()));
    }
}


void MainWindow::clearContract() {
    try {
        service.contract_goleste();
        reapply_filters();
        reapply_sorts();
        reloadTableFromCurrent();
        reloadListFromCurrent();
    } catch (const ContractException &ce) {
        QMessageBox::warning(this, "Contract error", QString::fromStdString(ce.getMesaj()));
    }
}


void MainWindow::reloadTableFromCurrent() const {
    tableModel->updateModel(currentView);
}


void MainWindow::reloadListFromCurrent() const {
    listModel->updateModel(currentView);
}


void MainWindow::openContractWindow() {
    contractWin = new ContractWindow(service);

    contractWin->setWindowTitle("Contract Discipline");
    contractWin->show();
    contractWin->raise(); // aduce in fata
    contractWin->activateWindow(); // ii da focus
}


void MainWindow::openContractWindowROnly() {
    contractWinROnly = new ContractWindowROnly(service);

    contractWinROnly->setWindowTitle("Contract cu Imagini uuuuu");
    contractWinROnly->show();
    contractWinROnly->raise(); // aduce in fata
    contractWinROnly->activateWindow(); // ii da focus
}


void MainWindow::generateTipButtons() {
    // curatam butoane vechi
    QLayoutItem *item;
    while ((item = tipLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }


    // grupam data
    for (const auto raport = service.raport_tip(); const auto &[fst, snd]: raport) {
        const QString tip = QString::fromStdString(fst);
        const int count = snd.getCount();

        auto *btn = makeBtn(tip, "", tipLayout, this);
        btn->setMaximumWidth(150);

        connect(btn, &QPushButton::clicked, this, [tip, count] {
            QMessageBox::information(nullptr, "Info",
                                     QString("Sunt %1 discipline de tip '%2'").arg(QString::number(count), tip));
        });
    }
}


optional<int> MainWindow::getValidNumber(const QLineEdit *input) {
    bool ok;
    int val = input->text().toInt(&ok);
    if (!ok || val <= 0) {
        QMessageBox::warning(this, "Input error", "Introduceti un numar valid (> 0)!");
        return nullopt;
    }

    return val;
}


QPushButton *MainWindow::makeBtn(const QString &text, const QString &tooltip, QHBoxLayout *layout, QObject *parent) {
    auto *btn = new QPushButton(text, dynamic_cast<QWidget *>(parent));
    btn->setToolTip(tooltip);
    layout->addWidget(btn);
    return btn;
}


void MainWindow::reapply_filters() {
    if (filteringByProf) {
        service.filtrare_profesor(lastProfFilter.toStdString(), currentView);
    } else if (filteringByHours) {
        service.filtrare_ore(lastHoursFilter, currentView);
    } else {
        currentView.clear();
        for (const auto &disciplina: service.getAll())
            currentView.emplace_back(disciplina);
    }
}


void MainWindow::reapply_sorts() {
    if (sortingByName)
        service.sortare_nume(currentView);
    else if (sortingByHours)
        service.sortare_ore(currentView);
    else if (sortingByProfTip)
        service.sortare_profesor_tip(currentView);
}


void MainWindow::deactivate_filters() {
    FilterProfBtn->setChecked(false);
    FilterHoursBtn->setChecked(false);
    filteringByProf = false;
    filteringByHours = false;
    lastProfFilter.clear();
    lastHoursFilter = -1;
}


void MainWindow::deactivate_sorts() {
    SortNameBtn->setChecked(false);
    SortHoursBtn->setChecked(false);
    SortProfBtn->setChecked(false);
    sortingByName = sortingByHours = sortingByProfTip = false;
}


void MainWindow::syncListFromTable(const QModelIndex &current) const {
    const QModelIndex listIndex = listModel->index(current.row(), 0);
    list->setCurrentIndex(listIndex);
}


void MainWindow::syncTableFromList(const QModelIndex &current) const {
    table->selectRow(current.row());
}
