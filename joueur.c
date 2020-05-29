#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "joueur.h"
#include "equipe.h"
#include "contrat.h"
#include "carte.h"

Joueur creerJoueur(int id, char* nom, Equipe* equipe, bool isBot) {
    Joueur j;
    j.id = id;
    strcpy(j.nom, nom);
    j.equipe = equipe;
    j.isBot = isBot;
    return j;
}