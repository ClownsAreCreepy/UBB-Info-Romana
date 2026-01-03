#include "teste_discipline.h"


void TesteDiscipline::test_validare() {
    RepoDisciplinaMem repo;
    ServiceDisciplina service{repo};

    service.adauga_service("a", 1, "Real", "M");
    assert(repo.getAll().size() == 1);

    try {
        service.adauga_service("", 12, "Real", "X");
        assert(false);
    } catch (const ValidationException &e) {
        assert(static_cast<string>(e.what()) == "Numele nu poate fi gol!\n");
    }

    try {
        service.adauga_service("", -12, "Mimi", "");
        assert(false);
    } catch (const ValidationException &e) {
        assert(
            e.getMesaj() ==
            "Numele nu poate fi gol!\nNumarul de ore trebuie sa fie pozitiv!\nTipul poate fi doar 'Uman', 'Real' sau '??'!\nProfesorul nu poate fi gol!\n");
    }

    try {
        service.modifica_service(0, "", -12, "Mimi", "");
        assert(false);
    } catch (const ValidationException &e) {
        assert(
            e.getMesaj() ==
            "Numele nu poate fi gol!\nNumarul de ore trebuie sa fie pozitiv!\nTipul poate fi doar 'Uman', 'Real' sau '??'!\nProfesorul nu poate fi gol!\n");
    }

    //testam tiparirea
    const Disciplina d("Matematica", 4, "Real", "Petru");
    ostringstream out;
    out << d;
    const string expected = "Nume: Matematica | Ore: 4 | Tip: Real | Profesor: Petru";
    assert(out.str() == expected);
}


void TesteDiscipline::test_adaugare(ServiceDisciplina &service) {
    assert(service.getAll().empty());
    service.adauga_service("A", 1, "Real", "A");
    assert(service.getAll().size() == 1);
    service.adauga_service("B", 2, "Real", "B");
    assert(service.getAll().size() == 2);
    assert(service.getAll()[0].getOre() == 1);

    try {
        service.adauga_service("B", 2, "Real", "B");
        assert(false);
    } catch (const RepoException &e) {
        assert(e.getMesaj() == "Disciplina exista deja!");
    }
}


void TesteDiscipline::test_modificare(ServiceDisciplina &service) {
    service.adauga_service("A", 1, "Real", "A");
    service.modifica_service(0, "B", 8, "Uman", "P");
    assert(service.getAll()[0].getProfesor() == "P");

    try {
        service.modifica_service(0, "B", 8, "Uman", "P");
        assert(false);
    } catch (const RepoException &e) {
        assert(e.getMesaj() == "Disciplina exista deja!");
    }

    try {
        service.modifica_service(50, "B", 8, "Uman", "P");
        assert(false);
    } catch (const RepoException &e) {
        assert(e.getMesaj() == "Disciplina nu a fost gasita!");
    }
}


void TesteDiscipline::test_stergere(ServiceDisciplina &service) {
    service.adauga_service("A", 1, "Real", "A");
    service.adauga_service("B", 2, "Uman", "B");

    try {
        service.sterge_service(2);
        assert(false);
    } catch (const RepoException &e) {
        assert(static_cast<string>(e.what()) == "Disciplina nu a fost gasita!");
    }

    service.sterge_service(0);
    assert(service.getAll().size() == 1);
    assert(service.getAll()[0].getNume() == "B");

    service.sterge_service(0);
    assert(service.getAll().empty());

    try {
        service.sterge_service(0);
        assert(false);
    } catch (const RepoException &e) {
        assert(e.getMesaj() == "Disciplina nu a fost gasita!");
    }

    try {
        service.sterge_service(-1);
        assert(false);
    } catch (const RepoException &e) {
        assert(e.getMesaj() == "Elementele sunt doar pe pozitii pozitive!");
    }
}



