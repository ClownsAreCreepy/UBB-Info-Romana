#include "validare_discipline.h"

const char *BaseException::what() const noexcept {
    return mesaj.c_str();
}

const string &BaseException::getMesaj() const noexcept {
    return mesaj;
}


const unordered_set<string> &Validator::validTypes() {
    static const unordered_set<string> t = {"Real", "Uman", "??"};
    return t;
}

void Validator::valideaza_disciplina(const Disciplina &d) {
    string mesaj;

    if (d.getNume().empty())
        mesaj += "Numele nu poate fi gol!\n";

    if (d.getOre() <= 0)
        mesaj += "Numarul de ore trebuie sa fie pozitiv!\n";

    if (!validTypes().contains(d.getTip()))
        mesaj += "Tipul poate fi doar 'Uman', 'Real' sau '??'!\n";

    if (d.getProfesor().empty())
        mesaj += "Profesorul nu poate fi gol!\n";


    if (!mesaj.empty()) {
        throw ValidationException(mesaj);
    }
}

void Validator::valideaza_index(int index, size_t maxim) {
    if (index < 0)
        throw RepoException("Elementele sunt doar pe pozitii pozitive!");
    if (static_cast<size_t>(index) >= maxim)
        throw RepoException("Disciplina nu a fost gasita!");
}

void Validator::valideaza_index_contract(int index, size_t maxim) {
    if (index < 0)
        throw ContractException("Nu se poate genera un contract cu un numar negativ de discipline!");
    if (static_cast<size_t>(index) > maxim)
        throw ContractException("Nu exista atatea discipline in catalog!");
}

void Validator::valideaza_ofstream(const string &file_path) {
    if (std::ofstream test(file_path); !test.is_open())
        throw FileException("Nu s-a putut scrie in fisier!");
}
