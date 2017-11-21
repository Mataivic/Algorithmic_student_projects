#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mots.h"

int main(int argc, char *argv[]) {

	if (argc == 3) {

		/******* Lecture du fichier *******/

		char* mot = argv[2];
		char* texte = (char*)malloc(1000*sizeof(char));

		FILE* fichier = fopen(argv[1], "r");
		while (fscanf(fichier, "%s\n", texte) != EOF) {
			size_t taille = strlen(texte);
			texte = (char*)realloc(texte, taille);
		}

		/******* Longueurs *******/
		int lM = (int)strlen(mot);
		int lT = (int)strlen(texte);

		/******* Vérifs *******/

		printf("%s\n", "Texte :");
		printf("%s\n", texte);
		printf("%s\n", "Mot recherché :");
		printf("%s\n", mot);

		// Naif
		printf("%d\n", naif(mot, texte, lM, lT));

		// Morris et Pratt
		int* bonpref = bonPref(mot, lM);
		for (int i=0; i <= lM; ++i) {
			printf("%d ", bonpref[i]);
		}	
		printf("\n");
		printf("%d\n", morrisPratt(mot, texte, lM, lT, bonpref));

		// KMP
		int* meilpref = meilPref(mot, lM);
		for (int i=0; i <= lM; ++i) {
			printf("%d ", meilpref[i]);
		}
		printf("\n");
		printf("%d\n", KMP(mot, texte, lM, lT, meilpref));

	} else {
		printf("%s\n", "Il n'y a pas assez d'arguments");		
	}

	return EXIT_SUCCESS;
}