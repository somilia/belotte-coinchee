#ifndef PROJECTIFB_JOUEUR_H
#define PROJECTIFB_JOUEUR_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "equipe.h"
#include "carte.h"

typedef struct Joueur Joueur;
struct Joueur {
    int numJoueur;
    char name[20];
    int contrat;
    int numEquipe;
    struct Equipe *equipe;
    bool hasBelote;
    bool isCapot;
    bool choseAtout;
    bool bot;
    struct Carte *carte;
};

Joueur joueur[3];


void creerJoueur(Joueur *joueur, bool bot, bool numEquipe, int numJoueur, char name[]/*, Carte carte[]*/);






#endif //PROJECTIFB_JOUEUR_H
