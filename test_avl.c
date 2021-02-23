#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

int main (int argc, char**argv)
{
  Arbre_AVL_t a ;

  if (argc != 2)
    {
      fprintf (stderr, "il manque le parametre nom de fichier\n") ;
      exit (-1) ;
    }

  a = lire_arbre (argv[1]) ;
  
  afficher_arbre (a,0) ;

  /*
   * Pour tester les fonctions de rotations et d'équilibrage, il suffit de tester les fonctions d'ajout et de suppression de clé.
   * 
  */

  // On copie a, on détruit toutes ses clés en les conservant dans une liste, et on reconstruit a à partir des clés.
  printf("Destruction de toutes les cles, reconstruction de l'arbre à partir des clés, et affichage de ce dernier : \n");
  int nbr_cles = nombre_cles_arbre_r(a);
  int cles[nbr_cles];
  for (int i = 0; i < nbr_cles; i++)
  {
    cles[i] = a->cle;
    a = detruire_cle(a, a->cle);
  }
  for (int i = 0; i < nbr_cles; i++)
  {
    a = ajouter_cle(a, cles[i]);
  }
  afficher_arbre(a, 0);

}
