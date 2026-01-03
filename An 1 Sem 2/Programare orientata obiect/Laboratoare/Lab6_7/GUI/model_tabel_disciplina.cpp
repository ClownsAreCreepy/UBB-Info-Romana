#include "model_tabel_disciplina.h"

void ModelTabelDisciplina::updateModel(const vector<Disciplina> &newData) {
    beginResetModel();
    items = newData;
    endResetModel();
}


int ModelTabelDisciplina::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return static_cast<int>(items.size());
}

int ModelTabelDisciplina::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 4;
}


QVariant ModelTabelDisciplina::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return {};

    const auto &d = items.at(static_cast<size_t>(index.row()));
    switch (index.column()) {
        case 0: return QString::fromStdString(d.getNume());
        case 1: return d.getOre();
        case 2: return QString::fromStdString(d.getTip());
        case 3: return QString::fromStdString(d.getProfesor());
        default: return {};
    }
}

QVariant ModelTabelDisciplina::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return {};

    switch (section) {
        case 0: return "Materie";
        case 1: return "Ore";
        case 2: return "Tip";
        case 3: return "Profesor";
        default: return {};
    }
}
