// Name: Diya Goyal
// Roll no: 102215255
// Question:1. Write code to represent an undirected graph using both adjacency matrix and adjacency list. Implement basic operations like adding and removing edges, printing the graph, and checking for the existence of an edge between two nodes.
 // a. Given a graph (represented as an adjacency list), implement the depth first search (DFS) and breadth first search (BFS) traversal starting from a specified node.
 // b. Write a program to check if  a given graph is bipartite.
// Acknowledgement: took help from GitHub Copilot 
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>
using namespace std;

class Graph {
private:
    int V;  // Number of vertices
    vector<vector<int>> adjMatrix;
    vector<list<int>> adjList;

public:
    Graph(int vertices) {
        V = vertices;
        adjMatrix.resize(V, vector<int>(V, 0));
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        if (u >= V || v >= V) return;

        // Adjacency Matrix
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;

        // Adjacency List
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    void removeEdge(int u, int v) {
        if (u >= V || v >= V) return;

        // Adjacency Matrix
        adjMatrix[u][v] = 0;
        adjMatrix[v][u] = 0;

        // Adjacency List
        adjList[u].remove(v);
        adjList[v].remove(u);
    }
    bool hasEdge(int u, int v) {
        if (u >= V || v >= V) return false;
    
        for (int neighbor : adjList[u]) {
            if (neighbor == v) {
                return true;
            }
        }
    
        return false;
    }

    void printAdjMatrix() {
        cout << "Adjacency Matrix:" << endl;
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void printAdjList() {
        cout << "Adjacency List:" << endl;
        for (int i = 0; i < V; ++i) {
            cout << i << ": ";
            for (int neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
    void DFSUtil(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";

        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        cout << "DFS starting from node " << start << ": ";
        DFSUtil(start, visited);
        cout << endl;
    }

    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS starting from node " << start << ": ";

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }

        cout << endl;
    }
bool isBipartite() {
    // color array: -1 = uncolored, 0/1 = two different colors
    vector<int> color(V, -1);

    // Check each connected component
    for(int start = 0; start < V; ++start) {
        if(color[start] == -1) {
            // BFS from this node
            queue<int> q;
            color[start] = 0; 
            q.push(start);

            while(!q.empty()) {
                int node = q.front();
                q.pop();

                for(int neighbor : adjList[node]) {
                    if(color[neighbor] == -1) {
                        // Assign opposite color to neighbor
                        color[neighbor] = 1 - color[node];
                        q.push(neighbor);
                    } else if(color[neighbor] == color[node]) {
                        // Conflict: same color on both ends
                        return false;
                    }
                }
            }
        }
    }
    // If no conflicts found, the graph is bipartite
    return true;
}
};

int main() {
    Graph g(5);

    g.addEdge(0, 1);
    g.addEdge(0, 4);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);

    g.printAdjMatrix();
    g.printAdjList();

    cout << "Has edge between 0 and 1: " << g.hasEdge(0, 1) << endl;
    cout << "Has edge between 2 and 4: " << g.hasEdge(2, 4) << endl;

    g.removeEdge(1, 4);

    cout << "\nAfter removing edge between 1 and 4:\n";
    g.printAdjMatrix();
    g.printAdjList();
    g.DFS(0);
    g.BFS(0);
    g.isBipartite() ? cout << "Graph is bipartite." : cout << "Graph is not bipartite.";
    return 0;
}
