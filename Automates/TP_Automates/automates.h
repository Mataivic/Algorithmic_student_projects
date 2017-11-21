typedef int etat;
typedef int* ensemble; // Tableau d'états

typedef struct transition {
	char lettre;
	etat destination;	
	struct transition* suivant;
}* ptransition;

//typedef struct transition* ptransition;

typedef struct _automate {
	int tailleAlpha;
	int nbEtats;
	etat etatInit;
	ensemble estTerminal;
	ptransition* tabListeTrans;
}* pautomate;

int* creer_estTerminal(int nbE);
void mettreTerminal(int* estT, etat e);
ptransition* creer_transitions(int nbE);
void ajout_transition(ptransition* tabT, etat source, etat dest, char a);

pautomate allouer_automate();
void init_automate(pautomate A, FILE *fauto);
pautomate creer_init_automate(char* nomFichier);
void affiche_automate(pautomate automate);
etat destination (pautomate Aut, etat source, char a);
int estReconnu(pautomate A, char* mot);