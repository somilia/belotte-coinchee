#ifndef PROJECTIFB_ANNONCE_H
#define PROJECTIFB_ANNONCE_H

#include "common.h"

Annonce hasAnnonce(Jeu* jeu, Joueur* joueur);

Annonce annonce_carre(Joueur* joueur);

Annonce annonce_suite(Joueur* joueur);

Annonce hasBelote(Jeu* jeu, Joueur* joueur);

int scoreAnnonce(Annonce annonce);

#endif