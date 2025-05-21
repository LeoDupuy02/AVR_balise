/* main.c */
#include "AVR.h"
#include "AVR_balise.h"
#include "pile.h"
#include "validation.h"
#include <stdio.h>

int main() {

    ABR* monABR = NewArbre();
    monABR->racine = Newnoeud(0);
  
    Insertion(monABR, 10);
    Insertion(monABR, 5);
    Insertion(monABR, 15);
    Insertion(monABR, 20);
    Insertion(monABR, 7);
    Insertion(monABR, -10);
    Insertion(monABR, 11);
    Insertion(monABR, 2);
    Insertion(monABR, 3);
    AffichageArbre(monABR->racine,0);

    versAbreBalise(monABR);
    AffichageArbreBalise(monABR->racine,0);

    //RotationGauche(monABR.racine->droite->droite);

    //AffichageArbreBalise(monABR.racine, 0);

    SuppressionArbre(monABR);

    return 0;
}
