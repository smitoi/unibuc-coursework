#include "../include/utils.hpp"

graf :: getNrNoduri()
{
    return nr_noduri;
}

std :: ostream& operator<<(std :: ostream& os, graf& g)
{
    return g.afisare(os);
}

std :: istream& operator>>(std :: istream& is, graf& g)
{
    return g.citire(is);
}
