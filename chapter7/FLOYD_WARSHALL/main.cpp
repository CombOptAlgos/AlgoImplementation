#include <iostream>
#include <vector>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
using namespace std;

typedef vector<vector<int> > Matrix;
const int INF = 999999999;

void floyd_warshall(int N, Matrix &L, Matrix &prev){
    rep(j, N){
        rep(i, N){
            if (i == j) continue;
            rep(k, N){
                if (k == j) continue;
                if (L[i][k] > L[i][j] + L[j][k]){
                    L[i][k] = L[i][j] + L[j][k];
                    prev[i][k] = prev[j][k];
                }
            }
        }
    }
}


int main(){

    int N, M; cin >> N >> M;
    Matrix L = Matrix(N, vector<int>(N, INF));
    Matrix prev = Matrix(N, vector<int>(N, INF));

    // initialization
    rep(i, M){
        int from, to, w; cin >> from >> to >> w;
        L[from][to] = w;
        prev[from][to] = from;
    }
    rep(i, N){
        L[i][i] = 0;
    }

    floyd_warshall(N, L, prev);

    // output
    rep(i, N){
        rep(j, N){
            if (prev[i][j] != INF) {
                cout << i << ' ' << j << ' ' << L[i][j] << endl;
            }
        }
    }
    printf("path matrix \n");
    rep(i, N){
        rep(j, N){
            if (prev[i][j] != INF){
                cout << i << ' ' << j << ' ' << prev[i][j] << endl;
            }
        }
    }

    return 0;
}