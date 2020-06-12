#include "jeu.h"

#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "carte.h"
#include "enchere.h"
#include "pli.h"
#include "annonce.h"

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
    
    jeu->equipes[0].scoreRound = 0;
    jeu->equipes[1].scoreRound = 0;

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


    // Phase calcul d'annonce et de belote
    for (int i = 0; i < 4; i++) {
        jeu->joueurs[i].belote = hasBelote(jeu, &jeu->joueurs[i]).nom == BELOTE;
        jeu->joueurs[i].annonce = hasAnnonce(jeu, &jeu->joueurs[i]);
    }

    for (int i = 0; i < 8; i++) {
        printf("\n------------ Contrat ------------\n");
        afficherContrat(jeu->enchere.contrat);
        printf("---------------------------------\n");
        phasePli(jeu);

        printf("Equipe %d : Round = %d pts (Total = %d pts)\n", jeu->equipes[0].id, jeu->equipes[0].scoreRound, jeu->equipes[0].score);
        printf("Equipe %d : Round = %d pts (Total = %d pts)\n", jeu->equipes[1].id, jeu->equipes[1].scoreRound, jeu->equipes[1].score);

        jeu->nbPli++;
    }

    calculerScoreDonne(jeu);

}

void calculerScoreDonne(Jeu *jeu) {
    Contrat contrat = jeu->enchere.contrat;

    // L'équipe qui a le contrat
    Equipe* preneurs = contrat.equipe;
    // L'équipe qui n'a pas le contrat (l'autre)
    Equipe* defenseurs = &jeu->equipes[(contrat.equipe->id + 1) % 2];

    int valeurAnnonces[2] = {0, 0};

    for (int i = 0; i < 4; i++) {
        valeurAnnonces[jeu->joueurs[i].equipe->id] += scoreAnnonce(jeu->joueurs[i].annonce);
    }

    if (contrat.equipe->scoreRound > contrat.valeur && contrat.equipe->scoreRound > defenseurs->scoreRound) {
        if (jeu->enchere.surcoinche) {
            preneurs->score += (contrat.valeur + 160) * 4;
        } else if (jeu->enchere.coinche) {
            preneurs->score += (contrat.valeur + 160) * 2;

        } else {    // Aucune coinche
            preneurs->score += contrat.valeur + preneurs->scoreRound;

            defenseurs->score += defenseurs->scoreRound;
        }
    } else {
        if (jeu->enchere.coinche) {
            // GERER COINCHE
        }
    }
}

bool isAtout(Jeu* jeu, Carte c) {
    return jeu->enchere.contrat.atout == c.couleur;
}

