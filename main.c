#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "carte.h"
#include "common.h"
#include "equipe.h"
#include "jeu.h"
#include "joueur.h"
#include "sauvegarde.h"

int main() {
    srand(time(NULL));
    int choixMenu;

    printf("****************************************\n");
    printf("*                                      *\n");
    printf("*           Belote coinchee            *\n");
    printf("*                                      *\n");
    printf("****************************************\n");

    do {
        printf("\nQue voulez vous faire ?\n\n");
        printf("1 : Demarrer une nouvelle partie\n");
        printf("2 : Afficher le tableau des scores\n");
        printf("3 : Quitter\n\n");

        if(!scanf("%d", &choixMenu)) {
            choixMenu = 3;
        }
        switch (choixMenu) {
            case 1:
                break;
            case 2:
                afficherScores();
                break;
            case 3:
                return EXIT_SUCCESS;
        }
    } while (choixMenu != 1);

    char nom[30]; 

    printf("Quel est votre nom?\n");

    if(!scanf("%s", nom)) {
        printf("Vous n'avez rien entré\n");
        strcpy(nom, "Default");
    }

    Carte paquet[TAILLE_PAQUET];
    initPaquetCarte(paquet);

    Joueur joueurs[4];
    Equipe equipe[2];

    equipe[0] = creerEquipe(0);
    equipe[1] = creerEquipe(1);

    joueurs[0] = creerJoueur(0, nom, &equipe[0], false);
    joueurs[1] = creerJoueur(1, "Ouest", &equipe[1], true);
    joueurs[2] = creerJoueur(2, "Nord", &equipe[0], true);
    joueurs[3] = creerJoueur(3, "Est", &equipe[1], true);

    equipe[0].membres[0] = joueurs[0];
    equipe[0].membres[1] = joueurs[2];

    equipe[1].membres[0] = joueurs[1];
    equipe[1].membres[1] = joueurs[3];

    Jeu jeu = creerJeu(joueurs, equipe, paquet, 100);

    lancerJeu(&jeu);
}