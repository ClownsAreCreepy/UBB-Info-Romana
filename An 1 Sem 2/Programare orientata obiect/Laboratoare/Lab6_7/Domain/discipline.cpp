#include "discipline.h"

ostream &operator<<(ostream &os, const Disciplina &d) {
    os << "Nume: " << d.getNume() << " | Ore: " << d.getOre() << " | Tip: " << d.getTip() << " | Profesor: " << d.getProfesor();
    return os;
}


const string &Disciplina::getNume() const noexcept {
    return nume;
}

int Disciplina::getOre() const noexcept {
    return ore;
}

const string &Disciplina::getTip() const noexcept {
    return tip;
}

const string &Disciplina::getProfesor() const noexcept {
    return profesor;
}
