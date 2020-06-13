#ifndef PROJECTIFB_ANNONCE_H
#define PROJECTIFB_ANNONCE_H

#include "common.h"

static inline const char* annonceToString(Annonce c) {
    static const char* annonces[] = {"Carré", "Cent", "Cinquante", "Tierce", "Belote", "Rien"};
    return annonces[c.nom];
}

Annonce hasAnnonce(Jeu* jeu, Joueur* joueur);

Annonce annonce_carre(Joueur* joueur);

Annonce annonce_suite(Joueur* joueur);

Annonce hasBelote(Jeu* jeu, Joueur* joueur);

int scoreAnnonce(Annonce annonce);

#endif