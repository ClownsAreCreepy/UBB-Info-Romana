#include "service_discipline.h"


void ServiceDisciplina::adauga_service(const string &nume, int ore, const string &tip, const string &profesor) {
    const Disciplina d{nume, ore, tip, profesor};
    Validator::valideaza_disciplina(d);

    repo.adauga(d);

    undoList.push_back(make_unique<UndoAdauga>(repo));
}

void ServiceDisciplina::modifica_service(int index, const string &nume_nou, int ora_noua, const string &tip_nou,
                                         const string &profesor_nou) {
    const Disciplina d{nume_nou, ora_noua, tip_nou, profesor_nou};
    Validator::valideaza_index(index, repo.getAll().size());
    Validator::valideaza_disciplina(d);

    const Disciplina d_veche = repo.cauta(static_cast<size_t>(index));

    repo.modifica(static_cast<size_t>(index), d);
    undoList.push_back(make_unique<UndoModifica>(repo, index, d_veche));
}

void ServiceDisciplina::sterge_service(int index) {
    Validator::valideaza_index(index, repo.getAll().size());

    const Disciplina d = repo.cauta(static_cast<size_t>(index));

    repo.sterge(index);
    undoList.push_back(make_unique<UndoSterge>(repo, index, d));
}

const Disciplina &ServiceDisciplina::cauta_service(int index) const {
    Validator::valideaza_index(index, repo.getAll().size());

    return repo.cauta(static_cast<size_t>(index));
}

const vector<Disciplina> &ServiceDisciplina::getAll() const noexcept {
    return repo.getAll();
}


void ServiceDisciplina::filtrare_ore(int ore, vector<Disciplina> &out) const {
    out.clear();
    const auto &all = repo.getAll();
    copy_if(all, back_inserter(out), [=](const Disciplina &d) {
        return d.getOre() == ore;
    });
}

void ServiceDisciplina::filtrare_profesor(const string &profesor, vector<Disciplina> &out) const {
    out.clear();
    const auto &all = repo.getAll();
    copy_if(all, back_inserter(out), [=](const Disciplina &d) {
        return d.getProfesor() == profesor;
    });
}

void ServiceDisciplina::sortare_nume(vector<Disciplina> &out) const {
    out = repo.getAll();
    sort(out, [](const Disciplina &a, const Disciplina &b) {
        return a.getNume() < b.getNume();
    });
}

void ServiceDisciplina::sortare_ore(vector<Disciplina> &out) const {
    out = repo.getAll();
    sort(out, [](const Disciplina &a, const Disciplina &b) {
        return a.getOre() < b.getOre();
    });
}

void ServiceDisciplina::sortare_profesor_tip(vector<Disciplina> &out) const {
    out = repo.getAll();
    sort(out.begin(), out.end(), [](const Disciplina &a, const Disciplina &b) {
        if (a.getProfesor() != b.getProfesor())
            return a.getProfesor() < b.getProfesor();
        return a.getTip() < b.getTip();
    });
}


void ServiceDisciplina::undo() {
    if (undoList.empty())
        throw RepoException("Nu mai exista operatii de refacut!");

    undoList.back()->doUndo();
    undoList.pop_back();
}


unordered_set<string> ServiceDisciplina::no_keywords() {
    static const unordered_set<string> k = {"nu", "Nu", "NU", "Nah", "nope", "Nuh uh"};
    return k;
}

void ServiceDisciplina::contract_adauga(const string &nume, const string &profesor, const string &dorinta) {
    vector<Disciplina> gasit;

    for (const auto &d: repo.getAll())
        if (d.getNume() == nume)
            gasit.emplace_back(d);

    if (gasit.empty())
        throw ContractException("Disciplina nu exista in catalog!");

    if (gasit.size() == 1 || no_keywords().contains(dorinta)) {
        contract.adauga(gasit[0]);
        notify_all();
        return;
    }

    if (gasit.size() > 1 && profesor.empty())
        throw ContractException("Exista mai multe discipline cu acest nume. Doriti un profesor anume?: ");

    for (const auto &d: gasit)
        if (d.getProfesor() == profesor) {
            contract.adauga(d);
            notify_all();
            return;
        }

    throw ContractException("Nu exista disciplina cu acel profesor!");
}

void ServiceDisciplina::contract_goleste() {
    contract.goleste();

    notify_all();
}

void ServiceDisciplina::contract_generare(int nr) {
    Validator::valideaza_index_contract(nr, repo.getAll().size());

    contract.generare(repo.getAll(), nr);

    notify_all();
}

const vector<Disciplina> &ServiceDisciplina::contract_getAll() const noexcept {
    return contract.getAll();
}


unordered_map<string, ReportDTO> ServiceDisciplina::raport_tip() const {
    unordered_map<string, ReportDTO> raport;

    for (const auto &d: repo.getAll()) {
        const string &tip = d.getTip();
        auto &dto = raport[tip];
        dto = ReportDTO(dto.getCount() + 1);
    }

    return raport;
}

void ServiceDisciplina::contract_exporta(const string &file_path) const {
    Validator::valideaza_ofstream(file_path);
    ofstream out(file_path);

    contract.exporta_contract(out);
}
