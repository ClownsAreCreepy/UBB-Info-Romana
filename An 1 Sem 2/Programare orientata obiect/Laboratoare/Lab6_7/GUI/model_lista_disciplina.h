#pragma once

#include <QAbstractListModel>
#include "../Service/service_discipline.h"

using std::to_string;

/**
 * Clasa model pentru lista
 */
class ModelListaDisciplina : public QAbstractListModel {
    Q_OBJECT

private:
    vector<Disciplina> items;

public:
    /**
     * Constructor explicit pentru o lista care respecta modelul
     * @param parent parinte (luam ca null)
     */
    explicit ModelListaDisciplina(QObject *parent = nullptr) : QAbstractListModel(parent) {
    }


    /**
     * Functia populeaza vectorul listei cu discipline
     * @param newData vector de discipline
     */
    void updateModel(const vector<Disciplina> &newData);


    /**
     * Functia returneaza numarul de randuri al listei
     * @param parent parinte
     * @return numarul de randuri
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;


    /**
     * Functia returneaza disciplina care este aleasa de utilizator
     * @param index returneaza randul pe care este selectia
     * @param role rol ig ??
     * @return disciplina care este pe randul ales
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};
