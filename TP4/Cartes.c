

#include <stdlib.h>   
#include "uno.h"      


void ajouter_carte(int* cartes, int* nb, int carte)
{
    cartes[*nb] = carte;
    *nb = *nb + 1;
}


void ajouter_exemplaires(int carte, int combien)
{
    int i;

    for (i = 0; i < combien; i++) {
        ajouter_carte(pioche, &nb_pioche, carte);
    }
}

void creer_jeu_de_cartes()
{
    int c, n;

    nb_pioche = 0;


    for (c = ROUGE; c <= VERT; c++) {
        ajouter_exemplaires(c * 100, 1);          

        // n vaut 1, 2, 3... jusqu'a 9
        for (n = 1; n <= 9; n++) {
            ajouter_exemplaires(c * 100 + n, 2);  
        }

        ajouter_exemplaires(c * 100 + PLUS2, 2);
        ajouter_exemplaires(c * 100 + RV, 2);
        ajouter_exemplaires(c * 100 + PS, 2);
    }

  
    ajouter_exemplaires(NOIR * 100 + JJ, 4);
    ajouter_exemplaires(NOIR * 100 + PLUS4, 4);
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


int piocher_une_carte()
{
    int i, sommet;

    // pioche vide : on remet la defausse dans la pioche
    
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

// retire la carte a la position indice et la renvoie
// les cartes suivantes sont decalees d'une case vers la gauche
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

// renvoie la carte qui est au sommet de la defausse 
int sommet_defausse()
{
    return defausse[nb_defausse - 1];
}