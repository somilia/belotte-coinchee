#include "contrat.h"
#include "joueur.h"
#include "equipe.h"
#include "menuenchere.h"

Contrat creerContrat(int valeur, Atout atout, Equipe* equipe) {
    Contrat c;
    c.valeur = valeur;
    c.atout = atout;
    c.equipe = equipe;

    return c;
}


void JoueurEnchere(Joueur *joueur, int contrat, int couleur, int *Pcontrat, int *Pcouleur)
{
    int choix = afficheMenuEnchere();

    int propositionContrat=0;
    int propositionCouleur=0;

    if (choix==2)
    {
        printf("Entrer une valeur de contrat \n");
        scanf("%d", &propositionContrat);

        printf("Vous avez choisi un contrat de %d\n", propositionContrat);

        while ((propositionContrat % 10 != 0) || (propositionContrat < contrat) || (propositionContrat < 80))
        {
            printf("\nLa valeur de contrat doit etre de minimum 80 ET doit etre un multiple de 10 ET doit etre superieur au contrat precedent, Reessayer: \n");
            scanf("%d", propositionContrat);
        }

        *Pcontrat = propositionContrat;
        printf("%d", propositionContrat);



        printf("Entrer une couleur: \nen choisissant une valeur entre 0 et 5 \n0: TREFLE, 1: CARREAU, 2: COEUR, 3: PIQUE, 4: SANS ATOUT, 5: TOUT ATOUT\n");
        scanf("%d", &propositionCouleur);
        while ((propositionCouleur < 0) || (propositionCouleur > 5))
        {
            printf("\nLa valeur de couleur doit etre comprise entre 1 et 4, Reessayer: \n");
            scanf("%d", propositionContrat);
        }


        *Pcouleur = propositionCouleur;


    }

}


void BotEnchere(Joueur *joueur[])
{

}

