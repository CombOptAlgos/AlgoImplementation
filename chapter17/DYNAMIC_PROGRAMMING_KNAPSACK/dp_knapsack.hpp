#ifndef DYNAMIC_PROGRAMMING_KNAPSACK_HPP
#define DYNAMIC_PROGRAMMING_KNAPSACK_HPP

#include <iostream>
#include <vector>
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define repi(i, s, n) for (int i = s; i < (int)(n); i++)
#define rrep(i, n) for (int i = (int)(n)-1; i >= 0; i--)
#define rrepi(i, e, n) for (int i = (int)(n)-1; i >= e; i--)

using namespace std;
const int INF = 99999999;

vector<int> dp_knapsack(int n, int weight[], int profit[], int W){

    // upper bound
    int C = 0;
    rep(i, n){
       C += profit[i];
    }

    // DP table init
    int dp[n+1][C+1];
    dp[0][0] = 0;
    rep(i, C){
       dp[0][i+1] = INF;
    }

    // dp
    int s[n+1][C+1];
    repi(j, 1, n+1){
        int cj = profit[j-1]; // dp tableのindexと一つindexがずれる
        int wj = weight[j-1];
        rep(k, C+1){
           s[j][k] = 0;
           dp[j][k] = dp[j-1][k]; // 要素jを加えても最小重みが変わらないとき
        }

        repi(k, cj, C+1){
            if (dp[j-1][k-cj] + wj <= min(W, dp[j][k])){ // 要素jを加えると最小重みが変わるとき
                dp[j][k] = dp[j-1][k-cj] + wj;
                s[j][k] = 1;
            }
        }
    }

    // compute result
    int k = 0;
    rrep(i, C+1){
        if (dp[n][i] < INF){
            k = i;
            break;
        }
    }

    vector<int> S; // optimum subset

    rrepi(j, 1, n+1){
        if (s[j][k]==1){
           S.push_back(j-1);
           k -= profit[j-1];
        }
    }

    return S;
}

void output_result(vector<int> S, int weight[], int profit[]){

    // output result
    int total_w = 0, total_c = 0;

    rep(i, S.size()){
        cout << S[i] << ' ';
        total_w += weight[S[i]];
        total_c += profit[S[i]];
    }
    cout << endl << total_w << ' ' << total_c << endl;
}

#endif //DYNAMIC_PROGRAMMING_KNAPSACK_HPP
