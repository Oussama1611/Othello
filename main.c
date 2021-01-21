#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"
#include "fonctions.c"


int main(void)
{
    Table Grille;
    init_table(Grille);
    aff_table(Grille);
    char coup=Blanc;
    while(!partie_terminee(Grille))
    {
        entrer_son_coup(Grille,coup);
        aff_table(Grille);
        if(rejouer_ou_non(Grille,inverse_coup(coup)))
            coup=inverse_coup(coup);
        else
            printf("Le joueur de pions [%c] passe son tour ! \n",inverse_coup(coup));
    }

    return 0;
}