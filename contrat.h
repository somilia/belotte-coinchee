#ifndef PROJECTIFB_CONTRAT_H
#define PROJECTIFB_CONTRAT_H

#include "equipe.h"
#include "joueur.h"

static inline const char* atoutToString(enum Atout a) {
    static const char* atouts[] = {
        "Trefle",
        "Carreau",
        "Coeur",
        "Pique",
        "Sans Atout",
        "Tout Atout"
    };

    return atouts[a];
}

Contrat creerContrat(int valeur, Atout atout, Equipe* equipe);

// Ordre: 7 8 9 10 V D R A
static const int POINTS_SA[] = {0, 0, 0, 10, 2, 3, 4, 19};
static const int POINTS_TA[] = {0, 0, 9, 5, 14, 1, 3, 6};


// void JoueurEnchere(Joueur *joueur, int contrat, int couleur, int *Pcontrat,
//                    int *Pcouleur);

// void BotEnchere(Joueur *joueur[]);

#endif  // PROJECTIFB_CONTRAT_H
