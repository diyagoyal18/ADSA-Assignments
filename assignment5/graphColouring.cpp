// Name: Diya Goyal
// Roll no: 102215255
// question: 4. Write a program to solve the graph coloring problem (minimum number of colors required to color the graph such that no two adjacent nodes have the same color).
// Acknowledgement: took help from GitHub Copilot 

#include <iostream>
#include <vector>

using namespace std;

class GraphColoring {
    int V; // Number of vertices
    vector<vector<int>> adj; // Adjacency matrix or list
    vector<int> color;

public:
    GraphColoring(int V) {
        this->V = V;
        adj.resize(V, vector<int>(V, 0)); // Using adjacency matrix
        color.resize(V, 0);
    }

    void addEdge(int u, int v) {
        adj[u][v] = 1;
        adj[v][u] = 1; // Undirected graph
    }

    bool isSafe(int node, int c) {
        for (int i = 0; i < V; i++) {
            if (adj[node][i] == 1 && color[i] == c)
                return false;
        }
        return true;
    }

    bool graphColoringUtil(int node, int m) {
        if (node == V) return true; // All nodes are colored

        for (int c = 1; c <= m; c++) {
            if (isSafe(node, c)) {
                color[node] = c;
                if (graphColoringUtil(node + 1, m)) return true;
                color[node] = 0; // Backtrack
            }
        }

        return false;
    }

    int findMinimumColors() {
        for (int m = 1; m <= V; m++) {
            fill(color.begin(), color.end(), 0);
            if (graphColoringUtil(0, m)) {
                return m;
            }
        }
        return V; // Worst case: each vertex needs a unique color
    }

    void printColors() {
        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << " ---> Color " << color[i] << endl;
        }
    }
};

int main() {
    int V = 4;
    GraphColoring g(V);

    // Sample graph
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);

    int minColors = g.findMinimumColors();
    cout << "Minimum number of colors required: " << minColors << endl;
    g.printColors();

    return 0;
}
