// Name: Diya Goyal
// Roll no: 102215255
// Question 2. Chromatic Number: You are given a connected graph consisting of N nodes and no cycles. You have to determine the chromatic number of the graph. NOTE : The chromatic number of a graph is the smallest number of colors needed to color the vertices of the graph so that no two adjacent vertexes share the same color. i. Find the minimum colors required for both cycle and non-cycle graphs.


// Acknowledgement: took help from GitHub Copilot
#include <iostream>
#include <vector>
using namespace std;


bool dfs(int node, int color, vector<vector<int>> &adj, vector<int> &colors) {
    colors[node] = color;
    for (int neighbor : adj[node]) {
        if (colors[neighbor] == -1) {
            if (!dfs(neighbor, 1 - color, adj, colors))
                return false;
        } else if (colors[neighbor] == color) {
            return false; // Not bipartite due to same-color neighbor
        }
    }
    return true;
}


int main() {
    int n, m;
    cin >> n >> m;


    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected graph
    }


    vector<int> colors(n + 1, -1);
    bool isBipartite = dfs(1, 0, adj, colors);


    if (n == 1)
        cout << 1 << endl;
    else if (isBipartite)
        cout << 2 << endl;
    else
        cout << 3 << endl;
    return 0;
}
