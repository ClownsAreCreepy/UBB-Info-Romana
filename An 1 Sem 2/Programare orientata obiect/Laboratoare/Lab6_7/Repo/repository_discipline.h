#pragma once
#include <vector>
#include "../Valid/validare_discipline.h"
#include <algorithm>

using std::vector;
using std::ranges::find;
using std::ranges::any_of;

/**
 * Clasa pur virtuala (interfata) pentru repository-uri
 */
class IRepoDisciplina {
public:
    /**
     * Destructor marcat virtual pentru mostenire
     */
    virtual ~IRepoDisciplina() = default;


    /**
     * Functia adauga o disciplina in repository
     * @param d o disciplina
     * @throw RepoException cu mesajul
     *      -"Disciplina exista deja!", daca disciplina exista deja in repository
     */
    virtual void adauga(const Disciplina &d) = 0;

    /**
     * Functia modifica o disciplina in repository
     * @param index pozitia elementului care va fi modificat
     * @param d datele noi ale disciplinei
     * @throw RepoException cu mesajul
     *      -"Disciplina exista deja!", daca disciplina noua exista deja in repository
     */
    virtual void modifica(size_t index, const Disciplina &d) = 0;

    /**
     * Functia sterge o disciplina in repository
     * @param index pozitia elementului care va fi sters
     */
    virtual void sterge(int index) = 0;

    /**
     * Functia returneaza un element din repository
     * @param index pozitia elementului dorit
     * @return elementul dorit
     */
    [[nodiscard]] virtual const Disciplina &cauta(size_t index) const = 0;

    /**
     * Functia returneaza intregul repository sub forma de vector
     * @return intregul repository sub forma de vector
     */
    [[nodiscard]] virtual const vector<Disciplina> &getAll() const noexcept = 0;

    /**
     * Functia virtuala protejata pentru inserare la o pozitie
     * Permite undo-ului sa insereze disciplina inapoi la index
     * @param index pozitia in care adaugam
     * @param d disciplina pe care o adaugam
     */
    virtual void inserare_la_index(size_t index, const Disciplina &d) = 0;

};


/**
 * Clasa RepoDisciplinaMem
 * Contine un vector dinamic, numit discipline, de discipline si functioneaza pe memorie
 */
class RepoDisciplinaMem : public IRepoDisciplina{
protected:
    vector<Disciplina> discipline;

public:
    /**
     * Constructorul creeaza o copie a functiei ot
     * @param ot alt repository
     */
    RepoDisciplinaMem(const RepoDisciplinaMem &ot) = delete;

    /**
     * Constructor implicit
     * Permite declararea unui repo neinitializat
     */
    RepoDisciplinaMem() = default;

    /**
     * Destructor implicit
     * Il scriem explicit pentru a-l face virtual, ca ca functioneze si in polimorfism
     */
    ~RepoDisciplinaMem() override = default;


    /**
     * Functia adauga o disciplina in repository
     * @param dis o disciplina
     * @throw RepoException cu mesajul
     *      -"Disciplina exista deja!", daca disciplina exista deja in repository
     */
    void adauga(const Disciplina &dis) override;

    /**
     * Functia modifica o disciplina in repository
     * @param index pozitia elementului care va fi modificat
     * @param ot datele noi ale disciplinei
     * @throw RepoException cu mesajul
     *      -"Disciplina exista deja!", daca disciplina noua exista deja in repository
     */
    void modifica(size_t index, const Disciplina &ot) override;

    /**
     * Functia sterge o disciplina in repository
     * @param index pozitia elementului care va fi sters
     */
    void sterge(int index) override;

    /**
     * Functia returneaza un element din repository
     * @param index pozitia elementului dorit
     * @return elementul dorit
     */
    [[nodiscard]] const Disciplina &cauta(size_t index) const override;

    /**
     * Functia returneaza intregul repository sub forma de vector
     * @return intregul repository sub forma de vector
     */
    [[nodiscard]] const vector<Disciplina> &getAll() const noexcept override;

    /**
     * Functia virtuala protejata pentru inserare la o pozitie
     * Permite undo-ului sa insereze disciplina inapoi la index
     * @param index pozitia in care adaugam
     * @param d disciplina pe care o adaugam
     */
    void inserare_la_index(size_t index, const Disciplina &d) override;


};
