#include "../include/utils.hpp"

matrice     randomMatrix(int linii, int coloane, int modulo = 1)
{
    int         maxLines = 0;
    int         maxCols = 0;
    matrice     temp;

    temp.actualizare(linii, coloane, 0);

    maxLines = temp.getRows();
    maxCols = temp.getCols();
    srand(time(nullptr));

    for (int index = 0; index < maxLines; index++)
        for (int jndex = 0; jndex < maxCols; jndex++)
            temp[index][jndex] = rand() % modulo;

    return temp;
}

void        citireAfisareNElemenete(int     n)
{
    matrice* listaMatrici = new matrice[n];
    for (int i = 0; i < n; i++)
    {
        std :: cin >> listaMatrici[i];
        std :: cout << listaMatrici[i];
    }
}


