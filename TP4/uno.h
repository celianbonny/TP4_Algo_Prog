
#ifndef UNO_H
#define UNO_H

#define MAX_CARTES  108
#define MAX_JOUEURS 10


#define PLUS2 10
#define RV    11
#define PS    12
#define JJ    13
#define PLUS4 14

// les couleurs
#define ROUGE 0
#define JAUNE 1
#define BLEU  2
#define VERT  3
#define NOIR  4


extern int pioche[MAX_CARTES];
extern int nb_pioche;

extern int defausse[MAX_CARTES];
extern int nb_defausse;

extern int mains[MAX_JOUEURS][MAX_CARTES];   // mains[0] = joueur humain
extern int nb_mains[MAX_JOUEURS];            // nombre de cartes de chaque joueur

extern int nb_joueurs;
extern int couleur_active;   // couleur a jouer en ce moment


// fonctions de cartes.c
void ajouter_carte(int* cartes, int* nb, int carte);
void creer_jeu_de_cartes();
void melanger_cartes(int* cartes, int nb);
int piocher_une_carte();
void piocher_plusieurs_cartes(int joueur, int n);
void distribuer_cartes();
int enlever_carte_de_la_main(int* cartes, int* nb, int indice);
int retourner_premiere_carte();

// fonctions de regles.c
int carte_peut_etre_posee(int carte, int sommet);
int main_peut_jouer(int* cartes, int nb, int sommet);

// fonctions de affichage.c
void afficher_couleur(int couleur);
void afficher_carte(int carte);
void afficher_ma_main(int* cartes, int nb);

// fonctions de menu.c
void vider_ligne();
int lire_nombre();
int demander_couleur();
void afficher_regles();
void demander_nb_joueurs();
int menu_principal();

#endif