#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

Pile *initialiser() {
    Pile *pile = malloc(sizeof(*pile));
    pile->premier = NULL;
}

void empiler(Pile *pile, int nvNombre)
{
    Element *nouveau = malloc(sizeof(*nouveau)); // on crée un élément
    if (pile == NULL || nouveau == NULL) {
        exit(EXIT_FAILURE);
    }

    nouveau->nombre = nvNombre; // on affecte la valeur nvNombre à l'élément nommé nouveau
    nouveau->suivant = pile->premier; // on empile sur le premier d'avant : suivant pointe sur premier (qui n'est plus premier)
    pile->premier = nouveau; // on précise que nouveau est le nouveau premier
}

int depiler(Pile *pile) {
    if (pile == NULL) {
        exit(EXIT_FAILURE);
    }

    int nombreDepile = 0;
    Element *elementDepile = pile->premier;

    if (pile != NULL && pile->premier != NULL) {
        nombreDepile = elementDepile->nombre;
        pile->premier = elementDepile->suivant;
        free(elementDepile);
    }

    return nombreDepile;
}

void afficherPile(Pile *pile) {
    if (pile == NULL) {
        exit(EXIT_FAILURE);
    }
    Element *actuel = pile->premier;

    while (actuel != NULL) {
        printf("%d\n", actuel->nombre);
        actuel = actuel->suivant;
    }

    printf("\n");
}

