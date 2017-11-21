#include <stdio.h>
#include <stdlib.h>
#include "arbrebin.h"

/*
	TODO : 
		- Traiter les cas if(estArbreVide) dans les fonctions où ce n'est pas encore fait
		- Utiliser les fonctions gauche et droite au lieu de arbre -> gauche et arbre -> droite
		- Parcours en largeur
		- Tri par tas
*/

Parbre arbreVide() {
	return  NULL;
}

int estArbreVide(Parbre arbre) {
	if (arbre == NULL) {
		return 1;
	} else {
		return 0;
	}
	//on peut faire simplement return p==NULL;
}

int racine(Parbre arbre) {
	return arbre -> valeur;	
}

// Afficher la branche de tous les éléments les plus à gauche
void printGauche(Parbre arbre) {	
	while (arbre != NULL) {
		printf("%d ", arbre -> valeur);
		arbre = arbre -> gauche;
	}
}

// Affiche la branche de tous les éléments les plus à droite
void printDroite(Parbre arbre) {
	while (arbre != NULL) {
		printf("%d ", arbre -> valeur);
		arbre = arbre -> droite;
	}
}

// Fonctions pour éviter d'écrire arbre -> gauche et arbre -> droit tout le temps
Parbre gauche(Parbre arbre){
	Parbre res = NULL;
	if (!estArbreVide(arbre)) res = arbre -> gauche;
	return res;
}

Parbre droite(Parbre arbre){
	Parbre res = NULL;
	if (!estArbreVide(arbre)) res = arbre -> droite;
	return res;
}

// Pour construire un arbre binaire (PAS FORCEMENT DE RECHERCHE - Ne pas combiner avec la fonction insertion)
Parbre construire(int x, Parbre a, Parbre b) {
	Parbre arbre = (Parbre)malloc(sizeof(struct _Parbre));	
	arbre -> valeur = x;
	arbre -> gauche = a;
	arbre -> droite = b;	
	return arbre;
}

int max(int a, int b) {
	if (a >= b) {
		return a;
	} else {
		return b;
	}
}

// Ne fonctionnent pas avec des arbres null
int hauteur(Parbre arbre) {	
	
	if (estArbreVide(arbre -> gauche)) {
		if (estArbreVide(arbre -> droite)) {
			return 1;
		} else {			
			return 1 + hauteur(arbre -> droite);
		}
	} else if (estArbreVide(arbre -> droite)) {
		return 1 + hauteur(arbre -> gauche);
	} else {
		return 1 + max(hauteur(arbre -> gauche), hauteur(arbre -> droite));
	}	
}

int nbFeuilles(Parbre arbre) {	
	
	if (estArbreVide(arbre -> gauche)) {
		if (estArbreVide(arbre -> droite)) {
			return 1;
		} else {
			return nbFeuilles(arbre -> droite);
		}
	} else if (estArbreVide(arbre -> droite)) {
		return nbFeuilles(arbre -> gauche);
	} else {
		return nbFeuilles(arbre -> gauche) + nbFeuilles(arbre -> droite);
	}
	
}

// A corriger
int nbNoeudsInternes(Parbre arbre) {
	
	if (estArbreVide(arbre -> gauche)) 
	{
		if (estArbreVide(arbre -> droite)) {
			return 0;
		} else {
			return 1 + nbNoeudsInternes(arbre -> droite);
		}
	} else if (estArbreVide(arbre -> droite)) {
		return 1 + nbNoeudsInternes(arbre -> gauche);
	} else {
		return 1 + nbNoeudsInternes(arbre -> gauche) + nbNoeudsInternes(arbre -> droite);
	}	
}

int nbNoeuds(Parbre arbre) {	
	
	if (estArbreVide(arbre -> gauche)) {
		if (estArbreVide(arbre -> droite)) {
			return 1;
		} else {
			return 1 + nbNoeuds(arbre -> droite);
		}		
	} else if (estArbreVide(arbre -> droite)) {
		return 1 + nbNoeuds(arbre -> gauche);		
	} else {
		return 1 + nbNoeuds(arbre -> gauche) + nbNoeuds(arbre -> droite);
	}	
}

// Parcours préfixe
void parcoursPref(Parbre arbre) {
	if (!estArbreVide(arbre)) {		
		printf("%d ", racine(arbre));
		parcoursPref(arbre -> gauche);
		parcoursPref(arbre -> droite);
	}	
}

