#include "jeu.h"

#include <stdlib.h>
#include <string.h>

#include "annonce.h"
#include "carte.h"
#include "common.h"
#include "enchere.h"
#include "pli.h"

Jeu creerJeu(Joueur joueurs[4], Equipe equipes[2], Carte paquet[TAILLE_PAQUET],
             int pointsObjectif) {
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

    j.pointsObjectif = pointsObjectif;
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
                   isAtout(jeu, carte) ? "*" : "",    // Afiche un * si atout
                   jeu->carteMaitre == i ? "+" : "",  // Affiche un + si maître
                   pointsCarte(carte, jeu->enchere.contrat), joueur->nom,
                   indicateurEquipe);

        } else {
            printf("-. ---\n");
        }
    }
}

void lancerJeu(Jeu* jeu) {
    int i = 0;

    Equipe* equipe = jeu->equipes;

    while (equipe[0].score < jeu->pointsObjectif &&
           equipe[1].score < jeu->pointsObjectif) {
        printf("\nDonne #%d:\n", i + 1);
        jeu->donneur = (jeu->donneur + 1) % 4;
        phaseRound(jeu);

        i++;
    }

    if (equipe[0].score > equipe[1].score) {
        printf("L'équipe %d a gagné avec %d points ! Bravo à %s et %s !\n",
               equipe[0].id, equipe[0].score, equipe[0].membres[0].nom,
               equipe[0].membres[1].nom);
    } else {
        printf("L'équipe %d a gagné avec %d points ! Bravo à %s et %s !\n",
               equipe[1].id, equipe[1].score, equipe[1].membres[0].nom,
               equipe[1].membres[1].nom);
    }

    // SAUVEGARDER SCORE ICI
}

void phaseRound(Jeu* jeu) {

    // Initialisation de la donne
    jeu->nbPli = 0;
    int nbRetry = 0;

    for (int i = 0; i < 2; i++) {
        jeu->equipes[i].victoires = 0;
        jeu->equipes[i].scoreRound = 0;
    }

    do {
        if (nbRetry > 0) {
            printf("Tout le monde a passé... Redistribution des cartes\n");
        }

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                jeu->joueurs[i].possedeCouleur[j] = 0;
            }
        }
        // Tant que personne n'a enchéri on mélange et redistribue les cartes
        melanger(jeu->paquet, 200);
        distribuer(jeu->joueurs, jeu->paquet);
        phaseEnchere(jeu);

        nbRetry++;
    } while (!jeu->enchere.encheri);

    // Phase calcul d'annonce et de belote
    for (int i = 0; i < 4; i++) {
        jeu->joueurs[i].belote = hasBelote(jeu, &jeu->joueurs[i]);
        jeu->joueurs[i].annonce = hasAnnonce(jeu, &jeu->joueurs[i]);
    }

    for (int i = 0; i < 8; i++) {
        printf("\n------------ Contrat ------------\n");
        afficherContrat(jeu->enchere.contrat);
        printf("---------------------------------\n");
        phasePli(jeu);

        printf("Equipe %d : Round = %d pts (Total = %d (+%d)pts)\n",
               jeu->equipes[0].id, jeu->equipes[0].scoreRound,
               jeu->equipes[0].score, jeu->equipes[0].scoreRound);
        printf("Equipe %d : Round = %d pts (Total = %d (+%d)pts)\n",
               jeu->equipes[1].id, jeu->equipes[1].scoreRound,
               jeu->equipes[1].score, jeu->equipes[1].scoreRound);

        jeu->nbPli++;
    }

    printf("\nLes 8 plis ont été joués. Résultats de la donne :\n");
    attribuerScoreDonne(jeu);
}

