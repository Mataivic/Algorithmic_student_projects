#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "automates_D.h"

// Définit un état d'un automate comme terminal
void mettreTerminal(pautomate A, etat e){
	A -> etatTerminal = e;
}

// Allocation mémoire de toutes les transitions d'un automate
ptransition* creer_transitions(int nbE){
	ptransition* tabListeTrans = (ptransition*)malloc((size_t)nbE * sizeof(struct transition));
	int i;
	for (i=0; i<nbE; i++) {
		tabListeTrans[i] = NULL;
	}
	return tabListeTrans;
}

// Ajoute une transition à un état d'un automate
void ajout_transition(ptransition* tabT, etat source, etat dest, char a){
	ptransition transi = (ptransition)malloc(sizeof(struct transition)); // allocation mémoire
	transi -> lettre = a;
	transi -> destination = dest;
	transi -> suivant = tabT[source]; // Ajout en tête
	tabT[source] = transi; // Actualisation tête de liste
}

// Supprime une transition
ptransition supprimer(ptransition transi, etat dest, char a) {    
    if (transi != NULL) {    	
        // Dans le cas ou l'element à supprimer est en tête. marche pas (pb de pointeur)
        if (transi -> lettre == a && transi -> destination == dest) {
            //transi = getSuivant(transi);
            transi = transi -> suivant;
        } else {
        	// Parcours de la liste jusqu'a l'element à supprimer
            ptransition tmp = transi; // Stockage de la tete de liste
            // Parcours de la liste jusqu'a la transition précédant la transition à supprimer            
            while (transi -> suivant -> lettre != a || transi -> suivant -> destination != dest) {    
                transi = getSuivant(transi);
            }                
            if (transi -> suivant -> suivant != NULL) { 
            	// Cas général           	
            	transi -> suivant = transi -> suivant -> suivant;
            } else {
            	// Dans le cas où l'élément à supprimer est en dernier. marche pas (pb de pointeur)           	
            	transi -> suivant = NULL;
            }
            // Retour sur la tete de file
            transi = tmp;
        }
    }
    return transi;
}

// Renvoie la destination d'une des transitions (de la lettre en paramètre) d'un état
etat destination (pautomate Aut, etat source, char a){
	etat destination = -1; // retourne -1 si la destination n'existe pas
	ptransition transi = Aut -> tabListeTrans[source];
	// Parcours de la liste des transitions de l'état source jusqu'à trouver la bonne lettre
	while (transi != NULL) {
		if (transi -> lettre == a) {
			destination = transi -> destination; // stocke la destination
			break;
		}
		transi = transi -> suivant;
	}
	return destination;
}

// Allocation mémoire d'un automate
// sans la taille de l'alphabet
pautomate nouvel_automate(void){
	pautomate Aut = (pautomate)malloc(sizeof(struct automate));	
	Aut -> etatInit = 0;	
	return Aut;	
}

//fonction qui crée l'automate reconnaissant le langage A*x pour l'alphabet A et un mot x
void creer_automate_mot(pautomate Aut, char* x, char* alphabet){	
	size_t len = strlen(x);
	Aut -> tailleAlpha = strlen(alphabet);	
	Aut -> nbetat = len+1;  // ensemble vide + longueur du mot ; compté à partir de 0, pas 1	
	Aut -> tabListeTrans = (ptransition*)malloc(len*sizeof(struct transition));  // Allocation mémoire des transitions	
	
	// Boucle 1 : etat 0 (mot vide), transitions 0 -> 0 pour chaque lettre de l'alphabet
	int i;
	for (i=0; i < Aut -> tailleAlpha; ++i) {		
		char lettre = alphabet[i];				
			ajout_transition(Aut -> tabListeTrans, 0, 0, lettre);
	}

	// Boucle 2 : transitions (état n, état n+1, mot[lettre courante])
	int t = 0; // etat courant
	int j;
	for (j=0; j < len ; ++j) {
		int p = t+1; // etat courant + 1
		etat r = destination(Aut, t, x[j]); // Récupère la destination état courant - lettre		
		Aut -> tabListeTrans[t] = supprimer(Aut -> tabListeTrans[t], r, x[j]);
		ajout_transition(Aut -> tabListeTrans, t, p, x[j]); // ajout de la transition de t qui pointe vers p		

		// Boucle 3 : transitions "vers l'arriere" apres calcul des bords		
		ptransition trans = Aut -> tabListeTrans[r];
		int num=0;
		while (trans != NULL){ //On parcourt le tableau de transitions			
			printf("%s %d\n", "Verif bug", num);
			num += 1;			
			ajout_transition(Aut->tabListeTrans, p, trans->destination, trans->lettre);						
			//Ajout de la position trans->destination pour la lettre trans->lettre
			trans = trans->suivant;			
		}
		
		t = p;
	}	
	
	mettreTerminal(Aut, t);	// dernier etat = etat terminal
}

