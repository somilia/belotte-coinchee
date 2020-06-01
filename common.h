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
    TREFLE_ATOUT    = 0,
    CARREAU_ATOUT   = 1,
    COEUR_ATOUT     = 2,
    PIQUE_ATOUT     = 3,
    SANS_ATOUT      = 4,
    TOUT_ATOUT      = 5
};
enum Couleur { TREFLE = 0, CARREAU = 1, COEUR = 2, PIQUE = 3 };
enum Valeur {
    SEPT = 0,
    HUIT = 1,
    NEUF = 2,
    DIX = 3,
    VALET = 4,
    DAME = 5,
    ROI = 6,
    AS = 7,
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
    Joueur* joueurs;
    Joueur* joueurActuel;
    int donneur;
    int nbCartes;
    int nbTours;
};

typedef struct NodeCarte NodeCarte;
struct NodeCarte {
    Carte carte;
    NodeCarte* suivant;
};

#endif