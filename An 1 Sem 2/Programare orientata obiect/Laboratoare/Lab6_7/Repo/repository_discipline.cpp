#include "repository_discipline.h"


void RepoDisciplinaMem::adauga(const Disciplina &dis) {
    if (find(discipline, dis) != discipline.end())
        throw RepoException("Disciplina exista deja!");

    discipline.emplace_back(dis);
}

void RepoDisciplinaMem::modifica(size_t index, const Disciplina &ot) {
    if (any_of(discipline, [&](const auto &d){
        return d == ot;}))
        throw RepoException("Disciplina exista deja!");

    discipline[index] = ot;
}

void RepoDisciplinaMem::sterge(int index) {
    discipline.erase(discipline.begin() + index);
}

const Disciplina &RepoDisciplinaMem::cauta(size_t index) const {
    return discipline[index];
}

const vector<Disciplina> &RepoDisciplinaMem::getAll() const noexcept {
    return discipline;
}

void RepoDisciplinaMem::inserare_la_index(size_t index, const Disciplina &d) {
    discipline.insert(discipline.begin() + static_cast<int>(index), d);
}