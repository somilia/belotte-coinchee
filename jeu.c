#include "jeu.h"

#include <stdlib.h>
#include "carte.h"

Jeu creerJeu() {
    Jeu j;
    j.nbCartes = 0;
    j.nbTours = 0;

    return j;
}

void retirerCartes(Jeu* jeu) {
    for (int i = 0; i < 4; i++) {
        jeu->pile[i] = NULL;
        jeu->nbCartes = 0;
    }
}

void afficherJeu(Jeu* jeu) {
    printf("Pile : \n");
    afficherPaquet(jeu->pile, 4);
}