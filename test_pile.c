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
        assert(empiler(pile, arbre) == 0);
    }
    assert(empiler(pile, arbre) == -1);

    for (int i=MAX_PILE_SIZE-1; i>=0; i--)
    {
        assert(depiler(pile) != NULL);
    }
    assert(depiler(pile) == NULL);

    printf("La structure pile est fonctionnelle !\n");
}