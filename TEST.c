#include <stdio.h>
#include <stdlib.h>

/* ============================= Structures ============================= */

typedef struct noeud_ 
{

    int clef;
    int equilibre;
    int hauteur;
    struct noeud_* gauche;
    struct noeud_* droite;
    struct noeud_* donnee;
    struct noeud_* pere;

} noeud;

typedef struct ABR_ 
{

    noeud* racine;
    int ordre;

} ABR;

/* ============================= Déclarations =========================== */

noeud* RotationGauche(noeud* piv);
noeud* RotationDroite(noeud* piv);

/* ============================= Création ================================ */

noeud* Newnoeud(int clef) {
    noeud* nouveau = (noeud*)malloc(sizeof(noeud));
    nouveau->clef = clef;
    nouveau->gauche = NULL;
    nouveau->droite = NULL;
    nouveau->donnee = NULL;
    nouveau->pere = NULL;
    nouveau->equilibre = 0;
    nouveau->hauteur = 0;

    return nouveau;
}

/* =============================== Affichage ============================== */


void AffichageArbre(noeud* n, int niveau) {

    if(niveau == 0){
        printf(" ====== Affichage de l'arbre ====== \n\n");
    }

    if (n == NULL) return;

    // Afficher d'abord le sous-arbre droit
    AffichageArbre(n->droite, niveau + 1);

    // Indenter selon le niveau pour simuler la hauteur
    for (int i = 0; i < niveau; i++)
        printf("    "); // 4 espaces d'indentation

    // Afficher la clef du nœud courant
    printf("%d\n", n->clef);

    // Afficher le sous-arbre gauche
    AffichageArbre(n->gauche, niveau + 1);
}


/* ============================== Recherche ============================= */

