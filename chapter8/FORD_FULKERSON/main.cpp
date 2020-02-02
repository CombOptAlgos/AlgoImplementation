#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

using namespace std;
const int INF = 999999999;

// 枝の構造体（行先のvertex, capacity, 逆辺のid）
struct edge {int to, capacity, rev_id;};

// Graphの隣接リスト
using Graph = vector<vector<edge> >;

// Graphに枝を追加
void add_edge(Graph &G, int from, int to, int capacity){

    G[from].push_back( (edge){to, capacity, (int)G[to].size()} );
}

// two arrow Graphに枝を追加
void add_edge_two_arrow(Graph &G, int from, int to, int capacity){

    G[from].push_back( (edge){to, capacity, (int)G[to].size()} );
    G[to].push_back( (edge){from, 0, (int)G[from].size()-1} );
}

// f-augmenting pathの計算
vector<int> dfs(Graph G, int v, int t, int N, bool &end_frag){
    cout << "hello world!" << endl;
    vector<int> path(N);
    vector<bool> seen(N, false);
    end_frag = true;

    // 探索済みの頂点
    seen[v] = true;

    rep(i, G[v].size()){
        if (G[v][i].capacity > 0){
            int next_v = G[v][i].to;

            path[v] = i; // next_v = G[v][path[v]].to
            if (next_v == t){
                end_frag = false;
                break;
            }

            if (!seen[next_v]) dfs(G, next_v, t, N, end_frag);
        }
    }
    return path;
}

// compute gamma
int compute_gamma(Graph G, vector<int> path, int v, int t){

    int gamma = INF;

    while(1){
        gamma = (gamma < G[v][path[v]].capacity ? gamma : G[v][path[v]].capacity);
        v = G[v][path[v]].to;
        if (v == t) break;
    }

    return gamma;
}

// augment
void augment(Graph &G, vector<int> path, int gamma, int v, int t){

    while(1){

        // path上の辺
        edge e = G[v][path[v]];
        e.capacity = e.capacity - gamma;
        // path上の辺の逆辺
        G[e.to][e.rev_id].capacity = G[e.to][e.rev_id].capacity + gamma;

        v = G[v][path[v]].to;
        if (v == t) break;
    }
}


int main(){

    // Graph入力
    int N, M; cin >> N >> M;
    int s, t; cin >> s >> t;
    Graph G(N), G2(N); // graph, two_arrow_graph
    rep(i, M){
        int from, to, cap; cin >> from >> to >> cap;
        add_edge(G, from, to, cap);
        add_edge_two_arrow(G2, from, to, cap);
    }

    // 初期化
    bool end_frag = false;

    // FORD FULKERSON
    while(1){
        // find augmenting s-t path
        vector<int> path = dfs(G2, s, t, N, end_frag);
        cout << "dfs ok" << endl;
        if (end_frag) break;

        // compute gamma
        int gamma = compute_gamma(G2, path, s, t);
        cout << "gamma" << endl;

        // augment f along path by gamma
        augment(G2, path, gamma, s, t);
        cout << "augment" << endl;
    }

    // max flowの出力
    rep(v, N){
        rep(i, G[v].size()){
            int f = G[v][i].capacity - G2[v][i].capacity;
            cout << v << ' ' << G[v][i].to << ' ' << f << endl;
        }
    }

    return 0;
}