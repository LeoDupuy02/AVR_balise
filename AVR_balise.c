/* AVR_balise.c */

#include <stdio.h>
#include <stdlib.h>
#include "AVR_balise.h"

/* ========================== Recherche Balise =============================== */

noeud* chercherBalise(noeud* racine, int clef){

    /* Ici on part d'un noeud pour faire la recherche */
    /* retour : noeud associé à la clef OU NULL si pas trouvée */

    noeud* found = NULL;

    if(racine == NULL){
        return NULL;
    }
    else if(racine->donnee != NULL){
        return NULL;
    }
    else{
        if(clef == racine->clef){
            return racine;
        }
        else if (clef > racine->clef){
            found = chercher(racine->droite, clef);
        }
        else if (clef < racine->clef){
            found = chercher(racine->gauche, clef);
        }
        else{
            return NULL;
        }
    }

    return found;
}

/* ======================== HAUTEUR et EQUILIBRE Balise ======================== */

/* On en prend pas en compte les feuilles externes ! */

int MajHauteurEquilibreBalise(noeud* racine) {

    /* mise à jour de la hauteur d'un noeud et de tout ses noeuds enfants */

    int hauteur_gauche = 0;
    int hauteur_droite = 0;
    int max_hauteur = 0;

    /* Si c'est une feuille (interne) on retourne */
    if(racine->gauche != NULL && racine->droite != NULL){
        if (racine->gauche->donnee != NULL && racine->droite->donnee != NULL){
            racine->hauteur = 0;
            racine->equilibre = 0;
            return 1;
        }
    }

    /* Si ce n'est pas une feuille */
    /* On vérifie que ses voisins existent */
    if(racine->gauche != NULL){
        if(racine->gauche->donnee == NULL){
            hauteur_gauche = MajHauteurEquilibreBalise(racine->gauche);
        }
        else{
            hauteur_gauche = 0;
        }
    }
    else{
        hauteur_gauche = 0;
    }

    if(racine->droite != NULL){
        if(racine->droite->donnee == NULL){
            hauteur_droite = MajHauteurEquilibreBalise(racine->droite);
        }
        else{
            hauteur_droite = 0;
        }
    }
    else{
        hauteur_droite = 0;
    }

    if (hauteur_gauche > hauteur_droite){
        max_hauteur = hauteur_gauche;
    }
    else{
        max_hauteur = hauteur_droite;
    }

    racine->hauteur = 1 + max_hauteur;
    racine->equilibre = hauteur_gauche - hauteur_droite;
    return racine->hauteur;
}

/* ============================= Insertion ================================= */

noeud* localiserPereBalise(noeud* racine, int clef) {
    if (racine == NULL) return NULL;

    printf("Début localisation pour racine = %d\n", racine->clef);

    if (clef < racine->clef) {
        if (racine->gauche != NULL && racine->gauche->donnee == NULL) {
            return localiserPereBalise(racine->gauche, clef);
        }
        return racine;
    } else if (clef > racine->clef) {
        if (racine->droite != NULL && racine->droite->donnee == NULL) {
            return localiserPereBalise(racine->droite, clef);
        }
        return racine;
    } else {
        printf("Déjà existant !\n");
        return NULL;
    }
}

int InsertionBalise(ABR* arbre, int clef) {
    if (arbre == NULL) return 1; // arbre non initialisé

    noeud* prx = NULL;
    noeud* mem = NULL;
    noeud* rcn = NULL;
    noeud* newn = NULL;

    if (arbre->racine == NULL) {
        arbre->racine = Newnoeud(clef);
        if (arbre->racine == NULL) return 1;
        return 0;
    }

    prx = localiserPereBalise(arbre->racine, clef);
    if (prx == NULL) {
        return 1; // clé déjà existante ou erreur
    }

    if (clef < prx->clef) {

        mem = prx->gauche;
        newn = Newnoeud(clef);
        prx->gauche = newn;
        prx->gauche->pere = prx;

        prx->gauche->gauche = mem;
        if(mem != NULL){
            prx->gauche->gauche->pere = prx->gauche;
        }

        prx->gauche->droite = Newnoeud(0);
        prx->gauche->droite->pere = prx->gauche;

        prx->gauche->droite->donnee = Newdonnee(clef);
    
    } else if (clef > prx->clef) {
        
        mem = prx->droite;
        newn = Newnoeud(clef);
        prx->droite = newn;
        prx->droite->pere = prx;

        printf("Next\n");

        prx->droite->droite = mem;
        if(mem != NULL){
            prx->droite->droite->pere = prx->droite;
        }

        prx->droite->gauche = Newnoeud(0);
        prx->droite->gauche->pere = prx->droite;

        prx->droite->gauche->donnee = Newdonnee(clef);
    }

    printf("MAJ\n");
    MajHauteurEquilibreBalise(arbre->racine);

    printf("REEQ\n");
    rcn = Reequilibre(arbre, prx);
    if (rcn != NULL && rcn->pere == NULL) {
        arbre->racine = rcn;
    }

    return 0;
}

