#ifndef PROJECTIFB_CONTRAT_H
#define PROJECTIFB_CONTRAT_H

#include "joueur.h"
#include "equipe.h"

void contrat(Joueur *joueur, Carte *tabcarte);

void JoueurEnchere(Joueur *joueur, int contrat, int couleur, int *Pcontrat, int *Pcouleur);

void BotEnchere(Joueur *joueur, Carte *tabcarte);





#endif //PROJECTIFB_CONTRAT_H
