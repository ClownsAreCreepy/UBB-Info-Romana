#pragma once
template<typename ElementT>
class IteratorLista;

/**
 * Template Lista
 * Se comporta ca un vector dinamic, cu tot cu metode si campuri
 * Ca campuri are numarul de elemente, capacitatea si un pointer la vectorul de elemente
 * @tparam ElementT element de un tip anume
 */
template<typename ElementT>
class Lista {
private:
    int lg; //numar de elemente
    int cap; //capacitate
    ElementT *elems; //elemente

    /**
     * Verificam daca mai exista loc in vector:
     *      -daca da, iesim din functie
     *      -daca nu, marim capacitatea vectorului
     */
    void ensureCapacity() {
        if (lg < cap)
            return; //mai avem loc

        cap = 2 * cap;
        auto *aux = new ElementT[cap];
        for (int i = 0; i < lg; ++i)
            aux[i] = elems[i];

        delete[] elems;
        elems = aux;
    }

public:
    //Constructori si distructori si operatii==================================================================================================================================================
    /**
     * Constructor default.
     * Alocam loc pentru 5 elemente
     */
    Lista() : lg{0}, cap{5}, elems{new ElementT[cap]} {
    }

    /**
     * Constructor de copiere -> (Rule of 3)
     * Obiectul curent (this) acum se creeaza
     * Aloca spatiu pentru elemente
     * Copiaza elementele din other in this
     * @param other alt vector
     */
    Lista(const Lista &other) : lg{other.lg}, cap{other.cap}, elems{new ElementT[other.cap]} {
        for (int i = 0; i < other.lg; ++i) elems[i] = other.elems[i];
    }

    /**
     * Operator assignment -> (Rule of 3)
     * Elibereaza ce era in obiectul curent (this)
     * Aloca spatiu pentru elemente
     * Copiaza elementele din other in this
     * @param other alt vector
     * @return vectorul modificat, caz in care e diferit de other
     *         vectorul nemodificat, caz in care e identic cu other
     */
    Lista &operator=(const Lista &other) {
        if (this == &other)
            return *this; //s-a facut l=l

        delete[] elems;
        elems = new ElementT[other.cap];
        //copiez elementele
        for (int i = 0; i < other.lg; ++i)
            elems[i] = other.elems[i];

        lg = other.lg;
        cap = other.cap;
        return *this;
    }

    /**
     * Destructor -> (Rule of 3)
     * Eliberam memoria
     */
    ~Lista() {
        delete[] elems;
    }

    /**
     * Move constructor -> (Rule of 5)
     * Apelat daca construim un nou vector dintr-un r-value (ex temporary)
     * Obiectul other nu se mai foloseste astfel se poate refolosi interiorul lui
     * @param other alt vector
     */
    Lista(Lista &&other) noexcept : lg{other.lg}, cap{other.cap}, elems{other.elems} {
        //Am copiat data pointer-ul de la other
        //Acum eliberam data pointer-ul de la obiectul sursa astfel incat destructorul nu elibereaza memoria de mai multe ori
        other.elems = nullptr;
        other.lg = 0;
        other.cap = 0;
    }

    /**
     * Move assignment -> (Rule of 5)
     * Similar cu move constructor
     * Folosit la assignment
     * Elibereaza ce continea obiectul curent (this)
     * "fura" interiorul lui other
     * pregateste other pentru distrugere
     * @param other alt vector
     * @return vectorul modificat, caz in care e diferit de other
     *         vectorul nemodificat, caz in care e identic cu other
     */
    Lista &operator=(Lista &&other) noexcept {
        if (this == &other)
            return *this;

        delete[] elems;
        //Copiem data pointer-ul de la other
        elems = other.elems;
        lg = other.lg;
        cap = other.cap;

        //Acum eliberam data pointer-ul de la obiectul sursa astfel incat destructorul nu elibereaza memoria de mai multe ori
        other.elems = nullptr;
        other.lg = 0;
        other.cap = 0;
        return *this;
    }

    //Gata cu constructori si distructori si operatii=========================================================================================================================================



    /**
     * Functia adauga in vector un nou element
     * @param el element de tip ElementT
     */
    void add(const ElementT &el) {
        ensureCapacity(); //daca e nevoie mai alocam memorie
        elems[lg++] = el;
    }

    /**
     * Functia returneaza elementul dorit vector
     * @param index pozitia elementului dorit
     * @return elementul dorit
     */
    ElementT &get(int index) const {
        return elems[index];
    }

    /**
     * Functia modifica elementul de pe pozitia index din vector
     * @param index pozitia elementului care trebuie modificat
     * @param el elementul nou
     */
    void set(int index, const ElementT &el) {
        elems[index] = el;
    }

    /**
     * Functia sterge elementul de pe pozitia index din vector
     * @param index pozitia elementului care trebuie sters
     */
    void removeAt(int index) {
        for (int i = index; i < lg - 1; ++i)
            elems[i] = elems[i + 1];
        lg--;
    }

    /**
     * Functia returneaza lungimea vectorului
     * @return lungimea vectorului
     */
    [[nodiscard]] int size() const noexcept {
        return lg;
    }



    /**
     * Functia returneaza un iterator care arata catre prima pozitie a iteratorului
     * @return un iterator pe prima pozitie a vectorului
     */
    IteratorLista<ElementT> begin() const {
        return IteratorLista<ElementT>(*this, 0);
    }

    /**
     * Functia returneaza un iterator care arata catre ultima pozitie a vectorului
     * @return un iterator pe ultima pozitie a vectorului
     */
    IteratorLista<ElementT> end() const {
        return IteratorLista<ElementT>(*this, lg);
    }
};



/**
 * Clasa Iterator
 * Itereaza peste elementele vectorului din Lista
 * Permite indexarea si utilizarea vectorului in range for
 * @tparam ElementT element de un tip anume
 */
template<typename ElementT>
class IteratorLista {
private:
    const Lista<ElementT> &lista;
    int poz;

public:
    /**
     * Constructor default
     * @param v o lista
     * @param poz pozitia pe care se va genera iteratorul
     */
    IteratorLista(const Lista<ElementT> &v, int poz) noexcept : lista{v}, poz{poz} {
    }

    /**
     * Operatia returneaza elementul curent
     * @return elementul curent
     */
    ElementT &operator*() const {
        return lista.get(poz);
    }

    /**
     * Operatia avanseaza iteratorul cu o pozitie
     * @return iteratorul modificat
     */
    IteratorLista &operator++() {
        poz++;
        return *this;
    }

    /**
     * Functia verifica daca pozitia iteratorului curent e aceeasi cu cea a iteratorului other
     * @param other alt iterator
     * @return true, daca pozitia iteratorului curent e aceeasi cu cea a iteratorului other
     *         false, in caz contrar
     */
    bool operator==(const IteratorLista &other) const {
        return poz == other.poz;
    }

    /**
     * Functia verifica daca pozitia iteratorului curent e diferita de cea a iteratorului other
     * @param other alt iterator
     * @return false, daca pozitia iteratorului curent e aceeasi cu cea a iteratorului other
     *         true, in caz contrar
     */
    bool operator!=(const IteratorLista &other) const {
        return poz != other.poz;
    }
};
