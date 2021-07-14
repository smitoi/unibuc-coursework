#include <bits/stdc++.h>
#include <map>
	
/// https://www.infoarena.ro/problema/muzica

using	namespace std;
	
int N, M;
long int A, B, C, D, E, aux, aux1, aux2, aux3;
map<int, int> vasmap;
ifstream	f("muzica.in");
ofstream	g("muzica.out");

int	main()	
{
	f >> N >> M;
	f >> A >> B >> C >> D >> E;

	for (int i = 0; i < N; i++)
	{
		f >> aux;
		vasmap[aux] = 1;
	}
	
	aux = 0;
	aux1 = A;
	if (vasmap.find(aux1) != vasmap.end())
	{
		aux++;
		vasmap.erase(aux1);
	}
	aux2 = B;
	if (vasmap.find(aux2) != vasmap.end())
	{
		aux++;
		vasmap.erase(aux2);
	}
	for (int i = 0; i < M - 2; i++)
	{
		aux3 = (C * aux2 + D * aux1) % E;
		if (vasmap.find(aux3) != vasmap.end())
		{
			aux++;
			vasmap.erase(aux3);
		}
		aux1 = aux2;
		aux2 = aux3;
	}
	
	g << aux;
}