#include "model_lista_disciplina.h"

void ModelListaDisciplina::updateModel(const vector<Disciplina> &newData) {
    beginResetModel();
    items = newData;
    endResetModel();
}


int ModelListaDisciplina::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return static_cast<int>(items.size());
}


QVariant ModelListaDisciplina::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return {};

    const auto &d = items.at(static_cast<size_t>(index.row()));
    return QString::fromStdString(d.getNume() + " | " +
                                       to_string(d.getOre()) + " ore | " +
                                       d.getTip() + " | " +
                                       d.getProfesor());
}