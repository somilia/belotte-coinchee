#include "sauvegarde.h"
#include <stdlib.h>
#include <stdio.h>

// Exemple de fichier scores.txt :
//
// <prenom>,<victoires>,<defaites>
// Somia,10,2 
// Lionel,6,0
// ...

void initialiserFichier() {
    FILE *fp;
    fp = fopen(SCORE_FILENAME, "a");
    fclose(fp);
}

int ajouterScore(Jeu* jeu) {

    initialiserFichier();

    FILE *fp;
    
    fp = fopen(SCORE_FILENAME, "r+");

    if (fp == NULL) {
        perror("fopen()");
        return EXIT_FAILURE;
    }

    fclose(fp);
}


int parseScoreFile() {
    initialiserFichier();
}