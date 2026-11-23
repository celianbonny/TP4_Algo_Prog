// prepare la partie

#include "uno.h"

void preparer_partie()
{
	nb_defausse = 0;
	creer_jeu_de_cartes();
	melanger_cartes(pioche, nb_pioche);
	distribuer_cartes();
	retourner_premiere_carte();
	courant = 0;
	sens = 1;
	
}

void passer_au_joueur_suivant()
{
	courant = (courant + sens + nb_joueurs) % nb_joueurs;
}

int partie_finie()
{
	int i;
	for (i = 0; i < nb_joueurs; i++) {
		if (nb_mains[i] == 0) {
			return 1;
		}
	}
	return 0;
}