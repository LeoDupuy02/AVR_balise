/* AVR.c */

#include "AVR.h"

/* ============================= Création ================================ */

noeud* Newnoeud(double clef){
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

donnee* Newdonnee(noeud* d){
    donnee* nouveau = (donnee*)malloc(sizeof(donnee));
    nouveau->donnee = d;
    return nouveau;
}

ABR* NewArbre(){
    ABR* nouveau = (ABR*)malloc(sizeof(ABR));
    nouveau->racine = NULL;
    return nouveau;
}

/* =========================== Hauteur et équilibre ======================= */

int hauteur(noeud* ne){
    if(ne == NULL){
        return -1;
    }
    else if(ne->donnee != NULL){
        return -1;
    }
    else{
        return ne->hauteur;
    }
}

void MajHauteurEquilibre(noeud* ne){

    if(ne != NULL){
        int htrg = hauteur(ne->gauche);
        int htrd = hauteur(ne->droite);
        ne->equilibre = htrg - htrd;
        if(htrd>htrg){
            ne->hauteur = 1 + htrd;
        }
        else{
            ne->hauteur = 1 + htrg;
        }
        printf("Maj de %f : hauteur = %d and equlibre = %d\n", ne->clef, ne->hauteur, ne->equilibre);
    }

}

/* ============================== Recherche ============================= */

noeud* chercher(noeud* racine, double clef){

    /* Ici on part d'un noeud pour faire la recherche de la clef (permet de limiter la taille du sous arbre à parcourir) */
    /* Retour : noeud associé à la clef OU NULL si pas trouvée */

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

noeud* Plus_Grand_Noeud(noeud* ne){

    /* Retour : le noeud de plus grande clef en partant de ne */
    /* Note : Vérifer auparavant que ne n'est pas nul */

    noeud* pg = NULL;

    if(ne->droite == NULL){
        return ne;
    }
    else if(ne->droite->donnee != NULL){
        return ne;
    }
    else{
        pg = Plus_Grand_Noeud(ne->droite);
        return pg;
    }

}

noeud* localiserPere(noeud* racine, double clef){

    if(racine->clef > clef){
        if(racine->gauche != NULL && racine->gauche->donnee == NULL){
            return localiserPere(racine->gauche, clef);
        }
        return racine;
    }
    else if(racine->clef < clef){
        if(racine->droite != NULL  && racine->gauche->donnee == NULL){
            return localiserPere(racine->droite, clef);
        }
        return racine;
    }
    else{
        return NULL;
    }
}

//void Chercher_et_remplacer_donnee(noeud* ng, noeud* nd){

//}

/* ===========================Fonctions générales ========================= */

int EstFilsGauche(noeud* ne){

    /* Toujours vérifier que ne.pere existe  au préalable */

    if(ne->pere->gauche == ne){
        return 1;
    }
    else{
        return 0;
    }

}

int EstFilsDroit(noeud* ne){

    /* Toujours vérifier que ne.pere existe au préalable */

    if(ne->pere->droite == ne){
        return 1;
    }
    else{
        return 0;
    }

}

/* =============================== Affichage ============================== */


void AffichageArbre(noeud* n, int niveau) {

    if(niveau == 0){
        printf("\n ====== Affichage de l'arbre ====== \n\n");
    }

    if (n == NULL) return;

    // Afficher d'abord le sous-arbre droit
    AffichageArbre(n->droite, niveau + 1);

    // Indenter selon le niveau pour simuler la hauteur
    for (int i = 0; i < niveau; i++)
        printf("    "); // 4 espaces d'indentation

    // Afficher la clef du nœud courant
    printf("%f\n", n->clef);

    // Afficher le sous-arbre gauche
    AffichageArbre(n->gauche, niveau + 1);
}


/* ============================================ Rotations ================================ */

noeud* RotationGauche(noeud* piv){

    printf("Rot G\n");

    noeud* rac = piv;
    noeud* prpiv = piv->pere;

    /* Attention : Pas de MAJ des hauteurs et de l'équilibre ici */
    /* N'agit que si piv existe et n'est pas une feuille externe */

    if(piv->gauche != NULL){
        if(piv->gauche->donnee == NULL){
            rac = piv->gauche;
            rac->pere = prpiv;
            if(prpiv != NULL){
                if(EstFilsGauche(piv)){
                    prpiv->gauche = rac;
                }
                else{
                    prpiv->droite = rac;
                }
            }
            piv->gauche = rac->droite;
            if(piv->gauche != NULL){
                piv->gauche->pere = piv;
            }
            rac->droite = piv;
            piv->pere = rac;
        }
    }

    MajHauteurEquilibre(rac->gauche);
    MajHauteurEquilibre(rac->droite);
    MajHauteurEquilibre(rac);

    return rac;
}

noeud* RotationDroite(noeud* piv){

    printf("Rot G\n");
    
    noeud* rac = piv;
    noeud* prpiv = piv->pere;

    /* Attention : Pas de MAJ des hauteurs et de l'équilibre ici */
    /* N'agit que si piv existe et n'est pas une feuille externe */

    if(piv->droite != NULL){
        if(piv->droite->donnee == NULL){
            rac = piv->droite;
            rac->pere = prpiv;
            if(prpiv != NULL){
                if(EstFilsGauche(piv)){
                    prpiv->gauche = rac;
                }
                else{
                    prpiv->droite = rac;
                }
            }
            piv->droite = rac->gauche;
            if(piv->droite != NULL){
                piv->droite->pere = piv;
            }
            rac->gauche = piv;
            piv->pere = rac;
        }
    }

    MajHauteurEquilibre(rac->gauche);
    MajHauteurEquilibre(rac->droite);
    MajHauteurEquilibre(rac);

    return rac;
}

/* =========================== Rééquilibrage ============================== */

noeud* Reequilibre(noeud* ne){

    /* On ne rééquilibre que un noeud !!!!*/
    /* Entrée : noeud qui va être rééquilibré */
    /* Sortie : noeud à la même hauteur de l'arbre rééquilibré */

    noeud* pntr = ne;
    noeud* rac = pntr;
    int eql, eqlfg, eqlfd = 0;

    if(pntr != NULL){
        if(pntr->donnee == NULL){
            printf("On va rééquilibre tout cela au niveau de : %f\n", ne->clef);
            eql = pntr->equilibre;
            if(eql == 2){
                /* OK car les feuilles externes ne sont pas pris en compte dans le calcul de la hauteur et de l'équilibre */
                eqlfg = pntr->gauche->equilibre;
                if(eqlfg>0){
                    rac = RotationGauche(pntr);
                }
                else{
                    pntr->gauche = RotationDroite(pntr->gauche);
                    rac = RotationGauche(pntr);
                }
            }
            if(eql == -2){
                /* OK car les feuilles externes ne sont pas pris en compte dans le calcul de la hauteur et de l'équilibre */
                eqlfd = pntr->droite->equilibre;
                if(eqlfd<0){
                    rac = RotationDroite(pntr);
                }
                else{
                    pntr->droite = RotationGauche(pntr->droite);
                    rac = RotationDroite(pntr);
                }
            } 
        }
    }
    else{
        rac = pntr;
    }

    return rac;
}

/* ============================ Suppression d'un noeud ================================ */

void Suppr_Donnee(noeud* ne){

    /* Supprime la donnée attachée à un noeud si celui-ci en possède*/

    if(ne->donnee != NULL){
        free(ne->donnee);
    }

}

noeud* Suppr_noeud(noeud* ne,double clef) {

    noeud* mg = NULL;
    noeud* md = NULL;
    donnee* mem = NULL;
    noeud* m = NULL;

    if (ne == NULL) return ne;

    if (clef < ne->clef) {
        ne->gauche = Suppr_noeud(ne->gauche, clef);
        if (ne->gauche) MajHauteurEquilibre(ne->gauche);
        ne->gauche = Reequilibre(ne->gauche);
    } 
    else if (clef > ne->clef) {
        ne->droite = Suppr_noeud(ne->droite, clef);
        if (ne->droite) MajHauteurEquilibre(ne->droite);
        ne->droite = Reequilibre(ne->droite);
    } 
    else {
        printf("Trouvé !\n");
        // Cas 1 : Aucun enfant (noeud feuille)
        if ((ne->gauche == NULL || ne->gauche->donnee != NULL) &&
            (ne->droite == NULL || ne->droite->donnee != NULL)) {
            printf("Cas feuille\n");
            if(ne->gauche != NULL){
                mem = ne->gauche->donnee;
            }
            if(ne->droite == NULL){
                ne->pere->droite = ne->gauche;
                free(ne);
                return NULL;
            }
            if(ne->pere != NULL){
                ne->droite->pere = ne->pere;
                if(EstFilsDroit(ne)){
                    ne->pere->droite = ne->droite;
                }
                else{
                    ne->pere->gauche = ne->droite;
                }
                Suppr_Donnee(ne->droite);
                ne->droite->donnee = mem;
            }
            else{
                Suppr_Donnee(ne->droite);
            }

            free(ne);
        }

        // Cas 2 : Un seul enfant
        else if (ne->gauche == NULL || ne->gauche->donnee != NULL) {
            printf("Cas un seul enfant de droite\n");
            md = ne->droite;
            mg = ne->gauche;

            if(ne->pere == NULL){
                Suppr_Donnee(mg);
                ne->droite->gauche->donnee->donnee = NULL;
                free(ne);
                return md;
            }

            mem = ne->gauche->donnee;
            Suppr_Donnee(mg);
            ne->droite->pere = ne->pere;
            if(EstFilsDroit(ne)){
                ne->pere->droite = ne->droite;
            }
            else{
                ne->pere->gauche = ne->droite;
            }

            m = md;
            while(m->gauche->donnee == NULL){
                m = m->gauche;
            }
            m->donnee = mem;

            free(ne);
            return md;
        } 
        else if (ne->droite == NULL || ne->droite->donnee != NULL) {
            printf("Cas un seul enfant de gauche\n");
            mg = ne->gauche;
            md = ne->droite;

            if(ne->pere == NULL){
                free(ne);
                return mg;
            }

            ne->gauche->pere = ne->pere;
            if(EstFilsDroit(ne)){
                ne->pere->droite = ne->gauche;
            }
            else{
                ne->pere->gauche = ne->gauche;
            }

            noeud* boucle = ne->gauche;

            while(boucle != NULL || boucle->donnee == NULL){
                boucle = boucle->droite;
            }
            if(boucle != NULL){
                mem = boucle->donnee;
                boucle->pere->droite = md;
                boucle->pere->droite->donnee = mem;
            }
            
            free(ne);

            return mg;
        }

        // Cas 3 : Deux enfants internes
        else {
            printf("Cas 3\n");
            noeud* remplaçant = Plus_Grand_Noeud(ne->gauche);
            ne->clef = remplaçant->clef;
            ne->gauche = Suppr_noeud(ne->gauche, remplaçant->clef);
            if (ne->gauche) MajHauteurEquilibre(ne->gauche);
            ne->gauche = Reequilibre(ne->gauche);
        }
    }

    MajHauteurEquilibre(ne);
    return Reequilibre(ne);
}

void Suppression_Noeud(ABR* arbre, double clef) {
    if (arbre == NULL || arbre->racine == NULL) return;
    if (chercher(arbre->racine, clef) == NULL) return;

    arbre->racine = Suppr_noeud(arbre->racine, clef);
    if (arbre->racine) {
        MajHauteurEquilibre(arbre->racine);
        arbre->racine = Reequilibre(arbre->racine);
    }
}

/* ============================= Insertion ================================= */

void Insertion(ABR* arbre, double clef) {

    /* Code itératif d'insertion dans un AVR */ 
    /* Retour : 1 si la valeur existe déjà, 0 sinon */

    printf("Insertion du noeud : %f\n", clef);

    if(arbre->racine == NULL){
        arbre->racine = Newnoeud(clef);
        MajHauteurEquilibre(arbre->racine);
    }
    else{
        arbre->racine = insr(arbre->racine, clef);
    }

    printf("Fin de l'insertion du noeud : %f\n", clef);
}

noeud* insr(noeud* racine, double clef){

    if(racine->clef>clef){
        if(racine->gauche != NULL){
            racine->gauche = insr(racine->gauche,clef);
            MajHauteurEquilibre(racine->gauche);
            racine->gauche = Reequilibre(racine->gauche);
        }
        else{
            racine->gauche = Newnoeud(clef);
            racine->gauche->pere = racine;
            MajHauteurEquilibre(racine->gauche);
        }
    }
    else if(racine->clef<clef){
        if(racine->droite != NULL){
            racine->droite = insr(racine->droite,clef);
            MajHauteurEquilibre(racine->droite);
            racine->droite = Reequilibre(racine->droite);
        }
        else{
            racine->droite = Newnoeud(clef);
            racine->droite->pere = racine;
            MajHauteurEquilibre(racine->droite);
        }
    }

    MajHauteurEquilibre(racine);
    racine = Reequilibre(racine);
    return racine;
}

/* ============================= Suppression arbre =========================== */

int SupprArbre(noeud* racine) {

    if (racine == NULL){
        return 0;
    }

    SupprArbre(racine->gauche);
    SupprArbre(racine->droite);

    if(racine->donnee != NULL){
        free(racine->donnee);
    }

    free(racine);

    return 0;

}

void SuppressionArbre(ABR* arbre){

    SupprArbre(arbre->racine);

    free(arbre);

    printf("Arbre totalement supprimé !\n");

}