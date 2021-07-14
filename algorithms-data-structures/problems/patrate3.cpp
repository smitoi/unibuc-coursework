#include <bits/stdc++.h>

using	namespace std;

/// https://www.infoarena.ro/problema/patrate3

ifstream f("patrate3.in");
ofstream g("patrate3.out");

unsigned int n, rez;
double aux, auy;
const double ERR = 1e-5;
class point {
	public:
		double x;
		double y;
		
		point(double a = 0, double b = 0)
		{
			x = a;
			y = b;
		}
		
		bool	operator<(const point& p) const
		{
			if (abs(x - p.x) < ERR)
				return y - p.y < ERR;
			
			return x - p.x < ERR;
		}
		bool	operator>(const point& p) const
		{
			if (abs(x - p.x) < ERR)
				return y - p.y > ERR;
			
			return x - p.x > ERR;
		}
		bool	operator==(const point &p) const
		{
			return (abs(x - p.x) <= ERR) && (abs(y - p.y) <= ERR);
		}
		bool 	operator!=(const point& p) const
		{
			return (abs(x - p.x) > ERR) || (abs(x - p.x) <= ERR && abs(x - p.x) > ERR);
		}
		friend ostream& operator<<(ostream& os, const point& p);
};

ostream& operator<<(ostream& os, const point& p)
{
	os << p.x << ' ' << p.y;
	return os;
}

vector<point> v;
point C, D;

int	main()	
{
	f >> n;
	
	while (n)
	{
		f >> aux >> auy;
		v.push_back(point(aux, auy));
		n--;
	}
	sort(v.begin(), v.end());

	for (int i = 0; i < v.size(); i++)
		for (int j = i + 1; j < v.size(); j++)
		{
			aux = v[j].x - v[i].x;
			auy = v[j].y - v[i].y;
			C = point(v[i].x - auy, v[i].y + aux);
			D = point(v[j].x - auy, v[j].y + aux);
            if(find(v.begin(), v.end(), C) != v.end() && find(v.begin(), v.end(), D) != v.end())
				rez++;
		}
	
    g << rez / 2;
    return 0;
	
}