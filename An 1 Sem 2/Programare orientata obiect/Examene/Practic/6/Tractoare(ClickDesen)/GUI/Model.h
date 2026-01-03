#pragma once

#include "../Service/Service.h"
#include <QAbstractTableModel>
#include <QTableView>

class ModelTabelTractoare : public QAbstractTableModel {
    Q_OBJECT
private:
    vector<Tractor> items;
    ServiceTractoare &service;
    string tip_filtrat;

public:
    ModelTabelTractoare(ServiceTractoare &s, QObject *parent = nullptr) : QAbstractTableModel(parent), service(s) {}

    void updateModel(const vector<Tractor> &newData);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    const Tractor &getTractorAtRow(int row) const { return items.at(row); }

    void setTipFiltrat(const string &tip);
};