#ifndef DFS_HPP
#define DFS_HPP

#include<iostream>
#include<vector>
#include<stack>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;
using Graph = vector<vector<int> >;

vector<bool> GRAPH_SCANNING(Graph G, int N, int s) {

    vector<bool> R(N, false);
    stack<int> S;
    // Graph T(N);
    R[s] = true; //seen
    S.push(s); //todo

    while (!S.empty()) {

        int v = S.top(); // DFS

        if (!G[v].empty()) {
            rep(i, G[v].size()) {
                int w = G[v][i];
                if (!R[w]) // w in V/R
                {
                    R[w] = true;
                    S.push(w);
                    // T[v].push_back(w); BFS tree
                }
            }
        }
        S.pop();// Q-v
    }
    return R;
}

#endif // DFS_HPP
