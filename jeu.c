#include "jeu.h"
#include <stdlib.h>
#include "carte.h"
#include "enchere.h"

Jeu creerJeu(Joueur joueurs[4]) {
    Jeu j;
    j.joueurs = joueurs;
    j.nbCartes = 0;
    j.nbTours = 0;
    j.donneur = 0;

    return j;
}

void resetPile(Jeu* jeu) {
    for (int i = 0; i < 4; i++) {
        jeu->pile[i] = NULL;
        jeu->nbCartes = 0;
    }
}

void afficherJeu(Jeu* jeu) {
    printf("Pile : \n");
    afficherPaquet(jeu->pile, 4);
}

bool carteValide(Jeu* jeu, Carte carte) {
    
}

// Jouer la couleur demandée à l'entame (première carte jouée)
// Si pas possible
// ->Possède un atout
//   ->Jouer un atout
//   ->Sauf si notre partenaire est maître (sa carte posé est la plus haute) 
//      =>Jouer n'importe quelle carte
// ->Ne possède pas d'atout
//   ->Jouer n'importe quelle carte

// Quand monter à l'atout:
// -l'entame est un atout
// -quand un adversaire coupe avec un atout
