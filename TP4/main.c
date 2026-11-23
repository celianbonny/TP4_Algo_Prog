

#include <stdio.h>    
#include <stdlib.h>   
#include <time.h>     
#include "uno.h"

int pioche[MAX_CARTES];
int nb_pioche;

int defausse[MAX_CARTES];
int nb_defausse;

int mains[MAX_JOUEURS][MAX_CARTES];
int nb_mains[MAX_JOUEURS];

int nb_joueurs;
int courant;
int sens;
int couleur_active;


// pour tester
int main()
{
    int sommet;

	srand((unsigned int)time(NULL)); // initialisation du générateur de nombres aléatoires

    if (menu_principal() == 0) {
        printf("A bientot !\n");
        return 0;
    }

	preparer_partie();
	sommet = sommet_defausse();



    if (couleur_active == NOIR) {
        printf("\nLa premiere carte est noire. Main du joueur %d :\n", courant + 1);
        afficher_ma_main(mains[courant], nb_mains[courant]);
        printf("\n");
        couleur_active = demander_couleur();
        }

    afficher_table();

	tour_du_joueur();
	
	passer_au_joueur_suivant();
	afficher_table();

    return 0;
}