void attribuerScoreDonne(Jeu* jeu) {
    Contrat contrat = jeu->enchere.contrat;

    // L'équipe qui a le contrat
    Equipe* preneurs = contrat.equipe;
    // L'équipe qui n'a pas le contrat (l'autre)
    Equipe* defenseurs = &jeu->equipes[(preneurs->id + 1) % 2];

    // Annonces de l'équipe 0 et 1
    int valAnnonces[2] = {0, 0};
    int valBelotes[2] = {0, 0};

    for (int i = 0; i < 4; i++) {
        Joueur joueur = jeu->joueurs[i];

        Annonce annonce = joueur.annonce;
        Annonce belote = joueur.belote;

        valAnnonces[joueur.equipe->id] += scoreAnnonce(annonce);
        valBelotes[joueur.equipe->id] += scoreAnnonce(belote);

        if (belote.nom == BELOTE) {
            printf("%s (équipe %d) a une belote !", joueur.nom,
                   joueur.equipe->id);
        }

        if (annonce.nom != RIEN) {
            printf("%s (équipe %d) avait un %s !", joueur.nom,
                   joueur.equipe->id, annonceToString(annonce));
        }
    }

    int annoncesPreneurs = valAnnonces[preneurs->id];
    int annoncesDef = valAnnonces[(preneurs->id + 1) % 2];

    int belotePreneurs = valBelotes[preneurs->id];
    int beloteDef = valBelotes[(preneurs->id + 1) % 2];

    Equipe* dixDeDer = poseurCarte(jeu, jeu->carteMaitre)->equipe;

    int gainsPreneurs = 0;
    int gainsDefenseurs = 0;

    printf("L'équipe %d remporte le Dix de Der ! (+10pts)\n", dixDeDer->id);
    if (dixDeDer == preneurs) {
        gainsPreneurs += 10;
    } else {
        gainsDefenseurs += 10;
    }

    bool preneursCapot = preneurs->victoires == 8;

    int gainCoinche = contrat.valeur + 160 + annoncesPreneurs + annoncesDef;

    if (preneurs->scoreRound > contrat.valeur &&
        preneurs->scoreRound > defenseurs->scoreRound || (preneursCapot && contrat.capot)) {
        printf("L'équipe %d respecte le contrat (%d > %d)\n", preneurs->id,
               preneurs->scoreRound, contrat.valeur);
        if (jeu->enchere.surcoinche) {
            printf(
                "L'équipe %d avait coinché mais les preneurs a surcoinché. x4 "
                "!\n",
                defenseurs->id);
            gainsPreneurs += gainCoinche * 4;

        } else if (jeu->enchere.coinche) {
            printf("L'équipe %d avait coinché. x2 !\n", defenseurs->id);
            gainsPreneurs += gainCoinche * 2;

        } else {  // Aucune coinche
            gainsPreneurs +=
                contrat.valeur + preneurs->scoreRound + annoncesPreneurs;
            gainsDefenseurs += defenseurs->scoreRound + annoncesDef;
        }
    } else {
        printf(
            "L'équipe %d ne respecte pas le contrat ou a moins de points que "
            "l'équipe adverse !\n",
            preneurs->id);
        if (jeu->enchere.surcoinche) {
            printf(
                "L'équipe %d avait coinché mais les preneurs ont surcoinché. "
                "x4 !\n",
                defenseurs->id);
            gainsDefenseurs += gainCoinche * 4;
        } else if (jeu->enchere.coinche) {
            printf("L'équipe %d avait coinché. x2 !\n", defenseurs->id);
            gainsDefenseurs += gainCoinche * 2;
        } else {  // Aucune coinche
            gainsDefenseurs += gainCoinche;
        }
    }

    // Tout le monde gagne la belote
    gainsPreneurs += belotePreneurs;
    gainsDefenseurs += beloteDef;

    preneurs->score += gainsPreneurs;
    defenseurs->score += gainsDefenseurs;

    printf("\nL'équipe %d (preneurs) remporte au total %d points!\n",
           preneurs->id, gainsPreneurs);
    printf("L'équipe %d remporte au total %d points!\n\n", defenseurs->id,
           gainsDefenseurs);
}

bool isAtout(Jeu* jeu, Carte c) {
    return jeu->enchere.contrat.atout == c.couleur;
}

// Utilisé pour facilement trier une liste de carte en fonction de leur valeur
// en points
struct _CompareEntry {
    int indiceCarte;
    int nbPoints;
};

int comparateurPointsCarte(const void* carte1, const void* carte2) {
    struct _CompareEntry a = *(struct _CompareEntry*)carte1;
    struct _CompareEntry b = *(struct _CompareEntry*)carte2;

    return (int)(a.nbPoints - b.nbPoints);
}

int trierCarteParPoints(Contrat contrat, Carte* cartes[], int triOutput[],
                        int nbCartes) {

    struct _CompareEntry* entries =
        (struct _CompareEntry*)malloc(sizeof(struct _CompareEntry) * nbCartes);

    int nbCartesReel = 0;
    // Remplissage tableau de structure de comparaison
    for (int i = 0; i < nbCartes; i++) {
        if (cartes[i] != NULL) {
            struct _CompareEntry entry = {
                .indiceCarte = i, .nbPoints = pointsCarte(*cartes[i], contrat)};
            entries[nbCartesReel] = entry;
            nbCartesReel++;
        }
    }

    qsort(entries, nbCartesReel, sizeof(struct _CompareEntry),
          comparateurPointsCarte);

    for (int i = 0; i < nbCartesReel; i++) {
        triOutput[i] = entries[i].indiceCarte;
    }

    for (int i = nbCartesReel; i < nbCartes; i++) {
        triOutput[i] = -1;
    }

    free(entries);

    return nbCartesReel;
}