#ifndef _BIBLIOLC_H_
#define _BIBLIOLC_H_

typedef struct livre
{
    int num;
    char *titre;
    char *auteur;
    struct livre *suivant;
    
}Livre;

typedef struct 
{
    Livre *L;
}Biblio;


// FONCTIONS CREATION

Livre* creer_livre(int num,char* titre,char *auteur);
Biblio* creer_biblio();

// FONCTIONS LIBERATION

void liberer_livre(Livre *livre);
void liberer_biblio(Biblio* biblio);

// FONCTION INSRTION

void inserer_en_tete(Biblio* biblio,int num,char *titre,char* auteur);


#endif


