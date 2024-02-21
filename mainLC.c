#include "entreeSortieLC.h"
#include "biblioLC.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void menu() {

    printf("Menu:\n");
    printf("1 - Afficher la bibliothèque\n");
    printf("2 - Insérer un ouvrage\n");
    printf("3 - Rechercher un ouvrage par numéro\n");
    printf("4 - Rechercher un ouvrage par titre\n");
    printf("5 - Rechercher des ouvrages par auteur\n");
    printf("6 - Rechercher les exemplaires\n");
    printf("7 - Supprimer un ouvrage\n");
    printf("8 - Fusionner deux bibliothèques\n");
    printf("9 - Sauvegarder dans le fichier\n");
    printf("0 - Quitter le programme\n");
    printf("Choisissez une option : ");
}

int main(int argc,char** argv){

    if (argc!=3){
        printf("Mauvais nombre d'arguments\n");
        exit(EXIT_FAILURE);
    }

    char* NOMFIC=argv[1];
    int N_LIGNES=atoi(argv[2]);

    Biblio* biblio=charger_n_entree(NOMFIC,N_LIGNES);
    Biblio* biblio2=charger_n_entree("test2.txt",50);
    int choix,segfault_prevention=1;
    
    do {
        menu();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                afficher_biblio(biblio);
                break;
            case 2:
                {
                    int num;
                    char titre[100];
                    char auteur[100];
                    printf("Entrez le numéro, le titre et l'auteur de l'ouvrage : ");
                    scanf("%d %s %s", &num, titre, auteur);
                    inserer_en_tete(biblio, num, titre, auteur);
                    printf("Ouvrage inséré avec succès.\n");
                }
                break;
            case 3:
                {
                    int num_recherche;
                    printf("Entrez le numéro de l'ouvrage à rechercher : ");
                    scanf("%d", &num_recherche);
                    Livre* livre = recherche_par_num(biblio, num_recherche);
                    if (livre != NULL) {
                        printf("Ouvrage trouvé : ");
                        afficher_livre(livre);
                    } else {
                        printf("Ouvrage non trouvé.\n");
                    }
                }
                break;
            case 4:
                {
                    char titre_recherche[100];
                    printf("Entrez le titre de l'ouvrage à rechercher : ");
                    scanf("%s", titre_recherche);
                    Livre* livre = recherche_par_titre(biblio, titre_recherche);
                    if (livre != NULL) {
                        printf("Ouvrage trouvé : ");
                        afficher_livre(livre);
                    } else {
                        printf("Ouvrage non trouvé.\n");
                    }
                }
                break;
            case 5:
                {
                    char auteur_recherche[100];
                    printf("Entrez l'auteur des ouvrages à rechercher : ");
                    scanf("%s", auteur_recherche);
                    Biblio* ouvrages_auteur = recherche_par_auteur(biblio, auteur_recherche);
                    if (ouvrages_auteur != NULL) {
                        printf("Ouvrages trouvés pour l'auteur %s:\n", auteur_recherche);
                        afficher_biblio(ouvrages_auteur);
                        liberer_biblio(ouvrages_auteur);
                    } else {
                        printf("Aucun ouvrage trouvé pour l'auteur %s.\n", auteur_recherche);
                    }
                }
                break;
            case 6:
                {
                    Biblio* exemplaires = recherche_exemplaires(biblio);
                    if (exemplaires != NULL) {
                        printf("Exemplaires trouvés :\n");
                        afficher_biblio(exemplaires);
                        liberer_biblio(exemplaires);
                    } else {
                        printf("Aucun exemplaire trouvé.\n");
                    }
                }
                break;
            case 7:
                {
                    int num_supprimer;
                    char titre_supprimer[100];
                    char auteur_supprimer[100];
                    printf("Entrez le numéro, le titre et l'auteur de l'ouvrage à supprimer : ");
                    scanf("%d %s %s", &num_supprimer, titre_supprimer, auteur_supprimer);
                    supprimer_ouvrage(biblio, num_supprimer, titre_supprimer, auteur_supprimer);
                    printf("Ouvrage supprimé avec succès.\n");
                }
                break;
            case 8:
                {
                    if(segfault_prevention==1)
                    {
                    fusion_biblio(biblio, biblio2);
                    printf("Bibliothèques fusionnées avec succès.\n");
                    segfault_prevention=0;
                    }else{
                        printf("Fusion deja faite\n");
                    }
                }
                break;
            case 9:
                {
                    enregistrer_biblio(biblio,"test.txt");
                    choix=0;
                    printf("Programme terminé.\n");
                    if (segfault_prevention==1) liberer_biblio(biblio2);
                }
                break;
            case 0:
                liberer_biblio(biblio);
                if (segfault_prevention==1) liberer_biblio(biblio2);
                printf("Programme terminé.\n");
                break;
            default:
                printf("Option invalide. Veuillez choisir à nouveau.\n");
        }
    } while (choix != 0);

    return 0;
}