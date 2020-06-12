#include "annonce.h"
#include "jeu.h"

#include <stdlib.h>
#include <string.h>



Annonce hasAnnonce(Jeu* jeu, Joueur* joueur) {

    Annonce a;
    
    a = annonce_carre(joueur);

    if (a.nom == CARRE)
        return a;

    a = annonce_suite(joueur);

    return a;
}

int scoreAnnonce(Annonce annonce) {
    
    switch (annonce.nom) {
        case RIEN:
            return 0;
        case CENT:
            return 100;
        case CINQUANTE:
            return 50;
        case TIERCE:
            return 20;
        case BELOTE:
            return 20;
    }

    if (annonce.nom == CARRE) {
        int valeurs[6] = {0, 0, 150, 100, 200, 100, 100};

        return valeurs[annonce.valeur];
    }

    return 0;
}

Annonce annonce_carre(Joueur* joueur) {
    int vals[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    Annonce annonce = {.nom = RIEN};
    for (int i = 0; i < 8; i++) {
        Valeur valeur = joueur->carte[i]->valeur;
        vals[valeur]++;

        if (vals[valeur] == 4) {  // On saute les valeurs 7 et 8
            annonce.nom = CARRE;
            annonce.valeur = valeur;
        }
    }

    return annonce;
}

int comparateurCarte(const void* carte1, const void* carte2) {
    Carte c1 = *(Carte*) carte1;
    Carte c2 = *(Carte*) carte2;

    return (int) (c1.valeur - c2.valeur);
}

Annonce annonce_suite(Joueur* joueur) {
    Carte copie[8] = NULL;

    // On crée une copie de la main du joueur pour pas la modifier dans notre tri
    memcpy(copie, joueur->carte, sizeof(Carte) * 8);

    // On trie notre copie pour pouvoir plus facilment voir si il existe une suite
    qsort(copie, 8, sizeof(Carte), comparateurCarte);


    // Trefle Carreau Coeur Pique
    int cntCouleur[4] = {0,0,0,0};
    Valeur prev[4] = {-1,-1,-1,-1};
    
    int longest[4] = {-1, -1, -1, -1};

    for (int i = 0; i < 8; i++) {
        Carte c = *joueur->carte[i];

        if (prev[c.couleur] != -1) {
            if (prev[c.couleur] == c.valeur - 1) {
                cntCouleur[c.couleur]++;
            } else {
                cntCouleur[c.couleur] = 0;
            }
        }

        if (cntCouleur[c.couleur] > longest[c.couleur]) {
            longest[c.couleur] = cntCouleur[c.couleur];
        }

        prev[c.couleur] = c.valeur;
    }

    int maxSuite = 0;

    Annonce annonce;

    for (int i = 0; i < 4; i++) {
        if (longest[i] > maxSuite) {
            maxSuite = longest[i];
        }
    }

    switch(maxSuite) {
        case 5:
            annonce.nom = CENT;
            break;
        case 4:
            annonce.nom = CINQUANTE;
            break;
        case 3:
            annonce.nom = TIERCE;
            break;
        default:
            annonce.nom = RIEN;
    }

    return annonce;
}

Annonce hasBelote(Jeu* jeu, Joueur *joueur) {
    Contrat contrat = jeu->enchere.contrat;

    bool hasDame = false;
    bool hasRoi = false;

    for (int i = 0; i < 8; i++) {
        if (isAtout(jeu, *joueur->carte[i])) {
            hasDame = joueur->carte[i]->valeur == DAME; 
            hasRoi = joueur->carte[i]->valeur == ROI; 
        }

        if (hasDame && hasRoi) {
            return (Annonce){.nom = BELOTE};
        }
    }

    return (Annonce){.nom = RIEN};
}