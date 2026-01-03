#pragma once

#include "../Repo/Repository.h"
#include "../Observe/Observe.h"
#include <iostream>
#include <exception>
#include <set>

class ServiceTask : public Observable{
private:
    RepoTask &repo;
    set<string> keywords;

    void sort_service();

public:
    ServiceTask(RepoTask &r) : repo(r) {
        sort_service();
        keywords = {"open", "inprogress", "closed"};
    }

    void adaugare_service(int id, const string &descriere, const vector<string> &programatori, const string &stare);

    const vector<int> &filtrare_service(vector<int> &filtrata, const string &programator);

    void set_stare_service(int id, const string &stare_noua);

    const vector<Task> &getAll() const { return repo.getAll(); }
    const set<string> &getKeywords() const { return keywords; }
};