#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "graphes-chevauchement.h"

// Les fonctions
// les commentaires sont ecrits sans accents pour eviter les problemes d'encodage

char* getFragment(Sommet s){
	return s -> fragment; 
}

// void fsd(LISTE_frag S
LISTE_frag fsd(LISTE_frag S){    
    if (S != NULL) {
        if (lenListe(S) == 2) {     // Si la liste ne contiend que deux fragments
            if (strstr(S -> frag, S -> suivant -> frag) != NULL) {
                S = supprimer(S, S -> suivant -> frag);
            } else if (strstr(S -> suivant -> frag, S -> frag) != NULL) {
                S = supprimer(S, S -> frag);
            }
        } else { // Cas général
            LISTE_frag temp1 = S;            
            while (temp1 -> suivant != NULL) {       // Parcours du premier de S jusqu'à l'avant-dernier de S
                LISTE_frag temp2 = getSuivant(temp1);   // Marche aussi pour les fichiers de une seule séquence (temp2=NULL direct)
                while (temp2 != NULL) {      // Parcours du deuxième de S jusqu'au dernier de S
                    // Suppression des fragments contenus dans d'autres :                
                    if (strstr(temp1 -> frag, temp2 -> frag) != NULL) {     // La chaine de temp2 est contenue dans temp1
                        S = supprimer(S, temp2 -> frag);                                                    
                        temp1 = S;                            
                        temp2 = getSuivant(S);                        
                    } else if (strstr(temp2 -> frag, temp1 -> frag) != NULL) {      // La chaine de temp1 est contenue dans temp2               
                        S = supprimer(S, temp1 -> frag);                                                                   
                        temp1 = S;                    
                        temp2 = getSuivant(S);
                    }
                    temp2 = getSuivant(temp2);                    
                }
                temp1 = getSuivant(temp1);
            }
        }    
    }
    return S; 
}

int lplc(char* x, char* y) {
    // Determine la longueur sur laquelle boucler
    int lx = (int)strlen(x);    

    int lplc = 0;
    int j =0;
    
    for (int i=lx-1; i >= 0 ; --i) {
        char* s1 = sousChaine(x, i, lx-1);      // Extraction des suffixes de x
        char* s2 = sousChaine(y, 0, j);         // Extraction des prefixes de y        
        j += 1;
        if (strcmp(s1, s2) == 0) {
            lplc = (int)strlen(s1);     // Si suffixe(s1)=prefixe(s2), lplc est egal a la longueur de s1 (ou s2)
        }
    }
    return lplc;
}

// Retourne une liste chainee de fragments d'ADN, lus a partir d'un fichier
LISTE_frag initListeFragments(LISTE_frag S, char *nomf) {
    FILE* fichier = fopen(nomf, "r");       // Ouverture du fichier de fragment    
    if (fichier != NULL) {
        char* fragTemp = (char*)malloc(100*sizeof(char));   // Declaration d'une chaine de caractere de taille 100
        while (fscanf(fichier,"%s\n",fragTemp) != EOF) {    // fragTemp contiend la ligne lue
            size_t taille = strlen(fragTemp);
            char* fragNew = (char*)malloc(taille*sizeof(char));     // Allocation memoire selon la taille de fragTemp
            fragNew = strncpy(fragNew, fragTemp, taille);
            S = inserer(S, fragNew);    // Insertion dans la liste de fragments.
            // Se fait en tete de liste : le dernier fragment du fichier test se retrouve en tete de liste
        }
        free(fragTemp);
        fclose(fichier);        // Fermeture du fichier
    }
    return S;
}

