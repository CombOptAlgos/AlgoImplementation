#ifndef BFS_HPP
#define BFS_HPP

#include<iostream>
#include<vector>
#include<queue>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;
using Graph = vector<vector<int> >;

vector<bool> GRAPH_SCANNING(Graph G, int N, int s) {

    vector<bool> R(N, false);
    queue<int> Q;
    // Graph T(N);
    R[s] = true; //seen
    Q.push(s); //todo

    while (!Q.empty()) {

        int v = Q.front(); // BFS

        if (!G[v].empty()) {
            rep(i, G[v].size()) {
                int w = G[v][i];
                if (!R[w]) // w in V/R
                {
                    R[w] = true;
                    Q.push(w);
                    // T[v].push_back(w); BFS tree
                }
            }
        }
        Q.pop();// Q-v
    }
    return R;
}

#endif // BFS_HPP
