#include "file_handler.h"

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

void enregistrer_liste(double* tab, int count, const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "w");
    if (!fichier) {
        perror("Erreur ouverture fichier");
        return;
    }

    // Écriture du nombre d'éléments
    fprintf(fichier, "%d\n", count);

    // Écriture des éléments un par un
    for (int i = 0; i < count; i++) {
        fprintf(fichier, "%f\n", tab[i]);
    }

    fclose(fichier);
}