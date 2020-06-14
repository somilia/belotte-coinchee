//
// Created by soso_ on 19-May-20.
//
#include "enchere.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "carte.h"

#include "equipe.h"
#include "joueur.h"

Contrat creerContrat(int valeur, Atout atout, Equipe* equipe, bool capot) {
    Contrat c;
    c.valeur = valeur;
    c.atout = atout;
    c.equipe = equipe;
    c.capot = capot;

    return c;
}

void afficherContrat(Contrat c) {
    if (c.capot) {
        printf("[Equipe %d] Capot - Atout: %s\n", c.equipe->id, atoutToString(c.atout));
    } else {
        printf("[Equipe %d] Valeur: %d - Atout: %s\n", c.equipe->id, c.valeur, atoutToString(c.atout));
    }
}


enum ChoixEnchere menuEnchere(struct EtatEnchere* etat, Joueur* joueur) {
    if (etat->encheri || etat->hasCapot) {
        printf("--------- Contrat actuel ---------\n");
        afficherContrat(etat->contrat);
        printf("----------------------------------\n");
    }

    printf("Que voulez vous annoncer ?\n");
    bool choixPossibles[5];

    for (enum ChoixEnchere i = PASSER; i < 5; i++) {
        choixPossibles[i] = choixEnchereValide(i, *etat, joueur);
        if (choixPossibles[i]) {
            printf("%d : %s\n", i, choixEnchereToString(i));
        }
    }

    int choix;

    bool ok = false;
    do {
        if (!scanf("%d", &choix)) {
            printf("Vous n'avez rien entré\n");
        }

        if (choix >= 0 && choix < 5) {
            if (choixPossibles[choix]) {
                ok = true;
            } else {
                printf("Choix pas possible !\n");
            }
        } else {
            printf("Le choix doit être entre 0 et 5 !\n");
        }
    } while (!ok);

    switch (choix) {
        case 0:
            break;
        case 1: {
            int val;
            printf("Vous proposez un contrat :\n");

            // Saisie du contrat (valeur + atout)
            while (1) {
                printf("Valeur : ");

                if (!scanf("%d", &val)) {
                    printf("Vous n'avez rien entré\n");
                };

                
                if (val % 10 == 0) { // Il faut que la valeur soit un multiple de 10
                    int minVal = 79;

                    if (etat->encheri) {
                        // SI jamais un contrat existe déjà, càd que quelqu'un a déjà enchéri
                        // on change la valeur minimale à la valeur du dernier contrat
                        minVal = etat->contrat.valeur;
                    }

                    if (val > minVal) {
                        break;
                    } else {
                        printf("La valeur doit être plus grande que %d\n",
                               minVal);
                    }
                } else {
                    printf("Veuillez entrer un multiple de 10.\n");
                }
            }

            printf("Choisissez l'atout :\n");
            for (int i = 0; i < 6; i++) {
                printf("%d. %s\n", i, atoutToString(i));
            }

            int atout;

            do {
                printf("Atout : ");
                if (!scanf("%d", &atout)) {
                    printf("Vous n'avez rien entré.\n");
                };
            } while (atout < 0 || atout > 6);

            printf("Vous avez choisi %s.\n", atoutToString(atout));


            // On crée un contrat que l'on assigne à l'état de l'enchère
            Contrat contrat = creerContrat(val, (Atout)atout, joueur->equipe, false);
            etat->contrat = contrat;
            break;
        }
        case 2:
            printf("Vous annoncez Capot ! \n");

            printf("Choisissez l'atout :\n");
            for (int i = 0; i < 6; i++) {
                printf("%d. %s\n", i, atoutToString(i));
            }

            int atout;

            // Saisie du contrat (seulement atout)
            do {
                printf("Atout : ");
                if (!scanf("%d", &atout)) {
                    printf("Vous n'avez rien entré\n");
                };
            } while (atout < 0 || atout > 5);

            printf("Vous avez choisi %s.\n", atoutToString(atout));

            // On crée un contrat fixe que l'on assigne à l'état de l'enchère
            Contrat contrat = creerContrat(250, (Atout)atout, joueur->equipe, true);
            etat->contrat = contrat;
            break;
        case 3:
            // printf("Vous coinchez !\n");
            break;
        case 4:
            // printf("Vous surcoinchez !\n");
            break;
    }

    return (enum ChoixEnchere)choix;
}


void initEtatEnchere(struct EtatEnchere* etat) {
    etat->nbTour = 0;
    etat->passConsecutif = 0;

    etat->encheri = false;
    etat->hasCapot = false;
    
    etat->joueurCoinche = NULL;
    etat->coinche = NULL;
    etat->surcoinche = NULL;
}

void etatEnchereSuivant(struct EtatEnchere* etat, enum ChoixEnchere choix, Joueur* joueur) {
    switch (choix) {
        case PASSER:
            etat->passConsecutif++;
            break;
        case ENCHERIR:
            etat->passConsecutif = 0;
            etat->encheri = true;
            break;
        case CAPOT:
            etat->passConsecutif = 0;
            etat->encheri = true;
            etat->hasCapot = true;
            break;
        case COINCHER:
            etat->passConsecutif = 1;
            etat->coinche = joueur->equipe;
            break;
        case SURCOINCHER:
            etat->passConsecutif = 0;
            etat->surcoinche = joueur->equipe;
            break;
    }
}

