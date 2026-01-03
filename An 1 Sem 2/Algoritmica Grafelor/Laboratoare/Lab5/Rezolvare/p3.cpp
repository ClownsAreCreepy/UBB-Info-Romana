#include <fstream>
#include <vector>
#include <set>
#include <stack>
#include <algorithm>

using namespace std;

vector<multiset<int>> graph;    // graful dat
vector<int> eulerian_cycle;     // ciclul cautat


bool esteConexSiGraduriPare(int V, int &start) {
    vector<bool> vizitat(V, false);

    // gasim primul nod cu muchii ca sa incepem dfs
    for (int i = 0; i < V; ++i)
        if (!graph[i].empty()) {
            start = i;
            break;
        }

    if (start == -1)
        return true;        // nu avem muchii, deci ciclul e valid

    // DFS pentru a verifica conectivitatea
    stack<int> st;
    st.push(start);
    vizitat[start] = true;

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        for (int v: graph[u])
            if (!vizitat[v]) {
                vizitat[v] = true;
                st.push(v);
            }
    }

    // daca avem noduri nevizitate cu muchii -> nu e conex
    // daca avem noduri cu graduri impare -> nu exista ciclu eulerian
    for (int i = 0 ; i< V; ++i) {
        if (!vizitat[i] && !graph[i].empty()) return false;
        if (graph[i].size() % 2 != 0) return false;
    }

    return true;
}


void dfs(int node) {
    //exploram folosing smecheria lui Hierholzer
    while (!graph[node].empty()) {
        int vecin = *graph[node].begin();                   // luam un vecin

        graph[node].erase(graph[node].begin());
        graph[vecin].erase(graph[vecin].find(node)); // stergem muchia pe care am parcurs-o

        dfs(vecin);
    }

    eulerian_cycle.push_back(node); //adaugam la ciclu invers
}


int main(int argc, char *argv[]) {
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);

    int V, E;
    fin >> V >> E;

    graph.resize(V);

    for (int i = 0; i < E; ++i) {
        int u,v;
        fin >> u >> v;
        graph[u].insert(v);
        graph[v].insert(u);     //graf neorientat
    }

    int start=-1;  // orice nod cu muchii

    // I am going to sacrifice someone
    if (!esteConexSiGraduriPare(V, start)) {
        fout << "Nu avem ciclu eulerian";
        return 0;
    }

    dfs(start);

    // iteram in ordine inversa, deoarece luam ciclul de la nodul de start, care e adaugat ultimul (cum e asa tot e ciclu valid, dar e mai scurt asa la sintaxa)
    for (int i = static_cast<int>(eulerian_cycle.size()) - 1; i > 0; --i)
        fout << eulerian_cycle[i] << (i - 1 > 0 ? " ": "");

    fin.close();
    fout.close();
    return 0;
}