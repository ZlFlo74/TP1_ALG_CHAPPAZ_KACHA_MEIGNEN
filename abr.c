#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "abr.h"
#include "pile.h"
#include "file.h"


#define max(a,b) ((a)>(b)?(a):(b))


int feuille (Arbre_t a)
{
  if (a == NULL)
    return 0 ;
  else
    {
      if ((a->fgauche == NULL) && (a->fdroite == NULL))
	return 1 ;
      else
	return 0 ;
    }
}

Arbre_t ajouter_noeud (Arbre_t a, Arbre_t n)
{
  /* ajouter le noeud n dans l'arbre a */
  
  if (a == NULL)
    return n ;
  else if (n->cle < a->cle)
	a->fgauche = ajouter_noeud (a->fgauche, n) ;
  else
	a->fdroite = ajouter_noeud (a->fdroite, n) ;
  return a ;
  
}  

Arbre_t rechercher_cle_arbre (Arbre_t a, int valeur)
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

Arbre_t ajouter_cle (Arbre_t a, int cle)
{
  Arbre_t n ;
  Arbre_t ptrouve ;
  
  /* 
     ajout de la clé. Creation du noeud n qu'on insere 
    dans l'arbre a
  */

  ptrouve = rechercher_cle_arbre (a, cle) ;

  if (ptrouve == NULL)
    {
      n = (Arbre_t) malloc (sizeof(noeud_t)) ;
      n->cle = cle;
      n->fgauche = NULL ;
      n->fdroite = NULL ;

      a = ajouter_noeud (a, n) ;
      return a ;
    }
  else
    return a ;
}


Arbre_t lire_arbre (char *nom_fichier)
{
  FILE *f ;
  int cle;
  Arbre_t a = NULL;
  
  f = fopen (nom_fichier, "r") ;

  while (fscanf (f, "%d", &cle) != EOF)
    {
      a = ajouter_cle (a, cle) ;
    }
    
  fclose (f) ;

  return a ;
}

void afficher_arbre (Arbre_t a, int niveau)
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


int hauteur_arbre_r (Arbre_t a)
{
  if (a == NULL)
    return -1;

  return 1 + max(hauteur_arbre_r(a->fgauche), hauteur_arbre_r(a->fdroite)); 
}

int hauteur_arbre_nr (Arbre_t a)
{
  Arbre_t n;
  pfile_t file = creer_file();
  int height = -1;
  enfiler(file, a);
  enfiler(file,  NULL);

  while (!file_vide(file))
  {
    n = defiler(file);
    if (n == NULL) 
    {
      if (!file_vide(file))
        enfiler(file,NULL);
      height++;
    }
    else
    {
      if (n->fgauche != NULL)
        enfiler(file,n->fgauche);
      if (n->fdroite != NULL)
        enfiler(file,n->fdroite);
    }
  }

  return height;
}


void parcourir_arbre_largeur (Arbre_t a)
{
  Arbre_t n;
  pfile_t file = creer_file();
  enfiler(file, a);
  while (!file_vide(file))
  {
    n = defiler(file);
    if (n != NULL)
    {
      enfiler(file, n->fgauche);
      enfiler(file, n->fdroite);
      printf("%d ", n->cle);
    }
  }
  detruire_file(file);
}

// A FAIRE
void afficher_nombre_noeuds_par_niveau (Arbre_t a)
{
  if(a == NULL){
    printf("Arbre vide");
    return;
  }
  pfile_t file = creer_file();
  enfiler(file,a);
  printf("Niveau 0 : %d noeud(s)\n",file->queue+1);
  int i = nombre_cles_arbre_nr(a);
  int cle = file->queue+1;
  int niveau = 1;
  while(i>cle){
    pfile_t newfile = creer_file();
    while (!file_vide(file)){
      pnoeud_t n = defiler(file);
      if (n->fdroite!=NULL){
        enfiler(newfile,n->fdroite);
      }
      if (n->fgauche!=NULL){
        enfiler(newfile,n->fgauche);
      }
    }
    cle += newfile->queue+1;
    printf("Niveau %d : %d noeud(s)\n",niveau,newfile->queue+1);
    file = newfile;
    niveau ++;
  }
  return ;
}


