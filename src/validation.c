#include "validation.h"

void validation_AVL(noeud* ne){

    printf("==> Noeud actuel : %d\n",ne->clef);

    if(ne->pere == NULL){
        printf("Pere de : %d est NULL\n", ne->clef);
    }
    else{
        printf("Pere actuel : %d\n",ne->pere->clef);
    }

    if(ne->gauche==NULL){
        printf("Gauche de %d est NULL\n", ne->clef);
    }
    else if(ne->donnee==NULL){
        printf("A gauche !\n");
        validation_AVL(ne->gauche);
    }

    if(ne->droite==NULL){
        printf("Droite de %d est NULL\n", ne->clef);
    }
    else if(ne->donnee==NULL){
        printf("A droite !\n");
        validation_AVL(ne->droite);
    }

    return;
}