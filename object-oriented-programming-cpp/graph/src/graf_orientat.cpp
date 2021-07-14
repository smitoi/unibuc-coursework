#include "../include/utils.hpp"

graf_orientat :: graf_orientat(): graf(0)
{
    mat = matrice();
}

graf_orientat :: graf_orientat(const matrice& m): graf(m.getCols())
{
    mat = m;
}

bool    graf_orientat :: isConex()
{
    bool    *vizitat;
    bool vizita = 1;
    vizitat = new bool[nr_noduri + 1];

    for (int index = 1; index <= nr_noduri; ++index)
        vizitat[index] = false;

    vizitat[1] = true;

    for (int index = 1; index <= nr_noduri; ++index)
        for (int jndex = 1; jndex <= nr_noduri; ++jndex)
            if (mat[index][jndex] == 1 && vizitat[index])
                vizitat[jndex] = 1;

    for (int index = 1; index <= nr_noduri; ++index)
        vizita = vizita && vizitat[index];

    delete[] vizitat;
    return vizita;
}

bool    graf_orientat::canBeTree()
{
    int     sum;

    for (int index = 1; index < this->mat.getRows(); index++)
    {
        sum = 0;
        for (int jndex = 1; jndex < this->mat.getRows(); jndex++)
            sum += this->mat[jndex][index];

        if (sum > 1)
            return false;
    }

    return true;
}

std::istream& graf_orientat :: citire(std :: istream& is)
{
    is >> nr_noduri;
    mat.actualizare(nr_noduri + 1, nr_noduri + 1, 0);

    for (int index = 1; index < nr_noduri + 1; ++index)
        for (int jndex = 1; jndex < nr_noduri + 1; ++jndex)
        {
            is >> mat[index][jndex];
            if (mat[index][jndex] != 0 && mat[index][jndex] != 1)
                mat[index][jndex] = 1;
        }

    return is;
}

std :: ostream& graf_orientat :: afisare(std :: ostream& os)
{
    os << nr_noduri << '\n';

    for (int index = 1; index < nr_noduri + 1; ++index)
    {
        for (int jndex = 1; jndex < nr_noduri + 1; ++jndex)
            os << mat[index][jndex] << ' ';
        os << '\n';
    }

    return os;
}

std :: istream& operator>>(std :: istream& is, graf_orientat& g)
{
    return g.citire(is);
}

std :: ostream& operator<<(std :: ostream& os, graf_orientat& g)
{
    return g.afisare(os);
}

void    graf_orientat::afisareVectorTati(int nod_start)
{
    int     *vectorTati = new int[nr_noduri + 1];
    std :: stack<int>   verif;
    int             ultimul;

    try {
        if (nod_start > nr_noduri)
            throw "Nodul de start nu este parte din vector\n";

        for (int index = 1; index < nr_noduri + 1; index++)
            vectorTati[index] = -1;

        vectorTati[nod_start] = 0;
        verif.push(vectorTati[nod_start]);

        if (this->canBeTree() == true)
        {
            while (verif.empty() == false)
            {
                ultimul = verif.top();
                verif.pop();
                for (int index = 1; index < nr_noduri + 1; index++)
                    if (vectorTati[index] == ultimul)
                    {
                        verif.push(index);
                        for (int jndex = 1; jndex < nr_noduri + 1; jndex++)
                            if (mat[index][jndex] == 1)
                                vectorTati[jndex] = index;
                    }
            }
        }
        else
            throw "Graful nu poate fi reprezentat ca arbore\n";

        for (int index = 1; index < nr_noduri + 1; index++)
            std :: cout << vectorTati[index] << ' ';
        std :: cout << '\n';
    }
    catch(char const* exc) {
        std::cerr << "error: " << exc;
    }
    delete[] vectorTati;
}
