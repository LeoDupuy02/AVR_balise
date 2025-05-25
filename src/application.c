#include "application.h"

// Génère un double dans [a, b]
double random_double(double a, double b) {
    return a + (b - a) * ((double)rand() / RAND_MAX);
}

double* generate_list(double a, double b, int nbPts){

    /* On considère qu'il est impossible d'avoir des doubles dans des listes de doubles */

    srand(time(NULL));
    double* r = malloc(nbPts*sizeof(double));
    if (r == NULL) {
        perror("Erreur d'allocation mémoire");
        return NULL;
    }

    for (int i = 0; i < nbPts; i++) {
        r[i] = random_double(a, b);
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

noeud* find_limit_low(noeud* ne, double clef){
    
    /* Entrée : ne : racine de l'arbre, clef : clef à trouver dans les noeuds internes */
    /* Sortie : noeud dont la clef est tout juste inférieure à la valeur b */

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
            return find_limit_low(ne->droite, clef);
        }
    }
    else{
        if(ne->gauche == NULL || ne->gauche->donnee != NULL){
            return ne;
        }
        else{
            return find_limit_low(ne->gauche, clef);
        }
    }
}

noeud* find_limit_donnee(noeud* ne){

    double clef = ne->clef;

    if(ne->droite != NULL){
        if((ne->droite->donnee != NULL && ne->gauche->donnee != NULL) || (ne->gauche != NULL)){
            return ne->gauche;
        }
    }

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

Pile* find_values_in_range(ABR* arbre, double start, double stop){
    
    Pile* maPile = creerPile();

    noeud* lim = find_limit_low(arbre->racine, stop);
    if(lim == NULL){
        return NULL;
    }

    noeud* ne = find_limit_donnee(lim);

    printf("Limite haute trouvée ! : %f\n", ne->clef);

    if(ne == NULL){
        return NULL;
    }

    ne = ne->donnee->donnee;

    while(ne != NULL && ne->clef >= start){
        push(maPile, ne->clef);
        if(ne->donnee != NULL){
            ne = ne->donnee->donnee;
        }
        else{
            ne = NULL;
        }
    }

    return maPile;
}