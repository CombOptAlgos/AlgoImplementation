#include <iostream>
#include "dinic.hpp"

using namespace std;

int main(void) {
    // read input.
    int N, M;
    cin >> N >> M;
    int s, t;
    cin >> s >> t;
    Graph G(N); 
    rep(i, M) {
        int from, to, capacity;
        cin >> from >> to >> capacity;
        add_new_edge_to_two_arrow_graph(G, from, to, capacity);
    }

    // run dinic's algorithm
    bool end_flag;
    dinic(G, s, t, N, end_flag);


    // print result
    output_result(G, N);

    return 0;
}
