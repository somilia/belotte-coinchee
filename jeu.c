#include "jeu.h"
#include <stdlib.h>
#include "carte.h"
#include "enchere.h"

Jeu creerJeu(Joueur joueurs[4], Equipe equipes[2], Carte paquet[TAILLE_PAQUET]) {
    Jeu j;
    j.joueurs = joueurs;
    j.nbPli = 0;
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

void nouveauPli(Jeu* jeu) {
    jeu->atoutPose = NULL;
    resetPile(jeu);

    jeu->carteMaitre = 0;
    jeu->entame = NULL;
    jeu->atoutPose = NULL;

    if (jeu->nbPli == 0)
        jeu->entameur = (jeu->donneur -  1) % 4;
    else
        jeu->entameur = poseurCarte(jeu, carteGagnante(jeu))->id;

    jeu->joueurActuel = &jeu->joueurs[jeu->entameur];
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
    Joueur* maitre = poseurCarte(jeu, jeu->carteMaitre);

    if (jeu->entame == NULL) {
        return true;
    }

    if (jeu->atoutPose == NULL && jeu->entame != NULL) {
        if (carte.couleur == jeu->entame->couleur)
            return true;
    }

    if (jeu->atoutPose == NULL && isAtout(jeu, carte))
        return true;


    if (jeu->atoutPose
        && isAtout(jeu, carte)
        && pointsCarte(carte, contrat) > pointsCarte(*jeu->atoutPose, contrat))
        return true;

    // Si le partenaire est le maître de l'équipe on peut jouer n'importe quelle carte
    if (isMemeEquipe(joueur, maitre))
        return true;

    if (jeu->entame != NULL)
    if (joueur->possedeCouleur[jeu->entame->couleur] == 0
            && !isMemeEquipe(joueur, maitre)
            && isAtout(jeu, carte))
        return true;
    
    

    return false;
}

void phasePli(Jeu* jeu) {

    nouveauPli(jeu);
    bool isDernierPli = jeu->nbPli == 7;

    for (int i = 0; i < 4; i++) {
        jeu->joueurActuel = &jeu->joueurs[(jeu->entameur + i) % 4];
        printf("Au tour de %s de jouer.\n", jeu->joueurActuel->nom);
        int choix;

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

        if (i == 0) // Si c'est le premier joueur
            jeu->entame = carteJouee;

        if (isAtout)
            jeu->atoutPose = carteJouee;

        poserCarte(jeu->joueurActuel, choix, jeu);

        jeu->carteMaitre = carteGagnante(jeu);
    }

    Equipe* gagnant = poseurCarte(jeu, jeu->carteMaitre)->equipe;
    int scorePli = pointsPile(jeu);

    gagnant->score += scorePli;
    printf("L'équipe %d remporte le pli (+%d pts)\n", gagnant->id, scorePli);
}

int pointsPile(Jeu *jeu) {
    int sum = 0;
    for (int i = 0; i < jeu->nbCartes; i++) {
        if (jeu->pile[i] != NULL) {
            sum += pointsCarte(*jeu->pile[i], jeu->enchere.contrat);
        }
    }

    return sum;
}


void phaseRound(Jeu* jeu) {
    distribuer(jeu->joueurs, jeu->paquet);
    jeu->nbPli = 0;

    phaseEnchere(jeu);
    for (int i = 0; i < 8; i++) {
        phasePli(jeu);
        jeu->nbPli++;
    }
};

int jouerCarteHumain(Jeu* jeu, Joueur* joueur){
    printf("Choisissez une carte :\n");

    bool choixPossible[8];

    for (int i = 0; i < 8; i++) {
        Carte carte = *(joueur->carte[i]);
        // printf("prout\n");
        char carteStr[16];
        carteToString(carte, carteStr);

        bool isValid = carteValide(jeu, joueur, carte);
        choixPossible[i] = isValid;

        if (isValid) {
            printf("%d. %s\n", i, carteStr);
        } else {
            printf("-. %s (pas jouable)\n", carteStr);
        }
    }

    int choix;

    bool ok = false;
    do {
        printf("Carte : ");
        if(!scanf("%d", &choix)) {
            printf("Vous n'avez rien entré\n");
        }

        if (choixPossible[choix]) {
            ok = true;
        } else {
            printf("Carte non valide...\n");
        }

    } while(!ok);

    return choix;
}

int jouerCarteBot(Jeu* jeu, Joueur* joueur){}


Joueur* poseurCarte(Jeu* jeu, int n) {
    return &jeu->joueurs[(jeu->entameur + n - 1) % 4];
}

bool isMemeEquipe(Joueur* j1, Joueur* j2) {
    return j1->equipe == j2->equipe;
}

bool isAtout(Jeu* jeu, Carte c) {
    return jeu->enchere.contrat.atout == c.couleur;
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