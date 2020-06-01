//
// Created by soso_ on 19-May-20.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menuenchere.h"

#include "carte.h"
#include "joueur.h"
#include "equipe.h"
#include "contrat.h"


int afficheMenuEnchere()
{
    int choixEnchere;
    printf("****************************************\n");
    printf("*                                      *\n");
    printf("*           Belote coinch%ce            *\n",130);
    printf("*                                      *\n");
    printf("****************************************\n");
    printf("\nPhase d'enchère...\n\n",138);
    printf("------------------------------------------------\n");
    printf("vos cartes : ");
    printf("JoueurX annoncec");
    printf("------------------------------------------------\n");
    printf("Que voulez vous annoncer ?\n");
    printf("1 : Passer\n");
    printf("2 : Ench%crir\n",130);
    printf("3 : Capot\n");
    printf("4 : Generale\n");
    printf("5 : Coinche\n\n");
    scanf("%d", &choixEnchere);
    switch(choixEnchere)
    {
        case 1:
            printf("vous passez..\n");
            break;
        case 2:
            printf("vous choisissez d'ench%crir\n",130);
            break;
        case 3:
            printf("vous annoncez Capot ! \n");
            break;
        case 4:
            printf("vous annoncez Generale ?? c'est quoi ?\n");
            break;
        case 5:
            printf("Capot");
            break;
        default:
            printf("vous devez entrer un chiffre entre 1 et 5\n");
    }
    return choixEnchere;
}