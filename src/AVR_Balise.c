/* AVR.c */

#include "AVR.h"
#include "pile.h"
#include "AVR_Balise.h"

/* =========================== Insertion ================================ */

void InsertionB(ABR* arbre, int clef) {

    /* Code itératif d'insertion dans un AVR */ 
    /* Retour : 1 si la valeur existe déjà, 0 sinon */

    printf("Insertion du noeud : %d\n", clef);

    if(arbre->racine == NULL){
        arbre->racine = Newnoeud(clef);
        MajHauteurEquilibre(arbre->racine);
    }
    else{
        arbre->racine = insrB(arbre->racine, clef);
    }

    printf("Fin de l'insertion du noeud : %d\n", clef);
}

noeud* insrB(noeud* racine, int clef){

    noeud* mem = NULL;

    if(racine->clef>clef){
        if(racine->gauche != NULL){
            if(racine->gauche->donnee == NULL){
                racine->gauche = insrB(racine->gauche,clef);
                MajHauteurEquilibre(racine->gauche);
                racine->gauche = Reequilibre(racine->gauche);
            }
            else{
                mem = racine->gauche;
                racine->gauche = Newnoeud(clef);
                racine->gauche->pere = racine;
                racine->gauche->gauche = Newnoeud(0);
                racine->gauche->gauche->pere = racine->gauche;
                racine->gauche->gauche->donnee = Newdonnee(clef);
                racine->gauche->droite = mem;
                racine->gauche->droite->pere = racine->gauche;
                MajHauteurEquilibre(racine->gauche);
            }
        }
        else{
            racine->gauche = Newnoeud(clef);
            racine->gauche->pere = racine;
            racine->gauche->gauche = Newnoeud(0);
            racine->gauche->gauche->pere = racine->gauche;
            racine->gauche->gauche->donnee = Newdonnee(clef);
            MajHauteurEquilibre(racine->gauche);
        }
    }
    else if(racine->clef<clef){
        if(racine->droite != NULL){
            if(racine->droite->donnee == NULL){
                racine->droite = insrB(racine->droite,clef);
                MajHauteurEquilibre(racine->droite);
                racine->droite = Reequilibre(racine->droite);
            }
            else{
                mem = racine->droite;
                racine->droite = Newnoeud(clef);
                racine->droite->pere = racine;
                racine->droite->gauche = Newnoeud(0);
                racine->droite->gauche->pere = racine->droite;
                racine->droite->gauche->donnee = Newdonnee(clef);
                racine->droite->droite = mem;
                racine->droite->droite->pere = racine->droite;
                MajHauteurEquilibre(racine->droite);
            }
        }
        else{
            racine->droite = Newnoeud(clef);
            racine->droite->pere = racine;
            racine->droite->gauche = Newnoeud(0);
            racine->droite->gauche->pere = racine->droite;
            racine->droite->gauche->donnee = Newdonnee(clef);
            MajHauteurEquilibre(racine->droite);
        }
    }

    return racine;
}

/* ==================== Transformation AVL <-> AVL Balisé =================== */

void versAbreBalise(ABR* arbre){

    printf("Début balisage\n");

    Pile* maPile = creerPile();
    afficherPile(maPile);

    CompleterArbreBalise(maPile, arbre->racine, NULL);

    printf("Fin du balisage\n");

    SupprimerPile(maPile);

}

void CompleterArbreBalise(Pile* pile, noeud* ne, noeud* mem){

    int cleGauche;
    int cleDroite;

    printf("Noeud actuel : %d\n", ne->clef);
    push(pile, ne->clef);
    
    /* Feuille */
    if(ne->droite == NULL && ne->gauche == NULL){

        cleGauche = pop(pile);
        noeud* gauche = Newnoeud(cleGauche);
        gauche->donnee = Newdonnee(mem);
        mem = gauche;
        ne->gauche = gauche;
        ne->gauche->pere = ne;

        if(!estVide(pile)){
            cleDroite = pop(pile);
            noeud* droite = Newnoeud(cleDroite);
            droite->donnee = Newdonnee(mem);
            mem = droite;
            ne->droite = droite;
            ne->droite->pere = ne;
        }
        return;
    }

    if(ne->gauche != NULL){
        CompleterArbreBalise(pile, ne->gauche, mem);
    }
    else{
        if(!estVide(pile)){
            cleGauche = pop(pile);
            noeud* gauche = Newnoeud(cleGauche);
            gauche->donnee = Newdonnee(mem);
            mem = gauche;
            ne->gauche = gauche;
            ne->gauche->pere = ne;
        }
    }
    if(ne->droite != NULL){
        CompleterArbreBalise(pile, ne->droite, mem);
    }
    else{
        if(!estVide(pile)){
            cleDroite = pop(pile);
            noeud* droite = Newnoeud(cleDroite);
            droite->donnee = Newdonnee(droite);
            ne->droite = droite;
            ne->droite->pere = ne;
        }
    }

    return;
}

/* --------------------------- Suppression donnée ----------------------------- */