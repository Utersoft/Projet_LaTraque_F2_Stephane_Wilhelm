#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED
#include <time.h>
#include <windows.h>


#define TAILLEPLATEAULARGEUR 15
#define TAILLEPLATEAULONGUEUR 30
#define TAILLEPLATEAUORIGINE 0
#define NBPISTEURMAX 10
#define NBPISTEURMIN 1
#define VIEMONK 4
#define TAILLEMIN 1
#define CHANCETIR 4
#define MAXDEPLACEMENT 6
#define MINDEPLACEMENT 1

typedef struct tPosition{
    int n_x;
    int n_y;
}tPosition;

typedef struct tPisteur{
    tPosition pos;
    char c_pisteur;
    int n_trace;
    int n_vie;
}tPisteur;

typedef struct tMonk{
    tPosition pos;
    int vie;
    char c_monk;
}tMonk;

typedef struct tPlateau{
    char c_affichage;
    char c_statutCase;
    int n_trace;
    char c_trace;
}tPlateau;

//proto
void initPisteur(tPisteur tabPisteur[], int *n_nbPisteur);
int verifEmplacementPisteur(tPisteur pisteur[], int taille);
int verifPlacePlateau(int n_x, int n_y);
void setPisteur(tPisteur tabPisteur[], int n_nbPisteur);
void placePisteur(tPlateau plateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tPisteur tabPisteur[], int n_nbPisteur);
int verifCaseAutour(tPlateau plateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], int n_x, int n_y);
void initMonk(tMonk *monk);
int verifPlaceMonk(tPlateau plateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], int n_x, int n_y);
void setMonk(tPlateau plateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tMonk *monk);
void placeMonk(tPlateau plateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tMonk monk);
void initPlateau(tPlateau plateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tPisteur tabPisteur[], int n_nbPisteur, tMonk *monk);
void affichPlateau(tPlateau plateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1]);
void affichVue(char tabVue[3][3]);
void phase_un_pisteur(tPlateau tabPlateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tPisteur *pisteur, tMonk *monk);
void deplacementPisteur(tPlateau tabPlateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tPisteur *pisteur);
void tourPisteur(tPlateau tabPlateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tPisteur tabPisteur[], int n_nbPisteur, tMonk *monk, char vuePisteur[3][3], char vueDeplacement[3][3]);
int verifCaseMonk(tPlateau tabPlateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tMonk monk, tPosition *pos);
void deplaceMonk(tPlateau tabPlateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tMonk *monk);
void tourMonk(tPlateau tabPlateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tMonk *monk, tPisteur tabPisteur[], int *n_nbPisteur, int decompteVisible);




#endif // DEFINE_H_INCLUDED
