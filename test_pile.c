#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "pile.h"
#include "abr.h"

int main(int argc, char**argv)
{
    Arbre_t arbre;

    ppile_t pile = creer_pile();
    assert(pile_vide(pile));

    for (int i=0; i<MAX_PILE_SIZE; i++)
    {
        arbre = malloc(sizeof(noeud_t));
        assert(empiler(pile, arbre));
    }
    assert(!empiler(pile, arbre));

    for (int i=MAX_PILE_SIZE-1; i>=0; i--)
    {
        arbre = depiler(pile);
        assert(arbre != NULL);
    }
    assert(depiler(pile) == NULL);

    assert(detruire_pile(pile) == 0);

    printf("La structure pile est fonctionnelle !\n");
}