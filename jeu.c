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

// Défausse = le joueur peut poser toutes ses cartes :
//      - Le joueur ne possède pas la carte de l'entame et ne possède aucun atout (et son partenaire n'a pas joué)
//      - Le joueur ne possède pas la carte de l'entame et son partenaire tient le pli (mais il peut posséder atout quand même)
//      - L'adversaire a coupé (avec un atout), et on ne possède pas d'atouts

// On doit jouer atout plus fort si :
//      - La couleur de l'entame est celle de l'atout
//      - Un adversaire a coupé avec un atout -> on doit jouer plus fort si on peut (sinon on doit jouer un atout moins fort)

// On doit jouer un atout moins fort si :
//      - Un adversaire a coupé avec un atout et qu'on n'a pas d'atout plus fort
// On peut jouer un atout moins fort si :
//      - Le partenaire a coupé et est maître et que le joueur n'a plus que des atout

// On peut jouer une carte si :
//      - Elle est de la couleur de l'entame
//      - Si c'est un atout et que personne n'a coupé


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
