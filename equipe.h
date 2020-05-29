
#ifndef PROJECTIFB_EQUIPE_H
#define PROJECTIFB_EQUIPE_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "joueur.h"

typedef struct Equipe Equipe;
struct Equipe {
    int id;
    int score;
};

Equipe creerEquipe(int id);

#endif  // PROJECTIFB_EQUIPE_H
