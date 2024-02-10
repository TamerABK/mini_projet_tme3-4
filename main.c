#include "entreeSortieLC.h"
#include "biblioLC.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc,char** argv){

    if (argc!=3){
        printf("Mauvais nombre d'arguments\n");
        exit(EXIT_FAILURE);
    }

    char* NOMFIC=argv[1];
    int N_LIGNES=atoi(argv[2]);

    Biblio* biblio=charger_n_entree(NOMFIC,N_LIGNES);


}