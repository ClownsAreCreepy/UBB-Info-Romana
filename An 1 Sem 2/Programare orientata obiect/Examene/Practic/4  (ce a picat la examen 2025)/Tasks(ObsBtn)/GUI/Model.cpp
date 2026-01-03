#include "Model.h"

void ModelTabelTask::updateModel(const vector<Task> &newData) {
    beginResetModel();
    items = newData;
    endResetModel();
}

int ModelTabelTask::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return static_cast<int>(items.size());
}

int ModelTabelTask::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 4;
}

QVariant ModelTabelTask::data(const QModelIndex &index, int role) const {
    if (! index.isValid() || role != Qt::DisplayRole)
        return {};

    const auto &t = items.at(index.row());
    switch (index.column()) {
        case 0: return t.getId();
        case 1: return QString::fromStdString(t.getDescriere());
        case 2: return t.getProgramatori().size();
        case 3: return QString::fromStdString(t.getStare());
        default: return {};
    }
}

QVariant ModelTabelTask::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return {};

    switch (section) {
        case 0: return "Id";
        case 1: return "Descriere";
        case 2: return "Nr programatori";
        case 3: return "Stare";
        default: return {};
    }
}