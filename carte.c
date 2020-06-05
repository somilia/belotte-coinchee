#include "carte.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "equipe.h"
#include "joueur.h"
#include "enchere.h"

#define POSER_SUCCES    1
#define POSER_PLEIN     2
#define POSER_ECHEC     0

void initPaquetCarte(Carte paquet[]) {
    Couleur couleurs[] = {TREFLE, CARREAU, COEUR, PIQUE};
    Valeur valeurs[] = {SEPT, HUIT, NEUF, DIX, VALET, DAME, ROI, AS};
    int ind = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
            paquet[ind] = creerCarte(couleurs[i], valeurs[j]);
            ind++;
        }
    }
}

Carte creerCarte(Couleur c, Valeur v) {
    Carte carte = {c, v};
    return carte;
}

int poserCarte(Carte **source, Jeu *jeu) {
    if (source == NULL) {
        return POSER_ECHEC;
    }

    if (jeu->nbCartes >= 4) {
        return POSER_PLEIN;
    }

    jeu->pile[jeu->nbCartes] = *source;
    *source = NULL;

    jeu->nbCartes++;

    return POSER_SUCCES;
}

int pointsCarte(Carte carte, Contrat contrat) {
    switch(contrat.atout) {
        case TOUT_ATOUT:
            return POINTS_TA[carte.valeur];
        case SANS_ATOUT:
            return POINTS_SA[carte.valeur];
    }

    if (carte.couleur == contrat.atout) {
        return POINTS_ATOUT[carte.valeur];
    } else {
        return POINTS_HORS_ATOUT[carte.valeur];
    }
}

void afficherCarte(Carte carte) {
    printf("%s de %s\n", valeurToString(carte.valeur),
           couleurToString(carte.couleur));
}

void afficherPaquet(Carte **paquet, int nbCartes) {
    for (int i = 0; i < nbCartes; ++i) {
        printf("%d. ", i + 1);
        if (paquet[i] == NULL) {
            printf(" ---\n");
        } else {
            afficherCarte(*paquet[i]);
        }
    }
}

void carteToString(Carte carte, char *output) {
    sprintf(output, "%s de %s", valeurToString(carte.valeur),
            couleurToString(carte.couleur));
}

void permute(Carte *carte1, Carte *carte2) {
    Carte perm;
    perm = *carte1, *carte1 = *carte2;
    *carte2 = perm;
}

void melanger(Carte *paquet, int nbMelange) {
    for (int i = 0; i <= nbMelange; i++) {
        permute(&paquet[rand() % 32], &paquet[rand() % 32]);
    }
}

void distribuer(Joueur joueurs[4], Carte paquet[TAILLE_PAQUET]) {
    int counter = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++) {
            joueurs[i].carte[j] = &paquet[counter];
            counter++;
        }
    }
}