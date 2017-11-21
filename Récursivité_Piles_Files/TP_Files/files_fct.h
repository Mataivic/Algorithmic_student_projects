#ifndef __FILES_FCT__
#define __FILES_FCT__

/*
typedef struct _Element {
	int valeur;
	struct _Element *suivant;
} *Element;

typedef struct _File {   
    struct _File *premier;
} *File;

*/

typedef struct _File {
	int valeur;
	struct _File *suivant;
} *File;

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