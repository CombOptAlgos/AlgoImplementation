#include<vector>
#include<iostream>
#include "strongly_connected_component.hpp"
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

using namespace std;
using Graph = vector<vector<int> >;

int main(){
    int V, E; cin >> V >> E;

    Graph G(V);
    rep(i, E)
    {
       int a, b;
       cin >> a >> b;
       G[a].push_back(b);
    }

    StronglyConnectedComponent scc(G, V);
    vector<int> comp = scc.run();

    rep(i, V)
    {
        cout << i << ' ' << comp[i] << endl;
    }

    return 0;
}
