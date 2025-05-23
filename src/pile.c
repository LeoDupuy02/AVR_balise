/* pile.c */

#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

/* Fichier définissant une pile : Structure de donnée du type LIFO */

/* ============================= Création ================================ */

Pile* creerPile() {
    Pile* pile = malloc(sizeof(Pile));
    pile->sommet = NULL;
    printf("Pile créée\n");
    return pile;
}

/* ============================ Vider la pile =========================== */

void viderPile(Pile* pile){
    while (!estVide(pile)) {
        pop(pile);
    }
}

/* ============================= Gestion ================================ */

// Empiler un élément
void push(Pile* pile, int valeur) {
    Element* nouveau = malloc(sizeof(Element));
    nouveau->valeur = valeur;
    if(pile->sommet != NULL){
        nouveau->suivant = pile->sommet;
    }
    else{
        nouveau->suivant = NULL;
    }
    pile->sommet = nouveau;
    printf("Push réussit\n");
}

// Dépiler un élément
int pop(Pile* pile) {
    if (pile->sommet == NULL) {
        fprintf(stderr, "Erreur : pile vide !\n");
        exit(EXIT_FAILURE);
    }
    Element* temp = pile->sommet;
    int valeur = temp->valeur;
    if(temp->suivant != NULL){
        pile->sommet = temp->suivant;
    }
    else{
        pile->sommet = NULL;
    }
    free(temp);
    printf("%d\n",valeur);
    return valeur;
}

int top(Pile* pile) {
    if (pile->sommet == NULL) {
        fprintf(stderr, "Erreur : pile vide !\n");
        exit(EXIT_FAILURE);
    }
    return pile->sommet->valeur;
}

int estVide(Pile* pile) {
    return pile->sommet == NULL;
}

/* ============================= Supprimmer la pile ================================ */

void SupprimerPile(Pile* pile) {
    while (!estVide(pile)) {
        pop(pile);
    }
    free(pile);
}

/* ============================== Afficher pile =================================== */

int afficherPile(Pile* pile) {

    if (estVide(pile)) {
        printf("Pile vide.\n");
        return 0;
    }

    printf("Contenu de la pile (du sommet vers la base) :\n");
    Element* courant = pile->sommet;
    while (courant != NULL) {
        printf("%d\n", courant->valeur);
        courant = courant->suivant;
    }
    return 1;
}


/* ================================= TEST PILE ======================================*/

// int main(){

//     int value;
//     Pile* pile = creerPile();

//     push(pile, 13);
//     push(pile, 20);

//     value = pop(pile);
//     printf("1er : %d\n",value);
//     value = pop(pile);
//     printf("2eme : %d\n",value);

//     printf("Est vide ? : %d\n",estVide(pile));
//     SupprimerPile(pile);

// }