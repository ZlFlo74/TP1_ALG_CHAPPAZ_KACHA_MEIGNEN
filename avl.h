#ifndef _AVL_H_
#define _AVL_H_

typedef struct n {
  int cle;
  int balance;
  struct n *fgauche, *fdroite;
} noeud_AVL_t, *pnoeud_AVL_t ;

/* type Arbre_AVL, pointeur vers un noeud */

typedef pnoeud_AVL_t Arbre_AVL_t;

Arbre_AVL_t rotation_gauche(Arbre_AVL_t a) ;

Arbre_AVL_t rotation_droite(Arbre_AVL_t a) ;

Arbre_AVL_t double_rotation_gauche(Arbre_AVL_t a) ;

Arbre_AVL_t double_rotation_droite(Arbre_AVL_t a) ;

Arbre_AVL_t reequilibrage(Arbre_AVL_t a);

Arbre_AVL_t ajouter_cle (Arbre_AVL_t a, int cle);

Arbre_AVL_t lire_arbre (char *nom_fichier) ;

void afficher_arbre (Arbre_AVL_t a, int niveau) ;

void actualiser_balances (Arbre_AVL_t a);

#endif