void TesteDiscipline::test_undo(ServiceDisciplina &service) {
    try {
        service.undo();
        assert(false);
    } catch (const RepoException &re) {
        assert(re.getMesaj() == "Nu mai exista operatii de refacut!");
    }

    service.adauga_service("Limba Romana", 8, "Uman", "Oana");
    service.adauga_service("Matematica", 8, "Real", "Petru");
    service.adauga_service("Desen", 2, "Uman", "Bianca");
    service.adauga_service("Sport", 4, "Real", "Dani");
    service.adauga_service("Istorie", 4, "Uman", "Vlad");
    service.adauga_service("Politica", 4, "Uman", "Tarlea");
    service.adauga_service("Informatica", 8, "Real", "Miha");
    service.adauga_service("Film", 6, "Uman", "Petru");
    service.adauga_service("Chestii random", 6, "??", "Gabi");
    service.adauga_service("Biologie", 6, "Real", "Rares");

    service.sterge_service(4);
    service.adauga_service("Opera", 4, "Uman", "Sopranos");
    service.modifica_service(6, "Movies", 6, "Uman", "Petru");
    service.sterge_service(6);


    service.undo();
    assert(service.getAll()[6].getNume() == "Movies");

    service.undo();
    assert(service.getAll()[6].getNume() == "Film");

    service.undo();
    assert(service.getAll().size() == 9);
    assert(service.getAll()[8].getNume() == "Biologie");

    service.undo();
    assert(service.getAll()[4].getNume() == "Istorie");
}


void TesteDiscipline::test_memorie() {
    RepoDisciplinaMem repo_add;
    ServiceDisciplina service_mem_add{repo_add};

    RepoDisciplinaMem repo_mod;
    ServiceDisciplina service_mem_mod{repo_mod};

    RepoDisciplinaMem repo_del;
    ServiceDisciplina service_mem_del{repo_del};

    RepoDisciplinaMem repo_undo;
    ServiceDisciplina service_mem_undo{repo_undo};


    test_adaugare(service_mem_add);
    test_modificare(service_mem_mod);
    test_stergere(service_mem_del);
    test_undo(service_mem_undo);
}


void TesteDiscipline::test_fisiere() { {
        char temp[L_tmpnam];
        tmpnam(temp);

        RepoDisciplinaFile repo(temp);
        ServiceDisciplina service{repo};

        test_adaugare(service);

        remove(temp);
    } {
        char temp[L_tmpnam];
        tmpnam(temp);

        RepoDisciplinaFile repo(temp);
        ServiceDisciplina service{repo};

        test_modificare(service);

        remove(temp);
    } {
        char temp[L_tmpnam];
        tmpnam(temp);

        RepoDisciplinaFile repo(temp);
        ServiceDisciplina service{repo};

        test_stergere(service);

        remove(temp);
    } {
        char temp[L_tmpnam];
        tmpnam(temp);

        RepoDisciplinaFile repo(temp);
        ServiceDisciplina service{repo};

        test_undo(service);

        remove(temp);
    }
}


void TesteDiscipline::test_cautare() {
    RepoDisciplinaMem repo;
    ServiceDisciplina service{repo};

    service.adauga_service("A", 1, "Real", "A");
    try {
        service.cauta_service(1);
        assert(false);
    } catch (const RepoException &e) {
        assert(e.getMesaj() == "Disciplina nu a fost gasita!");
    }

    try {
        service.cauta_service(-1);
        assert(false);
    } catch (const RepoException &e) {
        assert(e.getMesaj() == "Elementele sunt doar pe pozitii pozitive!");
    }

    const Disciplina &d = service.cauta_service(0);

    assert(d.getNume() == "A");
}

void TesteDiscipline::test_falsitate() {
    try {
        RepoDisciplinaFals repo_fals{5};
        assert(false);
    } catch (const ValidationException &ve) {
        assert(ve.getMesaj() == "Probabilitatea trebuie sa fie intre 0 si 1!");
    }

    RepoDisciplinaFals repo_fail(1.0);
    ServiceDisciplina service_fail(repo_fail);

    try {
        service_fail.adauga_service("Chimie", 3, "Real", "Ana");
        assert(false);
    } catch (const RepoException &re) {
        assert(re.getMesaj() == "Exceptie aruncata de repo!");
    }

    RepoDisciplinaFals repo_add{0.0};
    ServiceDisciplina service_add{repo_add};

    RepoDisciplinaFals repo_mod{0.0};
    ServiceDisciplina service_mod{repo_mod};

    RepoDisciplinaFals repo_del{0.0};
    ServiceDisciplina service_del{repo_del};

    RepoDisciplinaFals repo_undo{0};
    ServiceDisciplina service_undo{repo_undo};


    test_adaugare(service_add);
    test_modificare(service_mod);
    test_stergere(service_del);
    test_undo(service_undo);
}


