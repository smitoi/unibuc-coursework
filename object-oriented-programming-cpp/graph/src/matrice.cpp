#include "../include/utils.hpp"

matrice::matrice()
{
    linii = 0;
    coloane = 0;
}

matrice::matrice(int l, int c, int numar = 0)
{
    linii = l;
    coloane = c;

    valori = new int*[linii];

    for (int index = 0; index < linii; index++)
        valori[index] = new int[coloane];

    for (int index = 0; index < linii; index++)
        for (int jndex = 0; jndex < coloane; jndex++)
            valori[index][jndex] = numar;
}

matrice::matrice(const matrice &n)
{
    linii = n.linii;
    coloane = n.coloane;
    valori = new int*[linii];

    for (int index = 0; index < linii; index++)
        valori[index] = new int[coloane];

    for (int index = 0; index < linii; index++)
        for (int jndex = 0; jndex < coloane; jndex++)
            valori[index][jndex] = n.valori[index][jndex];
}

void    matrice::actualizare(int l = 0, int c = 0, int numar = 0)
{
    int **aux;
    int auxLinii;
    int auxCol;

    auxLinii = linii;
    auxCol = coloane;
    aux = new int*[linii];
    for (int index = 0; index < linii; ++index)
        aux[index] = new int[coloane];

    for (int index = 0; index < linii; ++index)
        for (int jndex = 0; jndex < coloane; ++jndex)
            aux[index][jndex] = valori[index][jndex];

    for (int index = 0; index < linii; index++)
        delete[] valori[index];
    if (linii != 0)
        delete[] valori;

    linii = l;
    coloane = c;

    valori = new int*[linii];

    for (int index = 0; index < linii; index++)
        valori[index] = new int[coloane];

    for (int index = 0; index < linii; index++)
        for (int jndex = 0; jndex < coloane; jndex++)
            if (index < auxLinii && jndex < auxCol)
                valori[index][jndex] = aux[index][jndex];
            else
                valori[index][jndex] = numar;

    for (int index = 0; index < auxLinii; ++index)
        delete[] aux[index];
    delete[] aux;
}

int    matrice::getCols() const
{
    return coloane;
}

int     matrice::getRows() const
{
    return linii;
}

matrice&    matrice::operator=(const matrice &n)
{
    if (this != &n)
    {
        for (int index = 0; index < linii; index++)
            delete[] valori[index];
        if (linii != 0)
            delete[] valori;

        linii = n.linii;
        coloane = n.coloane;

        valori = new int*[linii];
        for (int index = 0; index < linii; index++)
            valori[index] = new int[coloane];

        for (int index = 0; index < linii; index++)
            for (int jndex = 0; jndex < coloane; jndex++)
                valori[index][jndex] = n.valori[index][jndex];
    }
    return *this;
}

int* matrice::operator[](int i)
{
    return      valori[i];
}

void    matrice::diagonala(int   nr)
{
    int     lines = getRows();
    int     cols = getCols();

    if (lines != cols)
        return  ;

    for (int    index = 0; index < lines; index++)
        for (int    jndex = 0; jndex < cols; jndex++)
            if (index == jndex)
                valori[index][jndex] = nr;
}

std :: istream&    operator>>(std :: istream &is, matrice&m)
{
    int     x, y;
    is >> x;
    is >> y;

    m.actualizare(x, y, 0);
    for (int index = 0; index < m.linii; index++)
    {
        for (int jndex = 0; jndex < m.coloane; jndex++)
            is >> m.valori[index][jndex];
    }

    return is;
}

std :: ostream&    operator<<(std :: ostream &os, matrice&m)
{
    os << m.linii << ' ' << m.coloane << '\n';

    for (int index = 0; index < m.linii; index++)
    {
        for (int jndex = 0; jndex < m.coloane; jndex++)
            os << m.valori[index][jndex] << ' ';
        os << '\n';
    }

    return os;
}
