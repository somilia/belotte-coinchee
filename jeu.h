#ifndef PROJECTIFB_JEU_H
#define PROJECTIFB_JEU_H

#include "common.h"
#include "enchere.h"

// PASSER : toujours
// ENCHERIR : plus possible
//             si CAPOT ou
//             si COINCHE ou SURCOINCHE
//             si 3 ont passés
// CAPOT : si on peut plus encherir
// COINCHE : si quelqu'un a enchéri avant
// SURCOINCHÉ : seulement si l'équipe adverse a coinché


Jeu creerJeu();

void resetPile(Jeu* jeu);

bool carteValide(Jeu* jeu, Carte carte);

#endif