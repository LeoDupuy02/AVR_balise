#ifndef AVL_BALISE_H
#define AVL_BALISE_H

#include "pile.h"
#include "AVR.h"

int MajHauteurEquilibreBalise(noeud* racine);
noeud* localiserPereBalise(noeud* racine, int clef);
int InsertionBalise(ABR* arbre, int clef);
void AffichageArbreBalise(noeud* n, int niveau);
void versAbreBalise(ABR* arbre);
void CompleterArbreBalise(Pile* pile, noeud* ne);
int SuppressionNoeudBalise(ABR* arbre, int clef);
noeud* chercherBalise(noeud* racine, int clef);
void versArbreNonBalise(noeud* ne);

#endif // AVL_BALISE_H
