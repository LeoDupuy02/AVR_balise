#ifndef PILE_H
#define PILE_H

typedef struct Element_ {
    int valeur;
    struct Element_* suivant;
} Element;

typedef struct Pile_ {
    Element* sommet;
} Pile;

Pile* creerPile();
void viderPile(Pile* pile);
void push(Pile* pile, int valeur);
int pop(Pile* pile);
int top(Pile* pile);
int estVide(Pile* pile);
void SupprimerPile(Pile* pile);
int afficherPile(Pile* pile);


#endif // PILE_H
