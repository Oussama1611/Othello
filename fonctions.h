#ifndef __othello_h__
#define __othello_h__



/* Dimension du tableau */
#define D 8

/* Les pions a jouer */
#define EMPTY ' '
#define Blanc 'B' // first player
#define Noir 'N' // second player


/* definition d'un type de tableau */
typedef char Table[D][D];



/* Prototypes */
void init_table(Table T);
void aff_table(Table T);










#endif