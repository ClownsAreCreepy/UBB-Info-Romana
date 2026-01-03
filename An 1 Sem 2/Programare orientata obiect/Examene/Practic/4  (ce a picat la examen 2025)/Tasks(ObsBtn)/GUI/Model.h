#pragma once

#include "../Service/Service.h"
#include <QAbstractTableModel>
#include <QTableView>

class ModelTabelTask : public QAbstractTableModel{
    Q_OBJECT
private:
    vector<Task> items;

public:
    ModelTabelTask(QObject *parent = nullptr): QAbstractTableModel(parent) {}

    void updateModel(const vector<Task> &newData);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    const Task &getTaskAt(int row) const { return items.at(row); }
};
