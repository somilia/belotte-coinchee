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
            printf("\nIndice: %d\n", ind);
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

void melange(int *tab, int n)
{
    
    int i,nb2;
    nb2 = n;
    for(i=0;i<n;i++)
    {
        int tmp;
        int index = rand()%nb2;
        tmp = tab[index];
        tab[index] = tab[nb2-1];
        tab[n-i-1] = tmp;
        nb2--;
    }


    /**
    int i, j;
    int tmp;

    for( i=0; i< n-1; i++)
    {
        // j is a random number between i and n-1 (included)
        j = i + rand() % (n-i);

        //swap the values of tab[i] and tab[j]

        tmp = tab[i];
        tab[i] = tab[j];
        tab[j] = tmp;
    }
    **/

}

void permute(Carte *carte1, Carte *carte2)
{
    Carte perm;
    perm = *carte1,
    *carte1 = *carte2;
    *carte2=perm;
}
/**
void melangeTest(Carte paquet[])
{

    for(int i=0;i<=50;i++)
    {
        permute(&paquet[rand()%32], &paquet[rand()%32]);

    }
}**/


/**
void distribution(Carte paquet[], Carte jeu[], Carte jeu1[], Carte jeu2[], Carte jeu3[])
{

    Carte tab[3]={jeu[], jeu1[], jeu2[], jeu3[]};
    for(int j=0; j<4; j++)
    {
        int i=0;
        int n=7;

        for(i=0; i<n; i++)
        {
            tab[j]=paquet[i];
        }

        int i+=7;
        int n+=7;
    }


}**/