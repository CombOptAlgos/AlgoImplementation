#include<iostream>
#include<vector>
#include "euler.hpp"

#define rep(i,n) for(int i=0; i<(int)(n); i++)
using namespace std;

int main() {

    int N, M; cin >> N >> M;
    int s; cin >> s;

    Graph G(N);
    rep(i, M) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    vector<int> W = EULER(G, s);

    rep(i, W.size()) {
        cout << W[i] << ' ';
    }
    cout << endl;

    return 0;
}
