#include "../include/utils.hpp"
#include "windows.h"

void    citireNObiecte(std :: string filename)
{
    std :: ifstream file(filename);
    int     n;
    int     aux;
    char    tip;
    graf**  grafuri;

    file >> n;
    grafuri = new graf*[n];
    for (int index = 0; index < n; index++)
    {
        file >> tip;
        std :: cout << "S-A CITIT MATRICEA CU NUMARUL " << index + 1 << '\n';
        if (tip == 'O')
        {
            grafuri[index] = new graf_orientat();
            file >> *grafuri[index];
            std :: cout << *grafuri[index];
            std :: cout << "Is Conex: " << bool(grafuri[index]->isConex()) << '\n';
            if (grafuri[index]->isConex() == true)
            {
                std :: cout << "Dati nodul de start: ";
                std :: cin >> aux;
                grafuri[index]->afisareVectorTati(aux);
            }
            else
                std :: cerr << "error: " << "Nu se poate forma un arbore din graful dat" << '\n';
        }
        else if (tip == 'N')
        {
            grafuri[index] = new graf_neorientat();
            file >> *grafuri[index];
            std :: cout << *grafuri[index];
            std :: cout << "Is Conex: " << bool(grafuri[index]->isConex()) << '\n';
        }
        system("pause");
    }

    delete[] grafuri;
}
