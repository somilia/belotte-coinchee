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

    for (int i = 0; i < 8; i++) {
        j.carte[i] = NULL;
    }
    return j;
}

void afficherJoueur(Joueur j) {
    printf("Nom: %s [id=%d]\n", j.nom, j.id);
    printf("Equipe: %d\n", j.equipe->id);
    printf("Cartes:\n");
    afficherPaquet(j.carte, 8);
    printf("\n")
}