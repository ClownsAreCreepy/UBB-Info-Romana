#pragma once

#include <vector>
#include <algorithm>

using std::vector;

/**
 * Clasa observer pentru entitatile care observa un obiect
 */
class Observer {
public:
    /**
     * Functie pur virtuala pentru ca observatorii sa se modifice
     */
    virtual void update() = 0;

    /**
     * Destructor virtual, pentru apel polimorfic
     */
    virtual ~Observer() = default;
};


/**
 * Clasa observer pentru entitatile care sunt observate
 */
class Observable {
private:
    vector<Observer*> observers;

protected:
    /**
     * Functie care semnaleaza observatorilor sa se modifice
     */
    void notify_all();

    /**
     * Destructor virtual, pentru apel polimorfic
     */
    virtual ~Observable() = default;

public:
    /**
     * Functia adauga un observer in lista de observeri
     * @param obs observatorul care este adaugat
     */
    void addObserver(Observer *obs);

    /**
     * Functia sterge un observer din lista de observeri
     * Este creeata si pusa in destructorul observer-ului pentru a evita memory leaks
     * @param obs observatorul care este sters
     */
    void removeObserver(Observer *obs);
};