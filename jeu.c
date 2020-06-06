#include "jeu.h"
#include <stdlib.h>
#include "carte.h"
#include "enchere.h"

Jeu creerJeu(Joueur joueurs[4]) {
    Jeu j;
    j.joueurs = joueurs;
    j.nbCartes = 0;
    j.nbTours = 0;
    j.donneur = 0;

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

// Défausse = le joueur peut poser toutes ses cartes :
//      - Le joueur ne possède pas la carte de l'entame et ne possède aucun atout (et son partenaire n'a pas joué)
//      - Le joueur ne possède pas la carte de l'entame et son partenaire tient le pli (mais il peut posséder atout quand même)
//      - L'adversaire a coupé (avec un atout), et on ne possède pas d'atouts

// On doit jouer atout plus fort si :
//      - La couleur de l'entame est celle de l'atout
//      - Un adversaire a coupé avec un atout -> on doit jouer plus fort si on peut (sinon on doit jouer un atout moins fort)

// On doit jouer un atout moins fort si :
//      - Un adversaire a coupé avec un atout et qu'on n'a pas d'atout plus fort
// On peut jouer un atout moins fort si :
//      - Le partenaire a coupé et est maître et que le joueur n'a plus que des atout

// On peut jouer une carte si :
//      - Elle est de la couleur de l'entame
//      - Si c'est un atout et que personne n'a coupé
//      - Si on est défaussé
//      - Si la couleur de l'entame est celle de l'atout et que la carte est plus forte
//  

bool carteValide(Jeu* jeu, Joueur* joueur, Carte carte) {
    Contrat contrat = jeu->enchere.contrat;
    Joueur partenaire = jeu->

    if (jeu->atoutPose == NULL && carte.couleur == jeu->entame->couleur) {
        return true;
    }

    if (jeu->atoutPose == NULL && carte.couleur == contrat.atout) {
        return true;
    }

    if (jeu->atoutPose
        && carte.couleur == contrat.atout
        && pointsCarte(carte, contrat) > pointsCarte(*jeu->atoutPose, contrat)
    ) {
        return true;
    }

    if (carte.couleur != jeu->entame->couleur &&)



    return false;
}

void phaseJeu(Jeu* jeu) {
    for (int i = 0; i < 4; i++) {
        jeu->joueurActuel = &jeu->joueurs[(jeu->donneur + i) % 4];
        printf("Au tour de %s de jouer.\n", jeu->joueurActuel->nom);
        int choix;

        if (jeu->joueurActuel->isBot) {
            choix = jouerCarteHumain(jeu, jeu->joueurActuel);
        } else {
            choix = jouerCarteBot(jeu, jeu->joueurActuel);
        }

        Carte* carteJouee = jeu->joueurActuel->carte[choix];

        char carteStr[16];
        carteToString(*carteJouee, carteStr);

        printf("%s a joué : %s", jeu->joueurActuel->nom, carteStr);

        bool isAtout = carteJouee->couleur == jeu->enchere.contrat.atout;

        if (i == 0) // Si c'est le premier joueur
            jeu->entame = carteJouee;

        if (isAtout)
            jeu->atoutPose = carteJouee;

        poserCarte(&jeu->joueurActuel->carte[choix], jeu);

        jeu->carteMaitre = carteGagnante(jeu);
    }

    Equipe* gagnant = poseurCarte(jeu, jeu->carteMaitre)->equipe;
}



Joueur* poseurCarte(Jeu* jeu, int n) {
    return &jeu->joueurs[(jeu->donneur + n - 1) % 4];
}

int carteGagnante(Jeu* jeu) {
    int max = 0;
    int gagnant = 0;

    for (int i = 0; i < jeu->nbCartes; i++) {
        int points = pointsCarte(*jeu->pile[i], jeu->enchere.contrat);
        bool isAtout = jeu->pile[i]->couleur == jeu->enchere.contrat.atout;

        if (jeu->atoutPose != NULL) {
        // Si un atout a été posé
            if (points > max && isAtout) {
            // Et si cette carte est atout qui est supérieure au max
                max = points;
                gagnant = i;
            }
        } else {
            // Sinon, si il n'y a pas d'atout
            if (points > max) {
                max = points;
                gagnant = i;
            }
        }
    }

    return gagnant;
}