/* ====================== Suppression noeud Balise ============= */

int SuppressionNoeudBalise(ABR* arbre, int clef){

    /* Code récursif de suppression d'un noeud de l'arbre */
    /* Retour : 1 si la clef n'existe pas, 0 sinon */

    noeud* racine = NULL;

    versArbreNonBalise(arbre->racine);
    AffichageArbre(arbre->racine,0);

    if(chercher(arbre->racine,clef) != NULL){
        /* On retourne quelque chose avec suppr car la racine pourrait changer ! */
        racine = suppr(arbre, arbre->racine, clef);
        AffichageArbre(racine,0);
        MajHauteurEquilibre(racine);
        racine = Reequilibre(arbre, racine);
        if(racine != NULL){
            arbre->racine = racine;
            versAbreBalise(arbre);
            AffichageArbreBalise(arbre->racine,0);
            return 0;
        }
        
    }

    return 1;
}


/* ======================= Affichage ========================= */

void AffichageArbreBalise(noeud* n, int niveau) {

    if(niveau == 0){
        printf(" ====== Affichage de l'arbre ====== \n\n");
    }

    if (n == NULL) return;

    // Afficher d'abord le sous-arbre droit
    AffichageArbreBalise(n->droite, niveau + 1);

    // Indenter selon le niveau pour simuler la hauteur
    for (int i = 0; i < niveau; i++)
        printf("    "); // 4 espaces d'indentation

    // Afficher la clef du nœud courant
    if(n->gauche == NULL && n->droite == NULL){
        printf("[%d]\n", n->donnee->donnee);
    }
    else{
        printf("%d\n", n->clef);
    }
    // Afficher le sous-arbre gauche
    AffichageArbreBalise(n->gauche, niveau + 1);
}

/* ==================== Transformation =================== */

void versAbreBalise(ABR* arbre){

    Pile* maPile = creerPile();
    afficherPile(maPile);

    CompleterArbreBalise(maPile, arbre->racine);

    printf("Fin du balisage");

    SupprimerPile(maPile);

}

void CompleterArbreBalise(Pile* pile, noeud* ne){

    int cleGauche;
    int cleDroite;

    printf("Noeud actuel : %d\n", ne->clef);
    push(pile, ne->clef);
    
    /* Feuille */
    if(ne->droite == NULL && ne->gauche == NULL){

        noeud* gauche = Newnoeud(0);
        cleGauche = pop(pile);
        gauche->donnee = Newdonnee(cleGauche);
        ne->gauche = gauche;
        ne->gauche->pere = ne;

        if(!estVide(pile)){
            noeud* droite = Newnoeud(0);
            cleDroite = pop(pile);
            droite->donnee = Newdonnee(cleDroite);
            ne->droite = droite;
            ne->droite->pere = ne;
        }
        return;
    }

    if(ne->gauche != NULL){
        CompleterArbreBalise(pile, ne->gauche);
    }
    else{
        if(!estVide(pile)){
            noeud* gauche = Newnoeud(0);
            cleGauche = pop(pile);
            gauche->donnee = Newdonnee(cleGauche);
            ne->gauche = gauche;
            ne->gauche->pere = ne;
        }
    }
    if(ne->droite != NULL){
        CompleterArbreBalise(pile, ne->droite);
    }
    else{
        if(!estVide(pile)){
            noeud* droite = Newnoeud(0);
            cleDroite = pop(pile);
            droite->donnee = Newdonnee(cleDroite);
            ne->droite = droite;
            ne->droite->pere = ne;
        }
    }

    return;
}

void versArbreNonBalise(noeud* ne){
    
    if(ne != NULL){
        if(ne->pere != NULL){
            printf("ne pere: %d\n", ne->pere->clef);
        }
        else{
            printf("ne : %d\n", ne->clef);
        }
        /* Feuille */
        if(ne->donnee != NULL){

            if(EstFilsGauche(ne)){
                ne->pere->gauche = NULL;
                free(ne->donnee);
                free(ne);
            }
            else{
                ne->pere->droite = NULL;
                free(ne->donnee);
                free(ne);
            }
            return;
        }

        if(ne->gauche != NULL){
            versArbreNonBalise(ne->gauche);
        }
        if(ne->droite != NULL){
            versArbreNonBalise(ne->droite);
        }
    }



    return;

}
