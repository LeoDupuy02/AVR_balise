#ifndef PILE_H
#define PILE_H

typedef struct Element_ {
    double valeur;
    struct Element_* suivant;
} Element;

typedef struct Pile_ {
    Element* sommet;
} Pile;

Pile* creerPile();
void viderPile(Pile* pile);
void push(Pile* pile, double valeur);
double pop(Pile* pile);
double top(Pile* pile);
int estVide(Pile* pile);
void SupprimerPile(Pile* pile);
int afficherPile(Pile* pile);
void save_stack_to_file(Pile* pile, const char* filename);

#endif // PILE_H
