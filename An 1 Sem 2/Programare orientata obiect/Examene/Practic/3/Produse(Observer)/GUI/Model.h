#pragma once

#include "../Service/Service.h"
#include <QAbstractTableModel>
#include <QTableView>

class ModelTabelProdus : public QAbstractTableModel {
    Q_OBJECT
private:
    vector<Produs> items;
    ServiceProdus &service;
    int pret_filtrat = 0;

public:
    explicit ModelTabelProdus(ServiceProdus &service, QObject *parent = nullptr) : QAbstractTableModel(parent), service(service) {}

    void updateModel(const vector<Produs> &newData);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;


    void setPretFiltrat(int pret);
};