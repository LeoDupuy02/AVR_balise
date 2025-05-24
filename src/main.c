#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "AVR.h"
#include "AVR_Balise.h"
#include "graphviz_handler.h"
#include "application.h"
#include "pile.h"

double* lire_doubles_fichier(const char* nom_fichier, int* taille) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }

    if (fscanf(fichier, "%d", taille) != 1 || *taille <= 0) {
        fprintf(stderr, "Erreur de lecture du nombre de valeurs.\n");
        fclose(fichier);
        return NULL;
    }

    double* valeurs = malloc(*taille * sizeof(double));
    if (!valeurs) {
        perror("Erreur d'allocation mémoire");
        fclose(fichier);
        return NULL;
    }

    for (int i = 0; i < *taille; i++) {
        if (fscanf(fichier, "%lf", &valeurs[i]) != 1) {
            fprintf(stderr, "Erreur de lecture à la ligne %d\n", i + 2);
            free(valeurs);
            fclose(fichier);
            return NULL;
        }
    }

    fclose(fichier);
    return valeurs;
}

int main() {
    int State = 0, choice = 0, count = 0, type_arbre = 0;
    double* tab = NULL;
    double val = 0;
    char buffer[100];
    ABR* monABR = NewArbre();
    Pile* pile = creerPile();
    char* token = NULL;

    while (1) {
        switch (State) {
            case 0:
                printf("Menu :\n");
                printf(" 1 - Entrer des valeurs pour générer un AVL\n");
                printf(" 2 - Générer un AVL à partir d'un fichier\n");
                printf(" 3 - Ajouter une valeur (seulement pour AVL)\n");
                printf(" 4 - Supprimer une valeur (seulement pour AVL)\n");
                printf(" 5 - Vider l'arbre \n");
                printf(" 6 - Quitter\n");
                printf("Que voulez-vous faire : ");

                if (scanf("%d", &State) != 1) {
                    printf("Entrée invalide.\n");
                    while (getchar() != '\n');
                    State = 0;
                    continue;
                }

                if (State < 1 || State > 6) {
                    printf("Choix invalide, réessayez !\n");
                    State = 0;
                } else if (State == 6) {
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
                    State = 6;
                } else if (State == 5) {
                    State = 7;
                } else if (State == 4) {
                    State = 8;
                }
                break;

            case 1:
                /* On vide ce qu'il y a à vider */
                if(tab != NULL){
                    free(tab);
                }
                ABR* monABR = NewArbre();
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
                for (int i = 0; i < count; i++) {
                    printf("%f ", tab[i]);
                }
                printf("\n");

                State = 3;
                break;

            case 2:
                versAbreBalise(monABR);
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
                double a, b;
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
                char nom_fichier[256];
                printf("Entrez le nom du fichier contenant les données : ");
                scanf("%255s", nom_fichier);

                count = 0;
                tab = lire_doubles_fichier(nom_fichier, &count);
                if (!tab) return 1;

                for (int j = 0; j < count; j++) {
                    printf("%f\n", tab[j]);
                }
                State = 3;
                break;
            }

            case 6:
                if (monABR->racine != NULL) {
                    count = count + 1;
                    printf("Entrez la valeur à ajouter : ");
                    scanf("%lf", &val);
                    Insertion(monABR, val);
                    State = 3;
                } else {
                    printf("Erreur : arbre vide !\n");
                    State = 0;
                }
                break;

            case 7:
                monABR = NewArbre();
                State = 0;
                break;

            case 8:
                if (monABR->racine != NULL) {
                    count = count - 1;
                    printf("Entrez la valeur à supprimer : ");
                    scanf("%lf", &val);
                    Suppression_Noeud(monABR, val);
                    State = 3;
                } else {
                    printf("Erreur : arbre vide !\n");
                    State = 0;
                }
                break;

            default:
                State = 0;
                break;
        }
    }
    return 0;
}
