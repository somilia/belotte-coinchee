
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "equipe.h"
#include "joueur.h"

Equipe creerEquipe(int id)
{
    Equipe equipe;
    equipe.id = id;
    equipe.score = 0;

    return equipe;
}

