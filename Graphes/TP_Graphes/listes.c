#include <stdlib.h>
#include <stdio.h>
#include "listes.h"

Liste listeVide() {
	Liste liste = NULL;
	return liste;
}

int estListeVide(Liste liste) {
	return (liste == NULL);
}

// retourne la valuation du premier maillon d'une liste non vide
float getValuation(Liste liste) {
	return liste -> valuation;
}

// retourne la destination du premier maillon d'une liste non vide
int getDestination(Liste liste) {
	return liste -> destination;
}

// retourne le suivant du premier maillon d'une liste non vide
Liste getSuivant(Liste liste) {
	return liste -> suivant;
}

// retourne la liste avec un nouveau maillon en tete de valuation v et de destination d
Liste ajoutEnTete(Liste liste, float value, int dest) {
	Liste nouveau = (Liste)malloc(sizeof(struct _liste)); // on crée un élément	
	
	if (nouveau == NULL) {
    	printf("%s", "Erreur");
		exit(0);
	}
	
	nouveau -> valuation = value; //On assigne 'donnée à 'nouveau'
	nouveau -> destination = dest;
	nouveau -> suivant = liste; //On fait pointer 'nouveau' sur le sommet de la pile
	liste = nouveau; //On fait pointer le sommet de la pile sur nouveau
	return liste;
}

void afficherListe(Liste l) {
	while (l -> suivant != NULL) {
		printf("%d ", getDestination(l));
		l = l -> suivant;			
	}
	printf("%d", getDestination(l)); 
	/* A améliorer. La boucle while ne prend pas en compte la queue de la liste.
	Problème visible dans getLongueur() (besoin de 'return+1' au lieu de 'return')*/

	printf("\n");
}
