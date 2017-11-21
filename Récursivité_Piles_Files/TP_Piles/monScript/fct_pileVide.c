#include <stdlib.h>
#include <stdio.h>
#include "fct_pileVide.h"

// initialise ou vide une pile
Pile pileVide() {
	Pile pile = (Pile)malloc(sizeof(struct _Pile));
	pile = NULL;
	return pile;
}

// Test si la pile est vide (renvoie false si non vide, true si vide)
int estPileVide(Pile pile) {
	if(pile == NULL) {
		return 1;
	} 
	else {
		return 0;	
	}
}

// Ajouter un element au sommet de la pile
Pile empiler(Pile pile, int donnee) {	
	Pile nouveau = (Pile)malloc(sizeof(struct _Pile)); // on crée un élément	
	
	if (nouveau == NULL) {
    	printf("%s", "Erreur");
		exit(0);
	}
	
	nouveau -> valeur = donnee; //On assigne 'donnée à 'nouveau'
	nouveau -> suivant = pile; //On fait pointer 'nouveau' sur le sommet de la pile
	pile = nouveau; //On fait pointer le sommet de la pile sur nouveau
	return pile;
}

// Supprime le dernier element de la pile
Pile depiler(Pile pile) {		
    if (estPileVide(pile)) {
    	printf("%s", "Erreur");
		exit(0);
	}
	Pile nvSommet = pile -> suivant;
	free(pile);
	return nvSommet;
}

// Retourne le dernier element de la pile
int getSommet(Pile pile) {	
	int sommet;
	if (estPileVide(pile)) {
		printf("%s", "Erreur");
		exit(0);
	}

	sommet = pile -> valeur;
	return sommet;
}

// Vide la pile en libérant la mémoire
void videPile(Pile pile) {	
    while (!estPileVide(pile)) {
        pile = depiler(pile);
    }
}

//Affiche la pile
void afficherPile(Pile pile) {

	while (pile -> suivant != NULL) {		
		printf("%d ", getSommet(pile));
		pile = pile -> suivant;
		/* bug : le bas de la pile ne s'affiche pas; En inversant les deux lignes
		du while,  c'est le sommet de la pile qui ne s'affiche pas */
	}
	printf("%d", getSommet(pile));

	printf("\n");
}
