#include "../include/utils.hpp"

matrice::matrice()
{
    // std :: cout << "Matrice basic initializata" << '\n';
    linii = 0;
    coloane = 0;
    valori = nullptr;
}

matrice::matrice(int l, int c, int numar = 0)
{
    // std :: cout << "Incepere initializare matrice cu L = " << l << ", C = " << c << ", si numar = " << numar << '\n';
    linii = l;
    coloane = c;

    valori = new double*[linii];

    for (int index = 0; index < linii; index++)
        valori[index] = new double[coloane];

    for (int index = 0; index < linii; index++)
        for (int jndex = 0; jndex < coloane; jndex++)
            valori[index][jndex] = numar;
    // std :: cout << "Initializare terminata matrice cu L = " << l << ", C = " << c << ", si numar = " << numar << '\n';
}

matrice::matrice(const matrice &n)
{
    // std :: cout << "Copiere matrice cu L = " << n.linii << ", C = " << n.coloane << '\n';

    linii = n.linii;
    coloane = n.coloane;
    valori = new double*[linii];
    for (int index = 0; index < linii; index++)
        valori[index] = new double[coloane];

    for (int index = 0; index < linii; index++)
        for (int jndex = 0; jndex < coloane; jndex++)
            valori[index][jndex] = n.valori[index][jndex];

    // std :: cout << "Copiere terminata matrice cu L = " << n.linii << ", C = " << n.coloane << '\n';
}

void    matrice::actualizare(int l = 0, int c = 0, int numar = 0)
{
    // std :: cout << "Actualizare matrice cu L = " << l << ", C = " << c << ", si numar = " << numar << '\n';

    for (int index = 0; index < linii; index++)
        delete[] valori[index];
    if (linii != 0)
        delete[] valori;

    linii = l;
    coloane = c;

    valori = new double*[linii];

    for (int index = 0; index < linii; index++)
        valori[index] = new double[coloane];

    for (int index = 0; index < linii; index++)
        for (int jndex = 0; jndex < coloane; jndex++)
            valori[index][jndex] = numar;

    // std :: cout << "Actualizare terminata matrice cu L = " << l << ", C = " << c << ", si numar = " << numar << '\n';
}

int    matrice::getCols()
{
    return coloane;
}

int     matrice::getRows()
{
    return linii;
}

int     matrice::getElems()
{
    return linii * coloane;
}

void    matrice::afisare()
{
    linii = getRows();
    coloane = getCols();

    for (int index = 0; index < linii; index++)
    {
        for (int jndex = 0; jndex < coloane; jndex++)
            std :: cout << valori[index][jndex] << ' ';
        std :: cout << '\n';
    }
}

void    matrice::citire()
{
    linii = getRows();
    coloane = getCols();

    for (int index = 0; index < linii; index++)
        for (int jndex = 0; jndex < coloane; jndex++)
        {
            std :: cout << "Valorea de pe linia " << index + 1 << " si coloana " << jndex + 1 << " = ";
            std :: cin >> valori[index][jndex];
        }
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

        valori = new double*[linii];
        for (int index = 0; index < linii; index++)
            valori[index] = new double[coloane];

        for (int index = 0; index < linii; index++)
            for (int jndex = 0; jndex < coloane; jndex++)
                valori[index][jndex] = n.valori[index][jndex];
    }
    return *this;
}

double* matrice::operator[](int i)
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

matrice operator+(const matrice &m, const matrice& n)
{
    matrice temp(m.linii, m.coloane, 0);

    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
        {
            if (index >= n.linii)
                temp.valori[index][jndex] = m.valori[index][jndex];
            else
                temp.valori[index][jndex] = m.valori[index][jndex] + n.valori[index][jndex];
        }

    return temp;
}

matrice operator+(const matrice &m)
{
    matrice temp(m.linii, m.coloane, 0);

    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            temp.valori[index][jndex] = m.valori[index][jndex];

    return temp;
}

matrice operator-(const matrice &m)
{
    matrice temp(m.linii, m.coloane, 0);

    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            temp.valori[index][jndex] = -m.valori[index][jndex];

    return temp;
}

