#ifndef __GRAPHE__
#define __GRAPHE__

#include "listes.h" // Uniquement ici, pas dans le main ou le graphe.c, sinon conflits de définitions
#include "files.h"

typedef struct _sommet {
	char* etiquette;
	Liste successeurs;
} *Sommet;

struct _graphe {
	int nbSommets;
	Sommet * t;
};

typedef struct _graphe * Graphe;

int estVideGraphe (Graphe);
Sommet nouveauSommet(char *e);
Graphe nouveauGraphe(int n);
int getNbSommets(Graphe);
Sommet getSommet(Graphe g, int k);
Liste getSuccesseurs(Sommet);
void nouvelArc(Graphe g, int s, int d, float v);
void putEtiquette(Graphe g, int k, char* e );
char* getEtiquette(Graphe g, int k);
void visiteEnProfondeur(Graphe g, int s, int* marque);
void parcoursEnProfondeur(Graphe g);
void visiteEnLargeur (Graphe g, int s, int* marque, File f);
void parcoursEnLargeur (Graphe g);

#endif