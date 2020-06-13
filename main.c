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

    Joueur joueurs[4];
    Equipe equipe[2];

    equipe[0] = creerEquipe(0);
    equipe[1] = creerEquipe(1);

    joueurs[0] = creerJoueur(0, "Somia", &equipe[0], false);
    joueurs[1] = creerJoueur(1, "Lionel", &equipe[1], true);
    joueurs[2] = creerJoueur(2, "Younesse", &equipe[0], true);
    joueurs[3] = creerJoueur(3, "Yacine", &equipe[1], true);

    Jeu jeu = creerJeu(joueurs, equipe, paquet, 1000);

    // Contrat c = creerContrat(100, CARREAU_ATOUT, &equipe[0], false);

    // distribuer(joueurs, paquet);

    // poserCarte(&joueurs[0], 0, &jeu);
    // poserCarte(&joueurs[0], 4, &jeu);
    // poserCarte(&joueurs[0], 7, &jeu);
    // afficherPaquet(joueurs[0].carte, 8);

    // int tri[8];
    // trierCarteParPoints(c, joueurs[0].carte, tri, 8);

    // printf("\n");
    // for (int i = 0; i < 8; i++) {
    //     printf("%d. ", tri[i]);
    //     afficherCarte(*joueurs[0].carte[tri[i]]);
    // }

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