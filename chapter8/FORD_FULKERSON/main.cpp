#include <iostream>
#include "ford_fulkerson.hpp"

int main(){

    // read input
    int N, M; cin >> N >> M;
    int s, t; cin >> s >> t;
    Graph G(N); // two_arrow_graph

    rep(i, M){
        int from, to, cap; cin >> from >> to >> cap;
        add_edge_two_arrow(G, from, to, cap);
    }

    // run ford_fulkerson's algo
    ford_fulkerson(G, s, t, N);

    // output result
    output(G, N);

    return 0;
}
