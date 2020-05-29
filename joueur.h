#ifndef PROJECTIFB_JOUEUR_H
#define PROJECTIFB_JOUEUR_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "common.h"
#include "equipe.h"
#include "carte.h"

Joueur creerJoueur(int id, char* nom, struct Equipe* equipe, bool isBot);

void afficherJoueur(Joueur j);


#endif //PROJECTIFB_JOUEUR_H
