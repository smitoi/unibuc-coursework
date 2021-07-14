#include <bits/stdc++.h> 

// https://codeforces.com/problemset/problem/515/C
using namespace std;
     
char s[100];
char o[100];
int		n;
int		j = 0;

int main()
{
    cin >> n;
    cin >> s;
    	
   	for (int i = 0; i < n; i++)
   	{
   		if (s[i] == '6')
   		{
   			o[j] = '5';
   			o[j + 1] = '3';
   			j += 2;
   		}
   		else if (s[i] == '4')
   		{
   			o[j] = '2';
   			o[j + 1] = '2';
   			o[j + 2] = '3';
   			j += 3;
   		}
   		else if (s[i] == '8')
   		{
   			o[j] = '7';
   			o[j + 1] = '2';
   			o[j + 2] = '2';
   			o[j + 3] = '2';
   			j += 4;
   		}
   		else if (s[i] == '9')
   		{
   			o[j] = '7';
   			o[j + 1] = '2';
   			o[j + 2] = '3';
   			o[j + 3] = '3';
   			j += 4;
   		}
   		else if (s[i] != '1' && s[i] != '0') {
   			o[j] = s[i];
    		j++;
   		}
   	}
   	sort(o, o + j, greater<int>());
   	cout << o;
   	return 0;
}
