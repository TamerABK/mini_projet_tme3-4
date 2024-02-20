#include "entreeSortieLC.h"
#include "biblioLC.h"
#include "biblioH.h"
#include "entreeSortieH.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int main(int argc,char** argv ){

    if(argc!=3)
    {
        printf("Il faut passer un int positive en argument pour PAS et pour I-max\n");
        exit(EXIT_FAILURE);
    }

    clock_t temps_initial ;
    clock_t temps_final ;
    double temps_cpu_LC;
    double temps_cpu_H;
    Biblio* biblioLC;
    BiblioH* biblioH;
    int i=1000;
    int PAS=atoi(argv[1]);
    int I_max=atoi(argv[2])+1;

    FILE* f=fopen("cpuTimes.txt","w");

    while (i<I_max)
    {
        biblioLC=charger_n_entree("GdeBiblio.txt",i);
        biblioH=charger_n_entreesH("GdeBiblio.txt",i);

        temps_initial=clock();
        recherche_exemplaires(biblioLC);
        temps_final=clock();

        temps_cpu_LC=((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;

        temps_initial=clock();
        recherche_exemplairesH(biblioH);
        temps_final=clock();

        temps_cpu_H=((double)(temps_final-temps_initial))/CLOCKS_PER_SEC;

        fprintf(f,"%d %f %f\n",i,temps_cpu_LC,temps_cpu_H);

        liberer_biblio(biblioLC);
        liberer_biblioH(biblioH);
        i=i+PAS;

    }
    
    fclose(f);
}