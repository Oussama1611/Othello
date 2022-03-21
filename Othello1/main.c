#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "fonctions.c"

// main function
int main(void)
{
    Table T;
    int m=-1;
    int n;
    char coup=Blanc; 
    while(m!=0 && m!=1)
    {
    printf("Entrer votre choix : \n");
    printf("0:[continuer la partie en cours]\n");
    printf("1:[recommencer une nouvelle partie]\n");
    scanf("%d",&m);
    }
    init_table(T);
    if(m==1)
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
        printf("NB: Pour l'historique des mouvements vous pouvez remonter en haut \n");
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
