#ifndef __LISTES__
#define __LISTES__

struct _liste {
	float valuation;
	int destination;
	struct _liste* suivant;
};

typedef struct _liste * Liste;

Liste listeVide();
int estListeVide(Liste);
float getValuation(Liste);
int getDestination(Liste);
Liste getSuivant(Liste);
Liste ajoutEnTete(Liste, float, int);
void afficherListe(Liste l);

#endif