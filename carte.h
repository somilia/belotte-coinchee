#ifndef PROJECTIFB_CARTE_H
#define PROJECTIFB_CARTE_H

typedef enum Couleur Couleur;
enum Couleur {
    TREFLE,
    CARREAU,
    COEUR,
    PIQUE
};

typedef enum Valeur Valeur;
enum Valeur {
    HUIT,
    SEPT,
    NEUF,
    DIX,
    VALET,
    DAME,
    ROI,
    AS,
};


/**
typedef enum Valeur Valeur;
enum Valeur {
    VALET=20,
    NEUF=14,
    AS=11,
    DIX=10,
    ROI=4,
    DAME=3,
    HUIT=0,
    SEPT=0
};**/
/**
typedef enum Valeur_HA Valeur_HA;
enum Valeur_HA {
    VALET=2,
    NEUF=0,
    AS=11,
    DIX=10,
    ROI=4,
    DAME=3,
    HUIT=0,
    SEPT=0
}; **/


typedef struct Carte Carte;
struct Carte {
    Couleur couleur;
    Valeur valeur;
};


void creerPaquetCarte(Carte paquet[]);



void afficherCarte(Carte carte);
void permute(Carte *carte1, Carte *carte2);
void melangeTest(Carte paquet);
//void distribution(Carte paquet[], Carte jeu[], Carte jeu1[], Carte jeu2[], Carte jeu3[])

void melange(int *tab, int n);


#endif //PROJECTIFB_CARTE_H
