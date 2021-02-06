#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonctions.h"
#include "fonctions.c"


int main(void)
{
    Table T;
    int m=-1;
    int z;
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
        entrer_nom_joueur();
        enregistrer_nom_joueur();
        printf("Choisir niveau de difficulte :\n");
        printf("1:[easy]\n")  ;
        printf("2:[medium]\n");
        scanf("%d",&z);
    }
    else
    {
        charger_partie_encours(T);
        printf("Avec quelle difficulte vous voulez continuer :\n");
        printf("1:[easy]\n")  ;
        printf("2:[medium]\n");
        scanf("%d",&z);
    }
    aff_table(T);
    while(!partie_terminee(T))
    {
        n=entrer_son_coup(T,coup,z);
        enregistrer_coup_joueur(n);
        aff_table(T);
        printf("NB: Pour l'historique des mouvements vous pouvez remonter en haut \n");
        if(rejouer_ou_non(T,inverse_coup(coup)))
            coup=inverse_coup(coup);
        else
            if(coup==Noir)
                printf("Vous passez votre tour ! \n");
            else
                printf("La machine passe son tour ! \n");
                
    }
    sauvegarde_result();
    enregistrer_le_gagnant();
    Lire_trier_affi_scores();

    return 0;
}