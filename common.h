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

typedef struct Annonce Annonce;

#define TAILLE_PAQUET 32

enum ChoixEnchere {
    PASSER,
    ENCHERIR,
    CAPOT,
    COINCHER,
    SURCOINCHER,
};

enum Atout {
    TREFLE_ATOUT = 0,
    CARREAU_ATOUT = 1,
    COEUR_ATOUT = 2,
    PIQUE_ATOUT = 3,
    SANS_ATOUT = 4,
    TOUT_ATOUT = 5
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

enum NomAnnonce { CARRE, CENT, CINQUANTE, TIERCE, BELOTE, RIEN };

struct Annonce {
    enum NomAnnonce nom;
    Valeur valeur;  // Pour le carré seulement
};

struct Carte {
    Couleur couleur;
    Valeur valeur;
};

struct Joueur {
    int id;
    char nom[20];
    Equipe* equipe;
    bool isBot;
    Carte* carte[8];

    Annonce annonce;
    Annonce belote;

    // Nombre de couleurs que possède le joueur en main
    // {Trefle, Carreau, Coeur, Pique}
    int possedeCouleur[4];
};

struct Equipe {
    int id;
    int score;
    int scoreRound;
};
struct Contrat {
    int valeur;
    enum Atout atout;
    Equipe* equipe;
    bool capot;
};

typedef struct NodeCarte NodeCarte;
struct NodeCarte {
    Carte carte;
    NodeCarte* suivant;
};

struct EtatEnchere {
    Contrat contrat;

    bool encheri;
    int nbTour;
    Equipe* coinche;
    Equipe* surcoinche;

    Joueur* joueurCoinche;

    int passConsecutif;
    bool hasCapot;
};

struct Jeu {
    struct EtatEnchere enchere;

    Carte* paquet;

    Carte* pile[4];

    // Carte de l'entame
    Carte* entame;

    // Carte du meilleur atout au cours du pli (celle qui a coupé)
    Carte* atoutPose;

    // Position de la carte la plus forte posée pour le moment
    int carteMaitre;

    // Nombre de cartes sur le jeu (nombres d'éléments dans pile[4])
    int nbCartes;

    // Indice du joueur qui distribue 
    int donneur;

    // Indice du joueur dans joueurs[] qui commence le pli ou l'enchère
    int entameur;

    Joueur* joueurs;
    Joueur* joueurActuel;
    Joueur* joueurPrincipal;

    Equipe* equipes;

    int pointsObjectif; // Points qu'il faut atteindre pour finir le jeu
    
    int nbPli;
    int nbRound;
};

#endif