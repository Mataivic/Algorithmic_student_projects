#include <stdlib.h>
#include <stdio.h>
#include "arbrebin.h"

int main(void) {

	Parbre A = arbreVide();	
	// Test estArbreVide
	if (estArbreVide(A)) printf("%s\n", "A est vide.");	

	Parbre D = construire(9, NULL, NULL);
	printf("%d\n", estArbreVide(D));

	D = insertion(10, D);
	D = insertion(14, D);
	D = insertion(11, D);
	D = insertion(6, D);
	D = insertion(3, D);
	D = insertion(15, D);

	// Test divers
	int r = racine(D);
	printf("%s%d\n", "Racine de D: ", r);
	int h = hauteur(D);
	printf("%s", "hauteur de D: ");
	printf("%d\n", h);
	int f = nbFeuilles(D);
	printf("%s", "nbFeuilles de D: ");
	printf("%d\n", f);
	int ni = nbNoeudsInternes(D);
	printf("%s", "nbNoeudsInternes de D: ");
	printf("%d\n", ni);
	int n = nbNoeuds(D);
	printf("%s", "nbNoeuds de D: ");
	printf("%d\n", n);

	// Test de recherche
	printf("%s", "Recherche de 9 dans D : ");
	printf("%d\n", recherche(9, D));
	printf("%s", "Recherche de 10 dans D : ");
	printf("%d\n", recherche(10, D));
	printf("%s", "Recherche de 6 dans D : ");
	printf("%d\n", recherche(6, D));
	printf("%s", "Recherche de 3 dans D : ");
	printf("%d\n", recherche(3, D));
	printf("%s", "Recherche de 11 dans D : ");
	printf("%d\n", recherche(11, D));
	printf("%s", "Recherche de 14 dans D : ");
	printf("%d\n", recherche(14, D));
	printf("%s", "Recherche de 15 dans D : ");
	printf("%d\n", recherche(15, D));	
	printf("%s", "Recherche de 23 dans D : ");
	printf("%d\n", recherche(23, D));
	printf("%s", "Recherche de 1 dans D : ");
	printf("%d\n", recherche(1, D));


	printf("%s", "Branche tout à gauche : ");
	printGauche(D);
	printf("\n");
	printf("%s", "Branche tout à droite : ");
	printDroite(D);
	printf("\n");	
	Parbre D1 = gauche(D);
	Parbre D2 = droite(D);
	printf("%s", "Arbre gauche : ");
	parcoursPref(D1);
	printf("\n");
	printf("%s", "Arbre droit : ");
	parcoursPref(D2);
	printf("\n");
	// Test des parcours
	printf("%s", "Parcours préfixe de D : ");
	parcoursPref(D);
	printf("\n");
	printf("%s", "Parcours infixe de D : ");
	parcoursInf(D);
	printf("\n");
	printf("%s", "Parcours suffixe de D : ");
	parcoursSuff(D);
	printf("\n");
	/*
	printf("%s", "parcours en largeur de D : ");
	parcoursLargeur(D);
	printf("\n");
	*/

	printf("%s", "Maximum de D : ");
	printf("%d\n", elementMax(D));
	printf("%s", "Minimum de D : ");
	printf("%d\n", elementMin(D));

	printf("%s\n", "Suppression du maximum...");
	D = suppressionMax(D);
	
	printf("%s", "Suppresion de 6, ");
	D = suppression(6, D);
	printf("%s\n", "suppression de 14...");
	D = suppression(14, D);	
	printf("%s\n", "Suppression de la racine et construction d'un nouvel arbre...");
	D = suppressionRacine(D);

	printf("%s", "Parcours préfixe de D : ");
	parcoursPref(D);
	printf("\n");
	printf("%s", "Parcours infixe de D : ");
	parcoursInf(D);
	printf("\n");
	printf("%s", "Parcours suffixe de D : ");
	parcoursSuff(D);
	printf("\n");


	return EXIT_SUCCESS;
}
