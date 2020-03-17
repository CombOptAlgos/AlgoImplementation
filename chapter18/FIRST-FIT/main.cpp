#include <iostream>
#include <tuple>
#include <vector>
#include "ff.hpp"

using namespace std;

int main()
{
    int n; cin >> n;
    float a[n];

    for (int i = 0; i < n; i++)
        cin >> a[i];

	vector<int> f(n);
    vector<float> S(n);
	int k;
    tie(f,S,k) = First_Fit(n, a);

    for (int i = 0; i < k; i++)
	{
		cout << i+1 << ": " << S[i] << " ... ";
		for (int j = 0; j < n; j++)
		{
        	if(f[j] == i)
				cout << a[j] << " ";
		}
		cout << endl;
	}
  
    return 0;
}
