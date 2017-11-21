#include <stdlib.h>
#include <stdio.h>
#include "fct_pile.h"

int main() {

	Pile *pile = malloc(sizeof *pile);
	pile_push(*pile, 5);
	pile_push(*pile, 6);
	pile_push(*pile, 7);

	return EXIT_SUCCESS;
}
