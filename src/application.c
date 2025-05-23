#include "application.h"

// Génère un double dans [a, b]
double random_double(double a, double b) {
    return a + (b - a) * ((double)rand() / RAND_MAX);
}

double* generate_list(double a, double b, int nbPts){

    /* On considère qu'il est impossible d'avoir des doubles dans des listes de doubles */

    printf("Tableau de recherche : \n");

    srand(time(NULL));
    double* r = malloc(nbPts*sizeof(double));
    if (r == NULL) {
        perror("Erreur d'allocation mémoire");
        return NULL;
    }

    for (int i = 0; i < nbPts; i++) {
        r[i] = random_double(a, b);
    }

    // Affichage du tableau
    for (int i = 0; i < nbPts; i++) {
        printf("tab[%d] = %f\n", i, r[i]);
    }

    return r;
}

ABR* generate_AVL_B_from_list(int nbPts, double* list){

    ABR* R = NewArbre();

    for(int i = 0; i<nbPts; i++){
        Insertion(R, list[i]);
    }

    versAbreBalise(R);

    return R;
}

noeud* find_limit(noeud* ne, int clef){
    
    /* Entrée : ne : racine de l'arbre, clef : clef à trouver dans les noeuds internes */
    /* Sortie : noeud dont la clef est tout juste supérieur à la valeur a */

    /* Protection pour le reste du code */
    if(ne==NULL || ne->donnee != NULL){
        return NULL;
    }

    if(ne->clef == clef){
        return ne;
    }
    else if(ne->clef < clef){
        if(ne->droite == NULL || ne->droite->donnee != NULL){
            return ne;       
        }
        else{
            if(ne->droite->clef>clef){
                return ne;
            }
            else{
                return find_limit(ne->droite, clef);
            }
        }
    }
    else{
        if(ne->gauche == NULL || ne->gauche->donnee != NULL){
            return ne;
        }
        else{
            if(ne->gauche->clef<clef){
                return ne;
            }
            else{
                return find_limit(ne->gauche, clef);
            }
        }
    }
}

noeud* find_limit_donnee(noeud* ne){

    int clef = ne->clef;

    while(ne->clef != clef || ne->droite != NULL){
        ne = ne->droite;
    }

    if(ne->clef != clef){
        return NULL;
    }
    else{
        return ne;
    }
}

double* find_values_in_range(ABR* arbre, double start, double stop, int nbPts){
    
    double* R = malloc(nbPts*sizeof(double));
    int i = 0;

    noeud* lim = find_limit(arbre->racine, start);
    noeud* ne = find_limit_donnee(lim);
    if(ne == NULL){
        return NULL;
    }

    while(ne != NULL || ne->clef <= stop){
        R[i] = ne->clef;
        ne = ne->donnee->donnee;
    }

    return R;
}