#ifndef BRANCHING_HPP
#define BRANCHING_HPP

#include<iostream>
#include<vector>
using namespace std;

class Branching 
{
private:
    vector<int> T;    
    vector<int> H;    
    int N, M;

public:
    void init(int N, int M);
    
    int root(int a);
    bool share_same_parent(int a, int b);
    int height(int r);
    void merge(int a, int b);

    Branching(int M, int N);
    Branching();
};

Branching::Branching() {
    do { } while (0); // NOP;
}

Branching::Branching(int M, int N) {
    this->init(M, N);
}

void Branching::init(int N, int M) {
    this->N = N;
    this->M = M;

    T.resize(N);
    H.resize(N);

    fill(H.begin(), H.end(), 0);
    for (int i=0; i<N; i++) T[i] = i;
};

int Branching::root(int a)
{
    if (T[a] == a) return a;
    else 
    {
        int tmp = a;
        T[a] = T[T[a]];
        return root(T[tmp]);
    }
}

bool Branching::share_same_parent(int a, int b) {
    return root(a) == root(b);
}

void Branching::merge(int a, int b) {
    int r_a = root(a);
    int r_b = root(b);
    int h_a = H[r_a];
    int h_b = H[r_b];

    if (h_a > h_b) 
    {
        T[r_a] = r_b;
        H[r_b]++;
    }
    else 
    {
        T[r_b] = r_a;
        H[r_a]++;
    }
}
#endif //defineBRANCHING_HPP