GRAPHE construitGrapheChevauchement(GRAPHE G, LISTE_frag S) {   
    // Initialisation de G    
    G = nouveauGraphe(lenListe(S));    

    // Remplissage des sommets de G
    int numSom = 0;
    while (S != NULL) {
        G ->t[numSom] = nouveauSommet(S -> frag); // Ajout en tête : le dernier fragment du fichier est en premier !
        G -> t[0] -> successeurs = NULL;
        S = getSuivant(S);
        numSom += 1;
    }

    // Ajout des arcs - les insertions d'arcs se font en tête.
    // Si on affiche les successeurs d'un sommet, ils apparaissent donc par ordre decroissant de numero de sommet
    for (int i=0; i < getNbSommets(G)-1; ++i) {
        for (int j=i+1; j < getNbSommets(G); ++j) {
            // Comparaison des suffixes et prefixes            
            int chev = lplc(getFragment(G -> t[i]), getFragment(G -> t[j]));                    
            if (chev != 0) {                
                G -> t[i] -> successeurs = insererArc(G -> t[i] -> successeurs, chev, j);       // Cree arc. i vers j
            }
            int chev2 = lplc(getFragment(G -> t[j]), getFragment(G -> t[i]));            
            if (chev2 != 0) {
                G -> t[j] -> successeurs = insererArc(G -> t[j] -> successeurs, chev2, i);      // Cree un arc. j vers i
            }            
        }
    }
    return G;   
}

// Parcours un graphe en profondeur et affiche ses sommets à l'ecran
void parcoursEnProfondeur(GRAPHE G) {   
    int *marque = (int*)calloc(((size_t)getNbSommets(G)), sizeof(int));     // Tableau d'entiers de taille nbSommet(G), rempli de 0
	for (int i = 0; i < getNbSommets(G); i++) {
		if ( marque[i] == 0) {
			visiteEnProfondeur(G, i, marque);        // Si l'entier en position i == 0, appel de visiteEnProfondeur sur le sommet en position i
		}
	}    
}

/* ----------- FONCTIONS SUPPLEMENTAIRES ----------- */

/********************** Utilisee dans parcoursEnProfondeur *****************************/

void visiteEnProfondeur(GRAPHE g, int s, int* marque) {    
	marque[s] = 1;     // Le sommet est marque : il ne sera plus visite par la suite
    printf("        %s %d %s%s\n", "Sommet ", s, " - ", getFragment(g -> t[s]));     // Affichage du fragment porte par le sommet
    LISTE_arc tmp = g -> t[s] -> successeurs;   // Travail sur une copie de la liste de successeurs, pour ne pas modifier le pointeur "principal"
	while (tmp !=NULL) {      
		int dest = tmp -> destination;       // Recupere le sommet de destination
        if (marque[dest] == 0) {     // Si le sommet n'est pas marque
			visiteEnProfondeur(g, dest, marque);        // Appel recursif
		}
        tmp = getSuivantArc(tmp);
	}
}

// Retourne le nombre de sommets d'un graphe
int getNbSommets(GRAPHE g) {
    int nb = 0;
    if (!estVideGraphe(g)) nb = g -> nbSommets;        
    else printf("%s\n", "Le graphe est vide");
    return nb;    
}

// Teste si un graphe est vide
int estVideGraphe (GRAPHE g) {
    return (g == NULL);
}

/********************** Utilisee dans fsd **********************************************/
// Supprime un fragment d'une liste de fragment.
LISTE_frag supprimer(LISTE_frag S, char* unFrag) {    
    if (S != NULL) {
        if (strcmp(S -> frag, unFrag) == 0) {        // Dans le cas ou l'element à supprimer est en tête            
            S = getSuivant(S);
        } else {        // Parcours de la liste jusqu'a l'element à supprimer
            LISTE_frag tmp = S;     // Stockage de la tete de liste
            while (strcmp(S -> suivant -> frag, unFrag) != 0) {     // Parcours de la liste jusqu'a l'element qui porte le fragment en parametre            
                S = getSuivant(S);
            }
            // TODO : si le suivant -> suivant est NULL, ça fait segmentation fault, c'est pas mis automatiquement
            if (S -> suivant -> suivant != NULL) {
            	S -> suivant = S -> suivant -> suivant;     // Le precedent de l'element a supprimer pointe sur le suivant de l'element a supprimer
            } else {
            	S -> suivant = NULL;	// Dans le cas où l'élément à supprimer est en dernier
            }
            S = tmp;        // Retour sur la tete de file
        }
    }
    return S;
}

/***************************************************** Utilisee dans lplc *******************************************************/

