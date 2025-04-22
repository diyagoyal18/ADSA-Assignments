// Name: Diya Goyal
// Roll no: 102215255
// question: 3. Write a program to perform the topological sorting for a Directed Acyclic Graph (DAG).
// Acknowledgement: took help from GitHub Copilot 

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency list

public:
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v); // Directed edge from u to v
    }

    void topologicalSort() {
        vector<int> in_degree(V, 0);

        // Calculate in-degree of each vertex
        for (int u = 0; u < V; u++) {
            for (int v : adj[u]) {
                in_degree[v]++;
            }
        }

        queue<int> q;
        // Enqueue all vertices with in-degree 0
        for (int i = 0; i < V; i++) {
            if (in_degree[i] == 0)
                q.push(i);
        }

        vector<int> topo_order;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo_order.push_back(u);

            // Decrease in-degree of all neighbors
            for (int v : adj[u]) {
                in_degree[v]--;
                if (in_degree[v] == 0)
                    q.push(v);
            }
        }

        // Check for cycle
        if (topo_order.size() != V) {
            cout << "Graph has a cycle. Topological sorting not possible." << endl;
            return;
        }

        cout << "Topological Order: ";
        for (int node : topo_order)
            cout << node << " ";
        cout << endl;
    }
};

int main() {
    int V = 6;
    Graph g(V);

    // Sample DAG
    g.addEdge(5, 2);
    g.addEdge(5, 0);
    g.addEdge(4, 0);
    g.addEdge(4, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 1);

    g.topologicalSort();

    return 0;
}
