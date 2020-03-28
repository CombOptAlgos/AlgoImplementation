#include <iostream>
#include <vector>
#include "double_tree.hpp"

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

using namespace std;
using Graph = vector<vector<pair<int, int> > >;
using Graph_nonweight = vector<vector<int> >;

int main() {

    // input
    int a, b, w;
    int n; cin >> n;
    int M = n * (n-1) / 2;
    Graph Kn(n);
    rep(i, M){
        cin >> a >> b >> w;
        Kn[a].push_back(make_pair(b, w));
        Kn[b].push_back(make_pair(a, w));
    }

    // run double tree algorithm
    vector<int> Tour = double_tree(Kn, n);

    // output
    output_result(Tour);

    return 0;
}
