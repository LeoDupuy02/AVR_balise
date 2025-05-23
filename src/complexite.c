
double mesure_temps(void (*fonction)(int), int n) {
    clock_t debut = clock();
    fonction(n);
    clock_t fin = clock();
    return (double)(fin - debut) / CLOCKS_PER_SEC;
}

int main() {
    FILE* fichier = fopen("resultats.dat", "w");
    if (!fichier) {
        perror("Erreur d'ouverture du fichier");
        return 1;
    }

    fprintf(fichier, "#n\tfonction1\tfonction2\n");

    for (int n = 100; n <= 5000; n += 500) {
        double t1 = mesure_temps(fonction1, n);
        double t2 = mesure_temps(fonction2, n);
        fprintf(fichier, "%d\t%f\t%f\n", n, t1, t2);
        printf("n = %d, f1 = %.6fs, f2 = %.6fs\n", n, t1, t2);
    }

    fclose(fichier);

    // Génération du graphique avec gnuplot
    system("gnuplot -persist -e \""
           "set title 'Comparaison des temps d\\'exécution';"
           "set xlabel 'n';"
           "set ylabel 'Temps (s)';"
           "plot 'resultats.dat' using 1:2 with lines title 'fonction1', "
           "'resultats.dat' using 1:3 with lines title 'fonction2'\"");

    return 0;
}
