
/*
Name: Diya Goyal
Roll Number: 102215255
Question: 2. The Chef has a list of dishes he must prepare and he is able to work on many of them simultaneously (with the help of his employees, of course). For example, he can heat soup, bake a cake, marinate some meat, let some wine aerate, etc. all at the same time since no two of them require a common cooking tool. Unfortunately, his kitchen is dangerously low in its supply of tools and he has no more than one copy of each cooking tool. This means that some dishes cannot be prepared at the same time such as slicing two different cuts of meat since there is only one meat slicer. So, the Chef has scheduled the preparation of the dishes into rounds. In each round, he and his staff prepare some dishes of which no two require a common cooking tool. For simplicity's sake, he will not start preparing dishes from a certain round until all dishes from the previous round are completed. The Chef received the orders for today's dishes early in the day and he has had a lot of time to think about how to optimally schedule them. In fact, he even found a way to prepare all of the dishes in only 3 rounds! Unfortunately, he lost the piece of paper that contained this schedule and he has to start preparing dishes right away. He needs your help and he needs it fast! Your job is to assign, to each dish, a round in the schedule such that no two dishes scheduled in the same round require a common cooking tool. It doesn't matter if it uses more than three rounds. Of course, fewer rounds are preferred, but the Chef would be happy with any schedule right now.   
Acknowledgments: Geeks for geeks,classmates,
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to assign rounds (colors) using a greedy algorithm
void assignRounds(int n, const vector<vector<int>>& adj) {
    vector<int> round(n, -1);  // round[i] = round assigned to dish i
    vector<bool> used(n, false); // used[i] = is round i used by neighbors

    for (int u = 0; u < n; ++u) {
        // Mark all rounds used by adjacent dishes
        fill(used.begin(), used.end(), false);
        for (int v : adj[u]) {
            if (round[v] != -1)
                used[round[v]] = true;
        }

        // Find the first unused round
        int r;
        for (r = 0; r < n; ++r) {
            if (!used[r]) break;
        }

        round[u] = r;
    }

    // Output result
    for (int i = 0; i < n; ++i) {
        cout << "Dish " << i << " -> Round " << round[i] + 1 << endl; // +1 to make it 1-indexed
    }
}

int main() {
    int n, e;
    cout << "Enter number of dishes (nodes) and number of conflicts (edges): ";
    cin >> n >> e;

    vector<vector<int>> adj(n);
    cout << "Enter " << e << " pairs of conflicting dishes (0-indexed):" << endl;
    for (int i = 0; i < e; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    assignRounds(n, adj);
    return 0;
}
