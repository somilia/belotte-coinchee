#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "joueur.h"
#include "equipe.h"
#include "contrat.h"
#include "carte.h"



void creerJoueur(Joueur *joueur, bool bot, bool numEquipe, int numJoueur, char name[]/*, Carte carte[]*/) {
    joueur->numJoueur=numJoueur;
    strcpy(joueur->name, name);
    joueur->contrat=0;
    joueur->numEquipe=numEquipe;
   // joueur->equipe->numEquipe=numEquipe;
  //  memccpy(joueur->carte, carte, 8, sizeof(Carte));
    joueur->hasBelote=0;
    joueur->isCapot=0;
    joueur->choseAtout=0;
    joueur->bot=bot;
}
