/* ============================== EXPORTATION EN .dot d'un AVR ====================== */

void ExporterDotRec(FILE* fichier, noeud* n) {

    if (n == NULL)
        return;

    // Afficher le nœud
    if(n->gauche == NULL && n->droite == NULL && n->donnee != NULL){
        fprintf(fichier, "    \"%p\" [label=\"%d\",shape=box];\n", (void*)n, n->donnee->donnee); // Cercle (par défaut)
    }
    else{
        fprintf(fichier, "    \"%p\" [label=\"%d\"];\n", (void*)n, n->clef);
    }

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
}

int ExporterDot(const char* nom_fichier, ABR* arbre) {

    FILE* fichier = fopen(nom_fichier, "w");
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

    return 0;
}
