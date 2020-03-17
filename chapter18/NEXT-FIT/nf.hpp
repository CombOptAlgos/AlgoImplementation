#ifndef NF_HPP
#define NF_HPP

#include<iostream>
#include<vector>

using namespace std;

vector<int> Next_Fit(int n, float *a)
{
    int binCount = 1;
    float S = 0;
	vector<int> f(n);

    for (int i = 0; i < n; i++)
    {
        if (S + *(a + i) > 1)
        {
            binCount++;
            S = 0;        
        }
		f[i] = binCount;
        S += *(a + i);
    }

    return f;
}

#endif // NF_HPP
