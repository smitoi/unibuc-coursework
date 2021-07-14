# https://csacademy.com/contest/interview-archive/task/largest-concat-number/

#include <bits/stdc++.h>
using namespace std;

bool   compare(string a, string b)
{
    if (a + b > b + a) {
		return true;
	}
	else return false;
}

string largestConcat(vector<string>& v) {
    string rez = "";
    if (count(v.begin(), v.end(), "0") == (int)v.size())
        return "0";
    
    sort(v.begin(), v.end(), compare);
    
    for (size_t index = 0; index < v.size(); index++)
        rez += v[index];
    
    return rez;
}
   
int main() {
    int N;
    cin >> N;
    vector<string> v;
    for (int i = 0; i < N; ++i) {
        string number;
        cin >> number;
        v.push_back(number);
    }
    
    cout << largestConcat(v) << "\n";
    return 0;
}
