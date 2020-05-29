#include "contrat.h"
#include "joueur.h"
#include "equipe.h"
#include "menuenchere.h"

Contrat creerContrat(int valeur, Atout atout, Equipe* equipe) {
    Contrat c;
    c.valeur = valeur;
    c.atout = atout;
    c.equipe = equipe;

<<<<<<< HEAD
    return c;
=======
void contrat(Joueur *joueur, Carte *tabcarte)
{
    int contrat=0;
    int couleur=0;
    int *Pcontrat=&contrat;
    int *Pcouleur=&couleur;



  //  tabcarte[0][0]=*tabcarte[0];

    for (int i=0; i<=3; i++)
    {

        if (joueur[i].bot == 0)
        {
            printf("\n ui\n");
          //  JoueurEnchere(&joueur[0], contrat, couleur, Pcontrat, Pcouleur);
        }
        else {
            //BotEnchere(&joueur[i]);
            printf("\n nn\n");
        }
       // printf("La proposition de contrat est de %d", *Pcontrat);

        afficherCarte(tabcarte[1]);
        printf("\n");
        afficherCarte(tabcarte[2]);
        printf("\n");
    }

>>>>>>> f8cecbf26fc869859638f7d753864ef94d24e59e
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
            printf("\nLa valeur de couleur doit etre comprise entre 0 et 5, Reessayer: \n");
            scanf("%d", propositionContrat);
        }


        *Pcouleur = propositionCouleur;


    }

}
//Détermine si le bot doit enchérir et avec quelle couleur      //3 cartes fortes ->80 pts;     4 cartes fortes -> 120 pts
void BotEnchere(Joueur *joueur, Carte *tabcarte)                //3 cartes fortes d’une couleur annoncera contrat de 80 points pour cette couleur, 4 cartes fortes de cette couleur, annoncera un contrat de 120 points pour cette couleur
{
    int propositionContrat=0;
    int propositionCouleur=0;

    Carte tabcarteCouleur0[8]={0};
    Carte tabcarteCouleur1[8]={0};
    Carte tabcarteCouleur2[8]={0};
    Carte tabcarteCouleur3[8]={0};


    int couleur0 = 0;
    int couleur1 = 0;
    int couleur2 = 0;
    int couleur3 = 0;

    for (int i=0; i<8; i++)
    {
        if (tabcarte[i].couleur==0){
            couleur0++;
            *tabcarteCouleur0=tabcarte[i];

        }
        if (tabcarte[i].couleur==1){
            couleur1++;
            *tabcarteCouleur1=tabcarte[i];
        }
        if (tabcarte[i].couleur==2){
            couleur2++;
            *tabcarteCouleur2=tabcarte[i];
        }
        if (tabcarte[i].couleur==3){
            couleur3++;
            *tabcarteCouleur3=tabcarte[i];
        }
    }
    printf("\ncouleur0: %d; couleur1: %d; couleur2: %d; couleur3: %d;\n\n", couleur0, couleur1, couleur2, couleur3);

    Carte *tabcarteC[4]={tabcarteCouleur0, tabcarteCouleur1, tabcarteCouleur2, tabcarteCouleur3};

    for (int i = 0; i<couleur0; ++i){
        printf("\nCarte de couleur 0: carte %d\n",i);

        afficherCarte(tabcarteC[0][i]);
       // afficherCarte(tabcarteCouleur1[i]);
    }
    for (int i = 0; i<couleur1; ++i){
        printf("\nCarte de couleur 1: carte %d\n",i);

        afficherCarte(tabcarteC[1][i]);   //afficherCarte(tabcarteCouleur1[i]);
    }
    for (int i = 0; i<couleur2; ++i){
        printf("\nCarte de couleur 2: carte %d\n",i);

        afficherCarte(tabcarteC[2][i]);
    }
    for (int i = 0; i<couleur3; ++i){
        printf("\nCarte de couleur 3: carte %d\n",i);

        afficherCarte(tabcarteC[3][i]);
    }

    int tabNbrCouleur[]={couleur0, couleur1, couleur2, couleur3};

    for (int i=0; i<4; i++){

        if (tabNbrCouleur[i]>4){

            for (int j=0; j<couleur0; j++){

                afficherCarte(tabcarteC[i][j]);


            }
        }
    }


}

