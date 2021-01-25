#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"
#include "fonctions.c"


int main(void)
{
    Table T;
    init_table(T);
    aff_table(T);
    char coup=Blanc;
    while(!partie_terminee(T))
    {
        entrer_son_coup(T,coup);
        aff_table(T);
        if(rejouer_ou_non(T,inverse_coup(coup)))
            coup=inverse_coup(coup);
        else
            printf("Le joueur de pions [%c] passe son tour ! \n",inverse_coup(coup));
    }

    return 0;
}