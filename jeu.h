#ifndef PROJECTIFB_JEU_H
#define PROJECTIFB_JEU_H

#include "common.h"
#include "enchere.h"

// PASSER : toujours
// ENCHERIR : plus possible
//             si CAPOT ou
//             si COINCHE ou SURCOINCHE
//             si 3 ont passés
// CAPOT : si on peut plus encherir
// COINCHE : si quelqu'un a enchéri avant
// SURCOINCHÉ : seulement si l'équipe adverse a coinché


Jeu creerJeu();

void resetPile(Jeu* jeu);

bool carteValide(Jeu* jeu, Joueur* joueur, Carte carte);

// Retourne le joueur qui a posé la carte n dans la pile du jeu
// (n = [0,3])
Joueur* poseurCarte(Jeu* jeu, int n);

// Retourne l'indice de la carte la plus forte de la pile
int carteGagnante(Jeu* jeu);

int jouerCarteHumain(Jeu* jeu, Joueur* joueur);

int jouerCarteBot(Jeu* jeu, Joueur* joueur);

bool isMemeEquipe(Joueur* j1, Joueur* j2);

bool isAtout(Jeu* jeu, Carte c);

// Une donne = quand les 8 plis ont été joués
void phaseRound(Jeu* jeu);

// Un pli = les 4 cartes jouées
void phasePli(Jeu* jeu);

// Réinitialise le jeu pour lancer une nouvelle phase de pli
void nouveauPli(Jeu* jeu);

// Retourne les points des cartes posés par une équipe dans la pile du jeu
int pointsPile(Jeu *jeu);


#endif