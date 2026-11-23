

#define _CRT_SECURE_NO_WARNINGS   
#include <stdio.h>  
#include "uno.h"

void vider_ligne()
{
    
    while (getchar() != '\n') {
       
    }
}



int lire_nombre()
{
    int n;

    if (scanf("%d", &n) != 1) {
        n = -1;
        vider_ligne();
    }
    return n;
}

// demande une couleur au joueur (R, J, B ou V)

int demander_couleur()
{
    char saisie;

    while (1) {
        printf("Couleur (R/J/B/V) ? ");
        if (scanf(" %c", &saisie) != 1) {  
            saisie = '?';
        }
        vider_ligne();

        if (saisie == 'R' || saisie == 'r') {
            return ROUGE;
        }
        else if (saisie == 'J' || saisie == 'j') {
            return JAUNE;
        }
        else if (saisie == 'B' || saisie == 'b') {
            return BLEU;
        }
        else if (saisie == 'V' || saisie == 'v') {
            return VERT;
        }
        printf("Choix invalide.\n");
    }
}

// explique les regles
void afficher_regles()
{
    printf("\n--- REGLES ---\n");
    printf("Le but : etre le premier a ne plus avoir de cartes.\n");
    printf("On pose une carte de la meme couleur ou du meme numero que la carte au sommet.\n");
    printf("+2 : le suivant pioche 2 cartes (sauf s'il pose aussi un +2).\n");
    printf("RV : change le sens du jeu.\n");
    printf("PS : le joueur suivant passe son tour.\n");
    printf("JJ : on choisit la couleur.\n");
    printf("+4 : on choisit la couleur, le suivant pioche 4 cartes (il peut crier au bluff).\n");
    printf("Avec une seule carte, il faut dire UNO, sinon on pioche 2 cartes.\n");
}


void demander_nb_joueurs()
{
    int n = 0;

    while (n < 2 || n > MAX_JOUEURS) {
        printf("\nNombre de joueurs (2 a %d) : ", MAX_JOUEURS);
        n = lire_nombre();
        if (n < 2 || n > MAX_JOUEURS) {
            printf("Choix invalide.\n");
        }
    }
    nb_joueurs = n;
}


int menu_principal()
{
    int choix;

    while (1) {
        printf("\n=== UNO ===\n");
        printf("1) Jouer\n");
        printf("2) Regles\n");
        printf("3) Quitter\n");
        printf("Votre choix : ");
        choix = lire_nombre();

        if (choix == 1) {
            demander_nb_joueurs();
            return 1;
        }
        else if (choix == 2) {
            afficher_regles();
        }
        else if (choix == 3) {
            return 0;
        }
        else {
            printf("Choix invalide.\n");
        }
    }
}