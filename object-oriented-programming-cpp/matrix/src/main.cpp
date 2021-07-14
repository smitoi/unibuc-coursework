#include "../include/utils.hpp"

int     main()
{
    int     liniiA, liniiB;
    int     coloaneA, coloaneB, n;
    matrice A, B, C, O, auxOne, auxTwo, rezultat;

    std :: cout << "Rezolvam ecuatia A * X + B = O" << '\n';
    std :: cout << "Dati numarul de linii ale lui A = ";
    std :: cin >> liniiA;
    std :: cout << "Dati numarul de coloane ale lui A = ";
    std :: cin >> coloaneA;
    A.actualizare(liniiA, coloaneA, 0);
    A.citire();
    std :: cout << "Dati numarul de linii ale lui B = ";
    std :: cin >> liniiB;
    std :: cout << "Dati numarul de coloane ale lui B = ";
    std :: cin >> coloaneB;
    B.actualizare(liniiB, coloaneB, 0);
    B.citire();
    C = ~A;
    if (C.getRows() == 0 && C.getCols() == 0)
        std :: cout << "Nu exista solutie, matricea A nu are inversa" << '\n';
    else
    {
        rezultat = C * (-B);
        std :: cout << "Rezultatul este:" << '\n';
        rezultat.afisare();
    }


    std :: cout << '\n' << '\n';
    std :: cout << "Dati numarul de matrici ce trebuie memorate: ";

    std :: cin >> n;
    citireAfisareNElemenete(n);
    return (0);
}
