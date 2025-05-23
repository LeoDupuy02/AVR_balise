#ifndef APPLI_H
#define APPLI_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "AVR.h"
#include "AVR_Balise.h"

double random_double(double a, double b);
ABR* generate_AVL_B_from_list(int nbPts, double* list);
int* get_range(ABR* arbre, int a, int b, int nbPts);
noeud* find_limit(noeud* ne, int clef);
noeud* find_limit_donnee(noeud* ne);
double* find_values_in_range(ABR* arbre, double start, double stop, int nbPts);

#endif