matrice operator-(const matrice &m, const matrice& n)
{
    matrice temp(m.linii, m.coloane, 0);

    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
        {
            if (index >= n.linii)
                temp.valori[index][jndex] = m.valori[index][jndex];
            else
                temp.valori[index][jndex] = m.valori[index][jndex] - n.valori[index][jndex];
        }

    return temp;
}

matrice operator*(const matrice&m, const matrice&n)
{
    matrice temp;

    if (m.coloane != n.linii)
    {
        std :: cout << "ERR_NO_MULTIPLICATION\n";
        return temp;
    }

    temp.actualizare(m.linii, n.coloane, 0);
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < n.coloane; jndex++)
            for (int aux = 0; aux < m.coloane; aux++)
                temp.valori[index][jndex] = temp.valori[index][jndex] + m.valori[index][aux] * n.valori[aux][jndex];

    for (int index = 0; index < temp.linii; index++)
        for (int jndex = 0; jndex < temp.coloane; jndex++)
            if (temp.valori[index][jndex] < 10e-14 && temp.valori[index][jndex] > 0)
                temp.valori[index][jndex] = 0;
    return temp;
}

matrice operator*(const double numar, const matrice&m)
{
    matrice temp;

    temp.actualizare(m.linii, m.coloane, 0);
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            temp.valori[index][jndex] = m.valori[index][jndex] * numar;

    return temp;
}

matrice operator*(const matrice&m, const double numar)
{
    matrice temp;

    temp.actualizare(m.linii, m.coloane, 0);
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            temp.valori[index][jndex] = m.valori[index][jndex] * numar;

    return temp;
}

matrice&    operator+=(matrice &m, const matrice &n)
{
    m = m + n;
    return  m;
}

matrice&    operator-=(matrice &m, const matrice &n)
{
    m = m - n;
    return  m;
}

matrice&    operator*=(matrice &m, const matrice &n)
{
    m = m * n;
    return  m;
}

matrice&    operator*=(matrice &m, const double &n)
{
    m = m * n;
    return  m;
}

bool        operator!=(const matrice&m, const matrice &n)
{
    if (m.linii != n.linii || m.coloane != n.coloane)
        return true;

    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            if (m.valori[index][jndex] != n.valori[index][jndex])
                return true;

    return false;
}

bool        operator==(const matrice&m, const matrice &n)
{
    if (m.linii != n.linii || m.coloane != n.coloane)
        return false;

    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            if (m.valori[index][jndex] != n.valori[index][jndex])
                return false;

    return true;
}

bool        operator>=(const matrice&m, const matrice &n)
{
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            if (m.valori[index][jndex] < n.valori[index][jndex])
                return false;

    return true;
}

bool        operator>(const matrice&m, const matrice &n)
{
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            if (m.valori[index][jndex] <= n.valori[index][jndex])
                return false;

    return true;
}

bool        operator<=(const matrice&m, const matrice &n)
{
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            if (m.valori[index][jndex] > n.valori[index][jndex])
                return false;

    return true;
}

bool        operator<(const matrice&m, const matrice &n)
{
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            if (m.valori[index][jndex] >= n.valori[index][jndex])
                return false;

    return true;
}

bool        operator!=(const matrice&m, const double k)
{
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            if (m.valori[index][jndex] != k)
                return true;

    return false;
}

bool        operator==(const matrice&m, const double k)
{
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            if (m.valori[index][jndex] != k)
                return false;

    return true;
}

bool        operator>=(const matrice&m, const double k)
{
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            if (m.valori[index][jndex] < k)
                return false;

    return true;
}

bool        operator>(const matrice&m, const double k)
{
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            if (m.valori[index][jndex] <= k)
                return false;

    return true;
}

bool        operator<=(const matrice&m, const double k)
{
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            if (m.valori[index][jndex] > k)
                return false;

    return true;
}

bool        operator<(const matrice&m, const double k)
{
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            if (m.valori[index][jndex] >= k)
                return false;

    return true;
}

bool        operator!=(const double k, const matrice&m)
{
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            if (m.valori[index][jndex] != k)
                return true;

    return false;
}

bool        operator==(const double k, const matrice&m)
{
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            if (m.valori[index][jndex] != k)
                return false;

    return true;
}

