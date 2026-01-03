#pragma once
#include "../Domain/discipline.h"
#include <fstream>
#include <exception>
#include <unordered_set>

using std::string;
using std::exception;
using std::unordered_set;
using std::ofstream;

/**
 * O clasa de baza, care defineste comportamentul fiecarui tip special de exceptie
 * Contine mesajul care se va afisa in caz de exceptie
 */
class BaseException : public exception {
protected:
    string mesaj;

public:
    /**
     * Constructorul creeaza o exceptie si o arunca cu mesajul m
     * @param m mesajul care se afiseaza
     */
    explicit BaseException(string m) : mesaj{move(m)} {
    }

    /**
     * Functia returneaza mesajul de eroare a exceptiei cand e apelata de sistem
     * @return returneaza mesajul de eroare
     */
    [[nodiscard]] const char *what() const noexcept override;

    /**
     * Functia returneaza mesajul de eroare a exceptiei
     * @return returneaza mesajul de eroare
     */
    [[nodiscard]] const string &getMesaj() const noexcept;
};

/**
 * O clasa pentru lucru cu fisiere
 * Contine mesajul care se va afisa in caz de exceptie
 */
class FileException final : public BaseException {
    using BaseException::BaseException;
};


/**
 * O clasa pentru modificarea contractului
 * Contine mesajul care se va afisa in caz de exceptie
 */
class ContractException final : public BaseException {
    using BaseException::BaseException;
};

/**
 * O clasa pentru modificarea repository-ului
 * Contine mesajul care se va afisa in caz de exceptie
 */
class RepoException final : public BaseException {
    using BaseException::BaseException;
};


/**
 * O clasa pentru validarea tipurilor de data
 * Contine mesajul care se va afisa in caz de exceptie
 */
class ValidationException final : public BaseException {
    using BaseException::BaseException;
};


/**
 * Clasa pentru a valida tipurilor de date
 * Contine metode pentru validare
 */
class Validator final {
private:
    /**
     * Functia returneaza tipurile valide de discipline
     * @return tipurile valide de discipline
     */
    [[nodiscard]] static const unordered_set<string> &validTypes();

public:
    /**
     * Valideaza o disciplina data
     * @param d o disciplina
     * @throw ValidationException cu mesajul
     *      - "Numele nu poate fi gol!\n", daca numele disciplinei e gol
     *      - "Numarul de ore trebuie sa fie pozitiv!\n", daca numarul de ore a disciplinei este negativ
     *      - "Tipul poate fi doar 'Uman', 'Real' sau '??'!\n", daca tipul nu este {Uman, Real, ??}
     *      - "Profesorul nu poate fi gol", daca numele profesorului este gol
     */
    static void valideaza_disciplina(const Disciplina &d);

    /**
     * Functia verifica daca un numar este mai mare sau egal cu 0 si mai mic decat maxim
     * @param index un numar
     * @param maxim maximul posibil
     * @throw RepoException cu mesajul
     *      -"Elementele sunt doar pe pozitii pozitive!", daca index-ul este negativ
     *      -"Disciplina nu a fost gasita!", daca index-ul este mai mare decat maxim
     */
    static void valideaza_index(int index, size_t maxim);

    /**
     * Functia verifica daca un numar este mai mare sau egal cu 0 si mai mic decat maxim
     * Este specializata pentru lucru cu contracte
     * @param index un numar
     * @param maxim maximul posibil, in acest caz, marimea catalogului de discipline
     * @throw ContractException cu mesajul
     *      -"Nu se poate genera un contract cu un numar negativ de discipline!", daca index-ul este negativ
     *      -"Nu exista atatea discipline in catalog!", daca index-ul este mai mare decat maxim
     */
    static void valideaza_index_contract(int index, size_t maxim);

    /**
     * Functia verifica daca se poate scrie in fisierul dorit
     * @param file_path numele unui fisier
     * @throw FileException cu mesajul - "Nu s-a putut scrie in fisier!", daca nu se poate scrie in fisier
     */
    static void valideaza_ofstream(const string &file_path);
};
