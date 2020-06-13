#include "pli.h"

#include <stdlib.h>

#include "carte.h"
#include "enchere.h"
#include "jeu.h"
#include "joueur.h"

void nouveauPli(Jeu* jeu) {
    if (jeu->nbPli == 0)
        jeu->entameur = (jeu->donneur - 1) % 4;
    else
        jeu->entameur = poseurCarte(jeu, carteGagnante(jeu))->id;

    jeu->atoutPose = NULL;
    resetPile(jeu);

    jeu->carteMaitre = 0;
    jeu->entame = NULL;
    jeu->atoutPose = NULL;

    jeu->joueurActuel = &jeu->joueurs[jeu->entameur];
}

bool carteValide(Jeu* jeu, Joueur* joueur, Carte carte) {
    Contrat contrat = jeu->enchere.contrat;
    Joueur* maitre = poseurCarte(jeu, jeu->carteMaitre);

    bool hasAtout = joueur->possedeCouleur[contrat.atout];
    bool isAtout = carte.couleur == contrat.atout;

    bool atoutPose = jeu->atoutPose != NULL;
    bool entamePosee = jeu->entame != NULL;

    bool possedeQueAtout =
        joueur->possedeCouleur[contrat.atout] == 8 - jeu->nbPli;

    if (!entamePosee) {
        return true;
    }

    bool hasCouleurEntame = joueur->possedeCouleur[jeu->entame->couleur] > 0;
    bool isCouleurEntame = carte.couleur == jeu->entame->couleur;

    // Si on ne possède ni couleur de entame ni atout alors on est défaussé
    if (!hasCouleurEntame && !hasAtout) {
        return true;
    }

    // 2.2 "Si l'on ne possède pas de carte dans la couleur demandée, et que
    // notre partenaire n'est pas maître ou n'a pas encore joué: on est tenu de
    // jouer un atout si l'on en possède"
    if (!isMemeEquipe(joueur, maitre) && !hasCouleurEntame && hasAtout &&
        !isAtout) {
        return false;
    }

    if (!atoutPose) {
        if (isCouleurEntame || isAtout) {
            return true;
        }
    }

    if (atoutPose) {
        bool isMeilleurAtout = pointsCarte(carte, contrat) >
                                   pointsCarte(*jeu->atoutPose, contrat) &&
                               isAtout;
        bool hasMeilleurAtout =
            hasMeilleurCarte(jeu, joueur, *jeu->atoutPose);

        // 3. Lorsque l’on est conduit à jouer atout, soit parce qu’il s’agit de
        // la couleur demandée à l’entame, soit parce que l’on doit couper, on
        // doit toujours jouer un atout plus fort que ceux déjà présents sur le
        // tapis, même si cela est contraire à notre intérêt. Si cela s'avère
        // impossible, on peut jouer un atout plus faible.
        if (isAtout && isMeilleurAtout) {
            return true;
        }

        // 2.1 "Si l'on ne possède pas de carte dans la couleur demandée, et que
        // notre partenaire est maître c’est-à-dire qu’il a joué la meilleure
        // carte sur le tapis (on dit qu’il « tient le pli »): on peut alors
        // jouer n'importe quelle carte; on se "défausse". On peut également
        // jouer atout si bon nous semble"
        if (isMemeEquipe(joueur, maitre) && !hasCouleurEntame) {
            return true;
        }

        if (!hasMeilleurAtout) {
            return true;
        }

        // 2.2.Precision: "Si un adversaire a déjà coupé, et qu’il ne nous reste
        // que des atouts inférieurs au sien, il n’est pas obligatoire d’en
        // jouer un (on dit que l’on « ne pisse pas »), on peut se défausser."
        if (!isMemeEquipe(joueur, maitre) && !hasMeilleurAtout) {
            return true;
        }

        // 4. Lorsque notre partenaire, maître, a coupé une carte adverse et que
        // nous ne possédons plus que de l’atout, il n’est pas obligé de fournir
        // un atout supérieur. C’est le seul cas de figure, plutôt rare, où il
        // est permis de jouer un atout inférieur.
        if (isMemeEquipe(joueur, maitre) && possedeQueAtout) {
            return true;
        }
    }

    return false;
}

