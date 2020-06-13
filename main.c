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

int main() {
    srand(time(NULL));

    Carte paquet[TAILLE_PAQUET];
    initPaquetCarte(paquet);
    melanger(paquet, 150);

    Joueur joueurs[4];
    Equipe equipe[2];

    equipe[0] = creerEquipe(0);
    equipe[1] = creerEquipe(1);

    joueurs[0] = creerJoueur(0, "Somia", &equipe[0], false);
    joueurs[1] = creerJoueur(1, "Lionel", &equipe[1], true);
    joueurs[2] = creerJoueur(2, "Younesse", &equipe[0], true);
    joueurs[3] = creerJoueur(3, "Yacine", &equipe[1], true);

    Jeu jeu = creerJeu(joueurs, equipe, paquet, 1000);

    lancerJeu(&jeu);

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
                printf("Vous avez choisi de demarrer une partie\n");*/
}