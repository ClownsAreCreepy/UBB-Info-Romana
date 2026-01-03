#include "Service.h"

void ServiceTask::sort_service() {
    ranges::sort(repo.getAll(), [](const Task &a, const Task &b) {
        return a.getStare() < b.getStare();
    });
}

void ServiceTask::adaugare_service(int id, const string &descriere, const vector<string> &programatori, const string &stare) {
    string erori;

    for (const Task &t: repo.getAll())
        if (id == t.getId()) {
            erori += "Id-ul trebuie sa fie unic!\n";
            break;
        }

    if (descriere.empty())
        erori += "Descirerea nu poate fi goala!\n";

    if (programatori.empty() || programatori.size() > 4)
        erori += "Trebuie minim 1 sau maxim 4 programatori!\n";

    if (!keywords.contains(stare))
        erori += "Starea poate fi: open, inprogress sau closed\n";

    if (!erori.empty())
        throw runtime_error(erori);

    const Task t{id, descriere, programatori, stare};
    repo.adaugare(t);
    sort_service();
    notify_all();
}

const vector<int> &ServiceTask::filtrare_service(vector<int> &filtrata, const string &programator) {
    filtrata.clear();

    for (const Task &t: repo.getAll())
        for (const string &p: t.getProgramatori())
            if (p == programator) {
                filtrata.emplace_back(t.getId());
                break;
            }

    return filtrata;
}

void ServiceTask::set_stare_service(int id, const string &stare_noua) {
    repo.set_stare(id, stare_noua);
    sort_service();
    notify_all();
}
