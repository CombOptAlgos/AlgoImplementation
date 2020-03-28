#ifndef GOLDBERG_TARJAN_HPP
#define GOLDBERG_TARJAN_HPP

#include <iostream>
#include <vector>
#include <queue>

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


// push
void push(Graph &G, vector<queue<int> > &L, vector<int> &L_idx,
        vector<queue<int> > &A, vector<vector<bool> > &A_idx,
        int active_vertex, int admissible_edge_id, vector<int> &excess) {
    // set augmented value
    int gamma = excess[active_vertex];
    if (G[active_vertex][admissible_edge_id].residual_capacity<gamma)
        gamma = G[active_vertex][admissible_edge_id].residual_capacity;

    // augment flow along e = ( by gamma.
    int head = G[active_vertex][admissible_edge_id].to;
    int reverse_edge_id = G[active_vertex][admissible_edge_id].reverse_edge_id;
    G[active_vertex][admissible_edge_id].residual_capacity -= gamma;
    G[head][reverse_edge_id].residual_capacity += gamma;

    // update excess
    excess[active_vertex] += gamma;
    excess[head] -= gamma;

    // update L, L_idx
    // TODO(@teramoto) "implement here."
    
    // update A, A_idx
    // TODO(@teramoto) "implement here."

}


// relabel
void relabel(Graph &G, vector<queue<int> > &L, vector<int> &L_idx,
        vector<queue<int> > &A, vector<vector<bool> > &A_idx,
        int active_vertex, vector<int> &psi, int &active_level) {
    // update psi
    rep(i, G[active_vertex].size()) {
        int head = G[active_vertex][i].to;
        if (psi[active_vertex]>psi[head]+1)
            psi[active_vertex] = psi[head]+1;
    }

    // update active_level
    active_level++;

    // update L, L_idx
    // TODO(@teramoto) "implement here."
    
    // update A, A_idx
    // TODO(@teramoto) "implement here."

}


// goldberg tarjan algorithm
void goldberg_tarjan(Graph &G, int s, int t, int N) {
    vector<int> psi(N);
    vector<int> excess(N, 0);

    // max psi value of active vertices.
    int active_level = 0;

    // bidirectional list.
    // L(active_level) = { v (≠s,t) | psi(v) = active_level and v is active (excess(v) > 0) }.
    vector<queue<int> > L(2*N);
    vector<int> L_idx(N, INF);

    // bidirectional list.
    // A(v) = { (v, w) in residual graph s.t (v, w) is admissible (psi(v) = psi(w) + 1) }.
    vector<queue<int> > A(N);
    vector<vector<bool> > A_idx(N);

    // initialize label function
    rep(v, psi.size()) {
        if (v==s)
            psi[v] = N;
        else
            psi[v] = 0;
    }

    // set initial excess
    rep(i, G[s].size()) {
        int v = G[s][i].to;
        int flow = G[v][i].capacity - G[s][i].residual_capacity;
        excess[v] -= flow;
        excess[s] += flow;
    }
    
    // initialize L
    rep(v, N) {
        if (v!=s && v!=t && psi[v]==active_level && excess[v]>0)
            L[active_level].push(v);
            L_idx[v] = active_level;
    }

    // initialize A
    rep(v, N) {
        rep(i, G[v].size()) {
            int w = G[v][i].to;
            if (psi[v]==psi[w]+1) {
                A[v].push(i);
                A_idx[v][i] = true;
            } else {
                A_idx[v][i] = false;
            }
        }
    }
    
    // 3. augmentation
    while (active_level>=0) {
        // there exists at least one active vertices.
        int active_vertex = L[active_level].front();
        if (A[active_vertex].empty()) {
            // there are no admissible edge leaving from active vertex.
            relabel(G, L, L_idx, A, A_idx, active_vertex, psi, active_level);
        } else {
            int admissible_edge_id = A[active_vertex].front();
            push(G, L, L_idx, A, A_idx, active_vertex, admissible_edge_id, excess);
        }
    }
}


// print_result
void output_result(Graph &G, int N, int s) {
    int max_flow = 0;
    rep(i, G[s].size()) {
        if (G[s][i].capacity != 0) {
            max_flow += G[s][i].capacity - G[s][i].residual_capacity;
        }
    }
    cout << "max_flow\t" << max_flow << endl;

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

