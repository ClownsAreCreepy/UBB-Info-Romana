#pragma once
#include "../Contract/contract_discipline.h"
#include "../DTO/dto_discipline.h"
#include "../Undo/undo_discipline.h"
#include "../Observer/observer_discipline.h"
#include <unordered_map>
#include <memory>

using std::unordered_map;
using std::ranges::copy_if;
using std::ranges::sort;
using std::back_inserter;
using std::unique_ptr;
using std::make_unique;


/**
 * Clasa de service pentru repositor-ul de discipline
 * Clasa contine o referinta la repository-ul pe care il controleaza
 * Este mostenitor al clasei Observable
 */
class ServiceDisciplina : public Observable{
private:
    IRepoDisciplina &repo;
    ContractStudii contract;
    vector<unique_ptr<ActiuneUndo>> undoList;

public:
    /**
     * Constructor pentru declararea initializata a service-ului
     * @param repository un repository
     */
    explicit ServiceDisciplina(IRepoDisciplina &repository): repo{repository} {}

    /**
     * Constructor de copiere
     * Creeaza o copie a service-ului
     * @param ot un alt service
     */
    ServiceDisciplina(ServiceDisciplina &ot) = delete;

    /**
     * Operator de copiere
     * Creeaza o copie a service-ului
     */
    ServiceDisciplina &operator=(const ServiceDisciplina &) = delete;


    /**
     * Functia valideaza disciplina, apoi o adauga in repository daca totul e ok
     * @param nume numele disciplinei
     * @param ore numarul de ore pe saptamana
     * @param tip tipul disciplinei
     * @param profesor numele profesorului principal al disciplinei
     * @throw ValidationException cu mesajul
     *      - "Numele nu poate fi gol!\n", daca numele disciplinei e gol
     *      - "Numarul de ore trebuie sa fie pozitiv!\n", daca numarul de ore a disciplinei este negativ
     *      - "Tipul poate fi doar 'Uman', 'Real' sau '??'!\n", daca tipul nu este {Uman, Real, ??}
     *      - "Profesorul nu poate fi gol", daca numele profesorului este gol
     *@throw RepoException cu mesajul
     *      -"Disciplina exista deja!", daca disciplina exista deja in repository
     */
    void adauga_service(const string &nume, int ore, const string &tip, const string &profesor);

    /**
     * Functia valideaza index-ul si disciplina, apoi o modifica daca totul e ok
     * @param index pozitia elementului care va fi modificat
     * @param nume_nou numele nou al disciplinei
     * @param ora_noua numarul de ore nou pe saptamana
     * @param tip_nou tipul nou al disciplinei
     * @param profesor_nou numele profesorului principal nou al disciplinei
     * @throw RepoException cu mesajul
     *      -"Elementele sunt doar pe pozitii pozitive!", daca index-ul este negativ
     *      -"Disciplina nu a fost gasita!", daca index-ul este mai mare decat maxim
     *      -"Disciplina exista deja!", daca disciplina noua exista deja in repository
     * @throw ValidationException cu mesajul
     *      - "Numele nu poate fi gol!\n", daca numele disciplinei e gol
     *      - "Numarul de ore trebuie sa fie pozitiv!\n", daca numarul de ore a disciplinei este negativ
     *      - "Tipul poate fi doar 'Uman', 'Real' sau '??'!\n", daca tipul nu este {Uman, Real, ??}
     *      - "Profesorul nu poate fi gol", daca numele profesorului este gol
     */
    void modifica_service(int index, const string &nume_nou, int ora_noua, const string &tip_nou, const string &profesor_nou);

    /**
     * Functia valideaza index-ul, apoi o sterge din repository daca totul e ok
     * @param index pozitia elementului care va fi sters
     * @throw RepoException cu mesajul
     *      -"Elementele sunt doar pe pozitii pozitive!", daca index-ul este negativ
     *      -"Disciplina nu a fost gasita!", daca index-ul este mai mare decat maxim
     */
    void sterge_service(int index);

    /**
     * Functia returneaza elementul de pe pozitia index
     * @param index pozitia elementului care va fi sters
     * @return disciplina de pe pozitia index
     * @throw RepoException cu mesajul
     *      -"Elementele sunt doar pe pozitii pozitive!", daca index-ul este negativ
     *      -"Disciplina nu a fost gasita!", daca index-ul este mai mare decat maxim
     */
    const Disciplina &cauta_service(int index) const;

