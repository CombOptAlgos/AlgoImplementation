#include<iostream>
#include<vector>
#include<queue>
#include "bfs.hpp"

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;

int main(){

    int N, M; cin >> N >> M;
    int s; cin >> s;

    Graph G(N);
    rep(i, M){
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        // undirected graph
        G[b].push_back(a);
    }

    vector<bool> R = GRAPH_SCANNING(G, N, s);

    rep(i, N){
        if (R[i]){
            cout << (i==0 ? "" : " ") << i;
        }
    }
    cout << endl;

// output of BFS trew 
//    rep(i, N){
//        if (!T[i].empty()){
//            rep(j,T[i].size())
//            {
//                cout << i << ' ' << T[i][j] << endl;
//            }
//        }
//    }
  
    return 0;
}
