// Name: Diya Goyal
// Roll no: 102215255
// question: 5. Find the i. Euler path & Cycle ii. Hamiltonian path & Cycle for a given graph.
// Acknowledgement: took help from GitHub Copilot 

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

class Graph {
    int V;
    vector<list<int>> adj;

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }

    // Eulerian Path and Cycle
    void findEuler() {
        int odd = 0;
        for (int i = 0; i < V; i++) {
            if (adj[i].size() % 2 != 0) odd++;
        }

        if (odd == 0) cout << "Graph has an Eulerian Cycle.\n";
        else if (odd == 2) cout << "Graph has an Eulerian Path.\n";
        else cout << "Graph has neither Eulerian Path nor Cycle.\n";
    }

    // Hamiltonian Path and Cycle using Backtracking
    bool isSafe(int v, vector<bool> &visited, int pos, vector<int> &path) {
        if (find(adj[path[pos - 1]].begin(), adj[path[pos - 1]].end(), v) == adj[path[pos - 1]].end())
            return false;
        if (visited[v]) return false;
        return true;
    }

    bool hamCycleUtil(vector<int> &path, vector<bool> &visited, int pos) {
        if (pos == V) {
            // Check if there's an edge from last to first
            return find(adj[path[pos - 1]].begin(), adj[path[pos - 1]].end(), path[0]) != adj[path[pos - 1]].end();
        }

        for (int v = 1; v < V; v++) {
            if (isSafe(v, visited, pos, path)) {
                path[pos] = v;
                visited[v] = true;

                if (hamCycleUtil(path, visited, pos + 1))
                    return true;

                visited[v] = false;
            }
        }
        return false;
    }

    void findHamiltonianCycle() {
        vector<int> path(V, -1);
        vector<bool> visited(V, false);
        path[0] = 0;
        visited[0] = true;

        if (hamCycleUtil(path, visited, 1)) {
            cout << "Hamiltonian Cycle: ";
            for (int v : path) cout << v << " ";
            cout << path[0] << "\n";
        } else {
            cout << "No Hamiltonian Cycle exists.\n";
        }
    }

    bool hamPathUtil(vector<int> &path, vector<bool> &visited, int pos) {
        if (pos == V) return true;

        for (int v = 0; v < V; v++) {
            if (pos == 0 || isSafe(v, visited, pos, path)) {
                path[pos] = v;
                visited[v] = true;

                if (hamPathUtil(path, visited, pos + 1)) return true;

                visited[v] = false;
            }
        }
        return false;
    }

    void findHamiltonianPath() {
        vector<int> path(V, -1);
        vector<bool> visited(V, false);

        if (hamPathUtil(path, visited, 0)) {
            cout << "Hamiltonian Path: ";
            for (int v : path) cout << v << " ";
            cout << "\n";
        } else {
            cout << "No Hamiltonian Path exists.\n";
        }
    }
};

int main() {
    int V = 5;
    Graph g(V);

    // Sample graph
    g.addEdge(0, 1);
    g.addEdge(0, 3);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);

    cout << "i. Eulerian Check:\n";
    g.findEuler();

    cout << "\nii. Hamiltonian Path and Cycle:\n";
    g.findHamiltonianPath();
    g.findHamiltonianCycle();

    return 0;
}