noeud* chercher(noeud* racine, int clef){

    /* Ici on part d'un noeud pour faire la recherche */
    /* retour : noeud associé à la clef OU NULL si pas trouvée */

    noeud* found = NULL;

    if(racine == NULL){
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

noeud* plus_grand_noeud(noeud* ne){

    /* Retourne le noeud de plus grande clef en partant de ne */

    noeud* pg = NULL;

    if(ne->droite == NULL){
        return ne;
    }
    else{
        pg = plus_grand_noeud(ne->droite);
    }
    return pg;

}

/* ============================ Suppression de l'arbre ================================ */

int EstFilsGauche(noeud* ne){

    printf("EstFilsGauche");

    if(ne->pere->gauche == ne){
        return 1;
    }
    else{
        return 0;
    }

}

int EstFilsDroit(noeud* ne){

    printf("EstFilsDroit");

    if(ne->pere->droite == ne){
        return 1;
    }
    else{
        return 0;
    }

}

int SuppressionArbre(noeud* racine) {
    if (racine == NULL)
        return 0;

    SuppressionArbre(racine->gauche);
    SuppressionArbre(racine->droite);

    printf("Suppression du noeud : %d à l'adresse %p\n", racine->clef, (void*)racine);

    free(racine);

    return 0;
}

/* ======================================== HAUTEUR et EQUILIBRE ======================== */


int MajHauteurEquilibre(noeud* racine) {

    /* mise à jour de la hauteur d'un noeud et de tout ses noeuds enfants */

    int hauteur_gauche = 0;
    int hauteur_droite = 0;
    int max_hauteur = 0;

    /* Si c'est une feuille on retourne */
    if (racine->gauche == NULL && racine->droite == NULL){
        racine->hauteur = 0;
        racine->equilibre = 0;
        return 0;
    }

    /* Si ce n'est pas une feuille */
    /* On vérifie que ses voisins existent */
    if(racine->gauche != NULL){
        hauteur_gauche = MajHauteurEquilibre(racine->gauche);
    }
    else{
        hauteur_gauche = 0;
    }
    if(racine->droite != NULL){
        hauteur_droite = MajHauteurEquilibre(racine->droite);
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

/* =========================== Rééquilibrage ============================== */

noeud* Reequilibre(noeud* ne){
    noeud* pntr = ne;
    noeud* rac = pntr;
    noeud* piv = NULL;
    int eql = 0;
    int eqlfg = 0;
    int eqlfd = 0;

    while(pntr->equilibre < 2 && pntr->equilibre > -2){
        /* Si le noeud est équilibré alors on remonte */
        if(pntr->pere == NULL){
            printf(" Clef : %d\n",pntr->clef);
            return pntr;
        }
        else{
            pntr=pntr->pere;
            MajHauteurEquilibre(pntr);
        }
    }
    if(pntr != NULL){
        eql = pntr->equilibre;
        if(eql == 2){
            eqlfg = pntr->gauche->equilibre;
            if(eqlfg>0){
                rac = RotationGauche(pntr);
            }
            else{
                piv = RotationDroite(pntr->gauche);
                rac = RotationGauche(piv);
            }
        }
        if(eql == -2){
            eqlfd = pntr->droite->equilibre;
            if(eqlfd<0){
                rac = RotationDroite(pntr);
            }
            else{
                piv = RotationGauche(pntr->droite);
                rac = RotationDroite(piv);
            }
        }
    }
    else{
        rac = pntr;
    }
    return rac;
}

/* ============================ Suppression d'un noeud ================================ */

noeud* suppr(noeud* ne, int clef){

    /* Suppression d'un noeud dans un arbre par clef si celle-ci existe */
    /* Retour : la racine de l'arbre */

    noeud* racine = ne;
    noeud* nex = NULL;

    /* Cas trivial ! */
    if( racine == NULL ){
        return NULL;
    }
    /* Clef pas encore trouvée ! */
    if(ne->clef > clef){
        ne->gauche = suppr(ne->gauche, clef);
        MajHauteurEquilibre(ne->gauche);
        /*ne->gauche = Reequilibre(ne);*/
    }
    else if (ne->clef < clef){
        ne->droite = suppr(ne->droite, clef);
        MajHauteurEquilibre(ne->droite);
        /*ne->droite = Reequilibre(ne->droite);*/
    }
    /* On a trouvé la clef ! */
    else{
        /* Cas 1 : Le noeud est une feuille */
        if(ne->droite == NULL && ne->gauche == NULL){
            if(EstFilsGauche(ne)){
                ne->pere->gauche = NULL;
            }
            else{
                ne->pere->droite = NULL;
            }
            free(ne);
            return NULL;
        }
        else{
            /* Cas 2 : Un fils */
            if(ne->gauche == NULL){
                nex = ne;
                ne = ne->droite;
                ne->pere = nex->pere;
                free(nex);
            }
            else if(ne->droite == NULL){
                nex = ne;
                ne = ne->gauche;
                ne->pere = nex->pere;
                free(nex);
            }
            /* Cas 3 : Deux fils */
            else{
                nex = plus_grand_noeud(ne);
                ne->clef = nex->clef;
                ne->gauche = suppr(ne->gauche, nex->clef);
                /*ne->gauche = Reequilibre(ne->gauche);*/
            }

        }
        
    }
    return ne;
}

int SuppressionNoeud(ABR* arbre, int clef){

    /* Code récursif de suppression d'un noeud de l'arbre */
    /* Retour : 1 si la clef n'existe pas, 0 sinon */

    noeud* racine = NULL;

    if(chercher(arbre->racine,clef) != NULL){
        /* On retourne quelque chose avec suppr car la racine pourrait changer ! */
        racine = suppr(arbre->racine, clef);
        MajHauteurEquilibre(racine);
        racine = Reequilibre(racine);
        if(racine != NULL){
            arbre->racine = racine;
            return 0;
        }
        
    }

    return 1;
}

/* ============================================ Rotations ================================ */

noeud* RotationGauche(noeud* piv){
    
    noeud* rac = piv;
    noeud* prpiv = piv->pere;

    /* Attention : Pas de MAJ des hauteurs et de l'équilibre ici */

    if(piv->gauche != NULL){
        rac = piv->gauche;
        rac->pere = prpiv;
        if(prpiv != NULL && EstFilsGauche(piv)){
            prpiv->gauche = rac;
        }
        if(prpiv != NULL && EstFilsDroit(piv)){
            prpiv->droite = rac;
        }
        piv->gauche = rac->droite;
        if(piv->gauche != NULL){
            piv->gauche->pere = piv;
        }
        
        rac->droite = piv;
        piv->pere = rac;

    }

    return rac;
}

noeud* RotationDroite(noeud* piv){
    
    noeud* rac = piv;
    noeud* prpiv = piv->pere;

    /* Attention : Pas de MAJ des hauteurs et de l'équilibre ici */

    if(piv->droite != NULL){
        rac = piv->droite;
        rac->pere = prpiv;
        if(prpiv != NULL && EstFilsGauche(piv)){
            prpiv->gauche = rac;
        }
        if(prpiv != NULL && EstFilsDroit(piv)){
            prpiv->droite = rac;
        }
        piv->droite = rac->gauche;
        if(piv->droite != NULL){
            piv->droite->pere = piv;
        }
        
        rac->gauche = piv;
        piv->pere = rac;;

    }

    return rac;
}

/* ============================= Insertion ================================= */

noeud* localiserPere(noeud* racine, int clef){

    if(racine->clef > clef){
        if(racine->gauche != NULL){
            return localiserPere(racine->gauche, clef);
        }
        return racine;
    }
    else if(racine->clef < clef){
        if(racine->droite != NULL){
            return localiserPere(racine->droite, clef);
        }
        return racine;
    }
    else{
        return NULL;
    }
}

int Insertion(ABR* arbre, int clef) {

    /* Code itératif d'insertion dans un AVR */ 
    /* Retour : 1 si la valeur existe déjà, 0 sinon */

    noeud* prx = NULL;
    noeud* rcn = NULL;

    if(arbre->racine == NULL){
        arbre->racine = Newnoeud(clef);
    }
    else{
        prx = localiserPere(arbre->racine, clef);
        if(prx == NULL){
            return 1;
        }
        if(prx->clef > clef){
            prx->gauche = Newnoeud(clef);
            prx->gauche->pere = prx;
        }
        else{
            prx->droite = Newnoeud(clef);
            prx->droite->pere = prx;
        }
        MajHauteurEquilibre(prx);
        /*rcn = Reequilibre(prx);*/
        if(rcn != NULL && rcn->pere == NULL){
            arbre->racine = rcn;
        }
    }
    return 0;
}

/* ========================================= main ======================================= */

int main() {
    ABR monABR;
    monABR.racine = Newnoeud(0);

    monABR.racine->gauche = Newnoeud(-10);
    monABR.racine->gauche->pere = monABR.racine;

    monABR.racine->droite = Newnoeud(10);
    monABR.racine->droite->pere = monABR.racine;

    monABR.racine->droite->gauche = Newnoeud(5);
    monABR.racine->droite->gauche->pere = monABR.racine->droite;

    monABR.racine->droite->droite = Newnoeud(15);
    monABR.racine->droite->droite->pere = monABR.racine->droite;

    monABR.racine->droite->droite->droite = Newnoeud(17);
    monABR.racine->droite->droite->droite->pere = monABR.racine->droite->droite;

    monABR.racine->droite->droite->gauche = Newnoeud(14);
    monABR.racine->droite->droite->gauche->pere = monABR.racine->droite->droite;


    /* Recherche et equilibre */
    AffichageArbre(monABR.racine, 0);
    noeud* pgn = plus_grand_noeud(monABR.racine);
    MajHauteurEquilibre(monABR.racine);

    printf("Chercher : %p\n", chercher(monABR.racine, 15));
    printf("Chercher : %p\n", chercher(monABR.racine, 0));
    printf("Plus grand noeud : %d \n", pgn->clef);
    printf("Equilibre de l'arbre : %d \n",monABR.racine->equilibre);

    /* Rotations */
    printf(" => Rotations : \n");
    noeud* rac = RotationDroite(monABR.racine->droite);
    monABR.racine->droite = rac;
    AffichageArbre(monABR.racine,0);

    rac = RotationGauche(monABR.racine->droite);
    monABR.racine->droite = rac;
    AffichageArbre(monABR.racine,0);

    /* Rééquilibrage */
    printf(" => Rééquilibrage : \n");
    MajHauteurEquilibre(monABR.racine);
    noeud* reeq = Reequilibre(monABR.racine->droite->droite->droite);
    monABR.racine = reeq;
    AffichageArbre(monABR.racine,0);

    /* Insertion */
    printf("Insertion de 3 : %d\n",Insertion(&monABR, 3));
    printf("Insertion de -2 : %d\n",Insertion(&monABR, -2));
    AffichageArbre(monABR.racine,0);

    /* Suppression d'un noeud */
    printf(" => Suppression :\n");
    int n = SuppressionNoeud(&monABR, 5);
    AffichageArbre(monABR.racine,0);
    printf("Suppression du noeud 5 : %d\n", n);

    /* Suppression de l'arbre*/
    SuppressionArbre(monABR.racine);
    printf("Racine après suppression : %p\n", monABR.racine);

    return 0;
}
