#ifndef AVL_H
#define AVL_H

#include <stdio.h>

typedef struct donnee_ {
    int donnee;
} donnee;

typedef struct noeud_ {
    int clef;
    struct donnee_* donnee;
    struct noeud_* gauche;
    struct noeud_* droite;
    struct noeud_* pere;
    int hauteur;
    int equilibre;
} noeud;

typedef struct ABR_ {
    noeud* racine;
    int nb;
} ABR;

noeud* Newnoeud(int clef);
donnee* Newdonnee(int d);
void AffichageArbre(noeud* n, int niveau);
noeud* chercher(noeud* racine, int clef);
noeud* plus_grand_noeud(noeud* ne);
int EstFilsGauche(noeud* ne);
int EstFilsDroit(noeud* ne);
int SuppressionArbre(noeud* racine);
int MajHauteurEquilibre(noeud* racine);
noeud* Reequilibre(ABR* arbre, noeud* ne);
noeud* suppr(ABR* arbre, noeud* ne, int clef);
int SuppressionNoeud(ABR* arbre, int clef);
noeud* RotationGauche(noeud* piv);
noeud* RotationDroite(noeud* piv);
noeud* localiserPere(noeud* racine, int clef);
int Insertion(ABR* arbre, int clef);
void ExporterDotRec(FILE* fichier, noeud* n);
int ExporterDot(const char* nom_fichier, ABR* arbre);


#endif // AVL_H
