#ifndef __ARBREBIN__
#define __ARBREBIN__

typedef struct _Parbre
{
	int valeur;
	struct _Parbre *gauche;
	struct _Parbre *droite;
} *Parbre; //pointeur vers la structure

Parbre arbreVide();
int estArbreVide(Parbre p);

int racine(Parbre p);
void printGauche(Parbre p);
void printDroite(Parbre p);
Parbre gauche(Parbre arbre);
Parbre droite(Parbre arbre);

Parbre construire(int x, Parbre a, Parbre b);

int max(int a, int b);

int hauteur(Parbre arbre);
int nbFeuilles(Parbre arbre);
int nbNoeudsInternes(Parbre arbre);
int nbNoeuds(Parbre arbre);

void parcoursPref(Parbre);
void parcoursInf(Parbre);
void parcoursSuff(Parbre);
void parcoursLargeur(Parbre arbre);

Parbre insertion(int x, Parbre arbre);
int recherche (int x, Parbre arbre);

int elementMax(Parbre arbre);
int elementMin(Parbre arbre);

Parbre suppressionMax(Parbre arbre);
Parbre suppressionRacine (Parbre arbre);
Parbre suppression(int x, Parbre arbre);

#endif
