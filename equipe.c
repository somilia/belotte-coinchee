//
// Created by soso_ on 04-May-20.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "equipe.h"
#include "joueur.h"

void creerEquipe(Equipe* equipe, bool numEquipe)
{
    equipe->numEquipe=numEquipe;
    equipe->score=0;
}
