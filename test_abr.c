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
  
  printf("Affichage du premier arbre donné :\n");
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

  printf("Argument 1 inclus dans Argument 2 : %d\n\n", inclusion_arbre(a,a2));

  printf("Test de detruire_cle sur le premier argument.\n");
  printf("Destruction de toutes les cles, reconstruction de l'arbre à partir des clés, et affichage de ce dernier : \n");
  Arbre_t a_bis = copie_arbre(a);
  int nbr_cles = nombre_cles_arbre_r(a);
  int cles[nbr_cles];
  for (int i = 0; i < nbr_cles; i++)
  {
    cles[i] = a_bis->cle;
    a_bis = detruire_cle_arbre(a_bis, a_bis->cle);
  }
  for (int i = 0; i < nbr_cles; i++)
  {
    a_bis = ajouter_cle(a_bis, cles[i]);
  }
  afficher_arbre(a_bis, 0);
  
  
}
