#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "carte.h"
#include "joueur.h"
#include "equipe.h"
#include "contrat.h"



int main() {

    srand(time(NULL));


    Carte paquet[32] = {0};
    creerPaquetCarte(paquet);
/**
    printf("\npaquet non melange\n");
    for (int i = 0; i < 32; ++i)
    {
        printf("\n%d\n",i);
        afficherCarte(paquet[i]);
    }
**/
   melange(paquet);
/**
    printf("\npaquet melange\n");
    for (int i = 0; i < 32; ++i)
    {
        printf("\n%d\n",i);
        afficherCarte(paquet[i]);
    }
**/


   // creerEquipe(&equipe, 0);
   // creerEquipe(&equipe, 1);

    char nom[20];
  //  scanf("Entrer le nom du joueur %s", &nom);


    Carte jeu[8];
    Carte jeuEst[8];
    Carte jeuNord[8];
    Carte jeuOuest[8];

    distribution(paquet, jeu, jeuEst, jeuNord, jeuOuest);
    for (int i = 0; i<8; ++i)
    {
        printf("\nJeu: carte %d\n",i);
        afficherCarte(jeu[i]);
    }

    for (int i = 0; i<8; ++i)
    {
        printf("\nJeu: carte %d\n",i);
        afficherCarte(jeuEst[i]);
    }

    //scanf("Entrer le nom du joueur %s", joueur[0].name);

    creerJoueur(&joueur[0], 0, 0, 0, nom);
    creerJoueur(&joueur[1], 1, 1, 1, "Est");
    creerJoueur(&joueur[2], 1, 0, 2,"Nord");
    creerJoueur(&joueur[3], 1, 1, 3, "Ouest");


/**


    int choixMenu;
    printf("****************************************\n");
    printf("*                                      *\n");
    printf("*           Belote coinch%ce            *\n",130);
    printf("*                                      *\n");
    printf("****************************************\n");
    printf("\nQue voulez vous faire ?\n\n");
    printf("1 : D%cmarer une nouvelle partie\n",130);
    printf("2 : Afficher le tableau des scores\n");
    printf("3 : Quitter\n\n");
    scanf("%d", &choixMenu);
    switch(choixMenu) {
        case 1:
            printf("Vous avez choisi de demarrer une partie\n");

            contrat(&joueur[0]);

           break;
        case 2:
            printf("Vous avez choisi d'afficher le tableau des scores\n");
            break;
        case 3:
            exit(1);
        default:
            printf("Vous devez choisir 1, 2 ou 3");
    }
**/





//    Carte carte_a;
//    carte_a.couleur = CARREAU;
//    carte_a.valeur = DAME;
//    printf("Couleur: %d", carte_a.couleur);
/**    Carte paquet[32] = {0};
    creerPaquetCarte(paquet);
    for (int i = 0; i < 32; ++i) {
        afficherCarte(paquet[i]);
    }
**/
/**
 // Equipe equipe;
    creerEquipe(&equipe, 0);
    creerEquipe(&equipe, 1);

    char nom[20];
    scanf("Entrer le nom du joueur %s", &nom);


    creerJoueur(&joueur[0], 0, 0, 0, nom);
    //scanf("Entrer le nom du joueur %s", joueur[0].name);
    creerJoueur(&joueur[1], 1, 1, 1, "Est");
    creerJoueur(&joueur[2], 1, 0, 2,"Nord" );
    creerJoueur(&joueur[3], 1, 1, 3, "Ouest");

**/

    printf("Done \n");








    return 0;
}