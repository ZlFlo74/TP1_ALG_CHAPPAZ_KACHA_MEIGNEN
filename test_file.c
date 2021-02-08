#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "file.h"
#include "abr.h"

int main(int argc, char**argv)
{
    Arbre_t arbre;

    pfile_t file = creer_file();
    assert(file_vide(file));

    for (int i=0; i<MAX_FILE_SIZE; i++)
    {
        arbre = malloc(sizeof(noeud_t));
        assert(enfiler(file, arbre));
        assert(file->Tab[file->queue] == arbre);
    }
    assert(!enfiler(file, arbre));

    for (int i=MAX_FILE_SIZE-1; i>=0; i--)
    {
        arbre = defiler(file);
        assert(arbre != NULL);
        assert(file->Tab[i] != arbre);
    }
    assert(defiler(file) == NULL);

    assert(detruire_file(file) == 0);

    printf("La structure file est fonctionnelle !\n");
}