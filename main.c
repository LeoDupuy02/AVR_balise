/* main.c */
#include "AVR.h"
#include "AVR_balise.h"
#include "pile.h"

int main() {
    ABR monABR;
    monABR.racine = Newnoeud(0);
  
    Insertion(&monABR, 10);
    Insertion(&monABR, 5);
    Insertion(&monABR, 15);
    Insertion(&monABR, 20);
    Insertion(&monABR, 7);
    Insertion(&monABR, -10);
    Insertion(&monABR, 11);
    Insertion(&monABR, 2);
    Insertion(&monABR, 3);
    AffichageArbre(monABR.racine,0);

    noeud* Mich = chercher(monABR.racine, 0);
    printf("Equilibre d'interet : %d\n", Mich->equilibre);
    versAbreBalise(&monABR);
    AffichageArbreBalise(monABR.racine,0);

    printf(" === On passe à l'insertion === \n");

    InsertionBalise(&monABR, 45);
    AffichageArbreBalise(monABR.racine,0);

    printf("Suppression noeud\n");
    SuppressionNoeudBalise(&monABR, 20);

    SuppressionArbre(monABR.racine);

    return 0;
}
