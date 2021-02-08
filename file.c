#include <stdlib.h>

#include "abr.h"
#include "file.h"

pfile_t creer_file ()
{
  pfile_t file = malloc(sizeof(file_t));
  file->tete = 0;
  file->queue = -1;
  return file;
}

int detruire_file (pfile_t f)
{
  free(f);
  return 0;
}

int file_vide (pfile_t f)
{
  if (f->queue == -1)
    return 1;

  return 0 ;
}

int file_pleine (pfile_t f)
{
  if (f->queue == MAX_FILE_SIZE - 1)
    return 1;

  return 0;
}

pnoeud_t defiler (pfile_t f)
{
  if(file_vide(f))
    return NULL;

  pnoeud_t noeud = f->Tab[f->tete];
  for (int i=0; i<=f->queue; i++)
  {
    f->Tab[i] = f->Tab[i+1];
  }
  f->queue --;

  return noeud;
}

int enfiler (pfile_t f, pnoeud_t p)
{
  if (file_pleine(f))
    return 0;

  f->queue ++;
  f->Tab[f->queue] = p;
  return 1;
}
