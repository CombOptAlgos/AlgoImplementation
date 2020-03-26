#include <iostream>
#include "fujishige.hpp"

using namespace std;

int main(void) {
    // read input.
    int N, M;
    cin >> N >> M;
    int s, t;
    cin >> s >> t;
    Graph G(N);

    // max capacity
    int alpha = 0;

    rep(i, M) {
        int from, to, capacity;
        cin >> from >> to >> capacity;
        if (alpha < capacity)
            alpha = capacity;
        add_new_edge_to_two_arrow_graph(G, from, to, capacity);
    }

    // run fujishige's algorithm
    fujishige(G, s, t, N, alpha);

    // print max flow
    output_result(G, N);

    return 0;
}