bool        operator>=(const double k, const matrice&m)
{
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            if (m.valori[index][jndex] < k)
                return false;

    return true;
}

bool        operator>(const double k, const matrice&m)
{
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            if (m.valori[index][jndex] <= k)
                return false;

    return true;
}

bool        operator<=(const double k, const matrice&m)
{
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            if (m.valori[index][jndex] > k)
                return false;

    return true;
}

bool        operator<(const double k, const matrice&m)
{
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            if (m.valori[index][jndex] >= k)
                return false;

    return true;
}

int         operator!(const matrice &m)
{
    for (int index = 0; index < m.linii; index++)
        for (int jndex = 0; jndex < m.coloane; jndex++)
            if (m.valori[index][jndex] != 0)
                return (1);

    return (0);
}

double      matrice::determinant()
{
    int     maxCols = coloane;
    int     putere = 1;
    double  sumDet = 0;
    double  tempDet = 0;
    matrice temp;

    if (coloane != linii)
        return (0);

    if (coloane == 1 && linii == 1)
    {
        sumDet = valori[0][0];
        maxCols = -1;
    }
    else if (coloane == 2 && linii == 2)
    {
        sumDet = (valori[0][0] * valori[1][1] - valori[0][1] * valori[1][0]);
        maxCols = -1;
    }
    else if (coloane == 3 && linii == 3)
    {
        sumDet = valori[0][0] * valori[1][1] * valori[2][2] + valori[1][0] * valori[2][1] * valori [0][2] + valori[2][0] * valori[0][1] * valori [1][2]
        - (valori[0][2] * valori [1][1] * valori [2][0] + valori[1][2] * valori[2][1] * valori[0][0] + valori[2][2] * valori[0][1] * valori[1][0]);
        maxCols = -1;
    }

    for (int index = 0; index < maxCols; index++)
    {
        temp = submatrice(0, index);
        tempDet = temp.determinant();
        sumDet = sumDet + pow(-1, index) * valori[0][index] * tempDet;
        // std :: cout << '\n' << pow(-1, index) << " * " << valori[0][index] << " * " << tempDet << '\n';
        putere *= -1;
    }

    /*
    std :: cout << "Matrice:" << '\n';
    afisare();
    std :: cout << "Determinant:" << sumDet << '\n' << '\n';
    */
    return sumDet;
}

matrice     matrice::submatrice(const int linie,  const int coloana)
{
    matrice temp;
    temp.actualizare(linii - 1, coloane - 1, 0);
    // temp.afisare();
    int tempIndex = 0;
    int tempJndex = 0;
    for (int index = 0; index < linii; index++)
    {
        for (int jndex = 0; jndex < coloane; jndex++)
        {
            if (index == (linie) || jndex == (coloana))
                ;
            else
            {
            temp.valori[tempIndex][tempJndex] = valori[index][jndex];
            // std :: cout << temp.valori[tempIndex][tempJndex] << ' ';
            tempJndex++;
            }
        }
        if (tempJndex != 0)
        {
            tempJndex = 0;
            tempIndex++;
            // std :: cout << '\n';
        }
    }
    // std :: cout << '\n';
    return temp;
}

matrice operator~(const matrice& m)
{
    matrice temp = m;
    matrice inversa;
    double tempDet = temp.determinant();

    if (tempDet == 0 || (m.linii != m.coloane))
    {
        std :: cout << "ERR_CANT_INVERSE\n";
        return inversa;
    }

    inversa.actualizare(m.linii, m.coloane, 0);
    for (int index = 0; index < temp.linii; index++)
        for (int jndex = 0; jndex < temp.coloane; jndex++)
        {
            // temp.submatrice(index, jndex).afisare();
            // std :: cout << "a" << index << jndex << " = " << pow(-1, index + jndex) << " * " << temp.submatrice(index, jndex).determinant() << '\n';
            inversa.valori[jndex][index] = pow(-1, index + jndex) * (temp.submatrice(index, jndex).determinant());
        }
    tempDet = 1 / tempDet;
    // inversa.afisare();
    inversa = inversa * tempDet;

    return inversa;
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

std :: ostream&    operator<<(std :: ostream &os, const matrice&m)
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
