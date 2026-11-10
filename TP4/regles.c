#include "uno.h"

// renvoie 1 si on peut poser la carte, 0 sinon

int carte_peut_etre_posee(int carte, int sommet)
{
    if (carte / 100 == NOIR) {
        return 1;
    }
    if (carte / 100 == couleur_active) {
        return 1;
    }
    if (carte % 100 == sommet % 100) {
        return 1;
    }
    return 0;
}


int main_peut_jouer(int* cartes, int nb, int sommet)
{
    int i;

    for (i = 0; i < nb; i++) {
        if (carte_peut_etre_posee(cartes[i], sommet) == 1) {
            return 1;
        }
    }
    return 0;
}