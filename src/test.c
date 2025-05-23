#include "AVR.h"
#include "pile.h"
#include "AVR_Balise.h"
#include "graphviz_handler.h"

int test_Creations_Rotations() {

    /* Test de la création de noeuds et d'arbre et de rotation */

    ABR* monABR = NewArbre();
    monABR->racine = Newnoeud(0);

    monABR->racine->gauche = Newnoeud(-10);
    monABR->racine->gauche->pere = monABR->racine;

    monABR->racine->droite = Newnoeud(10);
    monABR->racine->droite->pere = monABR->racine;

    monABR->racine->droite->gauche = Newnoeud(5);
    monABR->racine->droite->gauche->pere = monABR->racine->droite;

    monABR->racine->droite->droite = Newnoeud(15);
    monABR->racine->droite->droite->pere = monABR->racine->droite;

    monABR->racine->droite->droite->droite = Newnoeud(17);
    monABR->racine->droite->droite->droite->pere = monABR->racine->droite->droite;

    monABR->racine->droite->droite->gauche = Newnoeud(14);
    monABR->racine->droite->droite->gauche->pere = monABR->racine->droite->droite;
    AffichageArbre(monABR->racine,0);

    RotationGauche(monABR->racine->droite);
    AffichageArbre(monABR->racine,0);

    RotationDroite(monABR->racine);
    AffichageArbre(monABR->racine,0);

    RotationDroite(monABR->racine->droite);
    AffichageArbre(monABR->racine,0);

    RotationDroite(monABR->racine->droite->droite);
    AffichageArbre(monABR->racine,0);

    RotationGauche(monABR->racine->droite->droite);
    AffichageArbre(monABR->racine,0);

    return 0;
}

int test_Recherche(){

    /* Test de la recherche dans un arbre */

    noeud* r = NULL;

    ABR* monABR = NewArbre();
    monABR->racine = Newnoeud(0);

    monABR->racine->gauche = Newnoeud(-10);
    monABR->racine->gauche->pere = monABR->racine;

    monABR->racine->droite = Newnoeud(10);
    monABR->racine->droite->pere = monABR->racine;

    monABR->racine->droite->gauche = Newnoeud(5);
    monABR->racine->droite->gauche->pere = monABR->racine->droite;

    monABR->racine->droite->droite = Newnoeud(15);
    monABR->racine->droite->droite->pere = monABR->racine->droite;

    monABR->racine->droite->droite->droite = Newnoeud(17);
    monABR->racine->droite->droite->droite->pere = monABR->racine->droite->droite;

    monABR->racine->droite->droite->gauche = Newnoeud(14);
    monABR->racine->droite->droite->gauche->pere = monABR->racine->droite->droite;
    
    AffichageArbre(monABR->racine,0);

    r = chercher(monABR->racine, -10);
    printf("Recherche de -10. Retour : %d\n", r->clef);

    r = chercher(monABR->racine, 0);
    printf("Recherche de 0. Retour : %d\n", r->clef);

    r = chercher(monABR->racine, 17);
    printf("Recherche de 17. Retour : %d\n", r->clef);

    r = chercher(monABR->racine, 62);
    printf("Recherche de 62. Retour : %d\n", r==NULL);

    r = Plus_Grand_Noeud(monABR->racine);
    printf("Plus grand noeud depuis %d : %d\n", monABR->racine->clef, r->clef);
    r = Plus_Grand_Noeud(monABR->racine->gauche);
    printf("Plus grand noeud depuis %d : %d\n", monABR->racine->gauche->clef, r->clef);

    return 0;

}

int main(){

    /* Test de l equilibrage d'un arbre */

    ABR* monABR = NewArbre();

    Insertion(monABR, 1);
    Insertion(monABR, 2);
    Insertion(monABR, 3);
    AffichageArbre(monABR->racine, 0);
    Insertion(monABR, 4);
    Insertion(monABR, 5);
    AffichageArbre(monABR->racine, 0);
    Insertion(monABR, 6);
    Insertion(monABR, 7);
    AffichageArbre(monABR->racine, 0);
    Insertion(monABR,8);
    AffichageArbre(monABR->racine, 0);

    Suppression_Noeud(monABR, 20);
    AffichageArbre(monABR->racine, 0);

    versAbreBalise(monABR);
    AffichageArbre(monABR->racine, 0);

    InsertionB(monABR, 60);
    AffichageArbre(monABR->racine, 0);

    ExporterDot("test1.dot", monABR);
    system("dot -Tpng test1.dot -o test1.png");

    SuppressionArbre(monABR);

    return 0;

}