#ifndef PROJECTIFB_MENUENCHERE_H
#define PROJECTIFB_MENUENCHERE_H

#include "common.h"
#include "jeu.h"

static inline const char* atoutToString(enum Atout a) {
    static const char* atouts[] = {
        "Trefle",
        "Carreau",
        "Coeur",
        "Pique",
        "Sans Atout",
        "Tout Atout"
    };

    return atouts[a];
}

//                              Ordre: 7  8  9   10  V   D  R  A
static const int POINTS_SA[]        = {0, 0, 0,  10, 2,  3, 4, 19};
static const int POINTS_TA[]        = {0, 0, 9,  5,  13, 2, 3, 6 };

static const int POINTS_HORS_ATOUT[]    = {0, 0, 0,  10, 2,  3, 4, 11};
static const int POINTS_ATOUT[]         = {0, 0, 14, 10, 20, 3, 4, 11};

static inline const char* choixEnchereToString(enum ChoixEnchere c) {
    static const char* choix_encheres[] = {"Passer", "Enchérir", "Capot", "Coincher", "Surcoincher"};
    return choix_encheres[c];
}

Contrat creerContrat(int valeur, Atout atout, Equipe* equipe, bool capot);

void afficherContrat(Contrat c);

enum ChoixEnchere menuEnchere(struct EtatEnchere* etat, Joueur* joueur);

void phaseEnchere(Jeu* jeu);

void afficherJeu(Jeu* jeu);

void etatEnchereSuivant(struct EtatEnchere* etat, enum ChoixEnchere choix, Joueur* joueur);

enum ChoixEnchere enchereHumain(Joueur* joueur, struct EtatEnchere* etatEnchere);

enum ChoixEnchere enchereBot(Joueur* joueur, struct EtatEnchere* etatEnchere);

// Permet de dire si un choix est valable en fonction de l'état de l'enchère.
bool choixEnchereValide(enum ChoixEnchere choix, struct EtatEnchere etat, Joueur* joueur);

#endif //PROJECTIFB_MENUENCHERE_H
