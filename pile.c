#include <stdlib.h>
#include "abr.h"
#include "pile.h"

ppile_t creer_pile ()
{
  ppile_t ppile = malloc(sizeof(pile_t));
  ppile->sommet = -1; // Aucun élément dans la pile, par convention, le sommet est à l'indice -1 du tableau

  return ppile;
}

int detruire_pile (ppile_t p)
{
  free(p);
  return 0;
}  

int pile_vide (ppile_t p)
{
  if (p->sommet == -1)
  {
    return 1 ;
  }

  return 0;
}

int pile_pleine (ppile_t p)
 {
  if (p->sommet == MAX_PILE_SIZE - 1)
  {
    return 1;
  }

  return 0;
} 

pnoeud_t depiler (ppile_t p)
{
  if (pile_vide(p))
  {
    return NULL;
  }

  pnoeud_t noeud = p->Tab[p->sommet];
  p->sommet --;

  return noeud ;
}

int empiler (ppile_t p, pnoeud_t pn)
{
  if (pile_pleine(p))
  {
    return -1;
  }

  p->sommet ++;
  p->Tab[p->sommet] = pn;

  return 0;
}
