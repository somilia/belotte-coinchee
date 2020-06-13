#ifndef PROJECTIFB_SAUVEGARDE_H
#define PROJECTIFB_SAUVEGARDE_H

#include <stdio.h>
#include "jeu.h"
#include "common.h"

#define SCORE_FILENAME "scores.txt"

int ajouterScore(Jeu* jeu);

void initialiserFichier();

int modifierLigne(char* id);


#endif