#pragma once

#include "../Service/service_discipline.h"
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <random>

using std::uniform_int_distribution;
using std::uniform_real_distribution;

/**
 * Clasa GUI pentru fereastra de vizualizare a contractului, sub forma de imagini
 * Mosteneste din clasa Observer, deoarece observa starea contractului
 */
class ContractWindowROnly : public QWidget, public Observer {
    Q_OBJECT

private:
    ServiceDisciplina &service;
    mt19937 rng{random_device{}()};

private slots:
    /**
     * Functia actualizeaza starea ferestrei in urma unei modificari a contractului
     */
    void update() override;

protected:
    /**
     * Functia pune atatea imagini pe pozitii random cate elemente sunt in contract
     * @param event ceva ig idk
     */
    void paintEvent(QPaintEvent *event) override;

public:

    /**
     * Functia creeaza o fereastra care are prezinta numarul de discipline din contract sub forma de poze
     * @param serv service-ul pe care lucreaza
     * @param parent parintele ????
     */
    explicit ContractWindowROnly(ServiceDisciplina &serv, QWidget *parent = nullptr);

    /**
    * Destructor explicit, pentru se putea elimina din lista de observatori
    */
    ~ContractWindowROnly() override;
};