int recherche_Mot_Auto(pautomate Aut, char* cible){
	//char* cible = lireFichier(texte_fichier);
	int len = (int)strlen(cible);
	if (len <= 200) { // Pour ne pas surcharger le terminal
		printf("\n%s%s\n", "    Cible de la recherche :", cible);
	} else {
		printf("\t%s\n", "n.b. : Pour plus de lisibilité, les fichiers cibles trop longs ne sont pas affichés");
	}
	int retour = -1; // -1 au lieu de 0 pour ne pas confondre aucune occurrence / occurrence en position 0
	int term = 0; // etat courant
	int i;	
	for (i=0; i < len; ++i) { // Parcours du mot
		// Automate parcouru tant qu'on atteint pas l'état terminal		
		term = destination(Aut, term, cible[i]); 
		if (term == Aut -> etatTerminal) {
			retour = i - Aut -> nbetat + 3; // itération - (longueur du mot+1) 
			break; // Arret à la première occurrence trouvée
		}		
	}	
	return retour;
}

/************* Fonctions Supplémentaires ***********************************************************/

// Affiche un automate
void affiche_automate(pautomate Aut, char* mot, char* alphabet){	
	printf("\n%s%s\n\n", "AUTOMATE RECONNAISSANT A*x du mot : ", mot);
	printf("    %s%s\n", "Alphabet : ", alphabet);
	printf("    %s%d\n", "Nombre d'états : ", Aut -> nbetat);
	printf("    %s%d\n", "Taille de l'alphabet : ", Aut -> tailleAlpha);
	printf("    %s%d\n", "Etat initial : ", Aut -> etatInit);
	printf("    %s%d\n", "Etat terminal : ", Aut -> etatTerminal);	
	printf("    %s\n", "Les transitions :");
	int i;
	// Boucle d'affichage des transitions de chaque état
	for (i=0; i < Aut -> nbetat; i++) {
		ptransition transi = Aut -> tabListeTrans[i];
		while (transi != NULL) {
			printf("\t%c%d%c %c%c %d%c\n", '(', i, ',', transi -> lettre, ',', transi -> destination, ')');
			transi = transi -> suivant;
		}
		printf("\n");
	}
}

// Lit un fichier texte et stocke son contenu dans une chaîne de caractères
char* lireFichier(char* filename){
	FILE* fichier = fopen(filename, "r");
	if (fichier != NULL) {

		fseek(fichier, 0, SEEK_END); // position en fin de fichier
		long l = ftell(fichier); // renvoie la longueur totale du fichier : nombre total de caractères
		fseek(fichier, 0, SEEK_SET); // position en début de fichier
		char* contenu = (char*)malloc((size_t)l); // la chaine où sera stocké le fichier
		char * chaine = (char*)malloc((size_t)l);
		if (contenu == NULL || chaine == NULL) return NULL;		
		
		//Concatène toutes les lignes lues dans le fichier, séparées par des espaces, tabulations ou retour à la ligne
		while(fscanf(fichier, "%s\n", chaine) != EOF || fscanf(fichier, "%s\t", chaine) != EOF || fscanf(fichier, "%s ", chaine) != EOF){
			strcat(contenu, chaine);
		}		
		free(chaine);
		//fclose(fichier); // cause un bug dans la boucle while de creer_automate_mot		
		return contenu;
	}else return NULL;
}

// Permet de passer à l'élément suivant d'une liste chaînée (liste de trnasitions)
ptransition getSuivant(ptransition tabTransi) {
    return tabTransi -> suivant;
}

// Vérifie la conformité du mot et du texte à l'alphabet
int gestionErreur(char* mot, char* texte, char* alphabet) {
	int okay = 1; // sert de booleen
	int i;	
	int lenm = (int)strlen(mot);
	int lent = (int)strlen(texte);
	// Parcours du mot recherché
	for (i=0; i < lenm; i++) {		
		if (strchr(alphabet, mot[i]) == NULL) {
			printf("\n%s\n", "Erreur : l'alphabet précisé ne correspond pas à celui du mot.");
			okay = 0;
			break; // Arret si lettre non conforme à l'alphabet
		}
	}
	// Parcours du texte ciblé
	for (i=0; i < lent; i++) {
		if (strchr(alphabet, texte[i]) == NULL) {
			printf("\n%s\n", "Erreur : l'alphabet précisé ne correspond pas à celui du texte.");
			okay = 0;
			break; // Arret si lettre non conforme à l'alphabet
		}
	}
	
	return okay;
}
