//
// Created by soso_ on 04-May-20.
//

#ifndef PROJECTIFB_EQUIPE_H
#define PROJECTIFB_EQUIPE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "joueur.h"


typedef struct Equipe Equipe;
struct Equipe {
    bool numEquipe;
    int score;
};

Equipe equipe;

void creerEquipe(Equipe* equipe, bool numEquipe);






#endif //PROJECTIFB_EQUIPE_H
