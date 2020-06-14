#include "sauvegarde.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Exemple de fichier scores.txt :
//
// <prenom>,<victoires>,<defaites>
// Somia,10,2
// Lionel,6,0
// ...

void initialiserFichier() {
    FILE* fp;
    fp = fopen(SCORE_FILENAME, "a");
    fclose(fp);
}

struct Score {
    char nom[30];
    int victoires;
    int defaites;
    long int pos;  // Position du nom dans le fichier
};

int ajouterScore(char* nom) {
    initialiserFichier();

    FILE* fp;

    fp = fopen(SCORE_FILENAME, "r+");

    if (fp == NULL) {
        perror("fopen()");
        return EXIT_FAILURE;
    }

    struct Score score = trouverNom(nom, fp);

    // Si c'est la fin du fichier c'est qu'on a pas trouvé le joueur gagnant
    if (score.pos == -1) {
        // Créer une nouvelle ligne

        fseek(fp, 0, SEEK_END);
        
        printf("[Scores] Nouveau nom !\n");
        fprintf(fp, "%s %-5d\n", nom, 1);
    } else {
        // Si on a trouvé quelqu'un
        fseek(fp, score.pos, SEEK_SET);
        // printf("%s, %d, pos=%ld\n", score.nom, score.victoires, score.pos);
        char buffer[128];

        sprintf(buffer, "%s %-5d\n", score.nom, score.victoires + 1);
        // printf("%s", buffer);

        fputs(buffer, fp);
    }

    fclose(fp);
}

void afficherScores() {
    FILE *fp;

    fp = fopen(SCORE_FILENAME, "r");

    printf("\n----- Livre des records ------\n");

    char line[150];
    struct Score score;
    while (fgets(line, 150, fp) !=  NULL) {
        score =parseLine(line);
        printf("- %-10s%-2d victoires\n", score.nom, score.victoires);
    }

    printf("\n------------------------------\n");

    fclose(fp);
}

struct Score trouverNom(char* nom, FILE* fp) {
    char line[150];
    char* token;

    long pos = ftell(fp);

    struct Score score;

    while (fgets(line, 150, fp) != NULL) {
        token = strtok(line, ",");
        score = parseLine(line);

        if (strcmp(score.nom, nom) == 0) {
            score.pos = pos;
            return score;
        }

        pos = ftell(fp);
    }
    
    score.pos = -1;
    return score;
}

int parseScoreFile() { initialiserFichier(); }

struct Score parseLine(char line[150]) {
    struct Score score = {""};
    char* token;
    char delim[] = " \n";

    token = strtok(line, delim);

    if (token != NULL) {
        strcpy(score.nom, token);
        // printf("token %s\n", token);
        token = strtok(NULL, delim);
        // printf("token %s\n", token);
        score.victoires = atoi(token);

        // token = strtok(NULL, delim);
        // // printf("token %s\n", token);
        // score.defaites = atoi(token);
    }

    return score;
}