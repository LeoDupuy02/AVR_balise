#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AVR.h"
#include "AVR_Balise.h"
#include "graphviz_handler.h"
#include "application.h"
#include "pile.h"
#include "file_handler.h"

int main() {
    int State = 0, choice = 0, count = 0, type_arbre = 0;
    double* tab = NULL;
    double val = 0;
    char buffer[100];
    ABR* monABR = NewArbre();
    Pile* pile = creerPile();
    char* token = NULL;
    double a, b;

    while (1) {
        switch (State) {
            case 0:
                printf("Menu :\n");
                printf(" 1 - Entrer des valeurs pour générer un AVL\n");
                printf(" 2 - Générer un AVL à partir d'un fichier\n");
                printf(" 3 - Générer un AVL aléatoirement avec des valeurs comprises entre a et b\n");
                printf(" 4 - Ajouter une valeur à l'arbre\n");
                printf(" 5 - Supprimer une valeur de l'arbre\n");
                printf(" 6 - Vider l'arbre \n");
                printf(" 7 - Quitter\n");
                printf("Que voulez-vous faire : ");

                if (scanf("%d", &State) != 1) {
                    printf("Entrée invalide.\n");
                    while (getchar() != '\n');
                    State = 0;
                    continue;
                }

                if (State < 1 || State > 7) {
                    printf("Choix invalide, réessayez !\n");
                    State = 0;
                } else if (State == 7) {
                    SuppressionArbre(monABR);
                    SupprimerPile(pile);
                    if (tab != NULL) {
                        free(tab);
                        tab = NULL;
                    }
                    return 0;
                } else if (State == 2) {
                    State = 5;
                } else if (State == 3) {
                    State = 9;
                }
                else if (State == 4) {
                    State = 6;
                } else if (State == 6) {
                    State = 7;
                } else if (State == 5) {
                    State = 8;
                }
                break;

            case 1:

                type_arbre = 0;

                /* On vide ce qu'il y a à vider */
                if(tab != NULL){
                    free(tab);
                }
                SupprArbre(monABR->racine);
                monABR->racine = NULL;
                memset(buffer, 0, sizeof(buffer));
                count = 0; 

                printf("Entrez vos valeurs séparées par un espace (ex: 1 2 3 ...) :\n");
                tab = malloc(100 * sizeof(double));
                while (getchar() != '\n');
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;

                token = strtok(buffer, " ");
                while (token != NULL && count < 100) {
                    tab[count++] = atoi(token);
                    token = strtok(NULL, " ");
                }

                printf("Vous avez saisi %d entiers :\n", count);
                
                printf("Enregistrement des points dans points.txt !\n");
                enregistrer_liste(tab, count, "points.txt");

                State = 3;
                break;

            case 2:
                if(type_arbre != 1){
                    versAbreBalise(monABR);
                }
                ExporterDot("File_AVL_Balise", monABR);
                type_arbre = 1;

                printf("Voulez-vous rechercher les entiers appartenant à [a, b] ? (0/1) : ");
                if (scanf("%d", &choice) != 1) {
                    printf("Entrée invalide.\n");
                    while (getchar() != '\n');
                    State = 0;
                    continue;
                }
                State = (choice == 1) ? 4 : 0;
                break;

            case 3:

                SupprArbre(monABR->racine);
                monABR->racine = NULL;
                for (int i = 0; i < count; i++) {
                    Insertion(monABR, tab[i]);
                }
                ExporterDot("File_AVL", monABR);
                type_arbre = 0;

                printf("Voulez-vous générer l'AVL balisé associé ? (0/1) : ");
                if (scanf("%d", &choice) != 1) {
                    printf("Entrée invalide.\n");
                    while (getchar() != '\n');
                    State = 0;
                    continue;
                }
                State = (choice == 1) ? 2 : 0;
                break;

            case 4: {
                printf("Entrez la borne inférieure a : ");
                scanf("%lf", &a);
                printf("Entrez la borne supérieure b : ");
                scanf("%lf", &b);

                printf("Recherche des entiers entre %f et %f...\n", a, b);
                pile = find_values_in_range(monABR, a, b);
                save_stack_to_file(pile, "intervalValues.txt");

                State = 0;
                break;
            }

            case 5: {

                /* On vide ce qu'il y a à vider */
                if(tab != NULL){
                    free(tab);
                }
                SupprArbre(monABR->racine);
                monABR->racine = NULL;
                memset(buffer, 0, sizeof(buffer));
                count = 0; 

                /* AVL */
                type_arbre = 0;

                char nom_fichier[256];
                printf("Entrez le nom du fichier contenant les données : ");
                scanf("%255s", nom_fichier);

                count = 0;
                tab = lire_doubles_fichier(nom_fichier, &count);
                if (!tab) return 1;

                State = 3;
                break;
            }

            case 6:
                if (monABR->racine != NULL) {
                    count = count + 1;
                    printf("Entrez la valeur à ajouter : ");
                    scanf("%lf", &val);
                    if(type_arbre == 0){
                        Insertion(monABR, val);
                    }
                    else{
                        InsertionB(monABR, val);
                    }
                    State = 2;
                } else {
                    printf("Erreur : arbre vide !\n");
                    State = 0;
                }
                break;

            case 7:
                SupprArbre(monABR->racine);
                monABR->racine = NULL;
                State = 0;
                break;

            case 8:
                if (monABR->racine != NULL) {
                    count = count - 1;
                    printf("Entrez la valeur à supprimer : ");
                    scanf("%lf", &val);
                    Suppression_Noeud(monABR, val);
                    State = 2;
                } 
                else {
                    printf("Erreur : arbre vide !\n");
                    State = 0;
                }
                break;

            case 9:{

                /* On vide ce qu'il y a à vider */
                if(tab != NULL){
                    free(tab);
                }
                SupprArbre(monABR->racine);
                monABR->racine = NULL;
                memset(buffer, 0, sizeof(buffer));
                count = 0; 

                /* AVL */
                type_arbre = 0;

                printf("Entrez la valeur de a : ");
                scanf("%lf", &a);
                printf("Entrez la valeur de b : ");
                scanf("%lf", &b);
                printf("Entrez le nombre de points : ");
                scanf("%d", &count);

                tab = generate_list(a,b,count);
                printf("Enregistrement des points dans points.txt !\n");
                enregistrer_liste(tab, count, "points.txt");

                State = 3;

                break;
            }

            default:
                State = 0;
                break;
        }
    }
    return 0;
}
