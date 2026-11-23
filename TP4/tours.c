#include <stdio.h>
#include "uno.h"	

void poser_carte(int joueur, int indice)
{
	int carte;
	carte = enlever_carte_de_la_main(mains[joueur], &nb_mains[joueur], indice);
	ajouter_carte(defausse, &nb_defausse, carte);
	couleur_active = carte / 100;
	if (carte / 100 == NOIR) {
		couleur_active = demander_couleur();
	}
}

void tour_du_joueur()
{
	int sommet;
	int choix;
	int carte;
	int indice;

	sommet = sommet_defausse();
	printf("\nMain du joueur %d :\n", courant + 1);
	afficher_ma_main(mains[courant], nb_mains[courant]);
	indice = -1;

	while (indice == -1)
	{
		printf("Numero de la carte a poser (0 pour piocher) : ");
		choix = lire_nombre();
		if (choix == 0) {
			carte = piocher_une_carte();
			ajouter_carte(mains[courant], &nb_mains[courant], carte);
			printf("Vous avez pioche la carte : ");
			afficher_carte(carte);
			printf("\n");
			return;
		}
		else if (choix < 1 || choix > nb_mains[courant]) {
			printf("Numero de carte invalide. Veuillez reessayer.\n");
		}
		else if (carte_peut_etre_posee(mains[courant][choix - 1], sommet) == 0) {
			printf("Vous ne pouvez pas poser cette carte. Veuillez reessayer.\n");
		}
		else {
			indice = choix - 1;
		}
	}
	carte = mains[courant][indice];
	poser_carte(courant, indice);
	printf("Vous avez pose la carte : ");
	afficher_carte(carte);
	printf("\n");
}
