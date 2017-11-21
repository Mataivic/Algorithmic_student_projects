#ifndef _FCT_PILEVIDE__
#define _FCT_PILEVIDE__

//typedef struct _Pile Pile;
typedef struct _Pile {
    int valeur; /* La donnée que notre pile stockera. */
    struct _Pile *suivant; /* Pointeur vers l'élément suivant de la pile. */
} *Pile;

Pile pileVide();
int estPileVide(Pile pile);
Pile empiler(Pile pile, int donnee);
Pile depiler(Pile pile);
int getSommet(Pile pile);
void videPile(Pile pile);
void afficherPile(Pile pile);

#endif
