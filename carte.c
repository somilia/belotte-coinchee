#include "carte.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contrat.h"
#include "equipe.h"
#include "joueur.h"

void initPaquetCarte(Carte paquet[]) {
    Couleur couleurs[] = {TREFLE, CARREAU, COEUR, PIQUE};
    Valeur valeurs[] = {SEPT, HUIT, NEUF, DIX, VALET, DAME, ROI, AS};
    int ind = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
            paquet[ind] = creerCarte(couleurs[i], valeurs[j]);
            ind++;
        }
    }
}

Carte creerCarte(Couleur c, Valeur v) {
    Carte carte = {c, v};
    return carte;
}

int pointcarte(Carte c /*, int atout*/)  // Test
{
    int point = 0;

    /** int ptcarteSA[] = {0, 0, 0, 10, 2, 3, 4, 19};
     int ptcarteTA[] = {0, 0, 9, 5, 14, 1, 3, 6};

     if (atout==5){  //Tout Atout

     }
     else {

     }**/
    /**
        switch(atout) {
          case 0: //Trefle

              break;
          case 1: //Carreau

              break;
          case 2: //Coeur

              break;
          case 3: //Pique

              break;
          case 4: //Sans Atout

              break;
          case 5: //Tout Atout

              break;
          case 6:
              exit(1);
          default:
              printf("Erreur valeur d'atout");
        }**/

    /** char *ccarte[]={"trefle","carreau","coeur","pique"};
     printf("Point carte %d \n", ptcarte[c.valeur]);
     printf(" %s \n",ccarte[c.couleur]);

     point=ptcarte[c.valeur];

     return point;**/
}

void afficherCarte(Carte carte) {
    printf("%s de %s\n", valeurToString(carte.valeur),
           couleurToString(carte.couleur));
}

void afficherPaquet(Carte *paquet, int nbCartes) {
    for (int i = 0; i < nbCartes; ++i) {
        afficherCarte(paquet[i]);
    }
}

void carteToString(Carte carte, char *output) {
    sprintf(output, "%s de %s", valeurToString(carte.valeur),
            couleurToString(carte.couleur));
}

void permute(Carte *carte1, Carte *carte2) {
    Carte perm;
    perm = *carte1, *carte1 = *carte2;
    *carte2 = perm;
}

void melanger(Carte *paquet, int nbMelange) {
    for (int i = 0; i <= nbMelange; i++) {
        permute(&paquet[rand() % 32], &paquet[rand() % 32]);
    }
}

void distribuer(Joueur joueurs[4], Carte paquet[TAILLE_PAQUET]) {
    int counter = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 8; j++)
        {
            joueurs[i].carte[j] = paquet[counter];
            counter++;
        }
    }
}
