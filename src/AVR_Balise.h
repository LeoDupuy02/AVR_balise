#ifndef AVL_B_H
#define AVL_B_H

#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

void InsertionB(ABR* arbre, int clef);
noeud* insrB(noeud* racine, int clef);

void versAbreBalise(ABR* arbre);
void CompleterArbreBalise(Pile* pile, noeud* ne);

#endif // AVL_B_H
