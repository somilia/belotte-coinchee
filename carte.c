#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "joueur.h"
#include "equipe.h"
#include "contrat.h"
#include "carte.h"

//void creerCarte(Couleur* couleur, Valeur* valeur){
//
//}

void creerPaquetCarte(Carte paquet[]){
    Couleur couleurs[] = {TREFLE, CARREAU, COEUR, PIQUE};
    Valeur valeurs[] = {VALET, NEUF, AS, DIX, ROI, DAME, HUIT, SEPT};
    int ind = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
//            printf("Valeur: %d\n", valeurs[i]);
//            printf("Couleur: %d\n", couleurs[j]);
            Carte carte;
            carte.couleur = couleurs[i];
            carte.valeur = valeurs[j];
            paquet[ind] = carte;
            printf("Indice: %d\n", ind);
            printf("Valeur: %d\n", carte.valeur);
            printf("Couleur: %d\n", carte.couleur);
            ind++;

        }
    }
}

void afficherCarte(Carte carte)
{
    printf("Valeur: %d\n", carte.valeur);
    printf("Couleur: %d\n", carte.couleur);
}



void permute(Carte *carte1, Carte *carte2)
{
    Carte perm;
    perm = *carte1,
            *carte1 = *carte2;
    *carte2=perm;
}

void melange(Carte paquet[])
{

    int i;
    for(i=0;i<=50;i++)
    {
        permute(&paquet[rand()%32],&paquet[rand()%32]);
    }

}

/**
void distribution(Carte paquet[], Carte jeu[], Carte jeu1[], Carte jeu2[], Carte jeu3[])
{

    int com1=0;
    int com2=0;

    for(int i=0; i<32; i++)
    {
        if (i%2!=0)
        {
            jeu[com1]=paquet[i];
            com1++;
        }
        if (i%3!=0)
        {
            jeu1[com2]=paquet[i];
            com2++;
        }
        if (i%3!=0)
        {
            jeu1[com2]=paquet[i];
            com2++;
        }
    }

}**/