#ifndef PROJECTIFB_SAUVEGARDE_H
#define PROJECTIFB_SAUVEGARDE_H

#include <stdio.h>
#include "jeu.h"
#include "common.h"

#define SCORE_FILENAME "scores.txt"

int ajouterScore(char* nom );
void afficherScores();

void initialiserFichier();

int modifierLigne(char* id);

struct Score trouverNom(char* nom, FILE* fp);
struct Score parseLine(char line[150]);

#endif