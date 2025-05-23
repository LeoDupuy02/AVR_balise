#include "AVR.h"
#include "graphviz_handler.h"

/* ============================== EXPORTATION EN .dot d'un AVR ====================== */

void ExporterDotRec(FILE* fichier, noeud* n) {

    if (n == NULL)
        return;

    // Afficher le nœud
    //if(n->gauche == NULL && n->droite == NULL && n->donnee != NULL){
    //    fprintf(fichier, "    \"%p\" [label=\"%d\",shape=box];\n", (void*)n, n->donnee->donnee); // Cercle (par défaut)
    //}
    //else{
    fprintf(fichier, "    \"%p\" [label=\"%d\"];\n", (void*)n, n->clef);
    //}

    // Relier au fils gauche
    if (n->gauche) {
        fprintf(fichier, "    \"%p\" -> \"%p\" [label=\"g\"];\n", (void*)n, (void*)n->gauche);
        ExporterDotRec(fichier, n->gauche);
    }

    // Relier au fils droit
    if (n->droite) {
        fprintf(fichier, "    \"%p\" -> \"%p\" [label=\"d\"];\n", (void*)n, (void*)n->droite);
        ExporterDotRec(fichier, n->droite);
    }

    system("dot -Tpng test1.dot -o test1.png");
}

int ExporterDot(const char* nom_fichier, ABR* arbre) {

    char file_name[256];
    snprintf(file_name, sizeof(file_name), "%s.dot", nom_fichier);

    FILE* fichier = fopen(file_name, "w");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier .dot");
        return 1;
    }

    fprintf(fichier, "digraph Arbre {\n");
    fprintf(fichier, "    node [shape=circle, fontname=\"Arial\"];\n");

    if (arbre->racine == NULL) {
        fprintf(fichier, "    vide [label=\"Arbre vide\"];\n");
    } else {
        ExporterDotRec(fichier, arbre->racine);
    }

    fprintf(fichier, "}\n");

    fclose(fichier);

    char commande[256];
    snprintf(commande, sizeof(commande), "dot -Tpng %s.dot -o %s.png", nom_fichier, nom_fichier);
    printf("%s\n", commande);
    
    // Exécution de la commande Graphviz
    system(commande);

    return 0;
}
