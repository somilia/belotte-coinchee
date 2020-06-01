#include "jeu.h"

#include <stdlib.h>
#include "carte.h"
#include "menuenchere.h"

Jeu creerJeu(Joueur joueurs[4]) {
    Jeu j;
    j.joueurs = joueurs;
    j.nbCartes = 0;
    j.nbTours = 0;

    return j;
}

struct TourEnchere {
    Contrat contrat;
    enum ChoixEnchere choix;
};

// PASSER : toujours
// ENCHERIR : plus possible
//             si CAPOT ou
//             si COINCHE ou SURCOINCHE
//             si 3 ont passés
// CAPOT : si on peut plus encherir
// COINCHE : si quelqu'un a enchéri avant
// SURCOINCHÉ : seulement si l'équipe adverse a coinché
struct EtatEnchere {
    Contrat dernierContrat;
    bool encheri;
    int nbTour;
    bool hasCoinche;
    Joueur* joueurCoinche;

    int passConsecutif;
    bool hasCapot;
};

void initEtatEnchere(struct EtatEnchere* etat) {
    etat->encheri = false;
    etat->nbTour = 0;
    etat->hasCoinche = false;
    etat->joueurCoinche = NULL;
    etat->passConsecutif = 0;
    etat->hasCapot = false;
}

void enchere(Jeu jeu) {
    bool enCours = true;

    struct EtatEnchere etat;
    initEtatEnchere(&etat);

    while (enCours) {
        for (int i = 0; i < 4; i++) {
            if (jeu.joueurs[i].isBot) {
                enchereBot(&jeu.joueurs[i]);
            } else {
                enchereHumain(&jeu.joueurs[i]);
            }
        }
    }
}

bool choixValable(enum ChoixEnchere choix, struct EtatEnchere etat) {
    switch (choix) {
        case PASSER:
            return true;

        case ENCHERIR:
            if (etat.hasCapot || etat.hasCoinche || etat.dernierContrat.valeur == 160) {
                return false;
            }

            if (etat.passConsecutif >= 3) {
                return false;
            }

            return true;

        case CAPOT:
            if (etat.hasCoinche || etat.dernierContrat.valeur == 160) {
                return false;
            }

            if (etat.passConsecutif >= 3) {
                return false;
            }

            return true;

        case COINCHER:
            if (etat.hasCoinche || !etat.encheri) {
                return false;
            }

            return true;

        case SURCOINCHER:
            if (!etat.hasCoinche) {
                return false;
            }

            return true;
    }
}


struct TourEnchere enchereBot(Joueur* joueur) {
    
}

struct TourEnchere enchereHumain(Joueur* joueur) {
    afficherMenuEnchere();

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