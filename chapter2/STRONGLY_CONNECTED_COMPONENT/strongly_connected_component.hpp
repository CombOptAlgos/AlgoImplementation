#include<vector>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define repr(i, n) for (int i = n-1; i >= 0; i--)

using namespace std;
using Graph = vector<vector<int> >;

class SCC
{
    public:
        int N = -1;
        int K = -1;
        vector<bool> R; //seen
        vector<int> psi_i;
        vector<int> comp;
        Graph G;
        int V;
        
        SCC(Graph G_, int V_);
        void visit1(int v);
        void visit2(int v);
        vector<int> run();
};

SCC::SCC(Graph G_, int V_)
{
    G = G_;
    V = V_;
}

void SCC::visit1(int v)
{
   R[v] = true;
   rep(i, G[v].size())
   {
       int w = G[v][i]; // (v, w) in E(G)
       if (!R[w]){ visit1(w); }
   }
   N++;
   psi_i[N] = v;
}


void SCC::visit2(int v)
{
    R[v] = true;
    rep(i, V){
        rep(j, G[i].size()){
            if (G[i][j] == v){
               int w = i; // (w, v) in E(G)
               if (!R[w]){ visit2(w); }
            }
        }
    }
    comp[v] = K;
}


vector<int> SCC::run()
{
    psi_i.assign(V, -1);
    comp.assign(V, -1);
    R.assign(V, false);
    rep(v, V){
        if (!R[v]){
            visit1(v);
        }
    }

    R.assign(V, false); //initialize

    repr(i, V){
        if (!R[psi_i[i]]){
           K++;
           visit2(psi_i[i]);
        }
    }
    return comp;
}