bool hasMeilleurCarte(Jeu* jeu, Joueur* joueur, Carte carte) {
    return premiereMeilleureCarte(jeu, joueur, carte) >= 0;
}

int premiereMeilleureCarte(Jeu* jeu, Joueur* joueur, Carte carte) {
    int ordre[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    return premiereMeilleureCarteOrdre(jeu, joueur, carte, ordre, 8);
}

int premiereMeilleureCarteOrdre(Jeu* jeu, Joueur* joueur, Carte carte,
                                int ordre[8], int nbCartes) {
    Contrat contrat = jeu->enchere.contrat;
    bool carteIsAtout = contrat.atout == carte.couleur;
    bool carteIsEntame = jeu->entame->couleur == carte.couleur;

    for (int i = 0; i < nbCartes; i++) {
        Carte* carteTmp = joueur->carte[ordre[i]];
        if (carteTmp != NULL) {
            bool joueurCarteIsAtout = contrat.atout == (*carteTmp).couleur;
            bool joueurCarteIsEntame =
                jeu->entame->couleur == (*carteTmp).couleur;

            if (pointsCarte(*carteTmp, contrat) > pointsCarte(carte, contrat) &&
                carteIsAtout == joueurCarteIsAtout &&
                carteIsEntame == joueurCarteIsEntame) {
                return ordre[i];
            }
        }
    }

    return NONE;
}

void phasePli(Jeu* jeu) {
    nouveauPli(jeu);
    bool isDernierPli = jeu->nbPli == 7;

    for (int i = 0; i < 4; i++) {
        jeu->joueurActuel = &jeu->joueurs[(jeu->entameur + i) % 4];
        printf("Au tour de %s de jouer.\n", jeu->joueurActuel->nom);
        // afficherJoueur(*jeu->joueurActuel);
        int choix;

        afficherPile(jeu);

        if (!jeu->joueurActuel->isBot) {
            choix = jouerCarteHumain(jeu, jeu->joueurActuel);
        } else {
            choix = jouerCarteBot(jeu, jeu->joueurActuel);
        }

        Carte* carteJouee = jeu->joueurActuel->carte[choix];

        char carteStr[16];
        carteToString(*carteJouee, carteStr);

        printf("%s a joué : %s\n", jeu->joueurActuel->nom, carteStr);

        bool isAtout = carteJouee->couleur == jeu->enchere.contrat.atout;

        // Si c'est le premier joueur
        if (i == 0) jeu->entame = carteJouee;

        if (isAtout) {
            bool isMeilleurAtout = true;
            if (jeu->atoutPose != NULL)
                isMeilleurAtout =
                    pointsCarte(*carteJouee, jeu->enchere.contrat) >
                    pointsCarte(*jeu->atoutPose, jeu->enchere.contrat);

            if (isMeilleurAtout) jeu->atoutPose = carteJouee;
        }

        poserCarte(jeu->joueurActuel, choix, jeu);

        jeu->carteMaitre = carteGagnante(jeu);

        printf("\n");
    }
    afficherPile(jeu);
    printf("\n");

    Joueur* gagnant = poseurCarte(jeu, jeu->carteMaitre);
    Equipe* equipeGagnante = gagnant->equipe;
    int scorePli = pointsPile(jeu);

    char carteStr[16];
    carteToString(*jeu->pile[jeu->carteMaitre], carteStr);

    equipeGagnante->scoreRound += scorePli;

    printf("%s remporte le pli (équipe %d) avec \"%s\" +%d pts\n", gagnant->nom,
           equipeGagnante->id, carteStr, scorePli);
}

int pointsPile(Jeu* jeu) {
    int sum = 0;
    for (int i = 0; i < jeu->nbCartes; i++) {
        if (jeu->pile[i] != NULL) {
            sum += pointsCarte(*jeu->pile[i], jeu->enchere.contrat);
        }
    }

    return sum;
}

int jouerCarteHumain(Jeu* jeu, Joueur* joueur) {
    printf("Choisissez une carte :\n");

    bool choixPossible[8];

    Contrat contrat = jeu->enchere.contrat;

    // Affichage de la main :
    for (int i = 0; i < 8; i++) {
        if (joueur->carte[i] != NULL) {
            Carte carte = *(joueur->carte[i]);

            char carteStr[16];
            carteToString(carte, carteStr);

            bool isValid = carteValide(jeu, joueur, carte);
            choixPossible[i] = isValid;

            if (isValid) {
                printf("%d. %s%s\t(%d pts)\n", i, carteStr,
                       isAtout(jeu, carte) ? "*" : "",
                       pointsCarte(carte, contrat));
            } else {
                printf("-. %s%s\t(%d pts)\n", carteStr,
                       isAtout(jeu, carte) ? "*" : "",
                       pointsCarte(carte, contrat));
            }
        } else {
            printf("-. ---\n");
        }
    }

    int choix;

    bool ok = false;
    do {
        printf("> ");
        if (!scanf("%d", &choix)) {
            printf("Vous n'avez rien entré\n");
            continue;
        }
        if (choix >= 0 && choix < 8) {
            if (choixPossible[choix] && joueur->carte[choix] != NULL)
                ok = true;
            else
                printf("Entrée non valide.\n");
        }

    } while (!ok);

    return choix;
}

int jouerCarteBot(Jeu* jeu, Joueur* joueur) {
    int tri[8];
    int choix;
    int n = trierCarteParPoints(jeu->enchere.contrat, joueur->carte, tri, 8);

    // Si c'est l'entame il pose sa carte la plus faible
    if (jeu->entame == NULL) {
        for (int i = 0; i < n; i++) {
            if (carteValide(jeu, joueur, *joueur->carte[tri[i]])) {
                return tri[i];
            }
        }
    }

    Carte carteMaitre = *jeu->pile[jeu->carteMaitre];

    int indiceCarte = premiereMeilleureCarteOrdre(jeu, joueur,
                                                  carteMaitre, tri, n);

    if (indiceCarte == NONE) {
        // Si l’IA n’est pas en mesure de remporter le pli, elle joue sa carte
        // la plus faible
        for (int i = 0; i < n; i++) {
            if (carteValide(jeu, joueur, *joueur->carte[tri[i]])) {
                choix = tri[i];
                break;
            }
        }
    } else {
        // Si l’IA est en mesure de remporter le pli avec une de ses cartes,
        // elle le fait en posant la carte la plus faible possible
        choix = indiceCarte;
    }

    return choix;
}

Joueur* poseurCarte(Jeu* jeu, int n) {
    return &jeu->joueurs[(jeu->entameur + n) % 4];
}

bool isMemeEquipe(Joueur* j1, Joueur* j2) { return j1->equipe == j2->equipe; }

int carteGagnante(Jeu* jeu) {
    int max = 0;
    int gagnant = 0;

    for (int i = 0; i < jeu->nbCartes; i++) {
        Carte carte = *jeu->pile[i];
        int points = pointsCarte(carte, jeu->enchere.contrat);
        // bool isAtout =carte->couleur == jeu->enchere.contrat.atout;

        if (jeu->atoutPose != NULL) {
            // Si un atout a été posé
            if (points > max && isAtout(jeu, carte)) {
                // Et si cette carte est atout qui est supérieure au max
                max = points;
                gagnant = i;
            }
        } else {
            // Sinon, si il n'y a pas d'atout de posé
            if (isAtout(jeu, carte)) {
                // Si un joueur coupe c'est celle ci qui devient la meilleure
                gagnant = i;
            } else if (points > max && carte.couleur == jeu->entame->couleur) {
                max = points;
                gagnant = i;
            }
        }
    }

    return gagnant;
}