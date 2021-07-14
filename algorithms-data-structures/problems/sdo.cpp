#include <bits/stdc++.h>

/// https://www.infoarena.ro/problema/sdo

using namespace std;
	
ifstream	f("sdo.in");
ofstream	g("sdo.out");

int LO[3000001], EQ[3000001], HI[3000001];

int quickselect(int v[], int len, int k)
{
    int pivot = v[rand() % len];
	
    int lo = 0, eq = 0, hi = 0;

    for (int i = 0; i < len; i++) 
	{
        if (v[i] < pivot)
		{
            LO[lo] = v[i];
			lo++;
		}
        else if(v[i] == pivot)
		{
            EQ[eq] = v[i];
			eq++;
		}
        else
		{
            HI[hi] = v[i];
			hi++;
		}
    } 
	
    if (k <= lo)
        return quickselect(LO, lo, k);
    else if (k <= lo + eq)
        return EQ[0];
    else
		return quickselect(HI, hi, (k - (lo + eq)));
}

int main()
{
	int n, k;
	f >> n >> k;
	
    for(int i = 0; i < n; i++)
        f >> EQ[i];
	
    g << quickselect(EQ, n, k) << '\n';
}