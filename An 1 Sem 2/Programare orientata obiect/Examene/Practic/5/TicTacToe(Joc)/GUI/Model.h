#pragma once

#include "../Service/Service.h"
#include <QAbstractTableModel>
#include <QTableView>

class ModelTabelJoc : public QAbstractTableModel {
private:
    vector<Joc> items;

public:
    void updateModel(const vector<Joc> &newData);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    ModelTabelJoc(QObject *parent = nullptr) : QAbstractTableModel(parent) {}

    const Joc &getJocAtRow(int row) { return items.at(row); }
};