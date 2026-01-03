#pragma once
#include "../Service/service_discipline.h"

using std::cin;
using std::cout;
using std::ws;

/**
 * Clasa Consola
 * Contine metodele de interactionare cu utilizatorul
 * Contine service-ul care opereaza pe lista de discipline
 */
class Consola final {
private:
    ServiceDisciplina &service;

public:
    /**
     * Constructorul pentru declarare intializata cu un service
     * @param serv service-ul care opereaza pe lista de discipline
     */
    explicit Consola(ServiceDisciplina &serv): service{serv} {}


    /**
     * Functia tipareste meniul aplicatiei
     */
    static void ui_meniu();

    /**
     * Functia afiseaza lista de discipline cu format foarte frumos
     * @param lista_de_afisat lista care trebuie afisata
     * @param titlu mesajul care se va afisa inainte de a se tipari lista
     */
    static void ui_afisare(const vector<Disciplina> &lista_de_afisat, const string &titlu);

    /**
     * Functia tipareste un mesaj, apoi citeste de la tastatura un numar intreg
     * Daca se scrie altceva, functia se reia si cere din nou un numar intreg
     * Se repeta pana se citeste un numar intreg
     * @param mesaj mesajul care se tipareste inainte de citire
     * @return numarul citit
     */
    static int citeste_int(const string &mesaj);

    /**
     * Functia tipareste un mesaj, apoi citeste de la tastatura un sir de caractere, pana la end_line
     * @param mesaj mesajul care se tipareste inainte de citire
     * @return sirul citit
     */
    static string citeste_string(const string &mesaj);


    /**
     * Functia preia de la tastatura datele necesare, apoi adauga in repository o noua disciplina
     */
    void ui_adaugare() const;

    /**
     * Functia preia de la tastatura datele necesare, apoi modifica o disciplina in repository
     */
    void ui_modificare() const;

    /**
     * Functia preia de la tastatura datele necesare, apoi sterge o disciplina din repository
     */
    void ui_stergere() const;

    /**
     * Functia preia de la tastatura datele necesare, apoi tipareste disciplina cautata din repository
     */
    void ui_cautare() const;


    /**
     * Functia preia de la tastatura datele necesare, apoi tipareste o lista filtrata dupa o conditie
     */
    void ui_filtrare() const;

    /**
     * Functia preia de la tastatura datele necesare, apoi tipareste o lista sortata dupa o conditie
     */
    void ui_sortare() const;

    /**
     * Functia afiseaza un raport a fiecarui tip existent si a frecventei sale
     */
    void ui_raport_tip() const;


    /**
     * Functia restituie starea precedenta a listei de discipline
     */
    void ui_undo() const;


    /**
     * Functia tipareste meniul aplicatiei, si ruleaza funtionalitatile dorite
     */
    void ui_contract() const;


    /**
     * Functia preia de la tastatura datele necesare, apoi adauga in contract o noua disciplina
     */
    void ui_contract_adauga() const;

    /**
     * Functia goleste contractul daca nu este deja gol
     */
    void ui_contract_goleste() const;

    /**
     * Functia preia de la tastatura datele necesare, apoi genereaza un nou contract cu disciplinele din repository
     */
    void ui_contract_random() const;


    /**
     * Functia exporteaza contractul curent la un fisier dat de la tastatura
     */
    void ui_contract_export() const;


    /**
     * Functia populeaza service-ul cu un numar mare de discipline
     * @param service service-ul pe care il modificam
     */
    static void preload_data(ServiceDisciplina &service);

    /**
     * Functia executa comanda dorita de utilizator
     * @param comanda numarul comanda care va fi executata
     * @param rulare variabila care decide daca aplicatia mai ruleaza sau nu
     */
    void executa_comanda(int comanda, bool &rulare) const;

    /**
     * Functia ruleaza aplicatia
     */
    void run() const;
};
