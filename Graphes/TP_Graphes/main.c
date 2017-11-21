#include <stdlib.h>
#include <stdio.h>
#include "graphe.h"

int main() {	

	Graphe monGraphe = nouveauGraphe(12);
	printf("%s%d\n", "graphe vide ? : ", estVideGraphe(monGraphe));
	printf("%s%d\n", "Nombre de Sommets : ", getNbSommets(monGraphe));

	putEtiquette(monGraphe, 0, "A");
	putEtiquette(monGraphe, 1, "B");
	putEtiquette(monGraphe, 2, "C");
	putEtiquette(monGraphe, 3, "D");
	putEtiquette(monGraphe, 4, "E");
	putEtiquette(monGraphe, 5, "F");
	putEtiquette(monGraphe, 6, "G");
	putEtiquette(monGraphe, 7, "H");
	putEtiquette(monGraphe, 8, "I");
	putEtiquette(monGraphe, 9, "J");
	putEtiquette(monGraphe, 10, "K");
	putEtiquette(monGraphe, 11, "L");
	
	for (int i=0; i<12; ++i) {
		printf("%s ", getEtiquette(monGraphe, i));
	}
	printf("\n");		

	/* La façon dont on construit l'arbre influence sur les parcours.
	Il faut construire les arcs en commençant par le n° de noeud le plus éloigné */

	nouvelArc(monGraphe, 0, 3, 1.0f);
	nouvelArc(monGraphe, 0, 2, 1.0f);
	nouvelArc(monGraphe, 0, 1, 1.0f);

	nouvelArc(monGraphe, 1, 5, 1.0f);
	nouvelArc(monGraphe, 1, 4, 1.0f);

	nouvelArc(monGraphe, 2, 8, 1.0f);
	nouvelArc(monGraphe, 2, 6, 1.0f);
	nouvelArc(monGraphe, 2, 7, 1.0f);

	nouvelArc(monGraphe, 3, 5, 1.0f);
	nouvelArc(monGraphe, 3, 1, 1.0f);

	nouvelArc(monGraphe, 4, 2, 1.0f);
	nouvelArc(monGraphe, 4, 0, 1.0f);

	nouvelArc(monGraphe, 5, 8, 1.0f);
	nouvelArc(monGraphe, 5, 6, 1.0f);

	nouvelArc(monGraphe, 6, 4, 1.0f);

	nouvelArc(monGraphe, 7, 6, 1.0f);
	nouvelArc(monGraphe, 7, 4, 1.0f);

	nouvelArc(monGraphe, 8, 3, 1.0f);

	nouvelArc(monGraphe, 9, 11, 1.0f);
	nouvelArc(monGraphe, 9, 10, 1.0f);

	nouvelArc(monGraphe, 11, 10, 1.0f);

	parcoursEnProfondeur(monGraphe);
	printf("\n");
	parcoursEnLargeur(monGraphe);
	printf("\n");
}
