#include "repository_fals_discipline.h"



void RepoDisciplinaFals::try_throw() const {
    if (uniform_real_distribution dist(0.0, 1.0); dist(gen) < prob)
        throw RepoException("Exceptie aruncata de repo!");
}

void RepoDisciplinaFals::adauga(const Disciplina &dis) {
    try_throw();

    for (const auto &val: data | values)
        if (val == dis) throw RepoException("Disciplina exista deja!");

    data[static_cast<int>(data.size())] = dis;
}

void RepoDisciplinaFals::modifica(size_t index, const Disciplina &d) {
    try_throw();

    for (const auto &val: data | values)
        if (val == d)
            throw RepoException("Disciplina exista deja!");

    data[static_cast<int>(index)] = d;
}

void RepoDisciplinaFals::sterge(int index) {
    try_throw();

    data.erase(index);

    int size = static_cast<int>(data.size()) + 1;
    for (int i = index + 1; i < size; ++i) {
        data[i-1] = data[i];
        data.erase(i);
    }
}

const Disciplina &RepoDisciplinaFals::cauta(size_t index) const {
    try_throw();
    return data.find(static_cast<int>(index))->second;
}

const vector<Disciplina> &RepoDisciplinaFals::getAll() const noexcept {
    static vector<Disciplina> cache;
    cache.clear();


    for (const auto &val : data | values)
        cache.emplace_back(val);

    return cache;
}

void RepoDisciplinaFals::inserare_la_index(size_t index, const Disciplina &d) {
    map<int, Disciplina> copie;

    // eliberam indexul
    for (auto &[key, val] : data)
        if (key >= static_cast<int>(index))
            copie[key + 1] = val;
        else
            copie[key] = val;

    // bagam pe cel care dorim pe pozitia index
    copie[static_cast<int>(index)] = d;
    data = move(copie);
}