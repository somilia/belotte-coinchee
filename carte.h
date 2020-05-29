#ifndef PROJECTIFB_CARTE_H
#define PROJECTIFB_CARTE_H

#include "joueur.h"

#define TAILLE_PAQUET 32

typedef struct Carte Carte;
typedef enum Couleur Couleur;
typedef enum Valeur Valeur;


enum Couleur {
    TREFLE,
    CARREAU,
    COEUR,
    PIQUE
};

enum Valeur {
    SEPT,
    HUIT,
    NEUF,
    DIX,
    VALET,
    DAME,
    ROI,
    AS,
};

struct Carte {
    Couleur couleur;
    Valeur valeur;
};




static inline const char* couleurToString(Couleur c) {
    static const char* str_couleur[] = {"Trefle","Carreau","Coeur","Pique"};
    return str_couleur[c];
}

static inline const char* valeurToString(Valeur v) {
    static const char* str_valeur[] = {"Sept","Huit","Neuf","Dix","Valet","Dame","Roi","As"};
    return str_valeur[v];
}


Carte creerCarte(Couleur c, Valeur v);
void carteToString(Carte carte, char *output);

void initPaquetCarte(Carte paquet[]);

int pointcarte(Carte c/*, int atout*/);

void afficherCarte(Carte carte);

void afficherPaquet(Carte *paquet, int nbCartes);

void permute(Carte *carte1, Carte *carte2);
void melanger(Carte *paquet, int nbMelange);

void distribuer(Joueur joueurs[4], Carte paquet[TAILLE_PAQUET]);

//void melangeTest(int *tab, int n);

#endif //PROJECTIFB_CARTE_H
