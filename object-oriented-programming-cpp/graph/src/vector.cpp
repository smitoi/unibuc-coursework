#include "../include/utils.hpp"

Vector::Vector()
{
    dimensiune = 0;
    valori = nullptr;
}

Vector::Vector(int  dim, int *v)
{
    try {
        dimensiune = dim;
        valori = new int[dimensiune];

        for (int index = 0; index < dim; ++index)
            valori[index] = v[index];
    }
    catch (std :: bad_alloc &ba)
    {
        std::cerr << "bad_alloc caught: " << ba.what();
        exit (EXIT_FAILURE);
    }
}

Vector::Vector(Vector& v)
{
    try {
        dimensiune = v.dimensiune;
        valori = new int[dimensiune];

        for (int index = 0; index < dimensiune; ++index)
            valori[index] = v[index];
    }
    catch (std :: bad_alloc & ba)
    {
        std::cerr << "bad_alloc caught: " << ba.what();
        exit (EXIT_FAILURE);
    }
}

void    Vector::actualizare(int dim, int val)
{
    int     *aux;
    int     auxDim;

    try {
        aux = new int[dimensiune];
        auxDim = dimensiune;

        for (int index = 0; index < dimensiune; ++index)
            aux[index] = valori[index];

        if (valori == nullptr || dimensiune != dim)
        {
            delete[] valori;
            dimensiune = dim;
            valori = new int[dimensiune];
        }

        for (int index = 0; index < dim; ++index)
            if (index < auxDim)
                valori[index] = aux[index];
            else
                valori[index] = val;

        delete[] aux;
    }
    catch (std :: bad_alloc & ba)
    {
        std::cerr << "bad_alloc caught: " << ba.what();
        exit (EXIT_FAILURE);
    }
}

void    Vector::push(int val)
{
    try {
        int     *aux = new int[dimensiune + 1];

        for (int index = 0; index < dimensiune; ++index)
            aux[index] = valori[index];
        aux[dimensiune] = val;

        delete[] valori;
        dimensiune = dimensiune + 1;
        valori = new int[dimensiune];

        for (int index = 0; index < dimensiune; ++index)
            valori[index] = aux[index];

        delete[] aux;
    }
    catch (std :: bad_alloc & ba)
    {
        std::cerr << "bad_alloc caught: " << ba.what();
        exit (EXIT_FAILURE);
    }
}

void    Vector::pop()
{
    int     *aux = new int[dimensiune - 1];

    for (int index = 0; index < dimensiune - 1; ++index)
        aux[index] = valori[index];

    delete[] valori;
    dimensiune = dimensiune - 1;
    valori = new int[dimensiune];

    for (int index = 0; index < dimensiune; ++index)
        valori[index] = aux[index];

    delete[] aux;
}

int     Vector::getLen()
{
    return dimensiune;
}

int*    Vector::getElems()
{
    return valori;
}

Vector& Vector::operator=(const Vector& v)
{
    if (this != &v)
    {
        if (valori == nullptr || dimensiune != v.dimensiune)
        {
            delete[] valori;
            dimensiune = v.dimensiune;
            valori = new int[dimensiune];
        }

        for (int index = 0; index < dimensiune; index++)
            valori[index] = v.valori[index];
    }

    return *this;
}

int&     Vector::operator[](int index)
{
    return valori[index];
}

std :: istream& operator>>(std :: istream &is, Vector& v)
{
    int     dim;
    is >> dim;

    v.actualizare(dim, 0);

    for (int index = 0; index < v.dimensiune; index++)
        is >> v.valori[index];

    return is;
}

std :: ostream& operator<<(std :: ostream &os, Vector& v)
{
    os << v.dimensiune << '\n';

    for (int index = 0; index < v.dimensiune; ++index)
        os << v.valori[index] << ' ';
    os << '\n';

    return os;
}
