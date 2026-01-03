#pragma once

#include <string>
#include <utility>
#include <iostream>

using std::ostream;
using std::string;
using std::move;


/**
 * Clasa de discipline
 * Reprezinta o disciplina cu un nume, nr de ore pe saptamana, tip si profesor principal
 */
class Disciplina final {
private:
    string nume;
    int ore = 0;
    string tip;
    string profesor;

public:
    /**
     * Constructor implicit.
     * Initializeaza valori goale/de baza
     */
    Disciplina() = default;

    /**
     * Constructor default
     * Initializeaza toate atributele explicit
     * @param nume numele disciplinei
     * @param ore numarul de ore pe saptamana
     * @param tip tipul disciplinei
     * @param prof numele profesorului principal al disciplinei
     */
    Disciplina(string nume, int ore, string tip, string prof) : nume{move(nume)}, ore{ore}, tip{move(tip)}, profesor{move(prof)} {
    }

    /**
     * Constructor de copiere
     * Creeaza o copie a disciplinei ot
     * @param ot alta disciplina
     */
    Disciplina(const Disciplina &ot) = default;

    /**
     * Operatie de copiere
     * Facuta pentru copiere protejata
     * @param ot alta disciplina
     */
    Disciplina &operator=(const Disciplina &ot) = default;

    /**
     * Constructor de alocare
     * Permite transfer de resurse eficient
     * @param ot alta disciplina
     */
    Disciplina(Disciplina &&ot) noexcept = default;

    /**
     * I like to move it move it
     */
    Disciplina &operator=(Disciplina &&) noexcept = default;

    /**
     * Operatorul verifica daca doua discipline sunt identice
     * @param ot alta disciplina
     * @return true daca disciplina actuala si disciplina ot au acelasi nume, ore pe saptamana, tip si profesor
     *         false, in caz contrar
     */
    bool operator==(const Disciplina &ot) const {
        return nume == ot.getNume() && ore == ot.getOre() && tip == ot.getTip() && profesor == ot.getProfesor();
    }


    /**
     * Operatia tipareste o instanta a disciplinei d
     * @param os instructiune de output
     * @param d o disciplina
     */
    friend ostream &operator<<(ostream &os, const Disciplina &d);


    /**
     * Functia returneaza numele disciplinei
     * @return numele disciplinei
     */
    [[nodiscard]] const string &getNume() const noexcept;

    /**
    * Functia returneaza numarul de ore a disciplinei
    * @return numarul de ore pe saptamana
    */
    [[nodiscard]] int getOre() const noexcept;

    /**
     * Functia returneaza tipul disciplinei
     * @return tipul disciplinei
     */
    [[nodiscard]] const string &getTip() const noexcept;

    /**
     * Functia returneaza profesorul principal al disciplinei
     * @return profesorul principal al disciplinei
     */
    [[nodiscard]] const string &getProfesor() const noexcept;
};
