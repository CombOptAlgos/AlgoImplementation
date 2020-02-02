#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

using namespace std;
const int INF = 999999999;

// 枝の構造体（行先のvertex, capacity, 逆辺のid）
struct edge {int to, capacity, rev_id;};

// 両矢印Graphの隣接リスト
using Graph = vector<vector<edge> >;

void add_edge(Graph &G, int from, int to, int capacity){

    G[from].push_back( (edge){to, capacity, (int)G[to].size()} );
    G[to].push_back( (edge){from, 0, (int)G[from].size()-1} );

}

// f-augmenting pathの計算
vector<int> dfs(Graph G, int v, int t, int N){
    vector<int> path(N);
    vector<bool> seen(N);

    // 探索済みの頂点
    seen[v] = true;

    rep(i, G[v].size()){
        if (G[v][i].capacity > 0){
            int next_v = G[v][i].to;

            path[v] = i; // next_v = G[v][path[v]].to
            if (next_v == t) break;

            if (!seen[next_v]) dfs(G, next_v, t, N);
        }
    }
    return path;
}

// compute gamma
int compute_gamma(Graph G, vector<int> f, vector<int> path, int v, int t){

    int gamma = INF;

    while(1){
        gamma = (gamma < G[v][path[v]].capacity ? gamma : G[v][path[v]].capacity);
        
        v = path[v];
        if (G[v][path[v]].to == t) break;
    }

    return gamma;
}

// augment
void augment(Graph &G, vector<int> f, vector<int> path, int N){

}


int main(){

    // Graph入力
    int N, M; cin >> N >> M;
    int s, t; cin >> s >> t;
    Graph G(N);
    rep(i, N){
        int from, to, cap; cin >> from >> to >> cap;
        add_edge(G, from, to, cap);

    }

    // flowの初期化
    vector<int> f(M);


    return 0;
}
