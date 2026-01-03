#pragma once
#include "repository_discipline.h"
#include <sstream>

using std::ifstream;
using std::ofstream;
using std::getline;
using std::stringstream;

/**
 * Clasa RepoDisciplinaFile
 * Contine un vector dinamic, numit discipline, de discipline si functioneaza pe fisiere
 */
class RepoDisciplinaFile final : public RepoDisciplinaMem {
private:
    string file_path;

    /**
     * Functia citeste dintr-un fisier
     */
    void load_from_file();

    /**
     * Functai scrie intr-un fisier (write)
     */
    void save_to_file() const;

public:
    /**
     * Constructor explicit
     * Creeaza un repository ce lucreaza cu un fisier
     * @param file_path calea catre fisier
     */
    explicit RepoDisciplinaFile(string file_path) : file_path(move(file_path)) {
        load_from_file();
    }


    /**
     * Functia adauga disciplina in repo si in fisier
     * @param dis disciplina adaugata
     */
    void adauga(const Disciplina &dis) override;

    /**
     * Functia modifica o disciplina din repo si din fisier
     * @param index pozitia disciplinei care va fi modificata
     * @param ot disciplina noua care va lua locul disciplinei modificate
     */
    void modifica(size_t index, const Disciplina &ot) override;

    /**
     * Functia sterge o disciplina din repo si din fisier
     * @param index pozitia disciplinei care va fi stearsa
     */
    void sterge(int index) override;

    /**
     * Functia virtuala protejata pentru inserare la o pozitie
     * Permite undo-ului sa insereze disciplina inapoi la index
     * @param index pozitia in care adaugam
     * @param d disciplina pe care o adaugam
     */
    void inserare_la_index(size_t index, const Disciplina &d) override;

};
