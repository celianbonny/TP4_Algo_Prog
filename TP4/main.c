

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
int couleur_active;


// pour tester
int main()
{
    int sommet;

    if (menu_principal() == 0) {
        printf("A bientot !\n");
        return 0;
    }

    nb_defausse = 0;

    creer_jeu_de_cartes();
    melanger_cartes(pioche, nb_pioche);
    distribuer_cartes();


    sommet = retourner_premiere_carte();


    printf("\nPioche : %d cartes (attendu %d)\n\n", nb_pioche, 108 - nb_joueurs * 7 - 1);
    printf("Carte au sommet : ");
    afficher_carte(sommet);
    printf("\n\n");
    printf("Main du joueur 0 :\n");
    afficher_ma_main(mains[0], nb_mains[0]);


    if (couleur_active == NOIR) {
        printf("\n");
        couleur_active = demander_couleur();
    }

    printf("\nCouleur active : ");
    afficher_couleur(couleur_active);
    printf("\n");

    if (main_peut_jouer(mains[0], nb_mains[0], sommet) == 1) {
        printf("\nLe joueur peut jouer\n");
    }
    else {
        printf("\nLe joueur doit piocher\n");
    }

    return 0;
}