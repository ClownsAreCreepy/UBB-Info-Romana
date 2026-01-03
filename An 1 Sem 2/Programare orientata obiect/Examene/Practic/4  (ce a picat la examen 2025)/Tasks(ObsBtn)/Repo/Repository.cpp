#include "Repository.h"

void RepoTask::load_from_file() {
    taskuri.clear();
    ifstream in(file_path);
    if (!in.is_open()) return;      // daca nu exista, o luam de la capat

    string line;
    while (getline(in, line)) {
        stringstream ss(line);
        int id = -1;
        string descriere, nume, stare;
        vector<string> programatori;

        ss >> id;
        ss.ignore(1);
        getline(ss, descriere, ',');

        // get the vector
        string programatori_str;
        getline(ss, programatori_str,',');

        stringstream progstream(programatori_str);
        while (progstream >> nume)
            programatori.push_back(nume);
        // done with the vector

        getline(ss, stare, ',');

        if (id != -1) {
            Task t{id, descriere, programatori, stare};
            taskuri.push_back(t);
        }
    }

    in.close();
}

void RepoTask::save_to_file() {
    ofstream out(file_path);
    for (const Task &t : taskuri) {
        out << t.getId() << ',' << t.getDescriere() << ',';

        vector programatori = t.getProgramatori();
        for (int i = 0; i < programatori.size(); ++i) {
            out << programatori[i];
            if (i != programatori.size() - 1)
                out << ' ';
        }
        out << ',' << t.getStare() << '\n';
    }
}

void RepoTask::adaugare(const Task &t) {
    load_from_file();
    taskuri.emplace_back(t);
    save_to_file();
}

void RepoTask::set_stare(int id, const string &stare_noua) {
    load_from_file();
    for (Task &t: taskuri)
        if (t.getId() == id)
            t.setStare(stare_noua);

    save_to_file();
}
