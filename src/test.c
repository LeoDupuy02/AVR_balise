#include "AVR.h"
#include "pile.h"
#include "AVR_Balise.h"
#include "graphviz_handler.h"
#include "application.h"

int main(){

    /* Test de l equilibrage d'un arbre */
    int i = 0;

    ABR* arbre = NewArbre();
    Insertion(arbre, 1);
    Insertion(arbre, 2);
    Insertion(arbre, 3);
    Insertion(arbre, 4);
    Insertion(arbre, 5);
    Insertion(arbre, 6);
    Insertion(arbre, 7);
    Insertion(arbre, 8);
    Insertion(arbre, 9);

    versAbreBalise(arbre);
    
    Suppression_Noeud(arbre, 6);
    ExporterDot("file", arbre);

    scanf("%d", &i);
    Suppression_Noeud(arbre, 5);
    ExporterDot("file", arbre);
    
    SuppressionArbre(arbre);

    return 0;

}