#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <stdlib.h>
#include "matrice.hpp"
#include "vector.hpp"
#include "lista.hpp"
#include "graf.hpp"
#include <cmath>
#include <stack>

void    citireNObiecte(std :: string);
void    afisareVectorTati(graf_orientat&, int);
/*
Tema12 - grafuri

Se dau urmatoarele clase:
-Lista (Vector *l)–lista de adiacenta
-Graf (int nr_noduri)–clasa abstracta
-Graf_Neorientat(Lista L): Graf
-Graf_Orientat (Matrice A):Graf

Clasele derivate trebuie sa contina constructor parametrizat prin care sa se evidentieze transmiterea parametrilor catre
constructorul din clasa de baza, destructor si  o metoda care sa afiseze vectorul de tati, dacă pentru un Graf Orientat
se verifica conexitatea lui și se da un nod de plecare pe post de rădăcina.
*/
#endif // UTILS_H
