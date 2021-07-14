#include "../include/utils.hpp"

Lista::Lista()
{
    dimensiune = 0;
    lista = nullptr;
}

Lista::Lista(int dim, Vector*     v)
{
    dimensiune = dim;
    try {
        lista = new Vector[dimensiune];

        for (int index = 0; index < dim; ++index)
            if (v == nullptr)
                lista[index] = Vector();
            else
                lista[index] = v[index];
    }
    catch (std::bad_alloc & ba)
    {
        std :: cerr << "bad_alloc caught: " << ba.what();
        exit (EXIT_FAILURE);
    }
}

Lista::Lista(Lista&     l)
{
    dimensiune = l.dimensiune;
    try {
        lista = new Vector[dimensiune];

        for (int index = 0; index < dimensiune; ++index)
            lista[index] = l[index];
    }
    catch (std::bad_alloc & ba)
    {
        std :: cerr << "bad_alloc caught: " << ba.what();
        exit (EXIT_FAILURE);
    }
}

int         Lista::getLen() const
{
    return dimensiune;
}

Lista&      Lista::operator=(const Lista& l)
{
    if (this != &l)
    {
        if (lista == nullptr || dimensiune != l.dimensiune)
        {
            delete[] lista;
            dimensiune = l.dimensiune;
            lista = new Vector[dimensiune];
        }

        for (int index = 0; index < dimensiune; ++index)
            lista[index] = l.lista[index];
    }

    return *this;
}

Vector&     Lista::operator[](int  index) const
{
    return lista[index];
}

std :: istream& operator>>(std :: istream &is, Lista& l)
{
    int     dim;
    is >> dim;

    l.dimensiune = dim;
    l.lista = new Vector[l.dimensiune];

    for (int index = 0; index < l.dimensiune; ++index)
        is >> l.lista[index];

    return is;
}

std :: ostream& operator<<(std :: ostream &os, Lista& l)
{
    os << l.dimensiune << '\n';

    for (int index = 0; index < l.dimensiune; ++index)
        os << l.lista[index];

    return os;
}
