/*
Name: Diya Goyal
Roll Number: 102215255
Question: 1. Chef was given a task by his teacher. He has to color a tree in such a way that no two adjacent nodes have the same colour. But Chef is not artistic and decides to colour them with numbers. He decides to make it a challenge and find the minimum numbers he can colour the graph with such that the sum in minimum. Given a tree, help Chef determine the minimum colour sum can be achieved when the tree is properly coloured.
Acknowledgments: Geeks for geeks,classmates,
*/
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int MAXN = 1005; // assuming at most 1000 nodes
const int MAXC = 20;   // we'll try colors from 1 to 20

vector<int> tree[MAXN];
int dp[MAXN][MAXC + 1]; // dp[node][color]
bool visited[MAXN];

// Tree DP function
void dfs(int node, int parent) {
    for (int color = 1; color <= MAXC; ++color) {
        dp[node][color] = color; // cost to paint current node
    }

    for (int child : tree[node]) {
        if (child == parent) continue;
        dfs(child, node);

        for (int color = 1; color <= MAXC; ++color) {
            int minChildSum = 0;
            for (int childColor = 1; childColor <= MAXC; ++childColor) {
                if (childColor != color) {
                    minChildSum = minChildSum == 0 ? dp[child][childColor] : min(minChildSum, dp[child][childColor]);
                }
            }
            dp[node][color] += minChildSum;
        }
    }
}

int main() {
    int n;
    cin >> n; // number of nodes

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    dfs(1, -1); // assuming node 1 as root

    int answer = INT_MAX;
    for (int c = 1; c <= MAXC; ++c) {
        answer = min(answer, dp[1][c]);
    }

    cout << answer << endl;
    return 0;
}
