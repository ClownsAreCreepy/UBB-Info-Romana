#include "Model.h"

void ModelTabelProdus::updateModel(const vector<Produs> &newData) {
    beginResetModel();
    items = newData;
    endResetModel();
}

int ModelTabelProdus::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return static_cast<int>(items.size());
}

int ModelTabelProdus::columnCount(const QModelIndex &parent) const {
    return 5;
}

QVariant ModelTabelProdus::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return {};

    if (role == Qt::BackgroundRole) {
        const auto &produs = items[index.row()];
        if (produs.getPret() <= pret_filtrat)
            return QBrush(QColor(Qt::red));
    }

    if (role == Qt::DisplayRole) {
        const auto &p = items.at(static_cast<size_t>(index.row()));
        switch (index.column()) {
            case 0: return p.getId();
            case 1: return QString::fromStdString(p.getNume());
            case 2: return QString::fromStdString(p.getTip());
            case 3: return p.getPret();
            case 4: return service.nr_vocale(p.getNume());
            default: return {};
        }
    }

    return {};
}
QVariant ModelTabelProdus::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return {};

    switch (section) {
        case 0: return "Id";
        case 1: return "Nume";
        case 2: return "Tip";
        case 3: return "Pret";
        case 4: return "Vocale in nume";
        default: return {};
    }
}

void ModelTabelProdus::setPretFiltrat(int pret) {
    pret_filtrat = pret;
    emit layoutChanged();
}
