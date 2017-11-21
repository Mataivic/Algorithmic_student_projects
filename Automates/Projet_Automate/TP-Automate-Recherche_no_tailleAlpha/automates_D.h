//automates.h

//type etat
typedef int etat;
//tableau des �tats
typedef int* ensemble ;

//chaque etat a une liste de transition
struct transition {
  char lettre;
  etat destination;
  struct transition *suivant; 
 };

typedef struct transition* ptransition;

// la structure de l'automate
typedef struct automate{
  int nbetat;
  int tailleAlpha;
  int etatInit;
  int etatTerminal;
  ptransition *tabListeTrans; 
  
}* pautomate;

//fonction qui indique le num�ro de l'�tat terminal
void mettreTerminal(pautomate A, etat e);
//fonction qui initialise le tableau de transitions
ptransition* creer_transitions(int nbE);
//fonction qui ajoute une transition au tableau de transistions
void ajout_transition(ptransition* tabT, etat source, etat dest, char a);
//fonction qui supprime une transition au tableau de transistions
ptransition supprimer(ptransition transi, etat dest, char a);
//renvoie le num�ro de l'�tat "cible" par l'�tat de d�part source et la transition �tiquet�e par a
etat destination (pautomate Aut, etat source, char a);
//fonction qui alloue l'automate
pautomate nouvel_automate(void);
//fonction qui cr�e l'automate reconnaissant le langage A*x pour l'alphabet A et un mot x
void creer_automate_mot(pautomate Aut, char* x, char* alphabet);
//Affiche l'automate
void affiche_automate(pautomate Aut, char* mot, char* alphabet);
//fonction qui prend un param�tre un automate reconnaissant A*x et le nom du fichier contenant le texte
  //renvoie la position de la premi�re occurrence de x dans le texte (-1 s'il n'apprait pas)
int recherche_Mot_Auto(pautomate Aut, char* cible);
// Lit le fichier contenant le mot � rechercher
char* lireFichier(char* fichier);
// Renvoie l'�l�ment suivant d'une liste chain�e
ptransition getSuivant(ptransition tabTransi);
// Gere les incompatibilites entre alphabet et le mot recherche
int gestionErreur(char* mot, char* texte, char* alphabet);
