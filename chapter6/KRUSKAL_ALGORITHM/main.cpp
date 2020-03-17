#include<iostream>
#include<vector>
#include<queue>
#include "kruskal.hpp"

using namespace std;
using Graph = vector<vector<pair<int, int> > >;
int N, M;

int main() {
    //weighted undirected graph Gを読み込んでGのminimum weight spannning tree Tを得る

    int a, b, w;
    
    cin >> N >> M;
    Graph G(N);
    for (int i=0; i<M; i++) {
        cin >> a >> b >> w;
        a--;
        b--;
        G[a].push_back(make_pair(b, w));
        G[b].push_back(make_pair(a, w));
    }

    Kruskal kr(G);

    Graph T = kr.run();

    // Tの出力
    int N_T = T.size();
    int M_T = N_T - 1; //spanning tree
    
    cout << N_T << " " << M_T << endl;

    for (int t_a=0; t_a<N; t_a++)
    {
        for (int j=0; j<T[t_a].size(); j++) {
            int t_b = T[t_a][j].first;
            int t_w = T[t_a][j].second;
            if (t_a < t_b) cout << t_a+1 << " " << t_b+1 << " " << t_w << endl;
        }
    }
}
