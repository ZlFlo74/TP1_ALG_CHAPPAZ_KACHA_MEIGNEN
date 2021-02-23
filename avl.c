#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

#define max(a,b) ((a)>(b)?(a):(b))

Arbre_AVL_t rotation_gauche(Arbre_AVL_t a)
{
    Arbre_AVL_t b = a->fdroite;

    a->fdroite = b->fgauche;
    b->fgauche = a;

    actualiser_balances(b);

    return b;
}

Arbre_AVL_t rotation_droite(Arbre_AVL_t a)
{
    Arbre_AVL_t b = a->fgauche;

    a->fgauche = b->fdroite;
    b->fdroite = a;

    actualiser_balances(b);

    return b;
}

Arbre_AVL_t double_rotation_gauche(Arbre_AVL_t a)
{
    a->fdroite = rotation_droite(a->fdroite);
    return rotation_gauche(a);
}

Arbre_AVL_t double_rotation_droite(Arbre_AVL_t a)
{
    a->fgauche = rotation_gauche(a->fgauche);
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

void actualiser_balances (Arbre_AVL_t a)
{
    if (a==NULL)
        return;
    else
    {
        a->balance = hauteur_arbre_r(a->fdroite) - hauteur_arbre_r(a->fgauche);
        actualiser_balances(a->fgauche);
        actualiser_balances(a->fdroite);
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
        actualiser_balances(a);
        a = reequilibrage(a);
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

Arbre_AVL_t detruire_cle (Arbre_AVL_t a, int cle)
{
  Arbre_AVL_t noeud_a_detruire = rechercher_cle_arbre(a, cle);
  Arbre_AVL_t arbre_a_actualiser;
  Arbre_AVL_t noeud_a_echanger ;
  if (noeud_a_detruire == NULL)
    return a;
  
  // Etape 1, passer le noeud a detruire en tant que feuille et le détruire
  if (noeud_a_detruire->fgauche == NULL && noeud_a_detruire->fdroite == NULL) {
    arbre_a_actualiser = a;
  }
  else if (noeud_a_detruire->fgauche == NULL) {
    noeud_a_echanger = noeud_a_detruire->fdroite;
    int cle_a_echanger = noeud_a_echanger->cle;
    noeud_a_echanger->cle = noeud_a_detruire->cle;
    noeud_a_detruire->cle = cle_a_echanger;
    noeud_a_detruire->fdroite = NULL;
    arbre_a_actualiser = noeud_a_detruire;
  }
  else {
    arbre_a_actualiser = noeud_a_detruire->fgauche;
    noeud_a_echanger = arbre_a_actualiser;
    while (noeud_a_echanger->fdroite != NULL)
    {
      noeud_a_echanger = noeud_a_echanger->fdroite;
    }
    int cle_a_echanger = noeud_a_echanger->cle;
    noeud_a_echanger->cle = noeud_a_detruire->cle;
    noeud_a_detruire->cle = cle_a_echanger;
    if (noeud_a_echanger->fgauche != NULL) {
      noeud_a_echanger = rotation_droite(noeud_a_echanger);
      noeud_a_echanger->fdroite = NULL;
    }
  }

  // Etape 2, on actualise les balances
  actualiser_balances(a);

  // Etape 3, on distingue les différents cas vus en cours pour réorganiser l'arbre
  if (arbre_a_actualiser->balance == -1) {} // CAS I : Rien à faire
  else if (arbre_a_actualiser->balance == 0) {  // CAS II : Des déséquilibres peuvent apparaître plus haut : on verifie
    if (a->balance == 2) {
      reequilibrage(a);
    }
  }
  else {
    if (arbre_a_actualiser->balance == -2) { // CAS III.1 : Reequilibrage du sous arbre nécessaire mais hauteur non modifiée
      reequilibrage(arbre_a_actualiser);
    }
    else {  // CAS III.2 et III.3
      reequilibrage(arbre_a_actualiser);
      reequilibrage(a);
    }
  }

  return a;
}

int nombre_cles_arbre_r (Arbre_AVL_t a)
{
  if (a==NULL) {return 0;}

  return 1 + nombre_cles_arbre_r(a->fgauche) + nombre_cles_arbre_r(a->fdroite) ;
}