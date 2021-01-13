#include <stdio.h>
/* Dimension du tableau */
#define D 8

/* Les pions a jouer */
#define EMPTY ' '
#define Blanc 'B' // first player
#define Noir 'N' // second player

/* definition d'un type de tableau */
typedef char Table[D][D];


/* Initialisation du tableau */

void init_table(Table T)
{
    int i,j;
    for (i=0;i<D;i++)
        for(j=0;j<D;j++)
            T[i][j]=EMPTY; // On initialise tout le tableau a des espaces vides 


    T[3][3]=Noir;   //
    T[4][4]=Noir;   // // Initialisation des quatres pions de milieu
    T[3][4]=Blanc;  // // Par definition du jeu
    T[4][3]=Blanc;  //
}

/* Affichage du Tableau */

void aff_table(Table T)
{
    int i,j;
    
    /* Affichage des chiffres en ligne */
    printf("\n");
    for (i=0; i<D; i++) 
        printf("  %d ", i+1);

    /* Definition et affichage de la grille */

    printf("\n+");
    for (i=0; i<D; i++)
        printf("---*");
    printf("\n");
    for (i=0; i<D; i++) {
        printf("|");
        for (j=0; j<D; j++)
           {if (T[i][j] == Blanc)
                printf("\033[31m %c \033[0m|", T[i][j]); // Les blancs en rouge 
            else
                printf("\033[34m %c \033[0m|", T[i][j]);} // Les noirs en bleu 
        printf(" %d\n+", i+1); // affichage des chiffres en colonne 
        for (j=0; j<D; j++)
            printf("---*");
        printf("\n");
    }
}


int main()
{
    char tableau[D][D];
    init_table(tableau);
    aff_table(tableau);
    return 0;
}

