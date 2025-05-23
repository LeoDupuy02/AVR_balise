#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>

typedef struct donnee_ {
    noeud* donnee;
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
} ABR;

noeud* Newnoeud(int clef);
donnee* Newdonnee(int d);
ABR* NewArbre();

int hauteur(noeud* ne);
void MajHauteurEquilibre(noeud* ne);
int MajHauteurEquilibreRec(noeud* ne);

noeud* chercher(noeud* racine, int clef);
noeud* Plus_Grand_Noeud(noeud* ne);
noeud* localiserPere(noeud* racine, int clef);

int EstFilsDroit(noeud* ne);
int EstFilsGauche(noeud* ne);

void AffichageArbre(noeud* n, int niveau);

noeud* RotationGauche(noeud* piv);
noeud* RotationDroite(noeud* piv);

noeud* Reequilibre(noeud* ne);

void Suppr_Donnee(noeud* ne);
noeud* Suppr_noeud(noeud* ne, int clef);
void Suppression_Noeud(ABR* arbre, int clef);

void Insertion(ABR* arbre, int clef);
noeud* insr(noeud* racine, int clef);

int SupprArbre(noeud* racine);
void SuppressionArbre(ABR* arbre);

#endif // AVL_H
