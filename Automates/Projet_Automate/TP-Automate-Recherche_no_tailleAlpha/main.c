// main.c pour atuomate A*x

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>


#include "automates_D.h"


int main(int argc, char **argv) {	
	pautomate autom;
	int position;

	//le programme principal prend en paramètres 3 arguments :	
	//le mot : argv[1]
	//le fichier contenant le texte : argv[2]
	//le fichier contenant l'alphabet : argv[3]

	/******* Lecture des fichiers *******/

	printf("\n%s\n", "***********************************************");
	printf("%s\n", "Lecture du texte cible...");
	char* texte = lireFichier(argv[2]);	
	printf("%s\n", "Lecture de l'alphabet...");
	char* alphabet = lireFichier(argv[3]);	
	
	// Verifie si les fichiers ont bien ete mis en memoire
	if (texte == NULL || alphabet == NULL) { 
		printf("\n%s\n", "Erreur lors de la lecture des fichiers");
		exit(0);
	}

	// Verifie la conformite alphabet/texte/mot	
	int verifAlpha = gestionErreur(argv[1], texte, alphabet); 
	if(argc != 4 || verifAlpha ==0) exit(0);

	/******* Création de l'automate *******/

	printf("%s\n", "Création de l'automate...");
	autom=nouvel_automate();		
	creer_automate_mot(autom, argv[1], alphabet); // argv[3] : l'alpabet, commun au mot et au texte
	
	printf("\n%s\n", "***********************************************");

	/******* Affichage de l'automate *******/
	// Limite : 200 etats (les automates trop gros peuvent faire planter le programme lors de l'affichage)
	if (autom -> nbetat <= 200) {
		affiche_automate(autom, argv[1], alphabet);
	} else {
		printf("%s\n", "n.b : les automates de plus de 200 états ne sont pas affichés");
	}

	/******* Recherche de la premiere occurrence du mot *******/

	position=recherche_Mot_Auto(autom, texte);

	printf("%s%d\n", "    Première occurence du mot recherché : ", position);
	printf("\t%s\n", "n.b : '-1' signifie que le mot n'est présent dans le texte ciblé.");
	printf("\n%s\n\n", "***********************************************");
	
	return 0;
}
