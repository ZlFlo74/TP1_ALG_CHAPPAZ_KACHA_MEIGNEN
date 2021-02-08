#include <stdio.h>
#include <stdlib.h>

#include "abr.h"

int main (int argc, char**argv)
{
  Arbre_t a, a2 ;

  if (argc != 3)
    {
      fprintf (stderr, "il manque les deux parametres nom de fichier\n") ;
      exit (-1) ;
    }

  a = lire_arbre (argv[1]) ;
  a2 = lire_arbre (argv[2]);
  
  afficher_arbre (a,0) ;

  printf("Hauteur de l'arbre (récursive) : %d\n", hauteur_arbre_r(a));
  printf("Hauteur de l'arbre (non récursive) : %d\n\n", hauteur_arbre_nr(a));

  printf("Test de parcourir_arbre_largeur : \n");
  parcourir_arbre_largeur(a);
  printf("\n\n");

  printf("Nombre de clés dans l'arbre (récursive) : %d\n", nombre_cles_arbre_r(a));
  printf("Nombre de clés dans l'arbre (non récursive) : %d\n\n", nombre_cles_arbre_nr(a));

  printf("Clé minimum : %d \n\n", trouver_cle_min(a));

  printf("Liste des clés triées : ");
  imprimer_liste_cle_triee_r(a);
  printf("\n\n");

  printf("Est arbre plein : %d\n", arbre_plein(a));
  printf("Est arbre parfait : %d\n\n", arbre_parfait(a));

  for (int i=1; i<16; i+=2) {
    Arbre_t result = rechercher_cle_sup_arbre(a,i);
    if (result == NULL) {
      printf("Clé de rechercher_cle_sup_arbre(a,%d) : NULL\n",i);
    }
    else {
      printf("Clé de rechercher_cle_sup_arbre(a,%d) : %d\n",i,result->cle);
    }
  }
  printf("\n");

  for (int i=1; i<16; i+=2) {
    Arbre_t result = rechercher_cle_inf_arbre(a,i);
    if (result == NULL) {
      printf("Clé de rechercher_cle_inf_arbre(a,%d) : NULL\n",i);
    }
    else {
      printf("Clé de rechercher_cle_inf_arbre(a,%d) : %d\n",i,result->cle);
    }
  }
  printf("\n");

  printf("Intersection des deux arbres : \n");
  afficher_arbre(intersection_deux_arbres(a,a2), 0);
  printf("\n");

  printf("Union des deux arbres : \n");
  afficher_arbre(union_deux_arbres(a,a2), 0);
  printf("\n");

}
