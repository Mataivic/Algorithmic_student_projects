#ifndef __FILES__
#define __FILES__

struct _File {
	int valeur;
	struct _File *suivant;
};

typedef struct _File * File;

File fileVide();
int estFileVide(File file);
File enfiler(File file, int x);
File defiler(File file);
int getDebut(File file);
int getFin(File file);
int getLongueur(File file);
void videFile(File file);
void afficherFile(File file);

#endif