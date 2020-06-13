#ifndef PROJECTIFB_PLI_H
#define PROJECTIFB_PLI_H

#include "common.h"

#define NONE -1

// Réinitialise le jeu pour lancer une nouvelle phase de pli
void nouveauPli(Jeu* jeu);

// Un pli = les 4 cartes jouées
void phasePli(Jeu* jeu);

// Retourne si la carte peut être posée sur la pile ou pas
bool carteValide(Jeu* jeu, Joueur* joueur, Carte carte);

// Retourne le joueur qui a posé la carte n dans la pile du jeu
// (n = [0,3])
Joueur* poseurCarte(Jeu* jeu, int n);

// Retourne l'indice de la carte la plus forte de la pile
int carteGagnante(Jeu* jeu);

int jouerCarteHumain(Jeu* jeu, Joueur* joueur);

int jouerCarteBot(Jeu* jeu, Joueur* joueur);

// Retourne les points des cartes posés par une équipe dans la pile du jeu
int pointsPile(Jeu *jeu);


// Retourne si le joueur possède une meilleure carte que celle en paramètre
bool hasMeilleurCarte(Contrat contrat, Joueur* joueur, Carte carte);

// Retourne l'indice de la première meilleure carte du joueur trouvée dans
int premiereMeilleureCarte(Contrat contrat, Joueur* joueur, Carte carte);

// Retourne l'indice de la première meilleure carte trouvée en fonction de l'ordre donné
int premiereMeilleureCarteOrdre(Contrat contrat, Joueur* joueur, Carte carte, int ordre[8], int nbCartes);

#endif