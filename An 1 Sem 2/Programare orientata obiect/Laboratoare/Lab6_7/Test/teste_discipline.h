#pragma once
#include "../Service/service_discipline.h"
#include <cassert>
#include <cstdio>

using std::cout;
using std::ostringstream;
using std::remove;

/**
 * Clasa pentru a testa aplicatia
 */
class TesteDiscipline final {
private:
    /**
    * Functia testeaza functionalitatea validare din aplicatie, cu tot cu tiparirea disciplinelor
    */
    static void test_validare();


    /**
     * Functia testeaza functionalitatea de adaugare din aplicatie
     * @param service serivce-ul cu care se apeleaza functia
     */
    static void test_adaugare(ServiceDisciplina &service);

    /**
     * Functia testeaza functionalitatea de modificare din aplicatie
     * @param service serivce-ul cu care se apeleaza functia
     */
    static void test_modificare(ServiceDisciplina &service);

    /**
    * Functia testeaza functionalitatea de stergere din aplicatie
    * @param service serivce-ul cu care se apeleaza functia
    */
    static void test_stergere(ServiceDisciplina &service);

    /**
    * Functia testeaza functionalitatea de refacere a listei de discipline din aplicatie
    * @param service serivce-ul cu care se apeleaza functia
    */
    static void test_undo(ServiceDisciplina &service);

    /**
     * Functia ruleaza testele pentru operatiile care lucreaza exclusiv pe memorie
     */
    static void test_memorie();

    /**
     * Functia ruleaza testele pentru operatiile care lucreaza exclusiv pe fisiere
     */
    static void test_fisiere();

    /**
     * Functia ruleaza testele pentru operatiile care lucreaza cu repository-ul fals
     */
    static void test_falsitate();

    /**
    * Functia testeaza functionalitatea cautare din aplicatie
    */
    static void test_cautare();


    /**
    * Functia testeaza functionalitatea filtrare din aplicatie
    */
    static void test_filtrare();

    /**
    * Functia testeaza functionalitatea sortare din aplicatie
    */
    static void test_sortare();


    /**
     * Functia testeaza functionaliatea de a raporta frecventa tipurilor de discipline in repository
     */
    static void test_raport_tip();


    /**
    * Functia testeaza functionaliatea de adaugare in contract din aplicatie
    */
    static void test_contract_adaugare();

    /**
     * Functia testeaza functionaliatea de golie a contractului din aplicatie
     */
    static void test_contract_goleste();

    /**
     * Functia testeaza functionaliatea de generare a unui contract din aplicatie
     */
    static void test_contract_generare();


    /**
     * Functia testeaza functionalitatea de a exporta contractul intr-un fisier dat
     */
    static void test_contract_export();

public:
    /**
    * Functia executa toate textele
    */
    static void testAll();
};