void TesteDiscipline::test_filtrare() {
    RepoDisciplinaMem repo;
    ServiceDisciplina service{repo};
    vector<Disciplina> out;


    service.adauga_service("Limba Romana", 8, "Uman", "Oana");
    service.adauga_service("Matematica", 8, "Real", "Petru");
    service.adauga_service("Desen", 2, "Uman", "Bianca");
    service.adauga_service("Sport", 4, "Real", "Dani");
    service.adauga_service("Istorie", 4, "Uman", "Vlad");
    service.adauga_service("Politica", 4, "Uman", "Tarlea");
    service.adauga_service("Informatica", 8, "Real", "Miha");
    service.adauga_service("Film", 6, "Uman", "Petru");
    service.adauga_service("Chestii random", 6, "??", "Gabi");
    service.adauga_service("Biologie", 6, "Real", "Rares");

    service.filtrare_ore(4, out);
    assert(out.size() == 3);
    assert(out[0].getNume() == "Sport");

    service.filtrare_ore(100, out);
    assert(out.empty());

    service.filtrare_profesor("Petru", out);
    assert(out.size() == 2);
    assert(out[0].getNume() == "Matematica");

    service.filtrare_profesor("Mark", out);
    assert(out.empty());
}


void TesteDiscipline::test_sortare() {
    RepoDisciplinaMem repo;
    ServiceDisciplina service{repo};
    vector<Disciplina> out;

    service.adauga_service("Limba Romana", 8, "Uman", "Oana");
    service.adauga_service("Matematica", 8, "Real", "Petru");
    service.adauga_service("Desen", 2, "Uman", "Bianca");
    service.adauga_service("Sport", 4, "Real", "Dani");
    service.adauga_service("Istorie", 4, "Uman", "Vlad");
    service.adauga_service("Politica", 4, "Uman", "Tarlea");
    service.adauga_service("Informatica", 8, "Real", "Miha");
    service.adauga_service("Film", 6, "Uman", "Petru");
    service.adauga_service("Chestii random", 6, "??", "Gabi");
    service.adauga_service("Biologie", 6, "Real", "Rares");

    service.sortare_nume(out);
    const Disciplina *prev = nullptr;
    for (const auto &d: out) {
        if (prev != nullptr)
            assert(prev->getNume() <= d.getNume());
        prev = &d;
    }

    service.sortare_ore(out);
    prev = nullptr;
    for (const auto &d: out) {
        if (prev != nullptr)
            assert(prev->getOre() <= d.getOre());
        prev = &d;
    }

    service.sortare_profesor_tip(out);
    prev = nullptr;
    for (const auto &d: out) {
        if (prev != nullptr)
            assert(
            prev->getProfesor() < d.getProfesor() || (prev->getProfesor() == d.getProfesor() && prev->getTip() < d.
                getTip()));
        prev = &d;
    }
}


void TesteDiscipline::test_raport_tip() {
    RepoDisciplinaMem repo;
    ServiceDisciplina service{repo};

    service.adauga_service("Limba Romana", 8, "Uman", "Oana");
    service.adauga_service("Matematica", 8, "Real", "Petru");
    service.adauga_service("Desen", 2, "Uman", "Bianca");
    service.adauga_service("Sport", 4, "Real", "Dani");
    service.adauga_service("Istorie", 4, "Uman", "Vlad");
    service.adauga_service("Politica", 4, "Uman", "Tarlea");
    service.adauga_service("Informatica", 8, "Real", "Miha");
    service.adauga_service("Geometrie", 6, "Uman", "Sergiu");
    service.adauga_service("Chestii random", 6, "??", "Gabi");
    service.adauga_service("Biologie", 6, "Real", "Rares");

    auto raport = service.raport_tip();
    assert(raport["Uman"].getCount() == 5);
    assert(raport["Real"].getCount() == 4);
    assert(raport["??"].getCount() == 1);
}


void TesteDiscipline::test_contract_adaugare() {
    RepoDisciplinaMem repo;
    ServiceDisciplina service{repo};

    service.adauga_service("Limba Romana", 8, "Uman", "Oana");
    service.adauga_service("Matematica", 8, "Real", "Petru");
    service.adauga_service("Matematica", 6, "Uman", "Sergiu");

    assert(service.contract_getAll().empty());
    service.contract_adauga("Limba Romana");
    assert(service.contract_getAll().size() == 1);
    assert(service.contract_getAll()[0].getProfesor() == "Oana");

    try {
        service.contract_adauga("Nu exista damn");
        assert(false);
    } catch (const ContractException &ce) {
        assert(ce.getMesaj() == "Disciplina nu exista in catalog!");
    }

    try {
        service.contract_adauga("Matematica");
        assert(false);
    } catch (const ContractException &ce) {
        assert(
            static_cast<string>(ce.what()) == "Exista mai multe discipline cu acest nume. Doriti un profesor anume?: ");
    }

    service.contract_adauga("Matematica", "Sergiu", "Perchance");
    assert(service.contract_getAll().size() == 2);
    assert(service.contract_getAll()[1].getOre() == 6);

    service.contract_adauga("Matematica", "", "Nah");
    assert(service.contract_getAll().size() == 3);
    assert(service.contract_getAll()[2].getOre() == 8);

    try {
        service.contract_adauga("Matematica", "Pipi", "Yea");
        assert(false);
    } catch (const ContractException &ce) {
        assert(ce.getMesaj() == "Nu exista disciplina cu acel profesor!");
    }

    try {
        service.contract_adauga("Limba Romana");
        assert(false);
    } catch (const ContractException &ce) {
        assert(ce.getMesaj() == "Disciplina exista deja in contract!");
    }
}