int nombre_cles_arbre_r (Arbre_t a)
{
  if (a==NULL) {return 0;}

  return 1 + nombre_cles_arbre_r(a->fgauche) + nombre_cles_arbre_r(a->fdroite) ;
}

int nombre_cles_arbre_nr (Arbre_t a)
{
  int nbr_noeuds = 0;

  Arbre_t n;
  pfile_t file = creer_file();
  enfiler(file, a);
  while (!file_vide(file))
  {
    n = defiler(file);
    if (n != NULL)
    {
      enfiler(file, n->fgauche);
      enfiler(file, n->fdroite);
      nbr_noeuds ++;
    }
  }
  detruire_file(file);
  
  return nbr_noeuds ;
}

int trouver_cle_min (Arbre_t a)
{
  Arbre_t n = a;

  while (n->fgauche != NULL)
  {
    n = n->fgauche;
  }
  
  return n->cle ; 
}

 

void imprimer_liste_cle_triee_r (Arbre_t a)
{
  // Parcours profaaaondeur infixe récursif
  if (a != NULL) {
    imprimer_liste_cle_triee_r(a->fgauche);
    printf("%d ", a->cle);
    imprimer_liste_cle_triee_r(a->fdroite);
  }
}

void imprimer_liste_cle_triee_nr (Arbre_t a)
{
  if(a == NULL){
    printf("Arbre vide");
    return;
  }
  pfile_t file = creer_file();
  enfiler(file,a);
  int i = nombre_cles_arbre_nr(a);
  i--;
  printf("nombre de cles : %d\n",i);
  while (i>file->queue){
    printf("file queue : %d\n",file->queue);
    pnoeud_t n = defiler(file);
    if (feuille(n)==1){
      printf("feuille");
      enfiler(file,n);

    }
    else {
      if (n->fgauche!=NULL){
        enfiler(file,n->fgauche);
      }
      Arbre_t ccc = malloc(sizeof(Arbre_t));
      ccc->cle = n->cle;
      ccc->fdroite = NULL;
      ccc->fgauche = NULL;
      enfiler(file,ccc);
      if (n->fdroite!=NULL){
        enfiler(file,n->fdroite);
      }
      printf("file queue fin : %d\n",file->queue);
    }
  }
  while(file->Tab[0]->cle>file->Tab[1]->cle){
    pnoeud_t n = defiler(file);
    enfiler(file,n);
  }
  
  for (int j=0; j<=file->queue;j++){
    printf("%d ,",file->Tab[j]->cle);
  }
  printf("\n");
  return ;
}


int arbre_plein (Arbre_t a)
{
  return (nombre_cles_arbre_r(a) == pow(2, hauteur_arbre_r(a) +1) - 1) ? 1 : 0;
}

int arbre_parfait (Arbre_t a)
{
  return (hauteur_arbre_r(a) == (int) log2(nombre_cles_arbre_r(a))) ? 1 : 0;
}




Arbre_t rechercher_cle_sup_arbre (Arbre_t a, int valeur)
{
  if (a == NULL) {
    return NULL;
  }
  else if (a->cle > valeur) {
    Arbre_t sous_arbre_gauche = rechercher_cle_sup_arbre(a->fgauche, valeur);
    if (sous_arbre_gauche == NULL) {
      return a;
    }
    else {
      return sous_arbre_gauche;
    }
  }
  else {
    Arbre_t sous_arbre_droit = rechercher_cle_sup_arbre(a->fdroite, valeur);
    return sous_arbre_droit;
  }
}

Arbre_t rechercher_cle_inf_arbre (Arbre_t a, int valeur)
{
  if (a == NULL) {
    return NULL;
  }
  else if (a->cle >= valeur) {
    Arbre_t sous_arbre_gauche = rechercher_cle_inf_arbre(a->fgauche, valeur);
    return sous_arbre_gauche;
  } 
  else {
    Arbre_t sous_arbre_droit = rechercher_cle_inf_arbre(a->fdroite, valeur);
    if (sous_arbre_droit == NULL) {
      return a;
    }
    else {
      return sous_arbre_droit;
    }
  }
  
}


