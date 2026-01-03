#include "contract_discipline.h"

void ContractStudii::adauga(const Disciplina &d) {
    if (find(contract, d) != contract.end())
        throw ContractException("Disciplina exista deja in contract!");

    contract.emplace_back(d);
}

void ContractStudii::goleste() {
    if (contract.empty())
        throw ContractException("Contractul este deja gol!");

    contract.clear();
}

void ContractStudii::generare(const vector<Disciplina> &all, int nr) {
    vector<Disciplina> amestecate = all;
    shuffle(amestecate, mt19937(random_device{}()));

    contract.clear();
    contract.insert(contract.end(), amestecate.begin(), amestecate.begin() + nr);
}

const vector<Disciplina> &ContractStudii::getAll() const noexcept {
    return contract;
}


void ContractStudii::exporta_contract(ofstream &out) const {
    for (const auto &disciplina: contract)
        out << disciplina << endl;
}
