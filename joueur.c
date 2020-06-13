#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "joueur.h"
#include "equipe.h"

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

    for (int i = 0; i < 4; i++) {
        j.possedeCouleur[i] = 0;
    }

    return j;
}

// int joueurNbCouleur(Joueur *joueur, Couleur couleur) {
//     return joueur->possedeCouleur[couleur];
// }

void afficherJoueur(Joueur j) {
    printf("Nom: %s [id=%d]\n", j.nom, j.id);
    printf("Equipe: %d\n", j.equipe->id);
    printf("Cartes [♣TR%d,♦CA%d,♥CO%d,♠PI%d] :\n", j.possedeCouleur[0], j.possedeCouleur[1], j.possedeCouleur[2], j.possedeCouleur[3]);
    afficherPaquet(j.carte, 8);
    printf("\n");
}