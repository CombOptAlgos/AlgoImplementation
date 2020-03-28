#ifndef KRUSKAL_HPP
#define KRUSKAL_HPP
#include<iostream>
#include<vector>
#include<queue>
#include "branching.hpp"
using namespace std;
using Graph = vector<vector<pair<int, int> > >;

class Kruskal
{
    public:
        int N, M; // グラフGの頂点数・枝数
    private:
        vector<tuple<int, int, int> > W;
    public:
        Kruskal(Graph G);
        Graph run();
        Branching B;
};          

Kruskal::Kruskal(Graph G)
{
    // Gから、(w, v, w)のリストであるWを作る
    N = G.size();
    M = 0;
    for (int g_a=0; g_a<N; g_a++)
    {
        vector<pair<int, int> > g = G[g_a];
        
        for (auto g_n : g)
        {
            int g_b = g_n.first;
            int g_w = g_n.second;
            if (g_a < g_b)
            {
                W.push_back(make_tuple(g_w, g_a, g_b));
            }
        }
    }
    M = W.size();
    B.init(M, N);
}

Graph Kruskal::run()
{
    queue<int> E;

    sort(W.begin(), W.end());
    reverse(W.begin(), W.end());

    int a, b, w; // two vertices
    for (int i=0; i<M; i++) {
        a = get<1>(W[i]);
        b = get<2>(W[i]);
        if (!B.share_same_parent(a, b)) {
            // このとき;circuitはできな
            E.push(i);
            B.merge(a, b); 
            assert(B.share_same_parent(a, b));
        }
    }

    Graph T(N);

    if (E.size() != N-1)
    {
        cout << "Graph does not have spanning tree" << endl;
    }
    else
    {
        while (!E.empty()){
            tuple<int, int, int> e = W[E.front()];
            E.pop();
            int t_a, t_b, t_w;
            tie(t_w, t_a, t_b) = e;
            T[t_a].push_back(make_tuple(t_b, t_w));
            T[t_b].push_back(make_tuple(t_a, t_w));
        }    
    }
    return T;
}

#endif // KRUSKAL_HPP
