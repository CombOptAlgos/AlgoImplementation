#ifndef EULER_HPP
#define EULER_HPP

#include <iostream>
#include <vector>

#define rep(i,n) for(int i=0; i<(int)(n); i++)
#define repi(i,s,n) for(int i=s; i<(int)(n); i++)
using namespace std;
using Graph = vector<vector<int> >;

vector<int> EULER(Graph G, int v) {
    vector<int> V;
    vector<int> W;
    int x, y;
    bool is_eulerian=true;

    V.push_back(v);
    x = v;
    if(!G[x].empty()) {
        while (!G[x].empty()) {
            y = G[x][0];
            V.push_back(y);
            G[x].erase(G[x].begin());
            G[y].erase(remove(G[y].begin(), G[y].end(), x), G[y].end());
            x = y;
        }
    }
    W.push_back(V[0]);
    repi(i, 1, V.size()-1) {
        vector<int> TMP = EULER(G, V[i]);
        if (TMP.back()!=V[i]) {
            is_eulerian=false;
        }
        rep(j, TMP.size()) {
            W.push_back(TMP[j]);
        }
    }
    if (V.size()!=1)
        W.push_back(V[V.size()-1]);

    if(!is_eulerian) {
        cout << "This graph is not eulerian" << endl;
        W.clear();
    }

    return W;
}

#endif // EULER_HPP
