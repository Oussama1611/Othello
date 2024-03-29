#ifndef __othello2_h__
#define __othello2_h__



/* Dimension du tableau */
#define D 8

/* Les pions a jouer */
#define EMPTY ' '
#define Blanc 'B' // first player
#define Noir 'N' // second player


/* definition d'un type de tableau */
typedef char Table[D][D];

/*table des strategies; chaque case a son poids */
int Stragtegies_table[]={   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
                            0, 100, -10,  10,   3,   3,  10, -10, 100,   0,
                            0, -10, -20,  -3,  -3,  -3,  -3, -20, -10,   0,
                            0,  10,  -3,   8,   1,   1,   8,  -3,  10,   0,
                            0,   3,  -3,   1,   1,   1,   1,  -3,   3,   0,
                            0,   3,  -3,   1,   1,   1,   1,  -3,   3,   0,
                            0,  10,  -3,   8,   1,   1,   8,  -3,  10,   0,
                            0, -10, -20,  -3,  -3,  -3,  -3, -20, -10,   0,
                            0, 100, -10,  10,   3,   3,  10, -10, 100,   0,
                            0,   0,   0,   0,   0,   0,   0,   0,   0,   0,};

/* definition d'un boolean */
typedef enum 
{
    false, 
    true
}Bool;


/* Definition d'une fiche du joueur */
typedef struct _Joueur
{
    char nom[40];
    int score;
}Joueur, * Ptr_Joueur;  /* le pointeur Joueur serve a voir quel nom de joueur on va ecrire dans l'affichage */

Joueur Joueur1,Machine={"Machine",0}; /* Declaration des structures des infos du joueur  */


/* Prototypes */
void entrer_info_joueur(void);
void init_table(Table T);
void aff_table(Table T);
Bool case_valide(int ligne,int colonne);
char inverse_coup(char coup);
Bool valide_verticale_haut(Table T,int ligne,int colonne,char coup);
Bool valide_verticale_bas(Table T,int ligne,int colonne,char coup);
Bool valide_horizontale_droite(Table T,int ligne,int colonne,char coup);
Bool valide_horizontale_gauche(Table T,int ligne,int colonne,char coup);
Bool valide_diagonale_haut_droit(Table T,int ligne,int colonne,char coup);
Bool valide_diagonale_haut_gauche(Table T,int ligne,int colonne,char coup);
Bool valide_diagonale_bas_droit(Table T,int ligne,int colonne,char coup);
Bool valide_diagonale_bas_gauche(Table T,int ligne,int colonne,char coup);
Bool coup_valide(Table T,int ligne,int colonne,char coup);
Bool rejouer_ou_non(Table T,char coup);
void entrer_coup_posterieur(Table T,int ligne,int colonne ,char coup);
int evaluate_table(Table T,char coup);
int minmax(Table T,char coup,int longueur);
int generer_nombre_aleatoire(void);
int entrer_son_coup(Table T, char coup,int z);
Bool partie_terminee(Table T);
void sauvegarde_result(void);
void enregistrer_le_gagnant(void);
void Lire_trier_affi_scores(void);
void charger_partie_encours(Table T);
void enregistrer_nom_joueur(void);
void enregistrer_coup_joueur(int n);












#endif
