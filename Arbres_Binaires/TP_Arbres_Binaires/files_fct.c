#include <stdio.h>
#include <stdlib.h>
#include "files_fct.h"

// Renvoie une file vide
File fileVide() {
	return NULL;
}

// Test si la file est vide
int estFileVide(File file) {
	return file == NULL;
}

// Ajoute un élément en queue de file
File enfiler(File file, int x) {
    File nouveau = (File)malloc(sizeof(struct _File));
    File retour = (File)malloc(sizeof(struct _File));
     
    if (nouveau != NULL) {
        nouveau -> suivant = NULL;
        nouveau -> valeur = x;
        if (file == NULL) {
            retour = nouveau;
        } else {
            retour = file;
            while (file -> suivant != NULL) {
                file = file -> suivant;
            }
            file -> suivant = nouveau;
        }
    }
    return retour;
}

// Supprime l'élément en tête de file
File defiler(File file) {
	if (estFileVide(file)) {
    	printf("%s", "Erreur");
		exit(0);
	}

	File newTete = file -> suivant;
	free(file);
	return newTete;
}

// Renvoie l'élément en tête de file
int getDebut(File file) {
	int debut;
	if (estFileVide(file)) {
		printf("%s", "Erreur");
		exit(0);
	}

	debut = file -> valeur;
	return debut;
}

// Renvoie l'élément en queue de file
int getFin(File file) {
	while (file -> suivant != NULL) {		
		file = file -> suivant;	
	}

	int fin = file -> valeur;
	return fin;
}

// Renvoie la longueur de la file
int getLongueur(File file) {
	int longueur = 0;
	while (file -> suivant != NULL) {		
		file = file -> suivant;
		longueur += 1;
	}

	return longueur+1; 
	/* +1 car mal écrit : ne prend pas en compte le dernier élément 
	(même problème que pour afficherFile */
}

// Vide la file
void videFile(File file) {
	while (!estFileVide(file)) {
        file = defiler(file);
    }
}

// Affiche la file
void afficherFile(File file) {
	while (file -> suivant != NULL) {
		printf("%d ", getDebut(file));
		file = file -> suivant;			
	}
	printf("%d", getDebut(file)); 
	/* A améliorer. La boucle while ne prend pas en compte la queue de la file.
	Problème visible dans getLongueur() (besoin de 'return+1' au lieu de 'return')*/

	printf("\n");
}
