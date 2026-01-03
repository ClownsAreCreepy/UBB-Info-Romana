#pragma once

#include <QAbstractTableModel>
#include "../Service/service_discipline.h"


/**
 * Clasa model pentru tabel
 */
class ModelTabelDisciplina : public QAbstractTableModel {
    Q_OBJECT

private:
    vector<Disciplina> items;

public:
    /**
     * Constructor explicit pentru un tabel care respecta modelul
     * @param parent parinte (luam ca null)
     */
    explicit ModelTabelDisciplina(QObject *parent = nullptr) : QAbstractTableModel(parent) {
    }

    /**
     * Functia populeaza vectorul tabelului cu discipline
     * @param newData vector de discipline
     */
    void updateModel(const vector<Disciplina> &newData);


    /**
     * Functia returneaza numarul de randuri al tabelului
     * @param parent parinte
     * @return numarul de randuri
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * Functia returneaza numarul de coloane al tabelului
     * @param parent parinte
     * @return numar de coloana
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;


    /**
     * Functia returneaza data care este aleasa de utilizator
     * @param index returneaza randul pe care este selectia
     * @param role rol ig ??
     * @return randul care este ales
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * Functia creeaza un antet pentru atributelor disciplinelor
     * @param section sectiunea atributelor
     * @param orientation orientarea atributelor
     * @param role rol ig ??
     * @return un antet pentru atributele disciplinelor
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};
