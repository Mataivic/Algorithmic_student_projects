#include <stdlib.h>
#include <stdio.h>
#include "graphe.h"
#include "files.h"

int estVideGraphe (Graphe g) {
	return (g == NULL);
}

// Cree sommet d'etiquette e, successeurs à NULL (allouer la memoire pour un sommet)
Sommet nouveauSommet(char *e) {
	Sommet newS = (Sommet)malloc(sizeof(struct _sommet));
	newS -> etiquette = e;
	newS -> successeurs = NULL;
	return newS;
}

Graphe nouveauGraphe(int n) {
	// Allocation graphe à n sommets	
	Graphe newG = (Graphe)malloc(sizeof(struct _graphe));
	newG -> nbSommets = n;
	// allocation de tableau de sommets
	newG -> t = (Sommet*)malloc((size_t)n*sizeof(Sommet));
	// appel n fois nouveauSommet(NULL)
	for (int i; i < n; ++i) {
		newG -> t[i] = nouveauSommet(NULL);
	}

	return newG;
}

int getNbSommets(Graphe g) {
	int nb = 0;
	if (!estVideGraphe(g)) {
		nb = g -> nbSommets;
		return nb;
	} else {
		printf("%s\n", "Le graphe est vide");
		return 0;
	}
}

Sommet getSommet(Graphe g, int k) {	
	Sommet som = g -> t[k];
	return som;
}

Liste getSuccesseurs(Sommet s) {
	Liste successeurs = s -> successeurs;
	return successeurs;
}

// Ajoute un arc s,v,d au graphe non vide g
void nouvelArc(Graphe g, int s, int d, float v) {
	g -> t[s] -> successeurs = ajoutEnTete(g -> t[s] ->successeurs, v, d);
}

void putEtiquette(Graphe g, int k, char* e ) {
	g -> t[k] -> etiquette = e;
}

char* getEtiquette(Graphe g, int k) {
	return g -> t[k] -> etiquette;
}

void visiteEnProfondeur(Graphe g, int s, int* marque) { // Pas bon : mauvais ordre
	
	marque[s] = 1;
	Liste a = g -> t[s] -> successeurs;
	//afficherListe(a);
	printf("%s ", getEtiquette(g, s));
	
	while (a !=NULL) {
		if (marque[getDestination(a)] == 0) {
			visiteEnProfondeur(g, getDestination(a), marque);	
		}
		a = getSuivant(a);
	}	
}

void parcoursEnProfondeur(Graphe g) { // OK
	
	// Marquage
	int* marque = (int*)malloc(((size_t)getNbSommets(g))*sizeof(int));
	for (int i=0; i < getNbSommets(g); i++) {
		marque[i] = 0;
	}
	
	// Visite en profondeur
	for (int i=0; i < getNbSommets(g); i++) {
		if ( marque[i] == 0) {
			visiteEnProfondeur(g, i, marque);
		}
	}	
}

void visiteEnLargeur (Graphe g, int s, int* marque, File f) {
	marque[s] = 1;
	f = enfiler(f, s);
	int x = 0;
	Liste a = g -> t[s] -> successeurs;

	while (!estFileVide(f)) {
		x = getDebut(f);
		f = defiler(f);
		printf("%s ", getEtiquette(g, x));

		while (a !=NULL) {
			if (marque[getDestination(a)] == 0) {
				marque[getDestination(a)] = 1;
				f = enfiler(f, getDestination(a));		
			}
			a = getSuivant(a);
		}	
	}
}

void parcoursEnLargeur (Graphe g) {
	File f = fileVide();

	// Marquage
	int* marque = (int*)malloc(((size_t)getNbSommets(g))*sizeof(int));
	for (int i=0; i < getNbSommets(g); i++) {
		marque[i] = 0;
	}

	// Visite en largeur
	for (int i=0; i < getNbSommets(g); i++) {
		if ( marque[i] == 0) {
			visiteEnLargeur(g, i, marque, f);
		}
	}
}