    /**
     * Functia returneaza intregul repository sub forma de vector
     * @return intregul repository sub forma de vector
     */
    [[nodiscard]] const vector<Disciplina> &getAll() const noexcept;


    /**
     * Functia creeaza un raport a frecventei tipurilor in repository
     * @return raportul care contine pe prima pozitie tipul si pe a doua frecventa sa in repository
     */
    [[nodiscard]] unordered_map<string, ReportDTO> raport_tip() const;


    /**
     * Functia modifica vectorul out astfel incat sa contina disciplinele filtrate dupa numarul de ore
     * @param ore numarul de ore dupa care se face filtrarea
     * @param out vector de discipline filtrat
     */
    void filtrare_ore(int ore, vector<Disciplina> &out) const;

    /**
     * Functia modifica vectorul out astfel incat sa contina disciplinele filtrate dupa numele unui profesor
     * @param profesor numele profesorului dupa care se face filtrarea
     * @param out vector de discipline filtrata
     */
    void filtrare_profesor(const string &profesor, vector<Disciplina> &out) const;

    /**
     * Functia modifica vectorul out astfel incat sa contina diciplinele sortate dupa nume
     * @param out vector de discipline sortata
     */
    void sortare_nume(vector<Disciplina> &out) const;

    /**
     * Functia modifica vectorul out astfel incat sa contina diciplinele sortate dupa ora
     * @param out vector de discipline sortata
     */
    void sortare_ore(vector<Disciplina> &out) const;

    /**
     * Functia modifica vectorul out astfel incat sa contina diciplinele sortate dupa profesor, apoi dupa tip
     * @param out vector de discipline sortata
     */
    void sortare_profesor_tip(vector<Disciplina> &out) const;


    /**
     * Functia reface lista de discipline sa fie ca inainte de apelarea ultimei comenzi
     * @throws RepoException cu mesajul "Nu mai exista operatii de refacut!" daca nu mai exista comenzi de refacut
     */
    void undo();


    /**
     * Functia returneaza o lista cu cuvinte cheie de nu
     * @return o lista cu cuvinte cheie de nu
     */
    [[nodiscard]] static unordered_set<string> no_keywords();

    /**
     * Functia adauga o disciplina in contract dupa nume si, optional, dupa profesor
     * @param nume numele disciplinei care trebuie adaugata
     * @param profesor numele profesorului principal al disciplinei, sau "" daca nu e specificat
     * @param dorinta dorinta de a adauga un disciplina cu numele nume a unui profesor specific
     * @throw ContractException cu mesajul
     *      - "Disciplina exista deja in contract!", daca disciplina se afla deja in contract
     *      - "Disciplina nu exista in catalog!", daca nu exista o disciplina cu numele nume
     *      - "Exista mai multe discipline cu acest nume. Doriti un profesor anume?: ", daca exista mai multe discipline cu acel nume si nu s-a specificat daca se doreste un profesor
     *      - "Nu exista diciplina cu acel profesor!" daca nu exista o disciplina cu numele nume si cu profesorul profesor
     */
    void contract_adauga(const string &nume, const string &profesor = "", const string &dorinta = "");

    /**
     * Functia goleste contractul de materii
     * @throw ContractException "Contractul este deja gol!", daca contractul este gol
     */
    void contract_goleste();

    /**
     * Functia adauga in mod aleator nr dicipline din repository in contract
     * @param nr numarul de discipline care vor fi adaugate
     * @throw ContractException cu mesajul
     *      - "Nu se poate genera un contract cu un numar negativ de discipline!", daca nr e negativ
     *      - "Nu exista atatea discipline in catalog!", daca nr e mai mare decat numarul de discipline din repository
     */
    void contract_generare(int nr);

    /**
     * Functia returneaza lista de discipline din contract sub forma de vector
     * @return contractul de discipline
     */
    [[nodiscard]] const vector<Disciplina> &contract_getAll() const noexcept;


    /**
     * Functia scrie contractul actual in fisierul cu drumul file_path
     * @param file_path drumul catre fisierul in care vrem sa scriem
     * @throw FileException cu mesajul - "Nu s-a putut scrie in fisier!", daca nu se poate scrie in fisier
     */
    void contract_exporta(const string &file_path) const;
};


