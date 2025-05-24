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
    int State = 0;
    int choice = 0;
    ABR* monABR = NewArbre();
    int count = 0;
    double* tab = NULL;
    Pile* pile = creerPile();
    double val = 0;
    int type_arbre = 0;

    while (1) {
        switch (State) {
            case 0:
                printf("Menu :\n");
                printf(" 1 - Entrer des valeurs pour générer un AVL\n");
                printf(" 2 - Générer un AVL à partir d'un fichier\n");
                printf(" 3 - Ajouter une valeur (seulement pour AVL)\n");
                printf(" 4 - Vider l'arbre \n");
                printf(" 5 - Quitter\n");
                printf("Que voulez-vous faire : ");
                if (scanf("%d", &State) != 1) {
                    printf("Entrée invalide.\n");
                    while (getchar() != '\n'); // vider buffer
                    State = 0;
                    continue;
                }
                if (State < 1 || State > 3) {
                    printf("Choix invalide, réessayez !\n");
                    State = 0;
                }
                if(State == 5){
                    State = 10;
                }
                if(State == 2){
                    State = 5;
                }
                if(State == 3){
                    State = 6;
                }
                if(State == 4){
                    State = 7;
                }
                break;

            case 1: {
                printf("Entrez vos valeurs séparées par un espace (ex: 1 2 3 ...) :\n");

                tab = malloc(100*sizeof(double));

                while (getchar() != '\n'); // vider buffer après scanf

                char buffer[100];

                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;

                char *token = strtok(buffer, " ");
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
            }

            case 2: {

                versAbreBalise(monABR);
                printf("Génération du png avec Graphviz...\n");
                ExporterDot("File_AVL_Balise", monABR);

                printf("Voulez-vous rechercher les entiers appartenant à [a, b] ? (0/1) : ");
                if (scanf("%d", &choice) != 1) {
                    printf("Entrée invalide.\n");
                    while (getchar() != '\n');
                    State = 0;
                    continue;
                }

                State = (choice == 1) ? 4 : 0;
                break;
            }

            case 3:{

                for (int i = 0; i < count; i++) {
                    Insertion(monABR, tab[i]);
                }

                printf("Génération du png avec Graphviz...\n");
                ExporterDot("File_AVL", monABR);

                printf("Voulez-vous générer l'AVL balisé associé ? (0/1) : ");
                if (scanf("%d", &choice) != 1) {
                    printf("Entrée invalide.\n");
                    while (getchar() != '\n');
                    State = 0;
                    continue;
                }

                State = (choice == 1) ? 2 : 0;

                break;
            }

            case 4: {
                double a, b;
                printf("Entrez la borne inférieure a : ");
                scanf("%lf", &a);
                printf("Entrez la borne supérieure b : ");
                scanf("%lf", &b);

                printf("Recherche des entiers entre %f et %f... : \n", a, b);
                
                pile = find_values_in_range(monABR,a,b);
                int i = 0;
                while(pile->sommet != NULL){
                    i += 1;
                    printf("%f\n", pop(pile));
                }
                printf("\n-> %d valeurs ont été trouvées dans l'intervalle !\n", i);

                State = 0;
                break;
            }
            case 5:{

                char nom_fichier[256];
                printf("Entrez le nom du fichier contenant les doubles : ");
                scanf("%255s", nom_fichier);

                count = 0;
                tab = lire_doubles_fichier(nom_fichier, &count);
                if (!tab) return 1;

                for(int j = 0; j<count; j++){
                    printf("%f\n", tab[j]);
                }

                State = 3;

                break;
            }
            case 6: {

                if(monABR->racine != NULL){
                    printf("Entrez la valeur à ajouter : ");
                    scanf("%lf", &val);
                    Insertion(monABR, val);
                    State = 3;
                }
                else{
                    printf("Erreur : arbre vide !\n");
                    State = 0;
                }

                break;
            }
            case 7:{
                monABR = NewArbre();

                State = 0;
                break;
            }
            case 10: {
                return 0;
            }
            default:
                State = 0;
                break;
        }
    }

    return 0;
}
