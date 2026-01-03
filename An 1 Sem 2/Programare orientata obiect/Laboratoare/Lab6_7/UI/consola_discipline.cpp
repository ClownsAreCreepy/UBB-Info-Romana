#include "consola_discipline.h"


void Consola::ui_meniu() {
    cout << "================== MENIU PRINCIPAL ==================" << endl;
    cout << "Optiuni:" << endl;
    cout << "0. Iesire" << endl;
    cout << "1. Tipareste disciplinele" << endl;
    cout << "2. Adauga o disciplina" << endl;
    cout << "3. Modifica o disciplina" << endl;
    cout << "4. Sterge o disciplina" << endl;
    cout << "5. Cauta o disciplina" << endl;
    cout << "6. Filtreaza disciplinele" << endl;
    cout << "7. Sorteaza disciplinele" << endl;
    cout << "8. Contract de studii" << endl;
    cout << "9. Raport pe tip" << endl;
    cout << "10. Refa ultima operatie" << endl;
    cout << ">>";
}

void Consola::ui_afisare(const vector<Disciplina> &lista_de_afisat, const string &titlu) {
    if (lista_de_afisat.empty()) {
        cout << "Nu exista discipline :(" << endl;
        return;
    }

    cout << endl << "================== " << titlu << " ==================" << endl;
    size_t i = 0;
    for (const auto &d: lista_de_afisat) {
        cout << "[" << i++ << "] " << d;
        if (i < lista_de_afisat.size()) cout << ";";
        cout << endl;
    }
}

int Consola::citeste_int(const string &mesaj) {
    int valoare;
    while (true) {
        cout << mesaj;
        cin >> valoare;
        if (cin.fail()) {
            cout << "!!!!!" << endl;
            cout << "Valoarea trebuie sa fie numar intreg" << endl << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return valoare;
        }
    }
}

string Consola::citeste_string(const string &mesaj) {
    string cuvant;
    cout << mesaj;
    if (cin.peek() == '\n')
        cin.ignore();
    getline(cin, cuvant);
    return cuvant;
}


void Consola::ui_adaugare() const {
    cin.ignore();
    const string nume = citeste_string("Numele materiei: ");
    const int ora = citeste_int("Numarul de ore pe saptamana: ");
    const string tip = citeste_string("Tipul materiei: ");
    const string profesor = citeste_string("Profesorul la materie: ");

    try {
        service.adauga_service(nume, ora, tip, profesor);
        cout << "Materie adaugata cu succes!";
    } catch (const RepoException &rex) {
        cout << endl << "!!!!!" << endl;
        cout << rex.getMesaj() << endl;
    }catch (const ValidationException &vex) {
        cout << "!!!!!" << endl;
        cout << vex.getMesaj() << endl;
    }
}

void Consola::ui_modificare() const {
    const int index = citeste_int("Introduceti pozitia disciplinei pe care doriti sa o modificati: ");
    const string nume = citeste_string("Numele nou al materiei: ");
    const int ora = citeste_int("Numarul nou de ore pe saptamana: ");
    const string tip = citeste_string("Tipul nou al materiei: ");
    const string profesor = citeste_string("Profesorul nou la materie: ");

    try {
        service.modifica_service(index, nume, ora, tip, profesor);
        cout << "Materie modificata cu succes!";
    } catch (const RepoException &ex) {
        cout << "!!!!!" << endl;
        cout << ex.getMesaj();
    }catch (const ValidationException &vex) {
        cout << "!!!!!" << endl;
        cout << vex.getMesaj() << endl;
    }
}

void Consola::ui_stergere() const {
    const int index = citeste_int("Introduceti pozitia disciplinei pe care doriti sa o stergeti: ");

    try {
        service.sterge_service(index);
        cout << "Materie stearsa cu succes!";
    } catch (const RepoException &ex) {
        cout << "!!!!!" << endl;
        cout << ex.getMesaj() << endl;
    }
}

void Consola::ui_cautare() const {
    const int index = citeste_int("Introduceti pozitia disciplinei pe care doriti sa o cautati: ");

    try {
        const Disciplina &d = service.cauta_service(index);
        cout << endl << "Gasit:  " << d;
    } catch (const RepoException &ex) {
        cout << "!!!!!" << endl;
        cout << ex.getMesaj() << endl;
    }
}


