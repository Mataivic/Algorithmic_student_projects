pautomate nouvel_automate(int tailleAlpha){
	pautomate Aut = (pautomate)malloc(sizeof(struct automate));
	Aut -> tailleAlpha = tailleAlpha;
	Aut -> etatInit = 0;	
	return Aut;	
}

// Lit le contenu d'un fichier
//(V1 (old) : une seule ligne, 1000 caractères maximum)
char* lireFichier(char* file) {
	FILE* fichier = fopen(file, "r");
	char* motRetour;
	if (fichier != NULL) {
		char* mot = (char*)malloc(100*sizeof(char));
		fgets(mot, 1000, fichier);
		motRetour = (char*)malloc(strlen(mot)*sizeof(char));
		motRetour = strncpy(motRetour, mot, strlen(mot));
	}
	return motRetour;
}

// A revoir
int recherche_Mot_Auto(pautomate Aut, char* texte_fichier){
	char* cible = lireFichier(texte_fichier);
	//printf("\n%s%s\n", "    Cible de la recherche :", cible);
	int retour = -1;
	int len = (int)strlen(cible);
	int term = 0;
	int i;	
	for (i=0; i <= len - Aut -> nbetat +1; ++i) {
		//term = 0;
		//printf("%d", term);
		while (destination(Aut, term, cible[i+term]) == term+1) {
			term = term+1;
		}	
		if (term == Aut -> etatTerminal) {
			retour = i+1; // Renvoie la position en comptant a partir de 1, pas 0
			break;
		}
		term = destination(Aut, term, cible[i+term]); // rajout pour retour en arrière. Ne amrche
	}	
	return retour;
}
