#include<iostream>
#include<vector>
#include<utility>
using namespace std;

const int INF=1e9;

int N, M, s, from, to, w;
vector<vector<int> > C;
vector<int> l, p;
vector<pair<int, int> > E;

void moore_bellman_ford() {
    // Initialization
    fill(l.begin(), l.end(), INF);
    l[s-1] = 0;
    
    for (int i=1; i<N; i++) {
        for (int j=0; j<M; j++) {
            int a, b;
            tie(a,b) = E[i];
            if (l[b] > l[a] + C[a][b]) {
                l[b]= l[a] +C[a][b];
                p[b] = a+1;
            }
        }
    }
}

int main() {
    cin >> N >> M >> s;
    cout << "Done!" << endl;
    l.resize(N);
    p.resize(N);
    E.resize(M);

    C.resize(N);
    for (int i=0; i<N; i++) {
        C[i].resize(N);
    }

    for (int i=0; i<M; i++) {
        cin >> from >> to >> w;
        C[from-1][to-1] = w;
        E[i] = make_pair(from-1, to-1);
    }

    moore_bellman_ford();

    cout << "s: " << s << endl;
    for (int i=0; i<N; i++) {
            cout << "distance between s and " << i+1 << " : ";
            if (l[i] == INF) cout << "Unreachable" << endl;
            else cout << l[i] << endl;
    }
    for (int i=0; i<N; i++) {
        if (i+1 != s) {
            cout << endl << "parent of " << i+1 << ": "; 
            if (p[i] != 0) cout << p[i];
            else cout << "Undefined";
        }
    }
}