void phaseEnchere(Jeu* jeu) {
    bool enCours = true;

    printf("****************************************\n");
    printf("*           Phase d'enchère            *\n");
    printf("****************************************\n\n");

    struct EtatEnchere etat;
    initEtatEnchere(&etat);

    int tourEnchere = 0;

    while (enCours) {
        enum ChoixEnchere choix;

        jeu->joueurActuel = &jeu->joueurs[(jeu->donneur + tourEnchere) % 4];

        printf("Au tour de %s d'annoncer.\n", jeu->joueurActuel->nom);

        if (jeu->joueurActuel->isBot) {
            choix = enchereBot(jeu->joueurActuel, &etat);
        } else {
            printf("Votre main :\n");
            afficherPaquet(jeu->joueurActuel->carte, 8);
            printf("\n");
            choix = enchereHumain(jeu->joueurActuel, &etat);
        }

        afficherAnnonceEnchere(*jeu->joueurActuel, etat, choix);
        etatEnchereSuivant(&etat, choix, jeu->joueurActuel);

        enCours = etat.passConsecutif != 3 && !etat.surcoinche;

        tourEnchere++;
    }

    jeu->enchere = etat;
}

void afficherAnnonceEnchere(Joueur joueur, struct EtatEnchere etat, enum ChoixEnchere choix) {
    switch(choix) {
        case PASSER:
            printf("%s passe.\n", joueur.nom);
            break;
        case ENCHERIR:
            printf("%s enchéri avec le contrat : ", joueur.nom);
            afficherContrat(etat.contrat);
            break;
        case CAPOT:
            printf("%s demande le Capot !", joueur.nom);
            break;
        case COINCHER:
            printf("%s coinche !", joueur.nom);
            break;
        case SURCOINCHER:
            printf("%s surcoinche !!", joueur.nom);
            break;
    }
}

bool choixEnchereValide(enum ChoixEnchere choix, struct EtatEnchere etat, Joueur* joueur) {
    switch (choix) {
        case PASSER:
            // On peut toujours passer.
            return true;

        case ENCHERIR:
            if (etat.hasCapot || etat.coinche || etat.passConsecutif >= 3) {
                // On ne peut pas enchérir si :
                // Un joueur a fait capot
                // Un joueur a déjà coinché
                // Trois joueurs ont passé consécutivement
                return false;
            }

            return true;

        case CAPOT:
            if (etat.coinche || etat.hasCapot ||  etat.passConsecutif >= 3) {
                // On ne peut pas faire capot si :
                // Un joueur a déjà coinché
                // Trois joueurs ont passé consécutivement
                return false;
            }

            return true;

        case COINCHER:
            if (etat.coinche || !etat.encheri || etat.contrat.equipe == joueur->equipe) {
                // Si quelqu'un a déjà coinché
                // Ou si personne n'a enchéri (= aucun contrat)
                // ou si le dernier contrat appartient à l'équipe du joueur actuel
                return false;
            }

            return true;

        case SURCOINCHER:
            if (!etat.coinche || etat.coinche == joueur->equipe) {
                // On ne peut pas surcoincher si:
                // L'équipe qui a coinché est la même que le joueur actuel
                return false;
            }

            return true;
    }
}

//3 cartes fortes ->80 pts;     4 cartes fortes -> 120 pts
enum ChoixEnchere enchereBot(Joueur* joueur, struct EtatEnchere* etat) {
    // Ce sont les cartes qui donnent des points
    bool cartesForte[] = {0, 0, 1, 1, 1, 0, 1, 1};

    // Nombre de cartes dans la même couleur considérée comme forte
    int nbCartesFortes[] = {0, 0, 0, 0};

    for (int i = 0; i < 8; i++) {
        bool isForte = cartesForte[joueur->carte[i]->valeur];
        if (isForte) {
            nbCartesFortes[joueur->carte[i]->couleur]++;
        }
    }

    Couleur meilleureCouleur = -1;
    int maxNb = 0;

    // Retourne la couleur qui a le plus de carte forte
    for (Couleur i = TREFLE; i <= PIQUE; i++) {
        if (nbCartesFortes[i] > maxNb) {
            maxNb = nbCartesFortes[i];
            meilleureCouleur = i;
        }
    }

    if (choixEnchereValide(ENCHERIR, *etat, joueur) && maxNb >= 3) {
        int valeurContrat;

        // Si quelqu'un avait déjà enchéri on rajoute 10 ou 30 à la valeur du contrat
        // Mais si le contrat dépasse 140  on passe
        if (etat->encheri) {
            if (etat->contrat.valeur <= 130 && etat->contrat.equipe != joueur->equipe) {
                if (maxNb == 3)
                    valeurContrat = etat->contrat.valeur + 10;
                else if (maxNb >= 4)
                    valeurContrat = etat->contrat.valeur + 20;
            } else {
                return PASSER;
            }
        } else {
            // Si personne n'a enchéri avant
            if (maxNb == 3)
                valeurContrat = 80;
            else if (maxNb >= 4)
                valeurContrat = 120;
        }
        
        Contrat contrat = creerContrat(valeurContrat, (Atout) meilleureCouleur, joueur->equipe, false);

        etat->contrat = contrat;

        return ENCHERIR;
    }

    return PASSER;
}

enum ChoixEnchere enchereHumain(Joueur* joueur, struct EtatEnchere* etatEnchere) {
    return menuEnchere(etatEnchere, joueur);
}

