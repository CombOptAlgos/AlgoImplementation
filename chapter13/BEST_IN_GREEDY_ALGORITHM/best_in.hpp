#ifndef BEEST_IN_HPP
#define BEEST_IN_HPP
#include<algorithm>
#include<vector>
#include<iostream>
#include<unordered_set>
using namespace std;

class BestInGreedy {
    private:
        int N; // cardinarity of ground set
        vector<pair<double, int> > C; // weight
        vector<unordered_set<int> > F; // Independence set
        bool is_independent(unordered_set<int> set);
    public:
        BestInGreedy(vector<vector<int> > F, vector<double> C);
        vector<int> run();
        int max_weight;
};

BestInGreedy::BestInGreedy(vector<vector<int> > F, vector<double> C) {
    this->N = C.size();
    this->C.resize(this->N);
    for (auto f : F) {
        unordered_set<int> f_set;
        for (auto f_e : f) {
            f_set.insert(f_e);
        }
        this->F.push_back(f_set);
    }
    for (int i=1; i<=N; i++) {
        // C whould be nonnegative
        assert(C[i-1] >= 0);
        this->C.push_back(make_pair(C[i-1], i));
    }
    this->max_weight = 0;
}

bool BestInGreedy::is_independent(unordered_set<int> subset) {
    // subsetがIndependentか判定する
    bool subset_is_independent = false;
    for (auto f : F) {
        if (subset == f) subset_is_independent = true;
    }
    return subset_is_independent;
}

vector<int> BestInGreedy::run() {
    // Cを降順にソート
    sort(C.begin(), C.end());
    reverse(C.begin(), C.end());
    
    //initialze
    vector<int> output(0);
    max_weight = 0;

    //update
    for (int i=0; i<N; i++) {
        pair<double, int> c = C[i];
        unordered_set<int> subset; 
        for (auto f : output) {
            subset.insert(f);
        }
        subset.insert(c.second);
        if (is_independent(subset)) {
            output.push_back(c.second);
            max_weight += c.first;
        }
    }
    return output;
}
#endif //BEEST_IN_HPP
