#ifndef FF_HPP
#define FF_HPP

#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

tuple<vector<int>, vector<float>, int> First_Fit(int n, float *a)
{
	vector<int> f(n);
    vector<float> S(n);

    for (int i = 0; i < n; i++)
    {
        S[i] = 0;
        int s = 0; 
        while (S[s] + *(a + i) > 1)
            s++;        
		f[i] = s;
        S[s] += *(a + i);
    }
    int k = 0;
    while (S[k] > 0)
        k++;
    return forward_as_tuple(f, S, k);
}

#endif // FF_HPP
