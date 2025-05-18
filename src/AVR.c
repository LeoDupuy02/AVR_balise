/* AVR.c */

#include "AVR.h"

/* ============================= Création ================================ */

noeud* Newnoeud(int clef){
    noeud* nouveau = (noeud*)malloc(sizeof(noeud));
    if(!nouveau){
        printf("Alloc fail\n");
    }
    nouveau->clef = clef;
    nouveau->gauche = NULL;
    nouveau->droite = NULL;
    nouveau->pere = NULL;
    nouveau->equilibre = 0;
    nouveau->hauteur = 0;
    nouveau->donnee = NULL;

    return nouveau;
}

donnee* Newdonnee(int d){
    donnee* nouveau = (donnee*)malloc(sizeof(donnee));
    nouveau->donnee = d;
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
    if(n->pere!=NULL && n->gauche != NULL && n->droite != NULL){
        printf("%d %d %d %d\n", n->clef, n->pere->clef, n->gauche->clef, n->droite->clef);
    }
    else if(n->pere != NULL){
        printf("%d %d\n", n->clef, n->pere->clef);
    }
    else if(n->pere == NULL){
        printf("%d %d %d\n",n->clef, n->gauche->clef, n->droite->clef);
    }

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

    if(ne->pere->gauche == ne){
        return 1;
    }
    else{
        return 0;
    }

}

int EstFilsDroit(noeud* ne){

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
        return 1;
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

noeud* Reequilibre(ABR* arbre, noeud* ne){

    int eql = 0;
    int eqlfg = 0;
    int eqlfd = 0;

    if(ne != NULL){

        eql = ne->equilibre;
        if(eql == 2){
            eqlfg = ne->gauche->equilibre;
            if(eqlfg>0){
                ne = RotationGauche(ne);
            }
            else{
                ne->gauche = RotationDroite(ne->gauche);
                ne = RotationGauche(ne);
            }
        }
        else if(eql == -2){
            eqlfd = ne->droite->equilibre;
            if(eqlfd<=0){
                ne = RotationDroite(ne);
            }
            else if(eqlfd > 0){
                ne->droite = RotationGauche(ne->droite);
                ne = RotationDroite(ne);
            }
        }
        if(ne->pere != NULL){
            MajHauteurEquilibre(arbre->racine);
            Reequilibre(arbre, ne->pere);
        }
        if(ne->pere == NULL){
            arbre->racine = ne;
        }

    }
    printf("Fin du reequilibrage\n");
    return arbre->racine;
}

/* ============================ Suppression d'un noeud ================================ */

noeud* suppression(ABR* arbre, noeud* ne, int clef) {

    noeud* pr = NULL;

    if (ne == NULL) return NULL;

    if (clef < ne->clef) {
        ne->gauche = suppression(arbre, ne->gauche, clef);
    } else if (clef > ne->clef) {
        ne->droite = suppression(arbre, ne->droite, clef);
    } else {
        // Cas 1 : feuille
        if (ne->gauche == NULL && ne->droite == NULL) {
            if (ne->pere != NULL) {
                if (EstFilsGauche(ne)) ne->pere->gauche = NULL;
                else ne->pere->droite = NULL;
            }
            pr = ne->pere;
            free(ne);
            MajHauteurEquilibre(arbre->racine);
            Reequilibre(arbre, pr);
            return NULL;
        }
        // Cas 2 : un seul fils
        else if (ne->gauche == NULL || ne->droite == NULL) {
            noeud* enfant = (ne->gauche != NULL) ? ne->gauche : ne->droite;
            enfant->pere = ne->pere;
            free(ne);
            MajHauteurEquilibre(arbre->racine);
            Reequilibre(arbre, enfant);
            return enfant;
        }
        // Cas 3 : deux fils
        else {
            noeud* remplaçant = plus_grand_noeud(ne->gauche);
            ne->clef = remplaçant->clef;
            ne->gauche = suppression(arbre, ne->gauche, remplaçant->clef);
        }
    }

    MajHauteurEquilibre(ne);
    AffichageArbre(arbre->racine,0);
    return arbre->racine;
}

int SuppressionNoeud(ABR* arbre, int clef) {

    if (arbre == NULL || arbre->racine == NULL) return 1;

    if (chercher(arbre->racine, clef) == NULL) return 1;

    suppression(arbre, arbre->racine, clef); 

    printf("Terminé\n");

    return 0;
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
        MajHauteurEquilibre(arbre->racine);
        arbre->racine = Reequilibre(arbre, prx);
    }
    return 0;
}

/* ============================== EXPORTATION EN .dot d'un AVR ====================== */

void ExporterDotRec(FILE* fichier, noeud* n) {

    if (n == NULL)
        return;

    // Afficher le nœud
    if(n->gauche == NULL && n->droite == NULL && n->donnee != NULL){
        fprintf(fichier, "    \"%p\" [label=\"%d\",shape=box];\n", (void*)n, n->donnee->donnee); // Cercle (par défaut)
    }
    else{
        fprintf(fichier, "    \"%p\" [label=\"%d\"];\n", (void*)n, n->clef);
    }

    // Relier au fils gauche
    if (n->gauche) {
        fprintf(fichier, "    \"%p\" -> \"%p\" [label=\"g\"];\n", (void*)n, (void*)n->gauche);
        ExporterDotRec(fichier, n->gauche);
    }

    // Relier au fils droit
    if (n->droite) {
        fprintf(fichier, "    \"%p\" -> \"%p\" [label=\"d\"];\n", (void*)n, (void*)n->droite);
        ExporterDotRec(fichier, n->droite);
    }
}

int ExporterDot(const char* nom_fichier, ABR* arbre) {

    FILE* fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier .dot");
        return 1;
    }

    fprintf(fichier, "digraph Arbre {\n");
    fprintf(fichier, "    node [shape=circle, fontname=\"Arial\"];\n");

    if (arbre->racine == NULL) {
        fprintf(fichier, "    vide [label=\"Arbre vide\"];\n");
    } else {
        ExporterDotRec(fichier, arbre->racine);
    }

    fprintf(fichier, "}\n");

    fclose(fichier);

    return 0;
}
