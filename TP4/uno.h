#ifndef UNO_H
#define UNO_H

#define MAX_CARTES  108
#define MAX_JOUEURS 10

// les chiffres sont de 0 a 9, les cartes speciales ont les numeros apres
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

// une carte = un seul nombre : couleur * 100 + type
// exemple : 205 = bleu (2) et type 5, donc "5 B"
// type = carte % 100     couleur = carte / 100

// variables globales

extern int pioche[MAX_CARTES];
extern int nb_pioche;

extern int defausse[MAX_CARTES];
extern int nb_defausse;

extern int mains[MAX_JOUEURS][MAX_CARTES];   
extern int nb_mains[MAX_JOUEURS];            

extern int nb_joueurs;
extern int courant;          
extern int sens;             
extern int couleur_active;   


// fonctions de cartes.c
void ajouter_carte(int* cartes, int* nb, int carte);
void ajouter_exemplaires(int carte, int combien);
void creer_jeu_de_cartes();
void melanger_cartes(int* cartes, int nb);
int piocher_une_carte();
void piocher_plusieurs_cartes(int joueur, int n);
void distribuer_cartes();
int enlever_carte_de_la_main(int* cartes, int* nb, int indice);
int retourner_premiere_carte();
int sommet_defausse();

// fonctions de regles.c
int carte_peut_etre_posee(int carte, int sommet);
int main_peut_jouer(int* cartes, int nb, int sommet);

// fonctions de affichage.c
void afficher_couleur(int couleur);
void afficher_carte(int carte);
void afficher_ma_main(int* cartes, int nb);
void afficher_table();

// fonctions de menu.c
void vider_ligne();
int lire_nombre();
int demander_couleur();
int demander_oui_non();
void afficher_regles();
void demander_nb_joueurs();
int menu_principal();

// fonctions de partie.c
void preparer_partie();
void passer_au_joueur_suivant();
int partie_finie();
#endif