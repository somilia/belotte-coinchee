#ifndef PROJECTIFB_CONTRAT_H
#define PROJECTIFB_CONTRAT_H

#include "equipe.h"
#include "joueur.h"

typedef enum Atout Atout;
enum Atout { TREFLE_ATOUT, CARREAU_ATOUT, COEUR_ATOUT, PIQUE_ATOUT, SANS_ATOUT, TOUT_ATOUT };

typedef struct Contrat {
    int valeur;
    enum Atout atout;
} Contrat;

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

void contrat(Joueur *joueur, Carte *tabcarte);

void JoueurEnchere(Joueur *joueur, int contrat, int couleur, int *Pcontrat,
                   int *Pcouleur);

void BotEnchere(Joueur *joueur[]);

#endif  // PROJECTIFB_CONTRAT_H
