#ifndef DINIC_HPP
#define DINIC_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <stack>

#define rep(i, n) for (int i=0; i<(int)(n); i++)

using namespace std;
const int INF = 999999999;

// structure of directed edge (from, to).
struct edge {
    int to;
    int capacity;
    int reverse_edge_id;
    int residual_capacity;
    bool level_graph; // if the edge is in level graph, then true.
};

// 'two arrow graph' (which can represent G and residual graph G_f simultaneously.)
// G[v] is the list of structure 'edge' of edges which leave v.
using Graph = vector<vector<edge> >;

using Path = vector<pair<int, int> >;

// add edge to two arrow graph
void add_new_edge_to_two_arrow_graph(Graph &G, int from, int to, int capacity) {
    // add new edges to end of the incidence list.
    int new_edge_id = (int)G[to].size();
    int new_reverse_edge_id = (int)G[from].size();
    edge new_edge = {to, capacity, new_edge_id, capacity, false};
    edge new_reverse_edge = {from, 0, new_reverse_edge_id, 0, false};

    // add edge and its reverse edge.
    G[from].push_back(new_edge);
    G[to].push_back(new_reverse_edge);
};


// construct level graph G_f^L of residual graph G_f.
void construct_level_graph(Graph &G, int s, int N) {
    // construct level graph by BFS.
    vector<int> distance(N, INF);
    queue<int> Q;

    // initialization
    distance[s] = 0;
    Q.push(s);
    int v = s;
    rep(i, G.size()) {
        rep(j, G[i].size())
            G[i][j].level_graph = false;
    }
    int current_distance = distance[s];

    // BFS
    while(!Q.empty()) {
        v = Q.front();
        Q.pop();
        current_distance = distance[v];

        rep(i, G[v].size()) {
            if (G[v][i].residual_capacity>0) {
                int w = G[v][i].to;

                // same distance is allowed. (level graph is not necessarily arborescence!)
                if (distance[w]==INF || distance[w]==current_distance+1) {
                    distance[w] = current_distance+1;
                    // add this edge to level graph.
                    G[v][i].level_graph = true;
                    Q.push(w);
                }
            }
        }
    }
}


// compute botlneck edge cost
int compute_bottleneck_edge_cost(Graph &G, Path path, int s, int t) {

    int gamma = INF;
    int index;
    int v = t;

    while(1) {
        index = path[v].second;
        v = path[v].first;
        if (gamma >= G[v][index].residual_capacity)
            gamma = G[v][index].residual_capacity;

        if (v==s)
            break;
    }

    return gamma;
}


// find s-t-flow in level graph.
pair<Path, int> find_s_t_flow(Graph &G, int s, int t, int N, bool &end_flag) {
    // return (s-t-path, flow-value) by DFS.
    Path path(N);
    vector<bool> visited(N, false);
    stack<int> S;

    // initialization
    end_flag = true;
    visited[s] = true;
    S.push(s);
    int v = s;

    // DFS
    while(!S.empty()) {
        v = S.top();
        S.pop();

        rep(i, G[v].size()) {
            if (G[v][i].level_graph && G[v][i].residual_capacity>0) {
                int w = G[v][i].to;

                if(!visited[w]) {
                    visited[w] = true;
                    path[w] = make_pair(v, i);
                    S.push(w);
                }

                if(w==t) {
                    end_flag = false;
                    break;
                }
            }
        }
        if (!end_flag)
            break;
    }

    // compute bottleneck edge cost
    int gamma = compute_bottleneck_edge_cost(G, path, s, t);

    pair<Path, int> s_t_flow = make_pair(path, gamma);

    return s_t_flow;
}

// augmentation
void augment(Graph &G, pair<Path, int> s_t_flow, int s, int t) {
    int index;
    int gamma = s_t_flow.second;
    Path path = s_t_flow.first;
    int v = t;

    while(1) {
        index = path[v].second;
        v = path[v].first;

        // an edge on s-t-path.
        G[v][index].residual_capacity -= gamma;

        // a reverse egde of an edge on the s-t-path.
        edge e = G[v][index];
        G[e.to][e.reverse_edge_id].residual_capacity += gamma; 

        if (v==s)
            break;
    }
}

// dinic's algorithm
void dinic(Graph &G, int s, int t, int N, bool &end_flag) {
    // 1, set zero flow.
    end_flag = false;

    while(1) {
        // 2. construct level graph.
        construct_level_graph(G, s, N);

        // 3. Find a blocking flow. if blocking flow is zero flow, then stop!
        // 4. augment flow by blocking flow and go to 2.
        // Using Exercise 20 of Chapter 8, modify 3 and 4 as below.
        
        // first time
        pair<Path, int> s_t_flow = find_s_t_flow(G, s, t, N, end_flag);
        if (end_flag) {
            // blocking flow is zero flow. stop!
            break;
        }
        augment(G, s_t_flow, s, t);

        // following iterations
        while(1) {
            pair<Path, int> s_t_flow = find_s_t_flow(G, s, t, N, end_flag);
            if (end_flag) {
                // blocking flow is already augmented!
                break;
            }
            augment(G, s_t_flow, s, t);
        }
    }
}


// output result
void output_result(Graph &G, int N) {
    int f;
    cout << "v_from\t" << "v_to\t" << "flow" << endl;
    rep(v, N) {
        rep(i, G[v].size()) {
            if (G[v][i].capacity != 0) {
                f = G[v][i].capacity - G[v][i].residual_capacity;
                cout << v << "\t\t" << G[v][i].to << "\t\t" << f << endl;
            }
        }
    }
}

#endif // DINIC_HPP
