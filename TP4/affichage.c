

#include <stdio.h>  
#include "uno.h"


void afficher_couleur(int couleur)
{
    if (couleur == ROUGE) {
        printf("R");
    }
    else if (couleur == JAUNE) {
        printf("J");
    }
    else if (couleur == BLEU) {
        printf("B");
    }
    else if (couleur == VERT) {
        printf("V");
    }
    else {
        printf("N");
    }
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

void afficher_table()
{
    int j; 
    printf("----------------------------------------\n");
	for (j = 0; j < nb_joueurs; j++) {
		printf("Joueur %d : %d cartes\n", j+1, nb_mains[j]);
	}
    printf("Sens :");
	if (sens == 1) {
		printf(" horaire\n");
	}
	else {
		printf(" anti-horaire\n");
	}

    printf("Carte au sommet : ");
	afficher_carte(sommet_defausse());
    printf("\n");
	printf("Couleur active : ");
	afficher_couleur(couleur_active);
	printf("\n");
	printf("Cartes restantes dans la pioche : %d\n", nb_pioche);
	printf("\n----------------------------------------\n");
	printf("\nC'est au joueur %d de jouer\n", courant + 1);
}