#include <iostream>
#include <vector>
#include "dp_knapsack.hpp"
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

using namespace std;

int main() {


    int n; cin >> n;
    int weight[n];
    int profit[n];
    rep(i, n){
        cin >> weight[i];
        cin >> profit[i];
    }
    int W; cin >> W;

    vector<int> S = dp_knapsack(n, weight, profit, W);

    output_result(S, weight, profit);

    return 0;
}