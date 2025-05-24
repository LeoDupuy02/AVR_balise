#include "AVR.h"
#include "graphviz_handler.h"

/* ============================== EXPORTATION EN .dot d'un AVR ====================== */

void ExporterDotRec(FILE* fichier, noeud* n) {

    if (n == NULL)
        return;

    // Afficher le nœud
    if(n->gauche == NULL && n->droite == NULL && n->donnee != NULL){
        fprintf(fichier, "    \"%p\" [label=\"%f\",shape=box];\n", (void*)n, n->clef); // Cercle (par défaut)
    }
    else{
        fprintf(fichier, "    \"%p\" [label=\"%f\"];\n", (void*)n, n->clef);
    }

    // Relier au fils gauche
    if (n->gauche) {
        fprintf(fichier, "    \"%p\" -> \"%p\" [label=\"g\"];\n", (void*)n, (void*)n->gauche);
        ExporterDotRec(fichier, n->gauche);
    }
    else{
        if(n->donnee != NULL){
             // Lien horizontal visuel, mais sans contrainte
            fprintf(fichier, "    \"%p\" -> \"%p\" [style=dashed, color=red, constraint=false];\n",
                    (void*)n, (void*)n->donnee->donnee);

            // Forcer à être sur la même ligne
            fprintf(fichier, "    { rank=same; \"%p\"; \"%p\"; }\n",
                    (void*)n, (void*)n->donnee->donnee);
        }
    }

    // Relier au fils droit
    if (n->droite) {
        fprintf(fichier, "    \"%p\" -> \"%p\" [label=\"d\"];\n", (void*)n, (void*)n->droite);
        ExporterDotRec(fichier, n->droite);
    }
    else{
       if(n->donnee != NULL){
             // Lien horizontal visuel, mais sans contrainte
            fprintf(fichier, "    \"%p\" -> \"%p\" [style=dashed, color=blue, constraint=false];\n",
                    (void*)n, (void*)n->donnee->donnee);

            // Forcer à être sur la même ligne
            fprintf(fichier, "    { rank=same; \"%p\"; \"%p\"; }\n",
                    (void*)n, (void*)n->donnee->donnee);
        }
    }

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
    snprintf(commande, sizeof(commande), "dot -Tpng %s.dot -o %s.png &", nom_fichier, nom_fichier);
    printf("%s\n", commande);
    
    // Exécution de la commande Graphviz
    system(commande);
    //Affichage de l'image
    snprintf(commande, sizeof(commande), "sudo -u $USER eog %s.png 2>/dev/null &", nom_fichier);
    printf("%s\n", commande);
    system(commande);

    return 0;
}
