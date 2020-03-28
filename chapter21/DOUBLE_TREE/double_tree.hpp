#ifndef DOUBLE_TREE_HPP
#define DOUBLE_TREE_HPP

#include <iostream>
#include <vector>
#include <stack>
#include "branching.hpp"
#include "kruskal.hpp"
#include "euler.hpp"

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

using namespace std;
const int INF = 999999999;
using Graph = vector<vector<pair<int, int> > >;
using Graph_nonweight = vector<vector<int> >;

Graph get_min_weight_spanning_tree(Graph Kn){

    Kruskal kr(Kn);
    Graph T = kr.run();
    return T;
}

Graph_nonweight graph_to_nonweight(Graph T, int n){

    Graph_nonweight T2(n);
    rep(i, n){
        rep(j, T[i].size()){
            T2[i].push_back(T[i][j].first);
        }
    }
    return T2;
}

Graph_nonweight make_two_copie_of_T(Graph_nonweight T2, int n){

    Graph_nonweight G(n);
    rep(i, n){
        rep(j, T2[i].size()){
            G[i].push_back(T2[i][j]);
            G[i].push_back(T2[i][j]);
        }
    }
    return G;
}

vector<int> get_hamiltonian_walk(Graph_nonweight G, int n){

    vector<int> Tour;

    // get eulerian walk
    vector<int> W = EULER(G, 0);

    vector<bool> visited(n, false);

    // compute hamiltonian tour
    rep(i, W.size()){
        if(!visited[W[i]]){
            Tour.push_back(W[i]);
            visited[i] = true;
        }
    }
    return Tour;
}

vector<int> double_tree(Graph Kn, int n){

    // get minimum spanning tree
    Graph T = get_min_weight_spanning_tree(Kn);

    Graph_nonweight T2 = graph_to_nonweight(T, n);

    Graph_nonweight G = make_two_copie_of_T(T2, n);

    vector<int> Tour = get_hamiltonian_walk(G, n);

    return Tour;
}

void output_result(vector<int> Tour){

    rep(i, Tour.size()){
        cout << Tour[i];
    }
    cout << endl;
}

#endif //DOUBLE_TREE_HPP
