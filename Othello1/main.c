#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "fonctions.c"


int main(void)
{
    Table T;
    int m;
    int n;
    char coup=Blanc; 
    printf("Tu veux continuer la partie en cours ? Entrer 1 si Oui , 0 si Non \n");
    scanf("%d",&m);
    init_table(T);
    if(m!=1)
    {
        entrer_noms_joueurs();
        enregistrer_noms_joueurs();
    }
    else
    {
        charger_partie_encours(T);
    }
    aff_table(T);
    while(!partie_terminee(T))
    {
        n=entrer_son_coup(T,coup);
        enregistrer_coups_joueurs(n);
        aff_table(T);
        if(rejouer_ou_non(T,inverse_coup(coup)))
            coup=inverse_coup(coup);
        else
            printf("Le joueur : %s [%c] passe son tour ! \n",nom_a_afficher(inverse_coup(coup))->nom,inverse_coup(coup));
    }
    sauvegarde_result();
    enregistrer_le_gagnant();
    Lire_trier_affi_scores();

    return 0;
}