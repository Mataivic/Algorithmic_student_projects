#include <stdlib.h>
#include <stdio.h>
#include "fct_pile.h"

void pile_push(Pile **p_pile, int donnee)
{
        Pile *p_nouveau = malloc(sizeof *p_nouveau);
        if (p_nouveau != NULL)
        {
                p_nouveau->donnee = donnee;
                p_nouveau->precedent = *p_pile;
                *p_pile = p_nouveau;
        }
}

int pile_pop(Pile **p_pile)
{
    int ret = -1;
    if (p_pile != NULL)
    {
        Pile *temporaire = (*p_pile)->precedent;
        ret = (*p_pile)->donnee;  
        free(*p_pile), *p_pile = NULL;
        *p_pile = temporaire;
    }
    return ret;
}

void pile_clear(Pile **p_pile)
{
    while (*p_pile != NULL)
    {
        pile_pop(p_pile);
    }
}

int pile_peek(Pile *p_pile)
{
    int ret = -1; /* Variable de retour. */
    if (p_pile != NULL) /* Si la pile n'est pas vide. */
    {
        ret = p_pile->donnee; /* On stocke dans la variable ret la valeur du dernier élément. */
    }
    return ret;
}