void TesteDiscipline::test_contract_goleste() {
    RepoDisciplinaMem repo;
    ServiceDisciplina service{repo};

    service.adauga_service("Limba Romana", 8, "Uman", "Oana");
    service.adauga_service("Matematica", 8, "Real", "Petru");

    service.contract_adauga("Limba Romana");
    service.contract_adauga("Matematica");

    assert(service.contract_getAll().size() == 2);

    service.contract_goleste();
    assert(service.contract_getAll().empty());

    try {
        service.contract_goleste();
        assert(false);
    } catch (const ContractException &ce) {
        assert(ce.getMesaj() == "Contractul este deja gol!");
    }
}


void TesteDiscipline::test_contract_generare() {
    RepoDisciplinaMem repo;
    ServiceDisciplina service{repo};

    service.adauga_service("Limba Romana", 8, "Uman", "Oana");
    service.adauga_service("Matematica", 8, "Real", "Petru");
    service.adauga_service("Desen", 2, "Uman", "Bianca");
    service.adauga_service("Sport", 4, "Real", "Dani");
    service.adauga_service("Istorie", 4, "Uman", "Vlad");
    service.adauga_service("Politica", 4, "Uman", "Tarlea");
    service.adauga_service("Informatica", 8, "Real", "Miha");

    service.contract_generare(5);
    assert(service.contract_getAll().size() == 5);

    service.contract_generare(7);
    assert(service.contract_getAll().size() == 7);

    const auto &gen = service.contract_getAll();
    for (size_t i = 0; i < gen.size() - 1; ++i)
        for (size_t j = i + 1; j < gen.size(); ++j)
            assert(gen[i] != gen[j]);

    try {
        service.contract_generare(-1);
        assert(false);
    } catch (const ContractException &ce) {
        assert(ce.getMesaj() == "Nu se poate genera un contract cu un numar negativ de discipline!");
    }

    try {
        service.contract_generare(12);
        assert(false);
    } catch (const ContractException &ce) {
        assert(ce.getMesaj() == "Nu exista atatea discipline in catalog!");
    }
}


void TesteDiscipline::test_contract_export() {
    RepoDisciplinaMem repo;
    ServiceDisciplina service{repo};

    service.adauga_service("Limba Romana", 8, "Uman", "Oana");
    service.adauga_service("Matematica", 8, "Real", "Petru");

    service.contract_adauga("Limba Romana");
    service.contract_adauga("Matematica");

    char temp_path[L_tmpnam];
    tmpnam(temp_path);
    const string file_path = temp_path;

    service.contract_exporta(file_path);

    ifstream in(file_path);
    assert(in.is_open());

    string line;
    int line_count = 0;
    bool found_romana = false, found_mate = false;

    while (getline(in, line)) {
        ++line_count;
        if (line.find("Limba Romana") != std::string::npos)
            found_romana = true;
        if (line.find("Matematica") != std::string::npos)
            found_mate = true;
    }

    in.close();
    remove(file_path.c_str());

    assert(line_count == 2);
    assert(found_romana);
    assert(found_mate);


    try {
        service.contract_exporta("/Mimi/mumu");
        assert(false);
    } catch (const FileException &fe) {
        assert(fe.getMesaj() == "Nu s-a putut scrie in fisier!");
        assert(static_cast<string>(fe.what()) == "Nu s-a putut scrie in fisier!");
    }
}


void TesteDiscipline::testAll() {
    test_validare();
    test_cautare();

    test_memorie();
    test_fisiere();
    test_falsitate();

    test_filtrare();
    test_sortare();

    test_raport_tip();

    test_contract_adaugare();
    test_contract_goleste();
    test_contract_generare();

    test_contract_export();
}
