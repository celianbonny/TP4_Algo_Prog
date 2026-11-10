

#include <stdlib.h>   
#include "uno.h"      


void ajouter_carte(int* cartes, int* nb, int carte)
{
    cartes[*nb] = carte;
    *nb = *nb + 1;
}


void creer_jeu_de_cartes()
{
    int c, n;

    nb_pioche = 0;

    for (c = ROUGE; c <= VERT; c++) {
        // un seul 0 par couleur
        ajouter_carte(pioche, &nb_pioche, c * 100);

        // 1 a 9 en double
        for (n = 1; n <= 9; n++) {
            ajouter_carte(pioche, &nb_pioche, c * 100 + n);
            ajouter_carte(pioche, &nb_pioche, c * 100 + n);
        }

        // 2 de chaque carte speciale
        for (n = 0; n < 2; n++) {
            ajouter_carte(pioche, &nb_pioche, c * 100 + PLUS2);
            ajouter_carte(pioche, &nb_pioche, c * 100 + RV);
            ajouter_carte(pioche, &nb_pioche, c * 100 + PS);
        }
    }

    // 4 jokers et 4 +4
    for (n = 0; n < 4; n++) {
        ajouter_carte(pioche, &nb_pioche, NOIR * 100 + JJ);
        ajouter_carte(pioche, &nb_pioche, NOIR * 100 + PLUS4);
    }
}


void melanger_cartes(int* cartes, int nb)
{
    int i, j, temp;

    for (i = nb - 1; i >= 1; i--) {
        j = rand() % (i + 1);
        temp = cartes[i];
        cartes[i] = cartes[j];
        cartes[j] = temp;
    }
}

// prend la derniere carte de la pioche et la renvoie
int piocher_une_carte()
{
    int i, sommet;


    if (nb_pioche == 0) {
        sommet = defausse[nb_defausse - 1];
        for (i = 0; i < nb_defausse - 1; i++) {
            pioche[i] = defausse[i];
        }
        nb_pioche = nb_defausse - 1;
        defausse[0] = sommet;
        nb_defausse = 1;
        melanger_cartes(pioche, nb_pioche);
    }

    nb_pioche = nb_pioche - 1;
    return pioche[nb_pioche];
}

// le joueur pioche n cartes
void piocher_plusieurs_cartes(int joueur, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        ajouter_carte(mains[joueur], &nb_mains[joueur], piocher_une_carte());
    }
}

// 7 cartes pour chaque joueur
void distribuer_cartes()
{
    int j;

    for (j = 0; j < nb_joueurs; j++) {
        nb_mains[j] = 0;
        piocher_plusieurs_cartes(j, 7);
    }
}


int enlever_carte_de_la_main(int* cartes, int* nb, int indice)
{
    int carte, i;

    carte = cartes[indice];
    for (i = indice; i < *nb - 1; i++) {
        cartes[i] = cartes[i + 1];
    }
    *nb = *nb - 1;
    return carte;
}


int retourner_premiere_carte()
{
    int carte;

    carte = piocher_une_carte();
    ajouter_carte(defausse, &nb_defausse, carte);
    couleur_active = carte / 100;
    return carte;
}