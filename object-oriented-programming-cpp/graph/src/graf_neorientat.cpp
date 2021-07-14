#include "../include/utils.hpp"

graf_neorientat :: graf_neorientat(): graf(0)
{
    lis = Lista();
}

graf_neorientat :: graf_neorientat(const Lista& L): graf(L.getLen())
{
    lis = L;
}

bool    graf_neorientat :: isConex()
{
    bool    *vizitat;
    bool vizita = 1;
    vizitat = new bool[nr_noduri + 1];

    for (int index = 1; index <= nr_noduri; ++index)
        vizitat[index] = false;

    vizitat[1] = true;

    for (int index = 1; index <= nr_noduri; ++index)
    {
        for (int jndex = 0; jndex < lis[index].getLen(); ++jndex)
            if (vizitat[index] == 1)
                vizitat[lis[index][jndex]] = 1;
            else if (vizitat[lis[index][jndex]] == 1)
                vizitat[index] = 1;
    }

    for (int index = 1; index <= nr_noduri; ++index)
        vizita = vizita && vizitat[index];

    delete vizitat;
    return vizita;
}

std::istream& graf_neorientat :: citire(std :: istream& is)
{
    is >> nr_noduri;
    Lista aux(nr_noduri + 1);
    int nod_s, nod_d;

    while (is >> nod_s >> nod_d)
    {
        if (nod_s == nod_d && nod_d == 0)
            break;
        aux[nod_s].push(nod_d);
        aux[nod_d].push(nod_s);
    }

    lis = aux;

    return is;
}

std :: ostream& graf_neorientat :: afisare(std :: ostream& os)
{
    os << nr_noduri << '\n';

    for (int index = 1; index < lis.getLen(); ++index)
        for (int jndex = 0; jndex < lis[index].getLen(); ++jndex)
            if (index < lis[index][jndex])
                os << index << ' ' << lis[index][jndex] << '\n';

    return os;
}

std :: istream& operator>>(std :: istream& is, graf_neorientat& g)
{
    return g.citire(is);
}

std :: ostream& operator<<(std :: ostream& os, graf_neorientat& g)
{
    return g.afisare(os);
}
