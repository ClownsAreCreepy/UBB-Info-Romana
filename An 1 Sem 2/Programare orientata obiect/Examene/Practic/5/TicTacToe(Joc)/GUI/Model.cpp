#include "Model.h"

void ModelTabelJoc::updateModel(const vector<Joc> &newData) {
    beginResetModel();
    items = newData;
    endResetModel();
}

int ModelTabelJoc::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return static_cast<int>(items.size());
}

int ModelTabelJoc::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 5;
}

QVariant ModelTabelJoc::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return {};

    const auto &j = items.at(index.row());
    switch (index.column()) {
        case 0: return j.getId();
        case 1: return j.getDimensiune();
        case 2: return QString::fromStdString(j.getTabla());
        case 3: return QString::fromStdString(j.getJucator());
        case 4: return QString::fromStdString(j.getStare());
        default: return {};
    }
}

QVariant ModelTabelJoc::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return {};

    switch (section) {
        case 0: return "Id";
        case 1: return "Dimensiune";
        case 2: return "Tabla";
        case 3: return "Jucator";
        case 4: return "Stare";
        default: return {};
    }
}
