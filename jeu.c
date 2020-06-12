#include "jeu.h"

#include <stdlib.h>
#include <string.h>

#include "carte.h"
#include "enchere.h"
#include "pli.h"

Jeu creerJeu(Joueur joueurs[4], Equipe equipes[2],
             Carte paquet[TAILLE_PAQUET]) {
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

    j.joueurPrincipal = &joueurs[0];

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

void afficherJeu(Jeu* jeu) { afficherPaquet(jeu->pile, 4); }

void afficherPile(Jeu* jeu) {
    printf("Pile : %d/4\n", jeu->nbCartes);
    for (int i = 0; i < 4; i++) {
        if (jeu->pile[i] != NULL) {
            Carte carte = *(jeu->pile[i]);

            char carteStr[16];
            carteToString(carte, carteStr);

            Joueur* joueur = poseurCarte(jeu, i);

            char indicateurEquipe[20] = "";

            if (joueur == jeu->joueurPrincipal) {
                strcpy(indicateurEquipe, "(vous)");
            } else if (isMemeEquipe(jeu->joueurPrincipal, joueur)) {
                strcpy(indicateurEquipe, "(coéquipier)");
            }

            printf("%d. %s%s %s\t(%d pts) <- %s %s\n", i, carteStr,
                   isAtout(jeu, carte) ? "*" : "", // Afiche un * si atout
                   jeu->carteMaitre == i? "+":"", // Affiche un + si maître
                   pointsCarte(carte, jeu->enchere.contrat),
                   joueur->nom,
                   indicateurEquipe
                );

        } else {
            printf("-. ---\n");
        }
    }
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
    } while (!jeu->enchere.encheri);

    for (int i = 0; i < 8; i++) {
        printf("\n------------ Contrat ------------\n");
        afficherContrat(jeu->enchere.contrat);
        printf("---------------------------------\n");
        phasePli(jeu);

        printf("Equipe %d : Score = %d\n", jeu->equipes[0].id, jeu->equipes[0].score);
        printf("Equipe %d : Score = %d\n", jeu->equipes[1].id, jeu->equipes[1].score);

        jeu->nbPli++;
    }
};

bool isAtout(Jeu* jeu, Carte c) {
    return jeu->enchere.contrat.atout == c.couleur;
}


