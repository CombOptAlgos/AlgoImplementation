#ifndef FUJISHIGE_HPP
#define FUJISHIGE_HPP

#include <iostream>
#include <vector>
#include <set>

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


// add edge to two arrow graph (residual graph)
void add_new_edge_to_two_arrow_graph(Graph &G, int from, int to, int capacity) {
    int new_edge_id = (int)G[to].size();
    int new_reverse_edge_id = (int)G[from].size();
    edge new_edge = {to, capacity, new_edge_id, capacity};
    edge new_reverse_edge = {from, 0, new_reverse_edge_id, 0};
    
    G[from].push_back(new_edge);
    G[to].push_back(new_reverse_edge);
};


// procedure of fujishige's algorithm
void fujishige(Graph &G, int s, int t, int N, int &alpha) {
    // [1] set zero flow. set alpha.
    int index;
    vector<int> b(N);
    vector<int> beta(N);
    set<int> X;

    // preserve vertex of each index.
    vector<int> v(N, INF);

    // preserve index of each vertex.
    vector<int> v_idx(N, INF);

    // flag used when going back to 2.
    bool reset = false;

    while(1) {
        // [2] reset variables.
        X.clear();
        rep(i, N)
            v[i] = INF;
        rep(i, N)
            v_idx[i] = INF;
        index = 0;
        rep(i, N)
            b[i] = 0;

        // set s to initial vertex.
        v[index] = s;
        v_idx[s] = index;

        while(1) {
            // [3] forwarding phase.
            rep(i, G[v[index]].size()) {
                int w = G[v[index]][i].to;
                int target_edge_residual_capacity = G[v[index]][i].residual_capacity;
                
                // scan edge (v, w) on residual graph (w is not scanned vertex.)
                if (target_edge_residual_capacity>0 && v_idx[w]>index) {
                    b[w] += target_edge_residual_capacity;
                    if (b[w]>=alpha)
                        X.insert(w);
                }
            }

            // [4] update alpha.
            if (X.empty()) {
                alpha /= 2;
                if (alpha!=0) {
                    // go back to 2.
                    reset = true;
                }
                break;
            }

            // [5] increment index.
            index += 1;
            auto itr = X.begin();
            int next_v = (int)*itr;
            v[index] = next_v;
            v_idx[next_v] = index;
            X.erase(itr);
            if (v[index]!=t) {
                // forwarding phase is lasting. go back to 3.
                continue;
            }

            // [6] backwarding phase.
            rep(i, N)
                beta[i] = 0;
            beta[t] = alpha;

            while(index>0) {
                rep(i, G[v[index]].size()) {
                    int p = G[v[index]][i].to;
                    int edge_id = G[v[index]][i].reverse_edge_id;
                    int target_edge_residual_capacity = G[p][edge_id].residual_capacity;

                    // scan edge (p, v) on residual graph (p is scanned vertex.)
                    if (target_edge_residual_capacity>0 && v_idx[p]<index) {
                        int beta2 = beta[v[index]];
                        if (beta2>target_edge_residual_capacity)
                            beta2 = target_edge_residual_capacity;

                        // augment f along edge (p, v) by beta2.
                        G[v[index]][i].residual_capacity += beta2;
                        G[p][edge_id].residual_capacity -= beta2;

                        // record augmentation to beta.
                        beta[v[index]] -= beta2;
                        beta[p] += beta2;

                        if (beta[v[index]]==0)
                            break;
                    }
                }
                // back to previous index.
                index -= 1;
            }
            // [7] go back to 2.
            reset = true;
            break;
        }

        if (!reset) {
            // alpha = 0. stop the algorithm.
            break;
        } else {
            // algorithm doesn't stop. go back to 2.
            reset = false;
            continue;
        }
    }
}


// function to print max flow
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


#endif // FUJISHIGE_HPP
