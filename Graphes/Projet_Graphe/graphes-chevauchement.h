#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Construction d'un graphe de chevauchement G = (S, A)
// a partir d'un fichier contenant des fragments d'ADN


// G est un graphe oriente pondere represente par listes d'adjacence 
// un fragment d'ADN est attaché à un sommet
// Il existe un arc de x vers y si il existe un suffixe non vide du fragment attaché à x
// qui est un prefixe du fragment attaché à y


// definition des types

// definition du type arc
typedef struct ELEMENT {
  int poids; //poids des arcs
  int destination; // numero du sommet de destination
  struct ELEMENT *suivant;
} ELEMENT;

// definition du type LISTE_arc
typedef ELEMENT *LISTE_arc ;

//definition du type sommet 
struct _sommet {
   char *fragment;   // le fragment attache au sommet
   LISTE_arc successeurs; // une liste de successeurs
};

// le type pointeur sur _sommet
typedef struct _sommet *Sommet;


// definition du type graphe pondere
typedef struct _GRAPHE {
   int nbSommets; //  nombre de sommets du graphe
   Sommet *t;     // un tableau de sommets indicé de 0 à nbSommets-1
} _GRAPHE;

// le type pointeur sur _GRAPHE
typedef struct _GRAPHE *GRAPHE;


// definition du type fragment
typedef struct fragment {
  char* frag;
  struct fragment *suivant;
} fragment;

// definition du type liste_frag
typedef fragment* LISTE_frag ;


// prototypes des fonctions

// getFragment(s) retourne le fragment attache au sommet s
char* getFragment(Sommet s);


// S est une liste chainee de chaines de caracteres
// fsd(S) supprime de la liste S toutes les chaines qui 
// sont facteur d'une autre chaine
//void fsd(LISTE_frag S);
LISTE_frag fsd(LISTE_frag S);


// x et y sont des chaines de caracteres
// lplc(x, y) retourne la longueur du plus long suffixe de x 
// qui est un prefixe de y
int lplc(char *x, char *y);

// S est une liste chainee de chaines de caracteres
// nomf est le nom d'un fichier texte contenant des fragments d'ADN
// initListeFragments(S, nomf) initialise l'ensemble S avec les fragments 
// contenus dans le fichier texte nomf
// void initListeFragments(LISTE_frag S, char *nomf);
LISTE_frag initListeFragments(LISTE_frag S, char *nomf);

// G est un graphe pondere
// S est une liste chainee de chaines de caracteres
// construitGrapheChevauchement(G,S) construit le graphe de chevauchement
// a partir des fragments contenus dans la liste S
GRAPHE construitGrapheChevauchement(GRAPHE G, LISTE_frag S); 

// G est un graphe pondere
// parcours de G en profondeur et affichage sur la sortie
void parcoursEnProfondeur(GRAPHE G);

// Structure supplementaire : liste
// WARNING : c'est la même structure que Element ! ! Fusionner ça
struct _liste {
	float valuation;
	int destination;
	struct _liste* suivant;
};

typedef struct _liste * Liste;

// Fonctions supplementaires
// Affiche le fragment d'un sommet et parcours ses successeurs
void visiteEnProfondeur(GRAPHE g, int s, int* marque);
//Renvoie le nombre de sommets d'un graphe G
int getNbSommets(GRAPHE g);
// Renvoie l'élément suivant d'une liste chainee de fragments
LISTE_frag getSuivant(LISTE_frag l);
// Renvoie l'élément suivant d'une liste chainee d'arcs
LISTE_arc getSuivantArc(LISTE_arc l);
// Supprime un élément d'une liste chainée (utilisée dans la fonction fsd)
LISTE_frag supprimer(LISTE_frag S, char* frag);
// Insère un élément en tête de liste chaînée de fragments
LISTE_frag inserer(LISTE_frag l, char* k);
// Insère un élément en tête de liste chaînée d'arcs
LISTE_arc insererArc(LISTE_arc A, int pds, int dest);
// Teste si un graphe est vide
int estVideGraphe (GRAPHE);
// Cree un nouveau sommet contenant le fragment e
Sommet nouveauSommet(char *e);
// Crée un graphe de n sommets
GRAPHE nouveauGraphe(int n);
// Retourne le sommet de g en position k
Sommet getSommet(GRAPHE g, int k);
// Retourne la liste des successeurs d'un sommet    // WARNING : même structure que ELEMENT !
Liste getSuccesseurs(Sommet);
// Ajoute a g un nouvel arc
void nouvelArc(GRAPHE g, int s, int d, float v);
// Retourne la longueur d'une liste chainee de fragments
int lenListe(LISTE_frag S);
// Affiche une liste de fragments
void printFrags(LISTE_frag S);
// Affiche une liste d'arcs
void printArc(LISTE_arc A);
// Retourne la sous-chaine de start à end d'une chaîne de caracteres
char* sousChaine(char* chaine, int start, int end);

LISTE_arc triDecroissant(LISTE_arc A);
void echangerElement(LISTE_arc A, LISTE_arc B);
