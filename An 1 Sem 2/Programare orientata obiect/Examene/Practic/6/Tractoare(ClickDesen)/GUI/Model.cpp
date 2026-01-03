#include "Model.h"

void ModelTabelTractoare::updateModel(const vector<Tractor> &newData) {
    beginResetModel();
    items = newData;
    endResetModel();
}

int ModelTabelTractoare::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return static_cast<int>(items.size());
}

int ModelTabelTractoare::columnCount(const QModelIndex &parent) const {
    return 5;
}

QVariant ModelTabelTractoare::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return {};

    if (role == Qt::BackgroundRole) {
        const auto &tractor = items[index.row()];
        if (tractor.getTip() == tip_filtrat)
            return QBrush(QColor(Qt::red));
    }

    if (role == Qt::DisplayRole) {
        const auto &t = getTractorAtRow(index.row());
        switch (index.column()) {
            case 0: return t.getId();
            case 1: return QString::fromStdString(t.getDenumire());
            case 2: return QString::fromStdString(t.getTip());
            case 3: return t.getRoti();
            case 4: return service.filtrare_tip(t.getTip());
            default: return {};
        }
    }
    return {};
}

QVariant ModelTabelTractoare::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return {};

    switch (section) {
        case 0: return "Id";
        case 1: return "Denumire";
        case 2: return "Tip";
        case 3: return "Numar roti";
        case 4: return "Acelasi tip";
        default: return {};
    }
}

void ModelTabelTractoare::setTipFiltrat(const string &tip) {
    tip_filtrat = tip;
    emit layoutChanged();
}
