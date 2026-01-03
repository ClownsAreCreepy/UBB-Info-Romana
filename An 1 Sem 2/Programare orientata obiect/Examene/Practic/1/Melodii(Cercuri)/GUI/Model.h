#pragma once

#include "../Service/Service.h"
#include <QAbstractTableModel>
#include <QTableView>

class ModelTableMelodii : public QAbstractTableModel {
    Q_OBJECT

private:
    vector<Melodie> items;
    ServiceMelodii &service;

public:
    ModelTableMelodii(ServiceMelodii &s, QObject *parent = nullptr) : QAbstractTableModel(parent), service(s) {}

    void updateModel(const vector<Melodie> &newData);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};