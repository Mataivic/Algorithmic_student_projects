#include <stdlib.h>
#include <stdio.h>
#include "automates.h"

int main() {

	char* automate = "automate";
	pautomate A = creer_init_automate(automate);
	affiche_automate(A);
	etat test = destination(A, 1, 'a');
	printf("%d\n", test);
	int test2 = estReconnu(A, "aba");
	int test3 = estReconnu(A, "abc");
	printf("%d%c %d\n", test2, ',', test3);

	return EXIT_SUCCESS;
}