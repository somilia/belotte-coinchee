#ifndef PROJECTIFB_COMMON_H
#define PROJECTIFB_COMMON_H

#include <stdbool.h>

typedef enum Couleur Couleur;
typedef enum Valeur Valeur;

typedef struct Equipe Equipe;

typedef struct Carte Carte;
typedef struct Joueur Joueur;

typedef enum Atout Atout;
typedef struct Contrat Contrat;

typedef struct Jeu Jeu;

enum Atout {
    TREFLE_ATOUT,
    CARREAU_ATOUT,
    COEUR_ATOUT,
    PIQUE_ATOUT,
    SANS_ATOUT,
    TOUT_ATOUT
};
enum Couleur { TREFLE, CARREAU, COEUR, PIQUE };
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

struct Joueur {
    int id;
    char nom[20];
    struct Equipe *equipe;
    bool isBot;
    Carte* carte[8];
};

struct Equipe {
    int id;
    int score;
};
struct Contrat {
    int valeur;
    enum Atout atout;
    Equipe* equipe;
};

struct Jeu {
    Contrat contrat;
    Carte* pile[4];
    int nbCartes;
    int nbTours;
};

typedef struct NodeCarte NodeCarte;
struct NodeCarte {
    Carte carte;
    NodeCarte* suivant;
};

#endif