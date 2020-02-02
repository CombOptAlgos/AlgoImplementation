#include<bits/stdc++.h>
using namespace std;

const int size = 500000+10;
const int INF = 1000000000+10;

int W, N, M, r, c, v, w;
int l[size*2], S[size], T[size];
vector<vector<pair<int, int> > > G;

unordered_set<int> R;
priority_queue<pair<int,int> > Q;

void dijkstra()
{
    Q.push(make_pair(0,r));
    while (R.size() < N)
    {
        bool is_valid=false;
        while (!is_valid)
        {
            v = Q.top().second;
            Q.pop();
            is_valid=(R.count(v)==0);
        }

        R.insert(v);
        for (auto e: G[v])
        {
            w = e.first;
            c = e.second;
            if ((R.count(w)==0) and (c!=INF) and (l[w] > l[v] + c))
            {
                l[w] = l[v] + c;
                Q.push(make_pair(-l[w], w));
            }
        }
    }
}
int main()
{
    cin >> N >> M >> r;
    fill(l, l+N, INF);
    l[r]=0; 
    for (int i=0; i<N; i++) Q.push(make_pair(-l[i], i));

    G.resize(N);

    for (int i=0; i<M; i++)
    {
        cin >> S[i] >> T[i] >> c;
        G[S[i]].push_back(make_pair(T[i], c));
    }

    dijkstra();

    for (int i=0; i<N; i++)
    {
        if (l[i] == INF) cout << "INF" << endl;
        else cout << l[i] << endl;
    }
}