// Parcours suffixe, utile pour vérifier une insertion car affichage dans l'ordre croissant
void parcoursSuff(Parbre arbre) {
	if (!estArbreVide(arbre)) {		
		parcoursInf(arbre -> gauche);		
		parcoursInf(arbre -> droite);
		printf("%d ", racine(arbre));
	}	
}

// parcours infixe
void parcoursInf(Parbre arbre) {
	if (!estArbreVide(arbre)) {		
		parcoursInf(arbre -> gauche);
		printf("%d ", racine(arbre));		
		parcoursInf(arbre -> droite);		
	}	
}

// parcours en largeur
void parcoursLargeur(Parbre arbre) {

	File f = fileVide();
	if (!estArbreVide(arbre)) {
		f = enfiler(f, racine(arbre));
	}

	int x = 0;

	while(!estFileVide(f)) {
		x = getDebut(f);
		printf("%d ", x);
		f = defiler(f);

		if (!estArbreVide(gauche(arbre))) {
			f = enfiler(f, racine(gauche(arbre)));
		}

		if (!estArbreVide(droite(arbre))) {
			f = enfiler(f, racine(droite(arbre)));
		}
	}
	
}

// Pour construire un arbre binaire de recherche
Parbre insertion(int x, Parbre arbre) {
	if (!estArbreVide(arbre)) {

		if (x == arbre -> valeur) {
			printf("%d%s\n", x, " est déjà présent dans l'arbre");
			return arbre;
		}

		if (x < arbre -> valeur) {
			arbre -> gauche = insertion(x, arbre -> gauche);
		} else if (x > arbre -> valeur) {
			arbre -> droite = insertion(x, arbre -> droite);
		}
	} else {
		return construire(x, NULL, NULL);
	}
	return arbre;
}

// booleen : renvoie 1 si le nombre est présent
int recherche (int x, Parbre arbre) {
	int i =0;
	if (!estArbreVide(arbre)) {
		if (arbre -> valeur == x) {
			i = 1;
		} else {
			if (x < racine(arbre)) i = recherche(x, arbre -> gauche);
			if (x > racine(arbre)) i = recherche(x, arbre -> droite);
		}
	} else { 
		i = 0;
	}
	return i;
}

// Retourne l'élément maximum d'un arbre (noeud tout à droite) : utilisé dans suppression racine
int elementMax(Parbre arbre) {
	int max = 0;
	while (arbre != NULL) {
		max = arbre -> valeur;
		arbre = arbre -> droite;
	}
	return max;
}

// Juste pour tester : renvoie la valeur minimum d'un arbre (noeud tout à gauche)
int elementMin(Parbre arbre) {
	int min = 0;
	while (arbre != NULL) {
		min = arbre -> valeur;
		arbre = arbre -> gauche;
	}
	return min;
}

// Mieux sans utiliser arbreRetour
Parbre suppressionMax(Parbre arbre){
	if(estArbreVide(arbre -> droite)) {
		arbre = arbre -> gauche;
	} else { // J'ai du mal à comprendre comment marche la récursion ici
		arbre -> droite = suppressionMax(arbre -> droite);
	}
	return arbre;
}

Parbre suppressionRacine (Parbre arbre) {
	Parbre arbreRetour = NULL;
	if (estArbreVide(arbre)) {
		arbreRetour = arbre;
	} else if(estArbreVide(arbre -> droite)) {
		arbreRetour = arbre -> gauche;		
	} else { // J'ai du mal à comprendre comment marche la récursion ici
		int max = elementMax(arbre -> gauche);		
		arbreRetour = construire(max, suppressionRacine(arbre -> gauche), arbre -> droite);
	} 

	return arbreRetour;
}

// si x = racine : on appelle suppressionRacine, sinon on fait récursivement à droite ou à gauche
Parbre suppression(int x, Parbre arbre) {
	Parbre arbreRetour = NULL;

	if (estArbreVide(arbre)) {
		arbreRetour = arbre;
	} else if (x == racine(arbre)) {
		arbreRetour = suppressionRacine(arbre);	
	} else if (x < racine(arbre)) {
		arbreRetour = construire(racine(arbre), suppression(x, arbre -> gauche), arbre -> droite);		
	} else if (x > racine(arbre)) {
		arbreRetour = construire(racine(arbre), arbre -> gauche, suppression(x, arbre -> droite));		
	}

	return arbreRetour;	
}
