#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "fonctions.h"


/* pour la sauvegarde des informations des joueurs */
void entrer_noms_joueurs(void)
{
    char name[40];
    printf("Donner votre nom (joueur des pions Blancs (B) ) : \n");
    scanf("%s",name);
    strcpy(Joueur1.nom,name);
    printf("Donner votre nom (joueur des pions Noirs (N) ) : \n");
    scanf("%s",name);
    strcpy(Joueur2.nom,name);
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*la fonction elementaire qui permet d'enregistrer les noms des joueurs */
void enregistrer_noms_joueurs(void)
{
    int i;
    remove("partie_encours.txt");
    FILE *fichier=fopen("partie_encours.txt","w");
    fprintf(fichier,"%s\n",Joueur1.nom);
    fprintf(fichier,"%s\n",Joueur2.nom);
    fclose(fichier);
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* fonction elementaire permettant de permuter les noms de joueurs lors de jeu */
Ptr_Joueur nom_a_afficher(char coup)
{
    Ptr_Joueur Ptr;
    if(coup==Blanc)
        Ptr=&Joueur1;
    else
        Ptr=&Joueur2;
    return Ptr;    
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* fonction qui initialise le tableau */
void init_table(Table T)
{
    int i,j;
    for (i=0;i<D;i++)
        for(j=0;j<D;j++)
            T[i][j]=EMPTY; // On initialise tout le tableau a des espaces vides 


    T[3][3]=Noir;   //
    T[4][4]=Noir;   // // Initialisation des quatres pions de milieu
    T[3][4]=Blanc;  // // par definition du jeu
    T[4][3]=Blanc;  //
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* fonction qui affiche le tableau */
void aff_table(Table  T)
{
    int i,j;
    
    /* Affichage des chiffres en ligne */
    printf("\n");
    for (i=0; i<D; i++) 
        printf("  %d ", i+1);

    /* Definition et affichage du tableau */

    printf("\n+");
    for (i=0; i<D; i++)
        printf("---*");
    printf("\n");
    for (i=0; i<D; i++) {
        printf("|");
        for (j=0; j<D; j++)
                printf(" %c |", T[i][j]); 
        printf(" %d\n+", 10*(i+1)); // affichage des chiffres en colonne 
        for (j=0; j<D; j++)
            printf("---*");
        printf("\n");
    }
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* fonction qui verifie si les valeurs entrees correspondent a des coups au sein du tableau */
Bool case_valide(int ligne,int colonne)
{
    if(ligne >=0 && ligne < D && colonne >=0 && colonne < D ) return true;
    else return false;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* fonction qui inverse le coup ,elle utilisee pour definir les fonctions ci-dessous */
char inverse_coup(char coup)
{
    if(coup==Noir) return Blanc;
    else return Noir;
        
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* fonction verifie si le coup est valide verticalement en haut */
Bool valide_verticale_haut(Table T,int ligne,int colonne,char coup) // le parametre coup ici sert a identifier le joueur en question 
{
    int i=ligne-1,yes=0;                    // l'entier "yes" permet de verifier si un pion existe 
    while(case_valide(i,colonne) && T[i][colonne]==inverse_coup(coup))
    {
        i--;   // la recherche de l'extrimite des pions du type "coup" 
        yes=1;
    }
    if (case_valide(i, colonne) && T[i][colonne] == coup && yes == 1) return true ;
    return false;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* fonction verifie si le coup est valide verticalement en bas */
Bool valide_verticale_bas(Table T,int ligne,int colonne,char coup)
{
    int i=ligne+1,yes=0;                    // l'entier "yes" permet de verifier si un pion existe 
    while(case_valide(i,colonne) && T[i][colonne]==inverse_coup(coup))
    {
        i++;   // la recherche de l'extrimite des pions du type "coup"
        yes=1;
    }
    if (case_valide(i,colonne) && T[i][colonne] == coup && yes == 1) return true ;
    return false;
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* fonction verifie si le coup est valide horizontalement a droite */
Bool valide_horizontale_droite(Table T,int ligne,int colonne,char coup)
{
    int j=colonne + 1,yes=0;                    // l'entier "yes" permet de verifier si un pion existe 
    while(case_valide(ligne,j) && T[ligne][j]==inverse_coup(coup))
    {
        j++;   // la recherche de l'extrimite des pions du type "coup"
        yes=1;
    }
    if (case_valide(ligne,j) && T[ligne][j] == coup && yes == 1) return true ;
    return false;
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* fonction verifie si le coup est valide horizontalement a gauche */
Bool valide_horizontale_gauche(Table T,int ligne,int colonne,char coup)
{
    int j=colonne - 1,yes=0;                    // l'entier "yes" permet de verifier si un pion existe 
    while(case_valide(ligne,j) && T[ligne][j]==inverse_coup(coup))
    {
        j--;   // la recherche de l'extrimite des pions du type "coup"
        yes=1;
    }
    if (case_valide(ligne,j) && T[ligne][j] == coup && yes == 1) return true ;
    return false;
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* fonction verifie si le coup est valide diagonalement en haut a droite (/) */
Bool valide_diagonale_haut_droit(Table T,int ligne,int colonne,char coup)
{
    int i=ligne-1,j=colonne+1,yes=0;
    while(case_valide(i,j) && T[i][j]==inverse_coup(coup))
    {
        i--;
        j++;
        yes=1;
    }
    if (case_valide(i,j) && T[i][j] == coup && yes == 1) return true ;
    return false;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* fonction verifie si le coup est valide diagonalement en haut a gauche (\) */
Bool valide_diagonale_haut_gauche(Table T,int ligne,int colonne,char coup)
{
    int i=ligne-1,j=colonne-1,yes=0;
    while(case_valide(i,j) && T[i][j]==inverse_coup(coup))
    {
        i--;
        j--;
        yes=1;
    }
    if (case_valide(i,j) && T[i][j] == coup && yes == 1) return true ;
    return false;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* fonction verifie si le coup est valide diagonalement en bas a droite (\) */
Bool valide_diagonale_bas_droit(Table T,int ligne,int colonne,char coup)
{
    int i=ligne+1,j=colonne+1,yes=0;
    while(case_valide(i,j) && T[i][j]==inverse_coup(coup))
    {
        i++;
        j++;
        yes=1;
    }
    if (case_valide(i,j) && T[i][j] == coup && yes == 1) return true ;
    return false;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* fonction verifie si le coup est valide diagonalement en bas a gauche (\) */
Bool valide_diagonale_bas_gauche(Table T,int ligne,int colonne,char coup)
{
    int i=ligne+1,j=colonne-1,yes=0;
    while(case_valide(i,j) && T[i][j]==inverse_coup(coup))
    {
        i++;
        j--;
        yes=1;
    }
    if (case_valide(i,j) && T[i][j] == coup && yes == 1) return true ;
    return false;

}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

/* defintion d'une fonction qui verifie si un coup est valide. Fonction qui rassemble toutes les fonctions predefinies ci-dessus */
Bool coup_valide(Table T,int ligne,int colonne,char coup)
{
    if (!case_valide(ligne, colonne) || T[ligne][colonne] != EMPTY) return false;
    if(valide_verticale_haut(T,ligne,colonne,coup) 
    || valide_verticale_bas(T,ligne,colonne,coup) 
    || valide_horizontale_droite(T,ligne,colonne,coup) 
    || valide_horizontale_gauche(T,ligne,colonne,coup) 
    || valide_diagonale_haut_droit(T,ligne,colonne,coup) 
    || valide_diagonale_haut_gauche(T,ligne,colonne,coup) 
    || valide_diagonale_bas_droit(T,ligne,colonne,coup) 
    || valide_diagonale_bas_gauche(T,ligne,colonne,coup))
    {
        return true;
    }
    return false;

}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* fonction pour verifier si un joueur peut jouer on non . */
Bool rejouer_ou_non(Table T,char coup)
{
    int i,j;
    for(i=0;i<D;i++)
        for(j=0;j<D;j++)
           {if(coup_valide(T,i,j,coup)) // verification s'il existe un coup valide
                return true;}
    return false;           
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* fonction permettant l'entree du coup de chaque joueur wt affichage de la grille */
int entrer_son_coup(Table T, char coup)         // l'entier k definit le nombre des coups effectues
{
    int n;
    int yes;     // pour la verification de recommencement de jeu 
    int i,j;     // un indice pour enregistrer les valeurs de n dans le table_entiers
    int ligne,colonne;
    do 
    {
        printf("C'est le tour de joueur : %s [%c]\n",nom_a_afficher(coup)->nom,coup);
        printf("Entrer 0 pour recommencer ! \n");
        printf("Veuillez saisir un entier de la forme 'ij' tel que i0 est la ligne et j est la colonne associee !\n");
        printf("Entrer l'entier : \n"); // on associe a chaque case un entier unique
        scanf("%d",&n);               // qui s'agit de la somme de l'entier de la ligne et l'entier de la colonne . 
        while(n==0)
        {   
            printf("!!!!!Est ce que cous voulez vraiement quitter cette partie ? Si oui ,enter encore 0 ! Si non enter un entier quelconque different de 0!!!!! \n");
            scanf("%d",&yes);
            if(yes==0)
            {   
                init_table(T);
                entrer_noms_joueurs();
                enregistrer_noms_joueurs();
                aff_table(T);
                break;   
            }    
            else
            {
                aff_table(T);
                printf("C'est le tour de joueur : %s [%c]\n",nom_a_afficher(coup)->nom,coup);
                printf("Veuillez saisir un entier de la forme 'ij' tel que i0 est la ligne et j est la colonne associee !\n");
                printf("Entrer l'entier : \n");
                scanf("%d",&n);
            }
        }        
        if(n!=0)
        {
            ligne=floor(n/10)-1;              // Ex : la case (4,5) est associe a l'entier 45.
            colonne=n%10-1;
        }    
    }while(!(n>10 && n<90 && n%10!=0) || !coup_valide(T,ligne,colonne,coup));
    if(coup_valide(T,ligne,colonne,coup))
        T[ligne][colonne]=coup;    
    if(valide_verticale_haut(T,ligne,colonne,coup)){
        i=ligne-1;
        while(case_valide(i,colonne) && T[i][colonne]==inverse_coup(coup)) 
            i--;
        if(case_valide(i,colonne) && T[i][colonne]==coup)
        {   i=ligne-1;
            while(T[i][colonne]==inverse_coup(coup))
            {  
                T[i][colonne]=coup;
                i--;
            } }    
    }
    if(valide_verticale_bas(T,ligne,colonne,coup)){
        i=ligne+1;
        while(case_valide(i,colonne) && T[i][colonne]==inverse_coup(coup)) 
            i++;
        if(case_valide(i,colonne) && T[i][colonne]==coup)
       {    i=ligne+1;
            while(T[i][colonne]==inverse_coup(coup))
            {
                T[i][colonne]=coup;
                i++;
            } }   
    }        
    if(valide_horizontale_droite(T,ligne,colonne,coup)) {
        j=colonne+1;
        while(case_valide(ligne,j) && T[ligne][j]==inverse_coup(coup)) 
            j++;
        if(case_valide(i,j) && T[ligne][j]==coup)
        {   j=colonne+1;
            while(T[ligne][j]==inverse_coup(coup))
            {
                T[ligne][j]=coup;
                j++;
            }  }
    }
    if(valide_horizontale_gauche(T,ligne,colonne,coup)) {
        j=colonne-1;
        while(case_valide(ligne,j) && T[ligne][j]==inverse_coup(coup)) 
            j--;
        if(case_valide(ligne,j) && T[ligne][j]==coup)
        {   j=colonne-1;
            while(T[ligne][j]==inverse_coup(coup))
            {
                T[ligne][j]=coup;
                j--;
            }  }     
    }                 
        
    if(valide_diagonale_bas_droit(T,ligne,colonne,coup)) {
        i=ligne+1;
        j=colonne+1;
        while(case_valide(i,j) && T[i][j]==inverse_coup(coup)) 
        {   i++;
            j++;
        }
        if(case_valide(i,j) && T[i][j]==coup)
        {   i=ligne+1;
            j=colonne+1;
            while(T[i][j]==inverse_coup(coup))
            {
                T[i][j]=coup;
                i++;
                j++;
            }  }              
    }
    if(valide_diagonale_bas_gauche(T,ligne,colonne,coup)) {
        i=ligne+1;
        j=colonne-1;
        while(case_valide(i,j) && T[i][j]==inverse_coup(coup)) 
        {   i++;
            j--;
        }
        if(case_valide(i,j) && T[i][j]==coup)
        {   i=ligne+1;
            j=colonne-1;
            while(T[i][j]==inverse_coup(coup))
            {
                T[i][j]=coup;
                i++;
                j--;
            }  }
    }            
    if(valide_diagonale_haut_droit(T,ligne,colonne,coup)) {
        i=ligne-1;
        j=colonne+1;
        while(case_valide(i,j) && T[i][j]==inverse_coup(coup)) 
        {   i--;
            j++;
        }
        if(case_valide(i,j) && T[i][j]==coup)
        {   i=ligne-1;
            j=colonne+1;
            while(T[i][j]==inverse_coup(coup))
            {
                T[i][j]=coup;
                i--;
                j++;
            } }
    }              
    if(valide_diagonale_haut_gauche(T,ligne,colonne,coup)) {
        i=ligne-1;
        j=colonne-1;
        while(case_valide(i,j) && T[i][j]==inverse_coup(coup)) 
        {   i--;
            j--;
        }
        if(case_valide(i,j) && T[i][j]==coup)
        {   i=ligne-1;
            j=colonne-1;
            while(T[i][j]==inverse_coup(coup))
            {
                T[i][j]=coup;
                i--;
                j--;
            } }
    }             
    return n;
// PS : A chaque condition "if" ci-dessus on voit est ce que le coup est valide selon chaque direction pour echanger les pions
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* fonction qui verifie si une partie est terminee ou non et affichage de resultat*/
Bool partie_terminee(Table T)
{
    int i,j, nb_noir=0,nb_blanc=0;
    for(i=0;i<D;i++)
        for(j=0;j<D;j++)
            if(T[i][j]==EMPTY && (rejouer_ou_non(T,Noir) || rejouer_ou_non(T,Blanc) ))
                return false;
            else if(T[i][j]==Blanc) nb_blanc++;
                else nb_noir++;
    Joueur1.score=nb_blanc;
    Joueur2.score=nb_noir;
    printf("La patrie est terminee !! \n");
    if(nb_noir<nb_blanc) 
        printf("!!!!!! Le joueur : %s [%c] a gagne !!!!!!!!\n",Joueur1.nom,Blanc);
    else if(nb_noir>nb_blanc)
        printf("!!!!!! Le joueur : %s [%c] a gagne !!!!!!!!\n",Joueur2.nom,Noir);
         else printf("!!!!! Egalite !!!!!");
    printf("le resultat est %s %d - %d %s \n",Joueur1.nom,Joueur1.score,Joueur2.score,Joueur2.nom );
    return true;                    
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* la fonction qui sert a enregistrer le resultat d'une partie dans le fichier sauvegarde.txt */
void sauvegarde_result(void)
{
    FILE *fic=fopen("Sauvegarde.txt","a");
    if(fic==NULL)
        exit(1);
    fprintf(fic,"%s (%d) VS %s (%d) ",Joueur1.nom,Joueur1.score,Joueur2.nom,Joueur2.score);
    fprintf(fic,"\n");
    fclose(fic);
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* la fonction qui va enregistrer le gagnant afin d'implementer la fonction qui va retourner les dix meilleurs scores */
void enregistrer_le_gagnant(void)
{
    FILE *fichier=fopen("Meilleures_scores.txt","a");
    if(fichier==NULL)
        exit(1);
    if(Joueur1.score<Joueur2.score)
        fprintf(fichier,"%s %d \n",Joueur2.nom,Joueur2.score);   
    if(Joueur2.score<Joueur1.score) 
        fprintf(fichier,"%s %d \n",Joueur1.nom,Joueur1.score);
    fclose(fichier);
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* la fonction qui lit tous les meilleures scores et fait le tri des scores puis l'affichage des dix meilleures scores*/
void Lire_trier_affi_scores(void)
{
    char name[40];
    int score;
    char temp_char; // un charactere temporaire pour calculer le nombre des lignes dans le fichier
    int n=0,i,j;
    FILE *fichier=fopen("Meilleures_scores.txt","r");
    if(fichier==NULL)
        exit(1);
    while(1)
    {   
        temp_char=fgetc(fichier);
        if(temp_char=='\n')    // incrementer le n si un saut de ligne est rencontre
            n++;
        if(feof(fichier))
            break; 
    }                       
    Joueur liste_scores[n];
    rewind(fichier);   // Reinitialisation du curseur
    n=0;
    while(!feof(fichier))
    {
        fscanf(fichier,"%s %d",liste_scores[n].nom,&(liste_scores[n].score));
        n++;
    }
    /* on commence par trier les pointeurs par les scores associes */
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
        {
            if(liste_scores[i].score < liste_scores[j].score)  /* le tri s'effectue en decroissance */
            {
                char temp_char[40];
                int temp_int;
                temp_int=liste_scores[i].score;                             /* on utilise un tri par selection */
                liste_scores[i].score=liste_scores[j].score;
                liste_scores[j].score=temp_int;
                strcpy(temp_char,liste_scores[i].nom);
                strcpy(liste_scores[i].nom,liste_scores[j].nom);
                strcpy(liste_scores[j].nom,temp_char);
            }
        }    
    printf("Les meilleures scores sont :\n");
    if(n-1<9)                                 // toujours une ligne est ajoutee lors de comptage donc on restreint une
    {                                         // cette didjonction des cas est due a une eventuelle incmpletude de dix scores dans le fichier
        for(i=0;i<n-1;i++)                                  
        {
            printf("%s %d \n",liste_scores[i].nom,liste_scores[i].score);
        }
    }
    else {
    for(i=0;i<10;i++)
        printf("%s %d \n",liste_scores[i].nom,liste_scores[i].score);}
    fclose(fichier);
    
}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* l fonction permet de charger une partie en cours */
void charger_partie_encours(Table T)
{
    int l;
    char coup=Blanc;
    int ligne,colonne,i,j;
    FILE *fichier=fopen("partie_encours.txt","r");
    if(fichier==NULL)
    {
        exit(1);
    }
    fscanf(fichier,"%s",Joueur1.nom); /* le fichier partie_encours a comme instrcution les deux noms en deux premieres ligne puis des entiers qui definissent les coups */
    fscanf(fichier,"%s",Joueur2.nom);
    while(1)
    {
        fscanf(fichier,"%d \n",&l);
        ligne=floor(l/10)-1;              /* malheuresement on a besoin de repeter toutes les fonctions elementaires pour effectuer les coups*/ 
        colonne=l%10-1;                  /* c'est due a la construction de entrer_son_coup() qui ne prend pas en parametre l'entier n */
        if(coup_valide(T,ligne,colonne,coup))
            T[ligne][colonne]=coup;
        if(valide_verticale_haut(T,ligne,colonne,coup)){
            i=ligne-1;
            while(case_valide(i,colonne) && T[i][colonne]==inverse_coup(coup)) 
                i--;
            if(case_valide(i,colonne) && T[i][colonne]==coup)
            {   i=ligne-1;
                while(T[i][colonne]==inverse_coup(coup))
                {  
                    T[i][colonne]=coup;
                    i--;
                } }    
        }
        if(valide_verticale_bas(T,ligne,colonne,coup)){
            i=ligne+1;
            while(case_valide(i,colonne) && T[i][colonne]==inverse_coup(coup)) 
                i++;
            if(case_valide(i,colonne) && T[i][colonne]==coup)
        {    i=ligne+1;
                while(T[i][colonne]==inverse_coup(coup))
                {
                    T[i][colonne]=coup;
                    i++;
                } }   
        }        
        if(valide_horizontale_droite(T,ligne,colonne,coup)) {
            j=colonne+1;
            while(case_valide(ligne,j) && T[ligne][j]==inverse_coup(coup)) 
                j++;
            if(case_valide(i,j) && T[ligne][j]==coup)
            {   j=colonne+1;
                while(T[ligne][j]==inverse_coup(coup))
                {
                    T[ligne][j]=coup;
                    j++;
                }  }
        }
        if(valide_horizontale_gauche(T,ligne,colonne,coup)) {
            j=colonne-1;
            while(case_valide(ligne,j) && T[ligne][j]==inverse_coup(coup)) 
                j--;
            if(case_valide(ligne,j) && T[ligne][j]==coup)
            {   j=colonne-1;
                while(T[ligne][j]==inverse_coup(coup))
                {
                    T[ligne][j]=coup;
                    j--;
                }  }     
        }                 
            
        if(valide_diagonale_bas_droit(T,ligne,colonne,coup)) {
            i=ligne+1;
            j=colonne+1;
            while(case_valide(i,j) && T[i][j]==inverse_coup(coup)) 
            {   i++;
                j++;
            }
            if(case_valide(i,j) && T[i][j]==coup)
            {   i=ligne+1;
                j=colonne+1;
                while(T[i][j]==inverse_coup(coup))
                {
                    T[i][j]=coup;
                    i++;
                    j++;
                }  }              
        }
        if(valide_diagonale_bas_gauche(T,ligne,colonne,coup)) {
            i=ligne+1;
            j=colonne-1;
            while(case_valide(i,j) && T[i][j]==inverse_coup(coup)) 
            {   i++;
                j--;
            }
            if(case_valide(i,j) && T[i][j]==coup)
            {   i=ligne+1;
                j=colonne-1;
                while(T[i][j]==inverse_coup(coup))
                {
                    T[i][j]=coup;
                    i++;
                    j--;
                }  }
        }            
        if(valide_diagonale_haut_droit(T,ligne,colonne,coup)) {
            i=ligne-1;
            j=colonne+1;
            while(case_valide(i,j) && T[i][j]==inverse_coup(coup)) 
            {   i--;
                j++;
            }
            if(case_valide(i,j) && T[i][j]==coup)
            {   i=ligne-1;
                j=colonne+1;
                while(T[i][j]==inverse_coup(coup))
                {
                    T[i][j]=coup;
                    i--;
                    j++;
                } }
        }              
        if(valide_diagonale_haut_gauche(T,ligne,colonne,coup)) {
            i=ligne-1;
            j=colonne-1;
            while(case_valide(i,j) && T[i][j]==inverse_coup(coup)) 
            {   i--;
                j--;
            }
            if(case_valide(i,j) && T[i][j]==coup)
            {   i=ligne-1;
                j=colonne-1;
                while(T[i][j]==inverse_coup(coup))
                {
                    T[i][j]=coup;
                    i--;
                    j--;
                } }
        }
        coup=inverse_coup(coup);             
        if(feof(fichier))
            break;
    }

}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* la fonction elementaire qui permet l'enregistrement des coups */
void enregistrer_coups_joueurs(int k)
{
    FILE *fichier=fopen("partie_encours.txt","a");
    fprintf(fichier,"%d\n",k);     /* on va ecrire les mouvements effectuees dans le fichier a partir du tableau Table_entiers */ 
    fclose(fichier); 
}