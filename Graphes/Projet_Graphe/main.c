#include <stdlib.h>
#include "graphes-chevauchement.h"

// Algorithme de construction d'un graphe de chevauchement 

// entree : nomf, nom d'un fichier texte contenant des fragments d'ADN
// sortie : G, le graphe de chevauchement 

int main(int argc, char *argv[]) {

    printf("\n%s\n", "********** Assemblage de fragments d'ADN par un arbre de chevauchement :**********");
    //declarations de variables
    
    // un graphe
    GRAPHE G=NULL;
    // une liste de chaines de caracteres
    LISTE_frag S = NULL;  

    // le nom du fichier est un parametre lu sur la ligne de commande
    char *nomf = argv[1];

    // initialisation de S a partir du contenu de nomf  
    S = initListeFragments(S, nomf);      // initListeFragments(S, nomf);
    printf("\n%s\n", "    - Liste des fragments :");
    printFrags(S);

    // on enleve de S les fragments internes a d'autres fragments  
    S = fsd(S);    
    printf("\n%s\n", "    - Liste des fragments après suppression des facteurs :");
    printFrags(S);

    // on construit le graphe de chevauchement G a partir de S
    G = construitGrapheChevauchement(G, S);
    printf("\n%s\n", "    - Création du graphe de chevauchement ...");   

    // Visualisation de chaque sommet et de son fragment attache
    printf("\n%s\n", "        Fragment à chaque sommet :");
    for (int i=0; i<getNbSommets(G); ++i) {
        printf("%s%d%s%s\n", "            Sommet ", i, " : ", G -> t[i] -> fragment);
    }

    // Visualisation des successeurs
    printf("\n%s\n", "        Successeurs de chaque sommet :");
    for (int i=0; i<getNbSommets(G); ++i) {
        printf("%s%d%s\n", "            Sommet ", i, " : ");
        printArc(G -> t[i] -> successeurs);
    }    

    // on parcourt G en profondeur et on affiche sur la sortie l'ordre de parcours sur les sommets
    printf("\n%s\n", "    - Parcours en profondeur du graphe de chevauchement :");    
    parcoursEnProfondeur(G);
    printf("\n%s\n", "    *********************************************************************************");

	/********************** Suppléments *************************************************/

    printf("\n%s\n","    - SUPPLEMENT : essai pour trouver le chemin qui permet d'assembler les fragments.");
    printf("\n%s\n","        (Détails dans le fichier README).");   

    printf("\n%s\n", "        - Tri decroissant des listes de sommets ...");
   
    for (int i=0; i<getNbSommets(G); ++i) {        
        G -> t[i] -> successeurs = triDecroissant(G -> t[i] -> successeurs);
    } 
/*
    printf("\n%s\n", "        Successeurs Triés de chaque sommet :");
    for (int i=0; i<getNbSommets(G); ++i) {
        printf("%s%d%s\n", "            Sommet ", i, " : ");
        printArc(G -> t[i] -> successeurs);
    }
*/
    printf("\n%s\n", "    - Parcours en profondeur actualisé :");
    parcoursEnProfondeur(G);    

    printf("\n%s\n\n", "*************************** Fin du programme *********************************");

    return EXIT_SUCCESS;
}
