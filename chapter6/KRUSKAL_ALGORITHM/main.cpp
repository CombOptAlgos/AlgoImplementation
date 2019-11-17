#include<iostream>
#include<vector>
#include<queue>
#include "Branching.h"
using namespace std;
int N, M;
queue<int> E;

int main() {
    cin >> N >> M;
    
    Branching B(N,M);
    int s, t, w; // head, tail and weight
    vector<tuple<int, int, int> > W(M);
    for (int i=0; i<M; i++) {
        cin >> s >> t >> w;
        W[i] = make_tuple(w,s,t);
    }
    
    int a, b; // two vertices
    sort(W.begin(), W.end());
    reverse(W.begin(), W.end());

    for (int i=0; i<M; i++) {
        a = get<1>(W[i]);
        b = get<2>(W[i]);
        if (!B.share_same_parent(a, b)) {
            E.push(i);
            B.merge(a, b); 
        }
    }

    // output results
    cout << N << " " << E.size() << endl;
    while (!E.empty()){
        tuple<int, int, int> e = W[E.front()];
        E.pop();
        cout << get<1>(e) << " " << get<2>(e) << " " << get<0>(e) << endl;
    }
}
