#include "AVR.h"
#include "pile.h"
#include "AVR_Balise.h"
#include "graphviz_handler.h"
#include "application.h"

int main(){

    /* Test de l equilibrage d'un arbre */

    double a = 45.5;
    double b = 75.5;
    int nbPts = 20;

    double* list = generate_list(a,b, nbPts);
    Pile* pile_retour = creerPile();

    ABR* arbre = generate_AVL_B_from_list(nbPts, list);

    ExporterDot("File", arbre);

    noeud* N = find_limit_low(arbre->racine, 67);
    if(N != NULL){
        printf("Limite haute is : %f\n", N->clef);
    }

    noeud* M = find_limit_donnee(N);
    if(M != NULL){
        printf("Donnée associée à la limite %f\n", M->clef);
    }

    pile_retour = find_values_in_range(arbre, 51, 66);
    if(pile_retour->sommet == NULL){
        return NULL;
    }
    while(pile_retour->sommet != NULL){
        printf(" L : %f ", pop(pile_retour));
    }
    printf("\n");

    return 0;

}