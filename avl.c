#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

#define max(a,b) ((a)>(b)?(a):(b))

Arbre_AVL_t rotation_gauche(Arbre_AVL_t a)
{
    Arbre_AVL_t b = a->fdroite;

    b->balance --;
    a->balance = - b->balance;

    a->fdroite = b->fgauche;
    b->fgauche = a;

    return b;
}

Arbre_AVL_t rotation_droite(Arbre_AVL_t a)
{
    Arbre_AVL_t b = a->fgauche;

    b->balance ++;
    a->balance = - b->balance;

    a->fgauche = b->fdroite;
    b->fdroite = a;

    return b;
}

Arbre_AVL_t double_rotation_gauche(Arbre_AVL_t a)
{
    a->fgauche = rotation_droite(a->fgauche);
    return rotation_gauche(a);
}

Arbre_AVL_t double_rotation_droite(Arbre_AVL_t a)
{
    a->fdroite = rotation_gauche(a->fdroite);
    return rotation_droite(a);
}

Arbre_AVL_t reequilibrage(Arbre_AVL_t a)
{
    if (a == NULL)
        return NULL;

    if (a->balance == 2)
    {
        if (a->fdroite->balance >= 0)
            a = rotation_gauche(a);
        else
            a = double_rotation_gauche(a);
    }
    else if (a->balance == -2)
    {
        if (a->fgauche->balance <= 0)
            a = rotation_droite(a);
        else
            a = double_rotation_droite(a);
    }

    return a;
}

int hauteur_arbre_r (Arbre_AVL_t a)
{
  if (a == NULL)
    return -1;

  return 1 + max(hauteur_arbre_r(a->fgauche), hauteur_arbre_r(a->fdroite)); 
}

void actualiser_balances (Arbre_AVL_t start, Arbre_AVL_t end)
{
    if (start==NULL || end==NULL || start->cle == end->cle)
        return;
    else
    {
        start->balance = hauteur_arbre_r(start->fdroite) - hauteur_arbre_r(start->fgauche);
        if (start->cle > end->cle)
            actualiser_balances(start->fgauche, end);
        else
            actualiser_balances(start->fdroite, end);
    }
}

Arbre_AVL_t ajouter_noeud (Arbre_AVL_t a, Arbre_AVL_t n)
{
    /* ajouter le noeud n dans l'arbre a */
    
    if (a == NULL)
        return n ;
    else 
    {
        if (n->cle < a->cle)
        {
            a->fgauche = ajouter_noeud (a->fgauche, n) ;
        }
        else
        {
            a->fdroite = ajouter_noeud (a->fdroite, n) ;
        }
        if (a->fgauche != NULL && a->fdroite != NULL)
        {
            actualiser_balances(a, n);
            a = reequilibrage(a);
        }
    }

    return a ;
}

Arbre_AVL_t rechercher_cle_arbre (Arbre_AVL_t a, int valeur)
{
  if (a == NULL)
    return NULL ;
  else
    {
      if (a->cle == valeur)
	return a ;
      else
	{
	  if (a->cle < valeur)
	    return rechercher_cle_arbre (a->fdroite, valeur) ;
	  else
	    return rechercher_cle_arbre (a->fgauche, valeur) ;
	}
    }
}

Arbre_AVL_t ajouter_cle (Arbre_AVL_t a, int cle)
{
    Arbre_AVL_t n ;
    Arbre_AVL_t ptrouve ;

    /* 
        ajout de la clé. Creation du noeud n qu'on insere 
        dans l'arbre a
    */

    ptrouve = rechercher_cle_arbre (a, cle) ;

    if (ptrouve == NULL)
    {
        n = (Arbre_AVL_t) malloc (sizeof(noeud_AVL_t)) ;
        n->cle = cle;
        n->balance = 0;
        n->fgauche = NULL ;
        n->fdroite = NULL ;

        a = ajouter_noeud (a, n) ;
        return a ;
    }
    else
        return a ;
}

Arbre_AVL_t lire_arbre (char *nom_fichier)
{
  FILE *f ;
  int cle;
  Arbre_AVL_t a = NULL;
  
  f = fopen (nom_fichier, "r") ;

  while (fscanf (f, "%d", &cle) != EOF)
    {
      a = ajouter_cle (a, cle) ;
    }
    
  fclose (f) ;

  return a ;
}

void afficher_arbre (Arbre_AVL_t a, int niveau)
{
  /*
    affichage de l'arbre a
    on l'affiche en le penchant sur sa gauche
    la partie droite (haute) se retrouve en l'air
  */
  
  int i ;
  
  if (a != NULL)
      {
	afficher_arbre (a->fdroite,niveau+1) ;
	
	for (i = 0; i < niveau; i++)
	  printf ("\t") ;
	printf (" %d (%d)\n\n", a->cle, niveau) ;

	afficher_arbre (a->fgauche, niveau+1) ;
      }
  return ;
}