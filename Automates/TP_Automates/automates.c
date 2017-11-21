#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "automates.h"

// Crée le tableau des états et les initialise comme non terminaux
int* creer_estTerminal(int nbE) {
	ensemble tableau = (ensemble)calloc((size_t)nbE, sizeof(int));
	return tableau;
}

// Détermine un état comme étant terminal
void mettreTerminal(int* estT, etat e) {
	estT[e] = 1;
}

// Crée et retourne un tableau de transitions de taille nbE
ptransition* creer_transitions(int nbE) {
	ptransition* tabListeTrans = (ptransition*)malloc((size_t)nbE * sizeof(struct transition));
	return tabListeTrans;
}

// Ajouter la transition à l'automate
void ajout_transition(ptransition* tabT, etat source, etat dest, char a) {
	ptransition transi = (ptransition)malloc(sizeof(struct transition));
	transi -> lettre = a;
	transi -> destination = dest;
	transi -> suivant = tabT[source];
	tabT[source] = transi;
}

pautomate allouer_automate() {
	pautomate new = (pautomate)malloc(sizeof(struct _automate));
	return new;
}

void init_automate(pautomate A, FILE *fauto) {	
	int nbTerm;
	
	if (fauto != NULL) {
		// Lecture de la taille de l'alphabet
		fscanf(fauto, "%d", &(A -> tailleAlpha));
		// Lecture du nombre d'états
		fscanf(fauto, "%d", &(A -> nbEtats));
		// Lecture de l'état initial
		fscanf(fauto, "%d", &(A -> etatInit));
		// Lecture du nombre et des positions des états terminaux
		A -> estTerminal = (ensemble)malloc((size_t)(A -> nbEtats)* sizeof(ensemble));
		fscanf(fauto, "%d", &nbTerm);		
		int f;
		for (int i=0; i < nbTerm; ++i) {		
			fscanf(fauto, "%d", &f);			
			mettreTerminal(A -> estTerminal, f);
		}	

		// Lecture des transitions		
		A -> tabListeTrans = creer_transitions(A -> nbEtats);		
		etat origine;
		char lettre;
		etat dest;
		while((fscanf(fauto, "%d %c %d", &origine, &lettre, &dest)) != EOF) {			
			ajout_transition(A -> tabListeTrans, origine, dest, lettre);
		}        
		fclose(fauto);
    } else {
        printf("Impossible d'ouvrir le fichier");
    }	
}

pautomate creer_init_automate(char* nomFichier) {
	FILE *f = fopen(nomFichier, "r");
	pautomate A = allouer_automate();
	init_automate(A,f);
	return A;
}

void affiche_automate(pautomate automate) {
	printf("%s%d\n", "Nombre d'états : ", automate -> nbEtats);
	printf("%s%d\n", "Taille de l'alphabet : ", automate -> tailleAlpha);
	printf("%s%d\n", "Etat initial : ", automate -> etatInit);
	printf("%s\n", "Etats terminaux : ");
	for(int i=0; i < automate -> nbEtats; i++) {
		if (automate -> estTerminal[i] == 1) {
			printf("%d%s", i, " - ");
		}
	}
	printf("\n%s\n", "Les transitions :");
	for (int i=0; i < automate -> nbEtats; i++) {
		ptransition transi = automate -> tabListeTrans[i];
		while (transi != NULL) {
			printf("%c%d%c %c%c %d%c\n", '(', i, ',', transi -> lettre, ',', transi -> destination, ')');
			transi = transi -> suivant;
		}
	}
}

// Retourne l'état de destinattion pour l'état de départ et la lettre en paramètres
etat destination (pautomate Aut, etat source, char a) {
	etat destination = -1;
	ptransition transi = Aut -> tabListeTrans[source];	
	while (transi != NULL) {
		if (transi -> lettre == a) {
			destination = transi -> destination;
			break;
		}
		transi = transi -> suivant;
	}
	return destination;
}

int estReconnu(pautomate A, char* mot) {
	int retour = 0;
	int len = (int)strlen(mot);
	int term =0;	
	int i=0;
	while (destination(A, term, mot[i]) != -1) {
		term = destination(A, term, mot[i]);
		i++;
	}	
	if (i == len && A -> estTerminal[term] == 1) {
		retour = 1;
	}
	
	return retour;
}

