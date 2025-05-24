#ifndef AVL_B_H
#define AVL_B_H

#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

void InsertionB(ABR* arbre, double clef);
noeud* insrB(noeud* racine, double clef);

void versAbreBalise(ABR* arbre);
noeud* CompleterArbreBalise(Pile* pile, noeud* ne, noeud* mem);

#endif // AVL_B_H
