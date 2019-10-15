#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;
using Graph = vector<vector<int> >;

vector<bool> GRAPH_SCANNING(Graph G, int N, int s) {

    vector<bool> R(N, false);
    vector<int> Q;
    // Graph T(N);
    R[s] = true; //seen
    Q.push_back(s); //todo

    while (!Q.empty()) {

        int v = Q[0]; // BFS

        if (!G[v].empty()) {
            rep(i, G[v].size()) {
                int w = G[v][i];
                if (!R[w]) // w in V/R
                {
                    R[w] = true;
                    Q.push_back(w);
                    // T[v].push_back(w);
                }
            }
        }
        Q.erase(Q.begin()); // Q-v
    }
    return R;
}

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
            cout << i << ' ';
        }
    }
    cout << endl;

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
