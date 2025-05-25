# Projet d'Arbre AVL Balisé en C

Ce projet implémente un arbre AVL standard et un "Arbre AVL Balisé" spécialisé en C. L'arbre AVL balisé est une variante où les nœuds internes guident les recherches, et les données réelles ou "balises" sont stockées dans des structures spécifiques de type feuille. Le projet inclut des fonctionnalités pour la création d'arbres (manuelle, depuis un fichier, aléatoire), la modification (insertion, suppression) et la recherche par intervalle.

## 📝 Utilisation du Menu (`main.c`)

Le programme démarre avec un menu interactif pour gérer les arbres AVL :

1.  **Entrer des valeurs pour générer un AVL** :
    * Demande à l'utilisateur de saisir des valeurs de type `double` séparées par des espaces.
    * Ces valeurs sont enregistrées dans `points.txt`.
    * Un arbre AVL standard est généré à partir de ces valeurs.
    * La structure de l'arbre AVL est exportée vers `../dot/File_AVL.dot` et visualisée sous forme de `../dot/File_AVL.png`.

2.  **Générer un AVL balisé à partir de l'AVL actuel** :
    * Convertit l'arbre AVL standard existant en un arbre AVL balisé.
    * L'arbre AVL balisé est exporté vers `../dot/File_AVL_Balise.dot` et visualisé sous forme de `../dot/File_AVL_Balise.png`.
    * Après cela, vous pouvez effectuer des recherches par intervalle (option 4 du menu principal, si vous choisissez de continuer).

3.  **Générer un AVL à partir d'un fichier** :
    * Demande un nom de fichier contenant des valeurs de type `double`. Le fichier doit avoir le nombre de valeurs sur la première ligne, suivi des nombres sur les lignes suivantes.
    * Un arbre AVL standard est généré.
    * La structure de l'arbre AVL est exportée vers `../dot/File_AVL.dot` et visualisée sous forme de `../dot/File_AVL.png`.

4.  **Générer un AVL aléatoirement avec des valeurs comprises entre a et b** :
    * Demande une borne inférieure `a`, une borne supérieure `b`, et le nombre de points à générer.
    * Des valeurs `double` aléatoires dans l'intervalle `[a, b]` sont générées.
    * Ces valeurs sont enregistrées dans `points.txt`.
    * Un arbre AVL standard est généré.
    * La structure de l'arbre AVL est exportée vers `../dot/File_AVL.dot` et visualisée sous forme de `../dot/File_AVL.png`.

5.  **Ajouter une valeur à l'arbre** :
    * Demande une valeur `double` à insérer dans l'arbre actuel.
    * Si l'arbre actuel est un AVL standard, `Insertion` est utilisée. S'il s'agit d'un AVL balisé (`type_arbre == 1`), `InsertionB` est utilisée.
    * L'arbre mis à jour est ensuite ré-exporté et visualisé.

6.  **Supprimer une valeur de l'arbre** :
    * Demande une valeur `double` à supprimer de l'arbre actuel.
    * L'arbre mis à jour est ensuite ré-exporté et visualisé.
    * *Note : La suppression est typiquement effectuée sur la représentation AVL standard avant la conversion en balisé, ou une logique spécifique pour la suppression dans l'AVL balisé serait dans `AVR_Balise.c` (bien que le `main.c` fourni suggère qu'il pourrait ré-exporter le type d'arbre actuel).*

7.  **Vider l'arbre** :
    * Vide l'arbre actuel, libérant tous les nœuds.

8.  **Quitter** :
    * Quitte le programme, libérant toute la mémoire allouée.

**Fichiers de Sortie** :
* Nombres saisis manuellement ou générés aléatoirement : `points.txt`.
* Visualisations de l'arbre AVL standard : `../dot/File_AVL.dot` et `../dot/File_AVL.png`.
* Visualisations de l'arbre AVL balisé : `../dot/File_AVL_Balise.dot` et `../dot/File_AVL_Balise.png`.
* Résultats des recherches par intervalle (déclenchées après la création d'un AVL balisé et le choix de l'option de recherche) : `intervalValues.txt`.

---

## ⚙️ Fonctionnalités des Modules Principaux

### `AVR.c` - Arbre AVL Standard
Ce fichier implémente la logique de base pour un arbre AVL auto-équilibré standard.
* **Création de Nœuds et d'Arbres** : `Newnoeud` pour les nœuds, `NewArbre` pour la structure de l'arbre. `Newdonnee` est utilisé pour créer des conteneurs de données, principalement pertinent pour la structure de l'arbre balisé mais défini ici.
* **Équilibrage** : `hauteur` calcule la hauteur des nœuds, et `MajHauteurEquilibre` met à jour la hauteur et les facteurs d'équilibre. `RotationGauche`, `RotationDroite`, et `Reequilibre` effectuent les rotations nécessaires et le rééquilibrage après les insertions ou suppressions.
* **Opérations** :
    * `Insertion` (et son assistant récursif `insr`) : Ajoute une nouvelle clé, en s'assurant que l'arbre reste équilibré.
    * `Suppression_Noeud` (et son assistant récursif `Suppr_noeud`) : Supprime une clé, en rééquilibrant l'arbre si nécessaire.
    * `chercher` : Localise un nœud avec une clé donnée.
* **Nettoyage** : `SupprArbre` et `SuppressionArbre` libèrent toute la mémoire de l'arbre.