void Consola::ui_filtrare() const {
    cout << endl << "1. Filtrare dupa ore";
    cout << endl << "2. Filtrare dupa profesor";
    const int comanda = citeste_int("\n>>");

    vector<Disciplina> lista_filtrata;
    if (comanda == 1) {
        const int ora = citeste_int("\nIntroduceti ora dupa care doriti sa filtrati: ");
        service.filtrare_ore(ora, lista_filtrata);
    } else if (comanda == 2) {
        cin.ignore();
        const string profesor = citeste_string("\nIntroduceti profesorul dupa care doriti sa filtrati: ");
        service.filtrare_profesor(profesor, lista_filtrata);
    } else {
        cout << "Comanda invalida!\n";
        return;
    }

    ui_afisare(lista_filtrata, "DISCIPLINE FILTRATE");
}

void Consola::ui_sortare() const {
    cout << endl << "1. Sortare dupa nume";
    cout << endl << "2. Sortare dupa ore";
    cout << endl << "3. Sortare dupa profesor si tip";
    const int comanda = citeste_int("\n>>");

    vector<Disciplina> lista_sortata;

    switch (comanda) {
        case 1: service.sortare_nume(lista_sortata);
            break;
        case 2: service.sortare_ore(lista_sortata);
            break;
        case 3: service.sortare_profesor_tip(lista_sortata);
            break;
        default: cout << "Comanda invalida!";
            return;
    }

    ui_afisare(lista_sortata, "DISCIPLINE SORTATE");
}


void Consola::ui_raport_tip() const {
    const auto raport = service.raport_tip();
    cout << endl << "================== RAPORT PE TIP ==================" << endl;
    for (const auto &[tip, dto]: raport)
        cout << "Tip: " << tip << "  | Numar: " << dto.getCount() << endl;
}


void Consola::ui_undo() const {
    try {
        service.undo();
        cout << "Ultima operatie a fost anulata cu succes!" << endl;
    } catch (const RepoException& re) {
        cout << "!!!!!" << endl;
        cout << re.getMesaj() << endl;
    }
}


void Consola::ui_contract() const {
    while (true) {
        cout << endl << "================== MENIU CONTRACT ==================" << endl;
        cout << "0. Inapoi" << endl;
        cout << "1. Adauga in contract" << endl;
        cout << "2. Goleste contract" << endl;
        cout << "3. Genereaza contract" << endl;
        cout << "4. Exporteaza contract" << endl;


        switch (citeste_int(">>")) {
            case 0: return;
            case 1: ui_contract_adauga();
                break;
            case 2: ui_contract_goleste();
                break;
            case 3: ui_contract_random();
                break;
            case 4: ui_contract_export();
                break;
            default: cout << "Comanda invalida!" << endl;
        }
    }
}

void Consola::ui_contract_adauga() const {
    const string nume = citeste_string("Nume disciplina: ");
    try {
        service.contract_adauga(nume);
        ui_afisare(service.contract_getAll(), "CONTRACT DE STUDII ANUAL");
    } catch (const ContractException &ce) {
        if (ce.getMesaj() != "Exista mai multe discipline cu acest nume. Doriti un profesor anume?: ") {
            cout << "!!!!!" << endl;
            cout << ce.getMesaj() << endl;
            return;
        }
        if (const string dorinta = citeste_string(ce.getMesaj()); ServiceDisciplina::no_keywords().contains(dorinta)) {
            service.contract_adauga(nume, "", dorinta);
            ui_afisare(service.contract_getAll(), "CONTRACT DE STUDII ANUAL");
        } else {
            const string profesor = citeste_string("Nume profesor: ");
            try {
                service.contract_adauga(nume, profesor);
                ui_afisare(service.contract_getAll(), "CONTRACT DE STUDII ANUAL");
            } catch (const ContractException &coex) {
                cout << "!!!!!" << endl;
                cout << coex.getMesaj() << endl;
            }
        }
    }
}

void Consola::ui_contract_goleste() const {
    try {
        service.contract_goleste();
        ui_afisare(service.contract_getAll(), "CONTRACT DE STUDII ANUAL");
    } catch (const ContractException &ce) {
        cout << "!!!!!" << endl;
        cout << ce.getMesaj() << endl;
    }
}

