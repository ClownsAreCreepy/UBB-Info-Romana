#pragma once

#include "repository_file_discipline.h"
#include <random>
#include <ranges>
#include <map>

using std::map;
using std::mt19937;
using std::random_device;
using std::uniform_real_distribution;
using std::views::values;
using std::ranges::sort;

/**
 * Clasa de repository care arunca exceptii cu o anumita probabilitate
 */
class RepoDisciplinaFals final : public IRepoDisciplina {
private:
    map<int, Disciplina> data;
    double prob;
    mutable mt19937 gen;

    /**
     * Functie care are o probabilitate sa arunce o exceptie de fiecare data cand e apelata
     */
    void try_throw() const;

public:
    /**
     * Constructor explicit pentru repository-ul naspa facut
     * @param probabilitate probabilitatea cu care se vor arunca exceptiile
     */
    explicit RepoDisciplinaFals(const double probabilitate) : prob{probabilitate}, gen{random_device{}()} {
        if (prob < 0.0 || prob > 1.0)
            throw ValidationException("Probabilitatea trebuie sa fie intre 0 si 1!");
    }

    /**
     * Destructorul specific acestui repository
     */
    ~RepoDisciplinaFals() override = default;


    /**
     * Functia adauga o disciplina in repository si are o sansa sa arunce exceptii
     * @param dis o disciplina
     * @throw RepoException cu mesajul
     *      -"Disciplina exista deja!", daca disciplina exista deja in repository
     */
    void adauga(const Disciplina &dis) override;

    /**
     * Functia modifica o disciplina in repository si are o sansa sa arunce exceptii
     * @param index pozitia elementului care va fi modificat
     * @param d datele noi ale disciplinei
     * @throw RepoException cu mesajul
     *      -"Disciplina exista deja!", daca disciplina noua exista deja in repository
     */
    void modifica(size_t index, const Disciplina &d) override;

    /**
     * Functia sterge o disciplina in repository si are o sansa sa arunce exceptii
     * @param index pozitia elementului care va fi sters
     */
    void sterge(int index) override;

    /**
     * Functia returneaza un element din repository si are o sansa sa arunce exceptii
     * @param index pozitia elementului dorit
     * @return elementul dorit
     */
    const Disciplina& cauta(size_t index) const override;

    /**
     * Functia returneaza intregul repository sub forma de vector
     * @return intregul repository sub forma de vector
     */
    const vector<Disciplina> &getAll() const noexcept override;

    /**
     * Functia virtuala protejata pentru inserare la o pozitie
     * Permite undo-ului sa insereze disciplina inapoi la index
     * @param index pozitia in care adaugam
     * @param d disciplina pe care o adaugam
     */
    void inserare_la_index(size_t index, const Disciplina &d) override;
};