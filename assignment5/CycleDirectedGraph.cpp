// Name: Diya Goyal
// Roll no: 102215255
// Question 2. Write a program to check for Cycles in a Directed Graph:
// Acknowledgement: took help from GitHub Copilot 

#include <iostream>
#include <vector>
using namespace std;

class Graph {
private:
    int V; // Number of vertices
    vector<vector<int>> adjList; // Adjacency list

    bool dfsCycleCheck(int node, vector<bool>& visited, vector<bool>& recursionStack) {
        visited[node] = true;
        recursionStack[node] = true;

        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                if (dfsCycleCheck(neighbor, visited, recursionStack)) {
                    return true;
                }
            } else if (recursionStack[neighbor]) {
                return true; // Cycle detected
            }
        }

        recursionStack[node] = false; // Remove the node from the recursion stack
        return false;
    }

public:
    Graph(int vertices) {
        V = vertices;
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    bool hasCycle() {
        vector<bool> visited(V, false);
        vector<bool> recursionStack(V, false);

        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                if (dfsCycleCheck(i, visited, recursionStack)) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 1); // This edge creates a cycle

    if (g.hasCycle()) {
        cout << "The graph contains a cycle.\n";
    } else {
        cout << "The graph does not contain a cycle.\n";
    }

    return 0;
}