### `AVR_Balise.c` - Arbre AVL Balisé
Ce module gère l'arbre AVL "balisé", où les nœuds internes sont des nœuds AVL standard, mais ils sont augmentés de nœuds feuilles spéciaux (balises) qui contiennent des données.
* **Insertion Balisée (`InsertionB`, `insrB`)** : Cette fonction insère une clé dans l'AVL balisé. Lorsqu'une nouvelle clé est insérée, cela implique typiquement la création d'un nœud interne pour la clé et la liaison de nouveaux nœuds "données" (feuilles externes) qui pourraient représenter des intervalles ou des pointeurs vers des données réelles. La structure décrite implique la création d'un nouveau nœud interne puis la liaison d'un enfant gauche (également un nœud interne avec la même clé) et d'un enfant droit (le sous-arbre original ou un nouveau nœud de données). Le nouveau fils gauche a ensuite des nœuds de données comme enfants.
* **Conversion (`versAbreBalise`, `CompleterArbreBalise`)** : Transforme un arbre AVL standard en un arbre AVL balisé. `CompleterArbreBalise` parcourt récursivement l'arbre AVL. Pour chaque nœud, il empile sa clé sur une pile. Lorsqu'il atteint une feuille dans l'AVL original ou un emplacement d'enfant vide, il crée de nouveaux nœuds "données" (feuilles externes) en utilisant les clés dépilées de la pile et les lie comme enfants, "balisant" ainsi efficacement les intervalles de l'arbre. Ces nœuds de données stockent des pointeurs (probablement vers d'autres nœuds ou structures de données, gérés par `Newdonnee`).

### `pile.c` - Implémentation de la Pile
Une implémentation simple de pile (LIFO - Dernier Entré, Premier Sorti) utilisée par d'autres modules.
* **Fonctions de base** : `creerPile`, `push` (ajouter un élément), `pop` (retirer un élément), `top` (consulter l'élément supérieur), `estVide` (vérifier si la pile est vide), et `SupprimerPile` (libérer la pile).
* **Utilisation** : Crucialement utilisée dans `AVR_Balise.c` pendant le processus `CompleterArbreBalise` pour gérer les clés lors de la création des feuilles de données. Également utilisée dans `application.c` pour stocker les résultats des recherches par intervalle.
* **Sortie** : `save_stack_to_file` peut écrire le contenu de la pile dans un fichier, utilisé pour `intervalValues.txt`.

### `application.c` - Logique Spécifique à l'Application
Fournit des fonctions qui utilisent l'arbre AVL balisé pour des opérations pratiques.
* **Génération de Données** : `random_double` et `generate_list` pour créer des listes de nombres aléatoires.
* **Création d'AVL Balisé** : `generate_AVL_B_from_list` prend une liste, construit un AVL standard, puis le convertit en un arbre AVL balisé en utilisant `versAbreBalise`.
* **Recherche par Intervalle (`find_values_in_range`)** :
    * C'est une application clé de l'arbre AVL balisé. Elle trouve toutes les valeurs dans un intervalle `[start, stop]` donné.
    * Elle utilise `find_limit_low` pour trouver un nœud interne proche de la valeur `stop`.
    * Ensuite, `find_limit_donnee` navigue probablement depuis ce nœud interne vers un nœud de données associé (feuille) qui marque une limite d'intervalle.
    * La fonction parcourt ensuite la liste chaînée de nœuds de données (balises), collectant les clés qui se trouvent dans l'intervalle `[start, stop]` et les empile sur une pile. Le parcours semble suivre les pointeurs `ne->donnee->donnee`, ce qui suggère que ces nœuds de données forment une structure de liste chaînée intégrée dans les feuilles de l'arbre.

### `file_handler.c` - Gestion des Entrées/Sorties de Fichiers
Gère la lecture et l'écriture de données dans des fichiers.
* `lire_doubles_fichier` : Lit un tableau de `double` depuis un fichier spécifié. Le format de fichier attendu est le nombre de `double` sur la première ligne, suivi de chaque `double` sur une nouvelle ligne.
* `enregistrer_liste` : Écrit un tableau de `double` dans un fichier dans le même format (nombre d'éléments en premier, puis les données). Ceci est utilisé pour enregistrer les listes d'entrée dans `points.txt`.

### `graphviz_handler.c` - Exportation Graphviz .dot
Génère des fichiers `.dot` pour visualiser les arbres avec Graphviz.
* `ExporterDot` et son assistant récursif `ExporterDotRec` parcourent l'arbre (AVL standard ou AVL balisé) et écrivent sa structure en langage DOT dans un fichier.
* Il distingue les nœuds internes (cercles) des nœuds de données/balises (boîtes, si `n->donnee != NULL` et que c'est une feuille en termes de structure AVL).
* Pour les arbres AVL balisés, il peut dessiner des lignes pointillées pour représenter les liens des nœuds internes vers leurs informations de "données" ou de "balise" si des conditions spécifiques sont remplies (par exemple, `n->donnee != NULL` lorsque `n->gauche` ou `n->droite` est NULL).
* La fonction utilise ensuite des appels `system` pour exécuter la commande `dot` de Graphviz afin de convertir le fichier `.dot` en une image `.png` et tente de l'afficher en utilisant `eog` (Eye of GNOME).

---

## 🛠️ Compilation et Exécution

(Vous ajouteriez typiquement les instructions de compilation ici, par exemple, en utilisant un Makefile)

Exemple :
```bash
gcc -o avl_program main.c AVR.c AVR_Balise.c pile.c application.c file_handler.c graphviz_handler.c -lm
./avl_program