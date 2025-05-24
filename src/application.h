#ifndef APPLI_H
#define APPLI_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVR.h"
#include "pile.h"
#include "AVR_Balise.h"

double random_double(double a, double b);
double* generate_list(double a, double b, int nbPts);
ABR* generate_AVL_B_from_list(int nbPts, double* list);
int* get_range(ABR* arbre, double a, double b, int nbPts);
noeud* find_limit_low(noeud* ne, double clef);
noeud* find_limit_donnee(noeud* ne);
Pile* find_values_in_range(ABR* arbre, double start, double stop);

#endif