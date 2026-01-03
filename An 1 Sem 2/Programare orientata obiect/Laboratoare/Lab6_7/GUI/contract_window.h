#pragma once

#include "../Service/service_discipline.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QInputDialog>

/**
 * Clasa GUI pentru fereastra de modificare si vizualizare a contractului
 * Mosteneste din clasa Observer, deoarece observa starea contractului
 */
class ContractWindow final : public QWidget, public Observer {
    Q_OBJECT

private:
    QTableWidget *contractTable;

    QLineEdit *numGenerateEdit;
    QLineEdit *addbyname;

    QPushButton *Addbtn;
    QPushButton *GenBtn;
    QPushButton *ClrBtn;
    QPushButton *ExpBtn;

    ServiceDisciplina &service;


    /**
    * Functie pentru a modifica contractul de discipline rezultat din ultima operatie
    */
    void reloadContract() const;

private slots:
    /**
     * Functie pentru a adauga o disciplina dupa nume
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

    /**
     * Functie pentru a exporta contractul intr-un fisier
     */
    void exportContract();

    /**
     * Functia actualizeaza starea ferestrei in urma unei modificari a contractului
     */
    void update() override;

public:
    /**
     * Functia creeaza o fereastra care are totul necesar pentru lucrul cu contractele de discipline
     * @param serv service-ul pe care lucreaza
     * @param parent nu are
     */
    explicit ContractWindow(ServiceDisciplina &serv, QWidget *parent = nullptr);

    /**
    * Destructor explicit, pentru se putea elimina din lista de observatori
    */
    ~ContractWindow() override;
};
