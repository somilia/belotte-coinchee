#include <stdlib.h>
#include "carte.h"
#include "enchere.h"
#include "pli.h"
#include "jeu.h"

Jeu creerJeu(Joueur joueurs[4], Equipe equipes[2], Carte paquet[TAILLE_PAQUET]) {
    Jeu j;
    j.joueurs = joueurs;
    j.nbPli = 0;
    j.nbRound = 0;
    j.entameur = 0;
    j.donneur = 1;

    j.equipes = equipes;
    
    resetPile(&j);

    j.paquet = paquet;

    j.carteMaitre = 0;
    j.joueurActuel = &joueurs[j.entameur];

    j.atoutPose = NULL;
    j.entame = NULL;


    return j;
}

void resetPile(Jeu* jeu) {
    for (int i = 0; i < 4; i++) {
        jeu->pile[i] = NULL;
        jeu->nbCartes = 0;
    }
}

void afficherJeu(Jeu* jeu) {
    printf("Pile : \n");
    afficherPaquet(jeu->pile, 4);
}

void phaseRound(Jeu* jeu) {
    jeu->nbPli = 0;

    int nbRetry = 0;

    do {
        if (nbRetry > 0) {
            printf("Tout le monde a passé... Redistribution des cartes\n");
        }
        // Tant que personne n'a enchéri on redistribue les cartes
        distribuer(jeu->joueurs, jeu->paquet);
        afficherJoueur(jeu->joueurs[0]);
        phaseEnchere(jeu);

        nbRetry++;
    } while(!jeu->enchere.encheri);

    for (int i = 0; i < 8; i++) {
        printf("------------ Contrat ------------\n");
        afficherContrat(jeu->enchere.contrat);
        printf("---------------------------------\n");
        phasePli(jeu);
        jeu->nbPli++;
    }
};

bool isAtout(Jeu* jeu, Carte c) {
    return jeu->enchere.contrat.atout == c.couleur;
}
