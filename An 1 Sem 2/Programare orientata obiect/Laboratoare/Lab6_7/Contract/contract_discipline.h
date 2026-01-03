#pragma once
#include "../Valid/validare_discipline.h"
#include <vector>
#include <random>
#include <algorithm>

using std::vector;
using std::ranges::find;
using std::ranges::shuffle;
using std::mt19937;
using std::random_device;
using std::endl;

class ContractStudii final {
private:
    vector<Disciplina> contract;

public:
    /**
     * Constructorul creeaza o copie a contractului ot
     * @param ot alt contract
     */
    ContractStudii(const ContractStudii &ot) = delete;

    /**
     * Operatorul creeaza o copie a contractului ot
     * @param ot alt contract
     */
    ContractStudii &operator=(const ContractStudii &ot) = delete;

    /**
     * Constructor implicit.
     * Permite creearea unui contract neinitializat
     */
    ContractStudii() = default;


    /**
     * Functia adauga o disciplina in contract
     * @param d o disciplina
     * @throw ContractException cu mesajul "Disciplina exista deja in contract!", daca disciplina se afla deja in contract
     */
    void adauga(const Disciplina &d);

    /**
     * Functia goleste contractul de materii
     * @throw ContractException "Contractul este deja gol!", daca contractul este gol
     */
    void goleste();

    /**
     * Functia adauga in contrat un numar dat de discipline la intamplare din repository
     * @param all vector de unde alegem disicplinele cu care populam contractul
     * @param nr numarul de discipline adaugate la intamplare
     */
    void generare(const vector<Disciplina> &all, int nr);

    /**
     * Functia returneaza lista de discipline din contract sub forma de vector
     * @return contractul de discipline
     */
    [[nodiscard]] const vector<Disciplina> &getAll() const noexcept;


    /**
     * Functia scrie intr-un fisier contractul actual
     * @param out modalitate de a scrie intr-un fisier, cu tot cu calea de fisier
     */
    void exporta_contract(ofstream &out) const;
};
