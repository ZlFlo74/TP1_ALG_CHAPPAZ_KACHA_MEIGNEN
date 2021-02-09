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

}
