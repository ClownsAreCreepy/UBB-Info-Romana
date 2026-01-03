#pragma once

#include "../Service/service_discipline.h"
#include "contract_window.h"
#include "contract_window_readonly.h"
#include "model_lista_disciplina.h"
#include "model_tabel_disciplina.h"
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QApplication>
#include <QFormLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QListView>


using std::optional;
using std::nullopt;


/**
 * Clasa GUI pentru fereastra principala
*/
class MainWindow final : public QWidget {
    Q_OBJECT

private:
    ContractWindow *contractWin = nullptr;
    ContractWindowROnly *contractWinROnly = nullptr;

    QTableView *table;
    QListView *list;

    ModelListaDisciplina *listModel;
    ModelTabelDisciplina *tableModel;

    QLineEdit *nameEdit;
    QLineEdit *hoursEdit;
    QLineEdit *typeEdit;
    QLineEdit *profEdit;
    QLineEdit *contractAddNameEdit;
    QLineEdit *contractGenerateEdit;

    QPushButton *AddBtn;
    QPushButton *ModBtn;
    QPushButton *DelBtn;
    QPushButton *SortNameBtn;
    QPushButton *SortHoursBtn;
    QPushButton *SortProfBtn;
    QPushButton *FilterProfBtn;
    QPushButton *FilterHoursBtn;
    QPushButton *UndoBtn;
    QPushButton *ContractAddNameBtn;
    QPushButton *ContractGenerateBtn;
    QPushButton *ContractClearBtn;

    QPushButton *ContractBtn;
    QPushButton *ContractROBtn;

    QWidget *tipWidget = nullptr;
    QHBoxLayout *tipLayout = nullptr;

    ServiceDisciplina &service;
    vector<Disciplina> currentView;

    bool filteringByProf = false;
    QString lastProfFilter = "";

    bool filteringByHours = false;
    int lastHoursFilter = -1;

    bool sortingByName = false;
    bool sortingByHours = false;
    bool sortingByProfTip = false;


    /**
     * Functie pentru a realiza conexiunile intre butoane si ce fac
     */
    void setupConnections();

    /**
     * Functie pentru a reaplica filtrul activ dupa o operatie (daca e unul activ)
     */
    void reapply_filters();

    /**
     * Functie pentru a dezactiva filtrul activ
     */
    void deactivate_filters();

    /**
     * Functie pentru a reaplica sortarea activa dupa o operatie (daca e unul activ)
     */
    void reapply_sorts();

    /**
     * Functie pentru a dezactiva sortarea activa
     */
    void deactivate_sorts();

    /**
     * Functie pentru a modifica tabelul cu disciplinele rezultate din ultima operatie
     */
    void reloadTableFromCurrent() const;

    /**
     * Functie pentru a modifica lista cu disciplinele rezultate din ultima operatie
     */
    void reloadListFromCurrent() const;


    /**
     * Functia verifica daca un numar luat dintr-un QLineEdit este valid
     * @param input linia de unde se extrage ora
     * @return numarul, sau o nullopt in cazul in care numarul de ore nu e valabil
     */
    optional<int> getValidNumber(const QLineEdit *input);


    /**
     * Functia creeaza un buton cu text si tooltip si il pune intr-un layout
     * @param text textul de te buton
     * @param tooltip descrierea butonului cand punem mouse-ul peste el
     * @param layout layout-ul in care vom pune butonul
     * @param parent parintele butonului ig
     * @return un buton avand aceste caracteristici
     */
    QPushButton *makeBtn(const QString &text, const QString &tooltip, QHBoxLayout *layout, QObject *parent = nullptr);

private slots:
    /**
     * Functia adauga o disciplina noua in fereastra
     */
    void addDisciplina();

    /**
     * Functia modifica o disciplina din fereastra
     */
    void modDisciplina();

    /**
     * Functia sterge o disciplina din fereastra
     */
    void delDisciplina();

    /**
     * Functia reface ultima operatie efectuata
     */
    void undoActiune();

    /**
     * Functia filtreaza disciplinele dupa un profesor
     */
    void filterProf();

    /**
     * Functia filtreaza disciplinele dupa un numar de ore
     */
    void filterOre();

    /**
     * Functia sorteaza disciplinele dupa nume
     */
    void sortNume();

    /**
     * Functia sorteaza disciplinele dupa numarul de ore
     */
    void sortOre();

    /**
     * Functia sorteaza disciplinele dupa profesor, apoi dupa tip daca ele au acelasi profesor
     */
    void sortProfTip();


    /**
     * Functia deschide fereastra cu contractul de discipline
     */
    void openContractWindow();


    void openContractWindowROnly();


    /**
     * Functia genereaza butoane pentru raportul de tip
     */
    void generateTipButtons();


    /**
     * Functia afiseaza alegerea facuta din lista in tabela
     */
    void syncListFromTable(const QModelIndex &current) const;

    /**
     * Functia afiseaza alegerea facuta din tabela in lista
     */
    void syncTableFromList(const QModelIndex &current) const;


    /**
     * Functie pentru a adauga o disciplina in contract dupa nume
     */
    void addByName();

    /**
     * Functie pentru a genera un contract la intamplare din disciplinele existente
     */
    void generateRandom();

    /**
     * Functie pentru a goli contractul
     */
    void clearContract();

public:
    /**
     * Functia creeaza o fereastra care are totul necesar pentru lucrul cu discipline
     * @param serv service-ul pe care lucreaza
     * @param parent parintele ferestrei - nu are
     */
    explicit MainWindow(ServiceDisciplina &serv, QWidget *parent = nullptr);
};
