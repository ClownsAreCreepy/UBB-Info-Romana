#pragma once

#include "../Domain/Task.h"
#include <sstream>
#include <fstream>
#include <algorithm>

class RepoTask {
private:
    vector<Task> taskuri;
    string file_path;

    void load_from_file();
    void save_to_file();

public:
    RepoTask(string fp) : file_path(move(fp)) { load_from_file(); }

    void adaugare(const Task &t);

    void set_stare(int id, const string &stare_noua);

    vector<Task> &getAll() { return taskuri; }
};