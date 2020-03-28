#ifndef GOLDBERG_TARJAN_HPP
#define GOLDBERG_TARJAN_HPP

#include <iostream>
#include <vector>

#define rep(i, n) for (int i=0; i<(int)(n); i++)

using namespace std;
const int INF = 999999999;

struct edge {
    int to;
    int capacity;
    int reverse_edge_id;
    int residual_capacity;
};

using Graph = vector<vector<edge> >;


// add edge to two arrow graph (residual graph) and initialize flow
void add_edge_and_initialize_flow(Graph &G, int from, int to, int capacity, int s) {
    int new_edge_id = (int)G[to].size();
    int new_reverse_edge_id = (int)G[from].size();
    int new_edge_residual_capacity;
    int new_reverse_edge_residual_capacity;
    
    // initialize flow.
    if (from==s) {
        // set f(e) = u(e)
        new_edge_residual_capacity = 0;
        new_reverse_edge_residual_capacity = capacity;
    } else {
        // set f(e) = 0
        new_edge_residual_capacity = capacity;
        new_reverse_edge_residual_capacity = 0;
    }

    // new edges.
    edge new_edge = {to, capacity, new_edge_id, new_edge_residual_capacity};
    edge new_reverse_edge = {from, 0, new_reverse_edge_id, new_reverse_edge_residual_capacity};

    // add new edges to two arrow graph.
    G[from].push_back(new_edge);
    G[to].push_back(new_reverse_edge);
}


void output_result(Graph &G, int N) {
    int f;
    cout << "v_from\t" << "v_to\t" << "flow" << endl;
    rep(v, N) {
        rep(i, G[v].size()) {
            if (G[v][i].capacity != 0) {
                f = G[v][i].capacity - G[v][i].residual_capacity;
                cout << v << "\t" << G[v][i].to << "\t" << f << endl;
            }
        }
    }
}

#endif // GOLDBERG_TARJAN_HPP

