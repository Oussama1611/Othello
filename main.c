#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"
#include "fonctions.c"


int main(void)
{
    char tableau[D][D];
    init_table(tableau);
    aff_table(tableau);
    return 0;
}