// Extrait la sous-chaîne chaine[start:end] d'une chaine de caracteres
// N'est pas parametree pour gerer les erreurs end < start
char* sousChaine(char* chaine, int start, int end) {
    char* sousChaine = NULL;

    int len = end - start + 1;      // Determine la taille de l'allocation memoire
    sousChaine = (char*)malloc((size_t)len * sizeof(char));

    int i;
    for (i = start; i <= end; ++i) {
        sousChaine[i-start] = chaine[i];        // Ajout des caracteres
    }
    sousChaine[i-start] = '\0';

    return sousChaine;
}

/*********************************************** Utilites diverses *************************************************************/

// Retourne l'element suivant d'une liste chainee de fragments
LISTE_frag getSuivant(LISTE_frag liste) {
    return liste -> suivant;
}

// Retourne l'element suivant d'une liste chainee d'arcs
LISTE_arc getSuivantArc(LISTE_arc liste) {
    return liste -> suivant;
}

// Renvoie la longueur d'une liste chainee
int lenListe(LISTE_frag S) {
    int len = 0;
    if (S != NULL) {
        while(S != NULL) {
            S = getSuivant(S);
            len += 1;       // Compteur incremente de 1 à chaque iteration d'un element
        }
    }
    return len;
}

// Affihe une liste de fragments
void printFrags(LISTE_frag S) {
    if (S != NULL) {
        while (S != NULL) {
            // Formatage pour un affichage propre en console
            printf("        %s\n", S -> frag);
            S = getSuivant(S);
        }
    }
}

// Affiche une liste d'arcs
void printArc(LISTE_arc A) {
    if (A != NULL) {
        while (A != NULL) {
            // Formatage pour un affichage propre en console
            printf("                %s%d%s%d\n", "Poids ", A -> poids, ", destination ", A -> destination);
            A = getSuivantArc(A);
        }
    }
}

/*
Les fonctions ci-dessous suivent le même principe:
    - Allcoation mémoire de la nouvelle structure
    - Initialisation des variables de la structure 
*/

// Insere un fragment en tete d'une liste de fragments
LISTE_frag inserer(LISTE_frag S, char* k) {
    LISTE_frag e = (LISTE_frag)malloc(sizeof(struct fragment));
    e -> frag = k;
    e -> suivant = S; 
    return e;
}

// Insere un arc (type 'element') en tete d'une liste d'arcs
LISTE_arc insererArc(LISTE_arc A, int pds, int dest) {
    LISTE_arc Abis = (LISTE_arc)malloc(sizeof(struct ELEMENT));
    Abis -> poids = pds;
    Abis -> destination = dest;
    Abis -> suivant = A;
    return Abis;
}

// Cree un nouveau sommet
Sommet nouveauSommet(char *e) {
    Sommet newS = (Sommet)malloc(sizeof(struct _sommet));
    newS -> fragment = e;
    newS -> successeurs = NULL;
    return newS;
}

// Cree un nouveau graphe
GRAPHE nouveauGraphe(int n) {
    GRAPHE G = (GRAPHE)malloc(sizeof(struct _GRAPHE));
    G -> nbSommets = n;
    G -> t = (Sommet*)malloc(n* sizeof(struct _sommet));
    return G;
}

/************************** Suppléments pour un parcours en profondeur optimal *************************************************/

LISTE_arc triDecroissant(LISTE_arc A) {
    if (A != NULL) {
        LISTE_arc tmp = A;
        int boo = 1;
        while (A -> suivant != NULL ) {
            if (A -> poids < A -> suivant -> poids) {
                echangerElement(A, A -> suivant); // Echange de deux éléments voisins qui ne sont pas dans le bon ordre            
                boo = 0;
            }
            A = getSuivantArc(A);
        }
        A = tmp;
        if (boo == 0) {		// Si boo == 1 : aucun échange n'a été fait, donc la liste est triée ; pas besoin d'appel récursif
            A = triDecroissant(A); // Appel récursif
        }
    }
    return A;
}

void echangerElement(LISTE_arc A, LISTE_arc B) {
    int pdsTmp = A -> poids;
    int destTmp = A -> destination;
    // Echange des poids et destination, sans toucher aux pointeurs
    A -> poids = B -> poids;
    A -> destination = B -> destination;
    B -> poids = pdsTmp;
    B -> destination = destTmp;
}