void SousArbre (Arbre_t a, Arbre_t fa, int d){
  Arbre_t tmp = fa;
  if(d){
    if (fa->fdroite == NULL){
      a->fdroite = fa->fgauche;
    }
    else if (fa->fgauche == NULL){
      a->fdroite = fa->fdroite;
    }
    else {
      fa = fa->fdroite;
      while (fa->fgauche != NULL){
        fa = fa->fgauche;
      }
      fa->fgauche = tmp->fgauche;
      a->fdroite = tmp->fdroite;
    }
  }
  else {
    if (fa->fdroite == NULL){
      a->fgauche = fa->fgauche;
    }
    else if (fa->fgauche == NULL){
      a->fgauche = fa->fdroite;
    }
    else {
      fa = fa->fdroite;
      while (fa->fgauche != NULL){
        fa = fa->fgauche;
      }
      fa->fgauche = tmp->fgauche;
      a->fgauche = tmp->fdroite;
    }
  }
}


Arbre_t detruire_cle_arbre (Arbre_t a, int cle)
{
  if (rechercher_cle_arbre(a,cle)==NULL){
    return NULL;
  }
  Arbre_t finalA = a;
  int find = 0;
  if (a->cle == cle){
    if (a->fdroite == NULL){
      return a->fgauche;
    }
    if (a->fgauche == NULL){
      return a->fdroite;
    }
    finalA = finalA->fdroite;
    while (finalA->fgauche != NULL){
      finalA = finalA->fgauche;
    }
    finalA->fgauche = a->fgauche;
    return a->fdroite;
  }
  while (find==0){
    if (finalA->fdroite != NULL && finalA->fdroite->cle == cle){
      find = 2;
    }
    else if (finalA->fgauche != NULL && finalA->fgauche->cle == cle){
      find = 1;
    }
    else if (rechercher_cle_arbre(finalA->fgauche,cle)==NULL){
      finalA = finalA->fdroite;
    }
    else{
      finalA = finalA->fgauche;
    }
  }
  if (find == 2){
    Arbre_t fd = finalA->fdroite;
    if (feuille(fd)){
      finalA->fdroite = NULL;
    }
    else{
      SousArbre(finalA,fd,1);
    }
  }
  else if (find == 1){
    Arbre_t fg = finalA->fgauche;
    if (feuille(fg)){
      finalA->fgauche = NULL;
    }
    else{
      SousArbre(finalA,fg,0);
    }
  }
  return a ;
}



Arbre_t intersection_deux_arbres (Arbre_t a1, Arbre_t a2)
{
  Arbre_t a_inter = NULL;
  Arbre_t iter;

  pfile_t file = creer_file();
  enfiler(file, a1);
  while (!file_vide(file))
  {
    iter = defiler(file);
    if (iter != NULL)
    {
      enfiler(file, iter->fgauche);
      enfiler(file, iter->fdroite);
      if (rechercher_cle_arbre(a2, iter->cle) != NULL)
      {
        a_inter = ajouter_cle(a_inter, iter->cle);
      }
    }
  }
  detruire_file(file);

  return a_inter ;
}

Arbre_t union_deux_arbres (Arbre_t a1, Arbre_t a2)
{
  Arbre_t a_union = copie_arbre(a1);
  Arbre_t iter;

  pfile_t file = creer_file();
  enfiler(file, a2);
  while (!file_vide(file))
  {
    iter = defiler(file);
    if (iter != NULL)
    {
      enfiler(file, iter->fgauche);
      enfiler(file, iter->fdroite);
      if (rechercher_cle_arbre(a1, iter->cle) == NULL)
      {
        a_union = ajouter_cle(a_union, iter->cle);
      }
    }
  }
  detruire_file(file);

  return a_union ;
}

// FONCTIONS ANNEXES

Arbre_t copie_arbre (Arbre_t a) 
{
  Arbre_t a_copie = NULL;
  Arbre_t iter;

  pfile_t file = creer_file();
  enfiler(file, a);
  while (!file_vide(file))
  {
    iter = defiler(file);
    if (iter != NULL)
    {
      enfiler(file, iter->fgauche);
      enfiler(file, iter->fdroite);
      a_copie = ajouter_cle(a_copie, iter->cle);
    }
  }
  detruire_file(file);

  return a_copie;
}