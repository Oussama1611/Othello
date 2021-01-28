#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "fonctions.c"


int main(void)
{
    Table T;
    entrer_noms_joueurs();
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
            printf("Le joueur : %s [%c] passe son tour ! \n",nom_a_afficher(inverse_coup(coup))->nom,inverse_coup(coup));
    }
    sauvegarde_result();

    return 0;
}