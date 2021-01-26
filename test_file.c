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
        assert(enfiler(file, arbre) == 0);
    }
    assert(enfiler(file, arbre) == -1);

    for (int i=MAX_FILE_SIZE-1; i>=0; i--)
    {
        assert(defiler(file) != NULL);
    }
    assert(defiler(file) == NULL);

    printf("La structure file est fonctionnelle !\n");
}