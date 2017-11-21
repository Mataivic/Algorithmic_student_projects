#ifndef _FCT_PILE__
#define _FCT_PILE__

typedef struct pile
{
    int donnee; /* La donnée que notre pile stockera. */
    struct pile *precedent; /* Pointeur vers l'élément précédent de la pile. */
} Pile;


void pile_push(Pile **p_pile, int donnee);
int pile_pop(Pile **p_pile);
void pile_clear(Pile **p_pile);
int pile_peek(Pile *p_pile);

#endif
