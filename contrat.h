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



void JoueurEnchere(Joueur *joueur, int contrat, int couleur, int *Pcontrat,
                   int *Pcouleur);

void BotEnchere(Joueur *joueur[]);

#endif  // PROJECTIFB_CONTRAT_H
