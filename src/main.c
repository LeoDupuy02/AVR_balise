#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AVR.h"
#include "AVR_Balise.h"
#include "graphviz_handler.h"
//#include "application.h"

int main() {
    int State = 0;
    int choice = 0;
    ABR* monABR = NULL;

    while (1) {
        switch (State) {
            case 0:
                printf("Menu :\n");
                printf(" 1 - Entrer des valeurs pour générer un AVL\n");
                printf(" 2 - Générer un AVL à partir d'un fichier\n");
                printf(" 3 - Quitter\n");
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
                if(State == 3){
                    State = 10;
                }
                break;

            case 1: {
                printf("Entrez vos valeurs séparées par un espace (ex: 1 2 3 ...) :\n");

                while (getchar() != '\n'); // vider buffer après scanf

                char buffer[100];
                int tab[100];
                int count = 0;

                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;

                char *token = strtok(buffer, " ");
                while (token != NULL && count < 100) {
                    tab[count++] = atoi(token);
                    token = strtok(NULL, " ");
                }

                printf("Vous avez saisi %d entiers :\n", count);
                for (int i = 0; i < count; i++) {
                    printf("%d ", tab[i]);
                }
                printf("\n");

                monABR = NewArbre();
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

            case 2:

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

                State = (choice == 1) ? 3 : 0;
                break;

            case 3: {
                double a, b;
                printf("Entrez la borne inférieure a : ");
                scanf("%lf", &a);
                printf("Entrez la borne supérieure b : ");
                scanf("%lf", &b);

                // Supposons que tu as une fonction à appeler ici
                // Exemple : AfficherValeursDansIntervalle(monABR, a, b);
                printf("Recherche des entiers entre %.2f et %.2f...\n", a, b);
                // Appelle ta fonction ici...

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

