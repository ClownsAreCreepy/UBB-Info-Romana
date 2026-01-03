#include "Model.h"

void ModelTableMelodii::updateModel(const vector<Melodie> &newData) {
    beginResetModel();
    items = newData;
    endResetModel();
}

int ModelTableMelodii::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return static_cast<int>(items.size());
}

int ModelTableMelodii::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 6;
}

QVariant ModelTableMelodii::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return {};

    const auto &m = items.at(static_cast<size_t>(index.row()));
    switch (index.column()) {
        case 0: return m.getId();
        case 1: return QString::fromStdString(m.getTitlu());
        case 2: return QString::fromStdString(m.getArtist());
        case 3: return QString::fromStdString(m.getGen());
        case 4: return service.melodii_cu_acelasi_autor(m.getArtist());
        case 5: return service.melodii_cu_acelasi_gen(m.getGen());
        default: return {};
    }
}

QVariant ModelTableMelodii::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return {};

    switch (section) {
        case 0: return "ID";
        case 1: return "Titlu";
        case 2: return "Artist";
        case 3: return "Gen";
        case 4: return "Acelasi artist";
        case 5: return "Acelasi gen";
        default: return {};
    }
}
