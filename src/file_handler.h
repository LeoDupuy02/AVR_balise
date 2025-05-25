#ifndef FH_H
#define FH_H

#include <stdio.h>
#include <stdlib.h>

double* lire_doubles_fichier(const char* nom_fichier, int* taille);
void enregistrer_liste(double* tab, int count, const char* nom_fichier);

#endif