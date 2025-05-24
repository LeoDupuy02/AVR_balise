/* AVR.c */

#include "AVR.h"
#include "pile.h"
#include "AVR_Balise.h"

/* =========================== Insertion ================================ */

void InsertionB(ABR* arbre, double clef) {

    /* Code itératif d'insertion dans un AVR */ 
    /* Retour : 1 si la valeur existe déjà, 0 sinon */

    printf("Insertion du noeud : %f\n", clef);

    if(arbre->racine == NULL){
        arbre->racine = Newnoeud(clef);
        MajHauteurEquilibre(arbre->racine);
    }
    else{
        arbre->racine = insrB(arbre->racine, clef);
    }

    printf("Fin de l'insertion du noeud : %f\n", clef);
}

noeud* insrB(noeud* racine, double clef){

    noeud* mem = NULL;
    donnee* mem_data = NULL;
    noeud* prprec = NULL;

    if(racine->clef>clef){
        if(racine->gauche != NULL){
            if(racine->gauche->donnee == NULL){
                racine->gauche = insrB(racine->gauche,clef);
                MajHauteurEquilibre(racine->gauche);
                racine->gauche = Reequilibre(racine->gauche);
            }
            else{
                mem = racine->gauche;
                mem_data = mem->donnee;
                racine->gauche = Newnoeud(clef);
                racine->gauche->pere = racine;
                racine->gauche->gauche = Newnoeud(clef);
                racine->gauche->gauche->pere = racine->gauche;
                racine->gauche->gauche->donnee = mem_data;
                racine->gauche->droite = mem;
                racine->gauche->droite->pere = racine->gauche;
                racine->gauche->droite->donnee = Newdonnee(racine->gauche->gauche);
                MajHauteurEquilibre(racine->gauche);
            }
        }
        else{
            /* Cas impossible ? */
            racine->gauche = Newnoeud(clef);
            racine->gauche->pere = racine;
            racine->gauche->gauche = Newnoeud(clef);
            racine->gauche->gauche->pere = racine->gauche;
            racine->gauche->gauche->donnee = Newdonnee(NULL);
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
                mem_data = mem->donnee;
                racine->droite = Newnoeud(clef);
                racine->droite->pere = racine;
                racine->droite->gauche = Newnoeud(clef);
                racine->droite->gauche->pere = racine->droite;
                racine->droite->gauche->donnee = mem_data;
                racine->droite->droite = mem;
                racine->droite->droite->pere = racine->droite;
                racine->droite->droite->donnee = Newdonnee(racine->gauche->gauche);
                MajHauteurEquilibre(racine->droite);
            }
        }
        else{
            /* On trouve la donnée précédente */
            mem = racine->gauche;
            mem_data = mem->donnee;
            while(mem->droite->donnee != NULL){
                mem = mem->droite;
                mem_data = mem->donnee;
            }
            mem->pere->droite = Newnoeud(mem->clef);
            prprec = mem->pere->droite;
            mem->pere->droite->donnee = Newdonnee(mem_data->donnee);

            racine->droite = Newnoeud(clef);
            racine->droite->pere = racine;
            racine->droite->gauche = mem;
            racine->droite->gauche->clef = clef;
            racine->droite->gauche->pere = racine->droite;
            racine->droite->gauche->donnee = Newdonnee(prprec);

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

noeud* CompleterArbreBalise(Pile* pile, noeud* ne, noeud* mem){

    double cleGauche;
    double cleDroite;

    printf("Noeud actuel : %f\n", ne->clef);
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

        return mem;
    }

    if(ne->gauche != NULL){
        mem = CompleterArbreBalise(pile, ne->gauche, mem);
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
        mem = CompleterArbreBalise(pile, ne->droite, mem);
    }
    else{
        if(!estVide(pile)){
            cleDroite = pop(pile);
            noeud* droite = Newnoeud(cleDroite);
            droite->donnee = Newdonnee(mem);
            mem = droite;
            ne->droite = droite;
            ne->droite->pere = ne;
        }
    }

    return mem;
}
