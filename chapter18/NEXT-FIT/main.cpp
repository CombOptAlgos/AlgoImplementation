#include<iostream>
#include<vector>
#include "nf.hpp"

using namespace std;

int main()
{
    int n; cin >> n;
    float a[n];

    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<int> f = Next_Fit(n, a);

	int k = f[n-1];

    for (int i = 1; i < k+1; i++)
	{
		cout << i << ": ";
		int c = 0;
		float b[n];
		float s = 0;
		for (int j = 0; j < n; j++)
		{
        	if(f[j] == i)
			{
				b[c] = a[j];
				c ++;
				s += a[j];
			}
		}
		cout << s << " ... ";
		for (int j = 0; j < c; j++)
			cout << b[j] << " ";
		
		cout << endl;
	}
  
    return 0;
}
