#ifndef PROJECTIFB_JOUEUR_H
#define PROJECTIFB_JOUEUR_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "equipe.h"
#include "carte.h"

typedef struct Joueur Joueur;

struct Joueur {
    int id;
    char nom[20];
    struct Equipe *equipe;
    bool isBot;
    Carte carte[8];
};

Joueur creerJoueur(int id, char* nom, Equipe* equipe, bool isBot);



#endif //PROJECTIFB_JOUEUR_H
