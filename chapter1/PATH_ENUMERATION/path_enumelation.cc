// p.4 Algorithm1.1
// 順列ベクトルを辞書順に生成するアルゴリズム

#include <bits/stdc++.h>
using namespace std;

void print(vector<int> V)
{
    for (int i=1; i<V.size(); i++)
    {
        cout << V[i] << " ";
    }
    cout << endl;
}

int main() 
{
    //step1
 
    int N;cin >>N;
    vector<int>  pi(N+1);
    for(int i=0; i<N+1; i++)
    {
        pi[i]=i;
    }

    int i=N-1;
    int k;

    while (i>=1)
    {
        //step2

        k=pi[i]+1;
        for (int j=0; j<N+1; j++)
        {
            auto f = pi.begin();
            if (!(find(f, f+i, k)==f+i)) k++;
            else break;
        }
        
        //setp3

        if (k<=N)
        {
            pi[i] = k;
            if (i==N) print(pi);
            if (i<N)
            {
                pi[i+1]=0;
                i++;
            }
        }
        if (k==N+1) i--;
    }
}

