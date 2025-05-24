#ifndef AVL_H
#define AVL_H

#include <stdio.h>
#include <stdlib.h>

struct noeud_;
struct donnee_;

typedef struct noeud_ {
    double clef;
    struct donnee_* donnee;
    struct noeud_* gauche;
    struct noeud_* droite;
    struct noeud_* pere;
    int hauteur;
    int equilibre;
} noeud;

typedef struct donnee_ {
    noeud* donnee;
} donnee;

typedef struct ABR_ {
    noeud* racine;
} ABR;

noeud* Newnoeud(double clef);
donnee* Newdonnee(noeud* d);
ABR* NewArbre();

int hauteur(noeud* ne);
void MajHauteurEquilibre(noeud* ne);
int MajHauteurEquilibreRec(noeud* ne);

noeud* chercher(noeud* racine, double clef);
noeud* Plus_Grand_Noeud(noeud* ne);
noeud* localiserPere(noeud* racine, double clef);

int EstFilsDroit(noeud* ne);
int EstFilsGauche(noeud* ne);

void AffichageArbre(noeud* n, int niveau);

noeud* RotationGauche(noeud* piv);
noeud* RotationDroite(noeud* piv);

noeud* Reequilibre(noeud* ne);

void Suppr_Donnee(noeud* ne);
noeud* Suppr_noeud(noeud* ne, double clef);
void Suppression_Noeud(ABR* arbre, double clef);

void Insertion(ABR* arbre, double clef);
noeud* insr(noeud* racine, double clef);

int SupprArbre(noeud* racine);
void SuppressionArbre(ABR* arbre);

#endif // AVL_H
