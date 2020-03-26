#ifndef JOHNSON_HPP
#define JOHNSON_HPP
#include<vector>
#include<iostream>
#include<cmath>
using namespace std;

class Johnson {
public:
    Johnson(int N, vector<vector<int> > Z, vector<double> C);
    vector<bool> run();
private:
    int N, M;
    vector<vector<int> > Z;
    vector<bool> T;
    vector<double> C;
    double prob_satisfy(vector<int> clause, vector<bool> T_);
    double exp(vector<bool> T_);
};

Johnson::Johnson(int N, vector<vector<int> > Z_, vector<double> C_) {
    this->N = N;
    this->Z = Z_;
    this->C = C_;
    this->M = Z_.size();
}

double Johnson::prob_satisfy(vector<int> clause, vector<bool> T_) {
    // T_でclauseがsatisfyされる確率を計算する
    // T_は、N個の真偽変数のうち、先頭からsize(T_)個は決まっており、残りはTrue/Falseが確率1/2でassignされる
    bool never_satisfied = true;
    bool is_negative;
    int n_unassigned_variable_in_clause = 0;
    int ith_boolean_variable_in_clause;
    for (int i=0; i<clause.size(); i++) {
        assert(clause[i] != 0);
        is_negative = clause[i] < 0;
        ith_boolean_variable_in_clause = (is_negative? -clause[i]: clause[i]); 
        if (ith_boolean_variable_in_clause <= T_.size()) {
            if ( !((!is_negative) ^ T_[ith_boolean_variable_in_clause-1])) {
                 return 1;   
            }
        }
        else {
            never_satisfied = false;
            n_unassigned_variable_in_clause++;
        }
    }
    if (never_satisfied) {  
        return 0;
    }
    else {
        return 1.0 - pow(0.5, n_unassigned_variable_in_clause);
    }
}

double Johnson::exp(vector<bool> T_) {
    double sum=0;
    for (int i=0; i<M; i++) {
        sum += C[i] * prob_satisfy(Z[i], T_);
    }
    return sum;
}

vector<bool> Johnson::run() {
    for (int i=0; i<N; i++) {
        vector<bool> T_tmp_t(T.size()), T_tmp_f(T.size());
        copy(T.begin(), T.end(), T_tmp_t.begin());
        copy(T.begin(), T.end(), T_tmp_f.begin());
        T_tmp_t.push_back(true);
        T_tmp_f.push_back(false);
        if (exp(T_tmp_t) >= exp(T_tmp_f)) {
            T.push_back(true);
        }
        else T.push_back(false);
    }
    return T;
}

#endif //JOHNSON_HPP
