#ifndef GV_H
#define GV_H

#include <stdio.h>
#include <stdlib.h>
#include "AVR.h"

void ExporterDotRec(FILE* fichier, noeud* n);
int ExporterDot(const char* nom_fichier, ABR* arbre);

#endif