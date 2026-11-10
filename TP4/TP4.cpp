#include <stdio.h>
#include <stdlib.h>   /* rand, srand */
#include <time.h>     /* time (pour le hasard) */

#define MAX_CARTES  108
#define MAX_JOUEURS 10

/* Types de cartes : 0 a 9 = les chiffres, puis les cartes speciales */
#define PLUS2 10
#define RV    11
#define PS    12
#define JJ    13
#define PLUS4 14

/* Couleurs : 'R', 'J', 'B', 'V' et 'N' (noir, pour JJ et +4) */

typedef struct {
    int  type;
    char couleur;
} Carte;

typedef struct {
    Carte cartes[MAX_CARTES];
    int   nb;
} Main;

typedef struct {
    Main pioche;
    Main defausse;
    Main joueurs[MAX_JOUEURS];
    int  nb_joueurs;
    int  courant;
    int  sens;
    char couleur_active;
    int  pile_plus2;
} Partie;


/* Ajoute une carte a la fin d'une main (ou de la pioche) */
void ajouter_carte(Main* m, int type, char couleur)
{
    m->cartes[m->nb].type = type;
    m->cartes[m->nb].couleur = couleur;
    m->nb = m->nb + 1;
}


/* ---------- Initialisation ---------- */

void creer_jeu_de_cartes(Main* pioche)
{
    char couleurs[4] = { 'R', 'J', 'B', 'V' };
    int c, n;

    pioche->nb = 0;

    for (c = 0; c < 4; c++) {
        ajouter_carte(pioche, 0, couleurs[c]);

        for (n = 1; n <= 9; n++) {
            ajouter_carte(pioche, n, couleurs[c]);
            ajouter_carte(pioche, n, couleurs[c]);
        }

        ajouter_carte(pioche, PLUS2, couleurs[c]);
        ajouter_carte(pioche, PLUS2, couleurs[c]);
        ajouter_carte(pioche, RV, couleurs[c]);
        ajouter_carte(pioche, RV, couleurs[c]);
        ajouter_carte(pioche, PS, couleurs[c]);
        ajouter_carte(pioche, PS, couleurs[c]);
    }

    for (n = 0; n < 4; n++) {
        ajouter_carte(pioche, JJ, 'N');
        ajouter_carte(pioche, PLUS4, 'N');
    }
}

void melanger_cartes(Main* m)
{
    int i, j;
    Carte temp;

    for (i = m->nb - 1; i >= 1; i--) {
        j = rand() % (i + 1);
        temp = m->cartes[i];
        m->cartes[i] = m->cartes[j];
        m->cartes[j] = temp;
    }
}


/* ---------- Gestion des cartes ---------- */

Carte piocher_une_carte(Partie* p)
{
    Carte carte;
    Carte sommet;
    int i;

    /* Pioche vide : on remet la defausse dans la pioche (sauf la derniere carte) */
    if (p->pioche.nb == 0) {
        sommet = p->defausse.cartes[p->defausse.nb - 1];
        for (i = 0; i < p->defausse.nb - 1; i++) {
            p->pioche.cartes[i] = p->defausse.cartes[i];
        }
        p->pioche.nb = p->defausse.nb - 1;
        p->defausse.cartes[0] = sommet;
        p->defausse.nb = 1;
        melanger_cartes(&p->pioche);
    }

    p->pioche.nb = p->pioche.nb - 1;
    carte = p->pioche.cartes[p->pioche.nb];
    return carte;
}

void piocher_plusieurs_cartes(Partie* p, int joueur, int n)
{
    int i;
    Carte carte;

    for (i = 0; i < n; i++) {
        carte = piocher_une_carte(p);
        ajouter_carte(&p->joueurs[joueur], carte.type, carte.couleur);
    }
}

void distribuer_cartes(Partie* p)
{
    int j;

    for (j = 0; j < p->nb_joueurs; j++) {
        p->joueurs[j].nb = 0;
        piocher_plusieurs_cartes(p, j, 7);
    }
}

Carte enlever_carte_de_la_main(Main* m, int indice)
{
    Carte carte;
    int i;

    carte = m->cartes[indice];
    for (i = indice; i < m->nb - 1; i++) {
        m->cartes[i] = m->cartes[i + 1];
    }
    m->nb = m->nb - 1;
    return carte;
}

int carte_peut_etre_posee(Carte carte, Carte sommet, char couleur_active)
{
    if (carte.couleur == 'N') {
        return 1;
    }
    if (carte.couleur == couleur_active) {
        return 1;
    }
    if (carte.type == sommet.type) {
        return 1;
    }
    return 0;
}

int main_peut_jouer(Main* m, Carte sommet, char couleur_active)
{
    int i;

    for (i = 0; i < m->nb; i++) {
        if (carte_peut_etre_posee(m->cartes[i], sommet, couleur_active) == 1) {
            return 1;
        }
    }
    return 0;
}


/* ---------- Affichage ---------- */

void afficher_carte(Carte carte)
{
    if (carte.type <= 9) {
        printf("%d", carte.type);
    }
    else if (carte.type == PLUS2) {
        printf("+2");
    }
    else if (carte.type == RV) {
        printf("RV");
    }
    else if (carte.type == PS) {
        printf("PS");
    }
    else if (carte.type == JJ) {
        printf("JJ");
    }
    else {
        printf("+4");
    }
    printf(" %c", carte.couleur);
}

void afficher_ma_main(Main* m)
{
    int i;

    for (i = 0; i < m->nb; i++) {
        printf("%d) ", i + 1);
        afficher_carte(m->cartes[i]);
        printf("\n");
    }
}


/* ---------- Test temporaire ---------- */

int main()
{
    Partie p;
    Carte sommet;

    srand((unsigned int)time(NULL));

    p.nb_joueurs = 2;
    p.defausse.nb = 0;

    creer_jeu_de_cartes(&p.pioche);
    melanger_cartes(&p.pioche);
    distribuer_cartes(&p);

    printf("Pioche : %d cartes (attendu 94)\n\n", p.pioche.nb);
    printf("Main du joueur 0 :\n");
    afficher_ma_main(&p.joueurs[0]);

    sommet.type = 5;
    sommet.couleur = 'R';
    if (main_peut_jouer(&p.joueurs[0], sommet, 'R') == 1) {
        printf("\nSur un 5 R, le joueur peut jouer\n");
    }
    else {
        printf("\nSur un 5 R, le joueur doit piocher\n");
    }

    return 0;
}