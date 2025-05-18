// Name: Diya Goyal
// Roll no: 102215255
// Question:1. Chef lives in Chefland. Chefland can be accurately represented by a certain number of intersections and the roads connecting them. Chefland is a strange place because all the roads there are one-way. Also, for any two intersections A and B, once you travel from A to B, you can never return to A again because there is simply no route you can take to get back to A. Unaware of this, Chef set out to visit his friend, and now he cannot return home! So, Chef decides to travel to the townhall and complain about this ridiculous system. Studying the map of Chefland, Chef wonders about the number of ways in which he can travel to the townhall. Help him find this number. As the number may be very large, print it modulo 10^9+7.    
// Acknowledgement: took help from GitHub Copilot
#include <iostream>
#include <vector>
#include <queue>
using namespace std;


const int MOD = 1e9 + 7;


int main() {
    int n, m;
    cin >> n >> m; // n = number of intersections (nodes), m = number of roads (edges)


    vector<vector<int>> adj(n + 1);
    vector<int> in_degree(n + 1, 0);


    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_degree[v]++;
    }


    int s, t;
    cin >> s >> t; // s = source, t = target


    // Topological Sort using Kahn's Algorithm
    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (in_degree[i] == 0)
            q.push(i);
    }


    vector<int> topo;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        topo.push_back(u);
        for (int v : adj[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0)
                q.push(v);
        }
    }


    // DP to count number of ways to reach each node from s
    vector<long long> dp(n + 1, 0);
    dp[s] = 1;


    for (int u : topo) {
        for (int v : adj[u]) {
            dp[v] = (dp[v] + dp[u]) % MOD;
        }
    }


    cout << dp[t] << endl;


    return 0;
}
