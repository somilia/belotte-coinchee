#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "joueur.h"
#include "equipe.h"
#include "contrat.h"
#include "carte.h"



void creerPaquetCarte(Carte paquet[]){
    Couleur couleurs[] = {TREFLE, CARREAU, COEUR, PIQUE};
    Valeur valeurs[] = {SEPT, HUIT, NEUF, DIX, VALET, DAME, ROI, AS};
    int ind = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 8; ++j) {
//            printf("Valeur: %d\n", valeurs[i]);
//            printf("Couleur: %d\n", couleurs[j]);

            paquet[ind].valeur=j;
            paquet[ind].couleur=i;

            /**Carte carte;
            carte.couleur = couleurs[i];
            carte.valeur = valeurs[j];
            paquet[ind] = carte;
            printf("\nIndice: %d\n", ind);
            printf("Valeur: %d\n", carte.valeur);
            printf("Couleur: %d\n", carte.couleur);**/
            ind++;

        }
    }
}

int pointcarte(Carte c/*, int atout*/) //Test
{
    int point=0;

  /**  switch(atout) {
        case 0: //Trefle
            *ptcarte[] = {0, 0, 14, 10, 20, 3, 4, 19};
            break;
        case 1: //Carreau
            *ptcarte[] = {0, 0, 14, 10, 20, 3, 4, 19};
            break;
        case 2: //Coeur
            *ptcarte[] = {0, 0, 14, 10, 20, 3, 4, 19};
            break;
        case 3: //Pique
            *ptcarte[] = {0, 0, 14, 10, 20, 3, 4, 19};
            break;
        case 4: //Sans Atout
            *ptcarte[] = {0, 0, 0, 10, 2, 3, 4, 19};
            break;
        case 5: //Tout Atout
            *ptcarte[] = {0, 0, 9, 5, 14, 1, 3, 6};
            break;
        case 6:
            exit(1);
        default:
            printf("Erreur valeur d'atout");

    }**/

    int ptcarte[]={0, 0, 0, 10, 2, 3, 4, 19};
    char *ccarte[]={"trefle","carreau","coeur","pique"};
    printf("Point carte %d \n", ptcarte[c.valeur]);
    printf(" %s \n",ccarte[c.couleur]);

    point=ptcarte[c.valeur];

    return point;
}

void affichecarte(Carte c)
{
    char *vcarte[]={"sept","huit","neuf","dix","valet","dame","roi","as"};
    char *ccarte[]={"trefle","carreau","coeur","pique"};
    printf(" %s ",vcarte[c.valeur]);
   // printf(" %s \n",ccarte[c.couleur]);
}

void afficherCarte(Carte carte)
{
    printf("Valeur: %d\n", carte.valeur);
    printf("Couleur: %d\n", carte.couleur);
    affichecarte(carte);
}




void permute(Carte *carte1, Carte *carte2)
{
    Carte perm;
    perm = *carte1,
    *carte1 = *carte2;
    *carte2=perm;
}

void melange(Carte *paquet)
{

    for(int i=0;i<=50;i++)
    {
        permute(&paquet[rand()%32], &paquet[rand()%32]);

    }
}



void distribution(Carte paquet[], Carte jeu[], Carte jeu1[], Carte jeu2[], Carte jeu3[])
{


    for(int i=0;i<32;i=i+4)
    {
        for (int p=0; p<4; p++)
        {
            jeu[p] = paquet[i];
            jeu1[p] = paquet[i+1];
            jeu2[p] = paquet[i+2];
            jeu3[p] = paquet[i+3];
        }

    }

}




/**
void melangeTest(int *tab, int n)
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

}**/