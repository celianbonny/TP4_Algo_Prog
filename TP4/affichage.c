

#include <stdio.h>  
#include "uno.h"


void afficher_couleur(int couleur)
{
    char noms[] = "RJBVN";

    printf("%c", noms[couleur]);
}


void afficher_carte(int carte)
{
    int type = carte % 100;

    if (type <= 9)          printf("%d", type);
    else if (type == PLUS2) printf("+2");
    else if (type == RV)    printf("RV");
    else if (type == PS)    printf("PS");
    else if (type == JJ)    printf("JJ");
    else                    printf("+4");

    printf(" ");
    afficher_couleur(carte / 100);
}


void afficher_ma_main(int* cartes, int nb)
{
    int i;

    for (i = 0; i < nb; i++) {
        printf("%d) ", i + 1);
        afficher_carte(cartes[i]);
        printf("\n");
    }
}