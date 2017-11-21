#include <stdlib.h>
#include <stdio.h>
#include "fct_pileVide.h"

int main() {
    
    printf("%s\n", "On crée une pile");
	Pile maPile = pileVide();

    printf("%s", "Test Pile vide : " );
    printf("%d\n", estPileVide(maPile));

    printf("%s\n", "On empile 3 fois : 4, 8, 15");
    maPile = empiler(maPile, 4);
    maPile = empiler(maPile, 8);
    maPile = empiler(maPile, 15);

    printf("%s", "Test Pile vide : ");
    printf("%d\n", estPileVide(maPile));

    printf("%s", "Affichage : ");
    afficherPile(maPile);
    
    printf("%s", "Sommet de la pile : ");
	printf("%d\n", getSommet(maPile));

    printf("%s\n", "On empile encore 3 fois : 16, 23, 42");
    maPile = empiler(maPile, 16);
    maPile = empiler(maPile, 23);
    maPile = empiler(maPile, 42);

    printf("%s", "Sommet de la pile : ");
    printf("%d\n", getSommet(maPile));

    printf("%s", "Affichage : ");
    afficherPile(maPile);
	
    printf("%s\n", "On dépile 2 fois");
	maPile = depiler(maPile);
	maPile = depiler(maPile);
	
	printf("%s", "Affichage : ");
    afficherPile(maPile);

    printf("%s", "Sommet de la pile : ");
	printf("%d\n", getSommet(maPile));

    printf("%s\n", "Vidage de la pile");
    videPile(maPile);

    printf("%s", "Test Pile vide : " );
    printf("%d\n", estPileVide(maPile));
   
    return EXIT_SUCCESS;
}
