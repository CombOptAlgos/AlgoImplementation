#include "johnson.hpp"
#include<iostream>
#include<vector>
#include<string>
using namespace std;

int N; // number of boolean variables
int M; // number of clause

vector<double> C; // cost function

vector<vector<int> > Z; // family of clause

int main() {
    cin >> N >> M;
    Z.resize(M);
    C.resize(M);
    int n_clause_i; // cardinarity of ith clause
    int received;
    for (int i=0; i<M; i++) {
        cin >> C[i] >> n_clause_i;
        for (int j=0; j<n_clause_i; j++) {
            cin >> received;
            Z[i].push_back(received);
        }
    }
    
    Johnson satsolver(N, Z, C);
    vector<bool> T = satsolver.run();

    // Output result
    for (auto t : T) {
        cout << (t? "true": "false" )<< endl;
    }
}
