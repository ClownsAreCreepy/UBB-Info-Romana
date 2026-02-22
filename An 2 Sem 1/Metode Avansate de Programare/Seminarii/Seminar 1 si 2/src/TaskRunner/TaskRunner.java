package TaskRunner;

import App.Task;

public interface TaskRunner {
    void executeOneTask();  // executa un singur task din colectie
    void executeAll();      // executa toate task-urile din colectie
    void addTask(Task t);   // adauga un task nou in colectia de task-uri
    boolean hasTask();      // verifica daca mai exista task-uri de executat
}
