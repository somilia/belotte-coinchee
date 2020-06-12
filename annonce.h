#ifndef PROJECTIFB_PLI_H
#define PROJECTIFB_PLI_H

#include "common.h"

enum NomAnnonce { CARRE, CENT, CINQUANTE, TIERCE, BELOTE, RIEN };

struct Annonce {
    enum NomAnnonce nom;
    Valeur valeur;  // Pour le carré seulement
};

Annonce hasAnnonce(Jeu* jeu, Joueur* joueur);

Annonce annonce_carre(Joueur* joueur);

Annonce annonce_suite(Joueur* joueur);

Annonce annonce_belote(Jeu* jeu, Joueur* joueur);

int scoreAnnonce(Annonce annonce);

#endif