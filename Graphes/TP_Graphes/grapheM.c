#include <stdlib.h>
#include <stdio.h>
#include "grapheM.h"

int estVideGrapheM(GrapheM g) {
	return (g == NULL);
}

GrapheM nouveauGrapheM(int n) {
	GrapheM newGM = (GrapheM)malloc(sizeof(struct _grapheM));
	newGM -> nbSommets = n;

	for (int i=0; i < n; i++) {
		for (int j=i; j < n; j++) {
			newGM -> m[i][j] = 0;
		}
	}
	return newGM;
}