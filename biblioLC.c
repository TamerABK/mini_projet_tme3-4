#include "biblioLC.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// FONCTIONS CREATION

Livre* creer_livre(int num,char* titre,char *auteur){

    Livre* livre=(Livre*)malloc(sizeof(Livre));

    if (!livre)
    { 
        printf("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    livre->num=num;
    livre->auteur= strdup(auteur);
    livre->titre= strdup(titre);
    livre->suivant=NULL;

    return livre;
}

Biblio* creer_biblio(){
    Biblio* biblio=(Biblio*)malloc(sizeof(Biblio));
    biblio->L=NULL;
    return biblio;
}

// FONCTION DE COMPARAISON

int compare_livre(Livre* l1, Livre* l2){

    if ((strcmp(l1->auteur,l2->auteur)==0)&&(strcmp(l1->titre,l2->titre)==0))
    {
        if (l1->num==l2->num)
        {
            return 1;
        }else{
            return 2;
        }
    }

    return 0;

}

// FONCTIONS LIBERATION

void liberer_livre(Livre *livre)
{
    free(livre->auteur);
    free(livre->titre);
    free(livre);
}



void liberer_biblio(Biblio* biblio){

    Livre* entrainDeLibere=biblio->L;
    Livre* aLibere;

    while (!entrainDeLibere)
    {
        aLibere=entrainDeLibere->suivant;
        liberer_livre(entrainDeLibere);
        entrainDeLibere=aLibere;
    }

    free(biblio);
    
}

void supprimer_ouvrage(Biblio* biblio,int num, char* auteur, char* titre){
	Livre* livre_curr=biblio->L;
    Livre* livre_compar= creer_livre(num,titre,auteur);
	Livre* livre_prec;
	while(livre_curr && compare_livre(livre_curr,livre_compar)!=1 ){
		livre_prec=livre_curr;
		livre_curr=livre_curr->suivant;
	}
	if(livre_curr && compare_livre(livre_curr,livre_compar)!=1){
		if(livre_prec){
			biblio->L=livre_curr->suivant;
		}
		else{
			livre_prec->suivant=livre_curr->suivant;
		}
		liberer_livre(livre_curr);
	}
    liberer_livre(livre_compar);
}

// FONCTION INSERTION

void inserer_en_tete(Biblio* biblio,int num,char *titre,char* auteur){

    Livre* nv_livre= creer_livre(num,titre,auteur);
    nv_livre->suivant=biblio->L;
    biblio->L=nv_livre;

}

// FONCTION FUSION

void fusion_biblio(Biblio* b1, Biblio* b2){
	
    if (!(b1->L)){
        Biblio* b_temp=b1;
        b1=b2;
        free (b_temp);

    }

    if (!(b2->L)){
        free(b2);
    }else{

        Livre* dernier_livre_b1=b1->L;

        while (dernier_livre_b1->suivant!=NULL)
        {
            dernier_livre_b1=dernier_livre_b1->suivant;
        }

        dernier_livre_b1->suivant=b2->L;

        free(b2); 
    }

}



// FONCTIONS DE RECHERCHE

Livre* recherche_par_num(Biblio* biblio,int num_recherche){

    Livre* livre_curr= biblio->L;

    while (livre_curr)
    {
        if (livre_curr->num==num_recherche)
        {
            return livre_curr;
        }
        livre_curr=livre_curr->suivant;
    }

    return NULL;
    
}

Livre* recherche_par_titre(Biblio* biblio,char* titre_recherche){

    Livre* livre_curr= biblio->L;

    while (livre_curr)
    {
        if (strcmp(livre_curr->titre,titre_recherche)==0)
        {
            return livre_curr;
        }
        
        livre_curr=livre_curr->suivant;
    }
    
    return NULL;

}


Biblio* recherche_par_auteur(Biblio* biblio,char* auteur_recherche){

    Livre* livre_curr=biblio->L;
    Biblio* biblio_auteur=creer_biblio();

    while (livre_curr)
    {
        if(strcmp(livre_curr->auteur,auteur_recherche)==0){
            inserer_en_tete(biblio_auteur,livre_curr->num,livre_curr->titre,auteur_recherche);
        }

        livre_curr=livre_curr->suivant;

    }
    
    return biblio_auteur;

}

Biblio* recherche_exemplaires(Biblio* biblio){

    Livre* livre_curr=biblio->L;
    

    Biblio* biblio_exemplaire= creer_biblio();

    while (livre_curr)
    {
        Livre* livre_curr2=biblio->L;
        while (livre_curr2)
        {
            if (compare_livre(livre_curr,livre_curr2)==2)
            {
                inserer_en_tete(biblio_exemplaire,livre_curr->num,livre_curr->titre,livre_curr->auteur);
            }

            livre_curr2=livre_curr2->suivant;

        }
        
        livre_curr=livre_curr->suivant;

    }

    return biblio_exemplaire;
    
}

// FONCTION D'AFFICHAGE

void afficher_livre(Livre* l){
	printf("%d : %s - %s\n",l->num,l->titre,l->auteur);
}

void afficher_biblio(Biblio* biblio){
    Livre* livre_curr=biblio->L;
	while(livre_curr){
		afficher_livre(livre_curr);
		livre_curr=livre_curr->suivant;
	}
}
