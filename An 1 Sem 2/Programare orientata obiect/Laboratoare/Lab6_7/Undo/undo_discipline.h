#pragma once
#include "../Repo/repository_fals_discipline.h"

/**
 * Clasa de baza ActiuneUndo
 * Clasa pur virtuala, facuta special pentru polimorfism
 */
class ActiuneUndo {
public:
    /**
     * Destructor virtual, pentru a functiona cu polimorfismul implementarii
     * Cand este apelat, verifica destructorul carei clasa Undo derivata trebuie apelat
     */
    virtual ~ActiuneUndo() = default;

    /**
     * Metoda pur-virtuala, fiecare clasa care o deriveaza are un cod propriu
     */
    virtual void doUndo() = 0;
};


/**
 * Clasa Undo pentru adaugare mostenita din clasa de baza ActiuneUndo
 */
class UndoAdauga final : public ActiuneUndo {
private:
    IRepoDisciplina &repo;

public:
    /**
     * Constructorul creeaza o instanta a clasei undo pentru a modifica un repo de discipline
     * @param r lista de discipline care trebuie modificata
     */
    explicit UndoAdauga(IRepoDisciplina &r) : repo{r} {}

    /**
     * Functia readuce lista la starea precedenta, stergand disciplina recent adaugata
     */
    void doUndo() override;
};


/**
 * Clasa Undo pentru modificare mostenita din clasa de baza ActiuneUndo
 */
class UndoModifica final : public ActiuneUndo {
private:
    IRepoDisciplina &repo;
    size_t index;
    Disciplina d_veche;

public:
    /**
    * Constructorul creeaza o instanta a clasei undo pentru a modifica un repository de discipline
     * @param r lista de discipline care trebuie modificata
     * @param i indexul de unde a fost modificata disciplina
     * @param dis disciplina modificata
     */
    UndoModifica(IRepoDisciplina &r, size_t i, Disciplina dis) : repo{r}, index{i}, d_veche{move(dis)} {}


    /**
     * Functia readuce lista la starea precedenta, modificand inapoi disciplina recent modificata
     */
    void doUndo() override;
};


/**
 * Clasa Undo pentru stergere mostenita din clasa de baza ActiuneUndo
 */
class UndoSterge final : public ActiuneUndo {
private:
    IRepoDisciplina &repo;
    size_t index;
    Disciplina d;

public:
    /**
    * Constructorul creeaza o instanta a clasei undo pentru a modifica un repository de discipline
     * @param r lista de discipline care trebuie modificata
     * @param i indexul de unde a fost modificata disciplina
     * @param dis disciplina stearsa
     */
    UndoSterge(IRepoDisciplina &r, size_t i, Disciplina dis) : repo{r}, index{i}, d{move(dis)} {}

    /**
     * Functia readuce lista la starea precedenta, adaugand inapoi disciplina recent stearsa
     */
    void doUndo() override;
};
