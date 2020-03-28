#include "best_in.hpp"
#include<vector>
#include<iostream>

int main() {
    int N, M; // cardinarity of group set and family of Independent sets
    vector<double> C; // weight
    vector<vector<int> > F; // Independent set

    cin >> N >> M;
    C.resize(N);
    F.resize(M);

    int size_of_ith_set;
    int element;
    for (int i=0; i<N; i++) {
        cin >> C[i];
    }
    for (int i=0; i<M; i++) {
        cin >> size_of_ith_set;
        for (int j=0; j<size_of_ith_set; j++) {
            cin >> element;
            F[i].push_back(element);
        }
    }
    BestInGreedy big(F, C);
    vector<int> result = big.run();

    // output result
    for (int e : result) {
        cout << e << endl;
    }
    cout << "total weight of independent set: " << big.max_weight << endl;
}
