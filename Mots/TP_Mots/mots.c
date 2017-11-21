#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mots.h"

/*
x : mot
m : longueur mot
y : texte
n : longueur texte
*/

int naif(char* mot, char* texte, int m, int n) {
	int nbOcc = 0;	
	
	for (int j=0; j <= n-m; ++j) {
		int i =0;
		while(i < m && mot[i] == texte[j+i]) {
			i++;
		}
		if (i == m) {
			nbOcc += 1;
		}
	}

	return nbOcc;
}

int morrisPratt(char* mot, char* texte, int m, int n, int* bonpref) {
	int nbOcc = 0;
	int i = 0;
	for (int j=0; j <= n-1; ++j) {
		while (i >= 0 && mot[i] != texte[j]) {
			i = bonpref[i];
		}
		i += 1;
		if (i == m) {
			nbOcc += 1;
			i = bonpref[i];
		}
	}
	return nbOcc;
}

int* bonPref(char* mot, int m) {
	int* bonpref = (int*)malloc((size_t)(m+1)*sizeof(int));
	bonpref[0] = -1;
	int i = 0;	
	for (int j=1; j <= m-1; ++j) {
		bonpref[j] = i;
		while (i>=0 && mot[i] != mot[j]) {
			i = bonpref[i];
		}
		i += 1;
	}
	bonpref[m] = i;
	return bonpref;
}

int KMP(char* mot, char* texte, int m, int n, int* meilpref) {
	int nbOcc = 0;
	int i = 0;
	for (int j=0; j <= n-1; ++j) {
		while (i>=0 && mot[i] != texte[j]) {			
			i = meilpref[i];
		}
		i += 1;
		if (i==m) {
			nbOcc += 1;
			i = meilpref[i];
		}
	}
	return nbOcc;
}

int* meilPref(char* mot, int m) {
	int* meilpref = (int*)malloc((size_t)(m+1)*sizeof(int));
	meilpref[0] = -1;
	int i = 0;
	for (int j=1; j <= m-1; ++j) {
		if(mot[i] == mot[j]) {
			meilpref[j] = meilpref[i];
		} else {
			meilpref[j] = i;
			while (i>=0 && mot[i] != mot[j]) {
				i = meilpref[i];
			}
		}
		i += 1;
	}
	meilpref[m] = i;
	return meilpref;
}