void Consola::ui_contract_random() const {
    const int nr = citeste_int("Cate discipline doriti sa adaugati?: ");

    try {
        service.contract_generare(nr);
        ui_afisare(service.contract_getAll(), "CONTRACT DE STUDII ANUAL");
    } catch (const ContractException &ce) {
        cout << "!!!!!" << endl;
        cout << ce.getMesaj() << endl;
    }
}


void Consola::ui_contract_export() const {
    const string file_path = citeste_string("Introduceti calea fisierului pentru export: ");
    try {
        service.contract_exporta(file_path);
        ui_afisare(service.contract_getAll(), "CONTRACT DE STUDII ANUAL");
    } catch (const FileException &fe) {
        cout << "!!!!!" << endl;
        cout << fe.getMesaj() << endl;
    }
}


void Consola::preload_data(ServiceDisciplina &service) {
    service.adauga_service("Chimie", 2, "Real", "Paula");
    service.adauga_service("Informatica", 2, "Real", "Miha");
    service.adauga_service("Limba Engleza", 4, "Uman", "Balabuci");
    service.adauga_service("Fizica", 2, "Real", "Dragos");
    service.adauga_service("Biologie", 2, "Real", "Rares");
    service.adauga_service("Matematica", 4, "Real", "Petru");
    service.adauga_service("Limba Romana", 4, "Uman", "Teddy");
    service.adauga_service("Istorie", 2, "Uman", "Vlad");
    service.adauga_service("Dirigentie", 1, "Uman", "Monea");
    service.adauga_service("Religie", 1, "Uman", "Alin Muresan");
    service.adauga_service("Limba Franceza", 2, "Uman", "Emily");
    service.adauga_service("Educatie fizica", 1, "Real", "Dani");
    service.adauga_service("TIC", 2, "Real", "ChatGPT");
    service.adauga_service("Geografie", 1, "Uman", "Amzu");
    service.adauga_service("Desen", 1, "Uman", "Oana");
    service.adauga_service("Muzica", 1, "Uman", "Angel");
    service.adauga_service("Educatie Antreprenoriala", 1, "Uman", "Vlad Barbu");
    service.adauga_service("Psihologie", 1, "Uman", "Mara");
    service.adauga_service("Economie", 1, "Uman", "Tarlea");
    service.adauga_service("Logica", 1, "Uman", "Jayce");
    service.adauga_service("Filosofie", 1, "Uman", "Matei");
    service.adauga_service("Desen", 2, "Uman", "Bianca");

    service.adauga_service("Bloons TD6", 2, "Real", "Alex");
    service.adauga_service("Chestii random", 1, "??", "Gabi");
    service.adauga_service("Having very bad taste in men", 10, "Uman", "Nicol");
    service.adauga_service("How to put on your t-shirt so your biceps are as visible as possible", 8, "Real", "Suciu");
    service.adauga_service("Ceva si el pe acolo", 2, "Uman", "Viorel");
}


void Consola::executa_comanda(int comanda, bool &rulare) const {
    switch (comanda) {
        case 0: rulare = false;
            break;
        case 1: ui_afisare(service.getAll(), "DISCIPLINE");
            break;
        case 2: ui_adaugare();
            break;
        case 3: ui_modificare();
            break;
        case 4: ui_stergere();
            break;
        case 5: ui_cautare();
            break;
        case 6: ui_filtrare();
            break;
        case 7: ui_sortare();
            break;
        case 8: ui_contract();
            break;
        case 9: ui_raport_tip();
            break;
        case 10: ui_undo();
            break;
        default: cout << "Comanda invalida!";
    }
}

void Consola::run() const {
    bool running = true;
    while (running) {
        int comanda;
        while (true) {
            ui_meniu();
            cin >> comanda;

            if (cin.fail()) {
                cout << "\033[31m!!!!!\033[0m\n";  // red
                cout << "!!!!!" << endl;
                cout << "Comanda trebuie sa fie numar intreg" << endl << endl << endl;
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else break;
        }

        executa_comanda(comanda, running);
        cout << "\n\n";
    }
}
