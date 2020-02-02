#include <bits/stdc++.h>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define repr(i, n) for (int i = n; i >= 0; i--)

using namespace std;
using Graph = vector<vector<int> >;

// global variables
int N = -1;
int K = -1;
vector<bool> R; //seen
vector<int> psi_i;
vector<int> comp;


void VISIT1(int v, Graph G)
{
   R[v] = true;
   rep(i, G[v].size())
   {
       int w = G[v][i]; // (v, w) in E(G)
       if (!R[w]){ VISIT1(w, G); }
   }
   N++;
   psi_i[N] = v;
}


void VISIT2(int v, Graph G, int V)
{
    R[v] = true;
    rep(i, V){
        rep(j, G[i].size()){
            if (G[i][j] == v){
               int w = i; // (w, v) in E(G)
               if (!R[w]){ VISIT2(w, G, V); }
            }
        }
    }
    comp[v] = K;
}


void STRONGLY_CONNECTED_COMPONENT(Graph G, int V)
{
    psi_i.assign(V, -1);
    comp.assign(V, -1);

    R.assign(V, false);
    rep(v, V){
        if (!R[v]){
           VISIT1(v, G);
        }
    }

    R.assign(V, false); //initialize
    repr(i, V){
        if (!R[psi_i[i]]){
           K++;
           VISIT2(psi_i[i], G, V);
        }
    }
}


int main(){
    int V, E; cin >> V >> E;

    Graph G(V);
    rep(i, E)
    {
       int a, b;
       cin >> a >> b;
       G[a].push_back(b);
    }

    STRONGLY_CONNECTED_COMPONENT(G, V);

    rep(i, V)
    {
        cout << i << ' ' << comp[i] << endl;
    }

    return 0;
}
