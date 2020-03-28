#include <iostream>
#include "goldberg_tarjan.hpp"

using namespace std;

int main(void) {
    // read input.
    int N, M;
    cin >> N >> M;
    int s, t;
    cin >> s >> t;
    Graph G(N);

    // set two arrow graph and initialize flow.
    rep(i, M) {
        int from, to, capacity;
        cin >> from >> to >> capacity;
        add_edge_and_initialize_flow(G, from, to, capacity, s);
    }

    goldberg_tarjan(G, s, t, N);

    output_result(G, N, s);

    return 0;
}
