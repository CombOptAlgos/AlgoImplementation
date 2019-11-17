#include<iostream>
#include<vector>

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

using namespace std;
using Graph = vector<vector<int> >;

int main(){

    int N, M; cin >> N >> M;
    Graph G(N);

    rep(i, M){
        int a, b, c;
        cin >> a >> b >> c;
        G[a-1].push_back(b-1);
    }

    printf("digraph { \n");
    rep(i, N) {
        printf("%d [label=%d]\n", i+1, i+1);
    }

    rep(i, M){
        if (G[i].size()){
            rep(j, G[i].size()){
                printf("%d -> %d \n", i+1, G[i][j]+1);
            }
        }
    }

    printf("} \n");
    return 0;
}