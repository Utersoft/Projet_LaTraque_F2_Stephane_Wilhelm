#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "define.h"


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


void initPisteur(tPisteur tabPisteur[], int *n_nbPisteur){
//BUT : initialiser les pisteurs à leur valeur par défaut
//ENTREE : /
//SORTIE : /
int n_i = 0;

    do{
        printf("Tout d'abord, combien de pisteur(s) desirez-vous avoir dans cette partie? (Max %d - Min %d)\n", NBPISTEURMAX, NBPISTEURMIN);
        fflush(stdin);
        scanf("%d", n_nbPisteur);
    }while (*n_nbPisteur < NBPISTEURMIN || *n_nbPisteur > NBPISTEURMAX);

    for(n_i = 0; n_i < *n_nbPisteur; n_i++){
        tabPisteur[n_i].pos.n_x = 0;
        tabPisteur[n_i].pos.n_y = 0;
        tabPisteur[n_i].c_pisteur = 'P';
        tabPisteur[n_i].n_trace = 160 + n_i;
        tabPisteur[n_i].n_vie = 1;
    }
}


int verifEmplacementPisteur(tPisteur pisteur[], int taille){
//BUT : Vérification que les positions ne sont pas déjà entrées lors du placement des pisteurs par le joueur
//ENTREE : /
//SORTIE : /
int n_i = 0;
int place = 1;

    for(n_i = 0; n_i < taille; n_i++){
        if ((pisteur[taille].pos.n_x == pisteur[n_i].pos.n_x) && (pisteur[taille].pos.n_y == pisteur[n_i].pos.n_y)){
            place = 0;
        }
    }
    return place;
}


int verifPlacePlateau(int n_x, int n_y){
//BUT : vérifie que les coordonnées sont bien comprises dans le plateau
//ENTREE : les coordonnées x et y
//SORTIE : /

    if((n_x >= TAILLEPLATEAULARGEUR || n_x <= TAILLEPLATEAUORIGINE) || (n_y >= TAILLEPLATEAULONGUEUR || n_y <= TAILLEPLATEAUORIGINE)){
        return 0;
    }else{
        return 1;
    }
}



void setPisteur(tPisteur tabPisteur[], int n_nbPisteur){
//BUT : setter les places des pisteurs
//ENTREE : les coordonnées des pisteurs
//SORTIE :
int n_i = 0;

    do{
        printf("Entrez la coordonnee (valide) X du pisteur %d. (entre %d et %d)\n", (n_i + 1), TAILLEMIN, TAILLEPLATEAULARGEUR - 1);
        scanf("%d", &tabPisteur[n_i].pos.n_x);
        fflush(stdin);
        printf("Entrez la coorddonnee (valide) Y du pisteur %d. (entre %d et %d)\n", (n_i + 1), TAILLEMIN, TAILLEPLATEAULONGUEUR - 1);
        scanf("%d", &tabPisteur[n_i].pos.n_y);
        if((verifEmplacementPisteur(tabPisteur, n_i) == 1) && (verifPlacePlateau(tabPisteur[n_i].pos.n_x, tabPisteur[n_i].pos.n_y) == 1)){
            n_i++;
        }
    }while(n_i < n_nbPisteur);
}


void placePisteur(tPlateau plateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tPisteur tabPisteur[], int n_nbPisteur){
//BUT : placer les plisteur sur le plateau
//ENTREE : /
//SORTIE : /
int n_i = 0;

    for(n_i = 0; n_i < n_nbPisteur; n_i++){
        plateau[tabPisteur[n_i].pos.n_x][tabPisteur[n_i].pos.n_y].c_affichage = tabPisteur[n_i].c_pisteur;
        plateau[tabPisteur[n_i].pos.n_x][tabPisteur[n_i].pos.n_y].c_statutCase = tabPisteur[n_i].c_pisteur;
        plateau[tabPisteur[n_i].pos.n_x][tabPisteur[n_i].pos.n_y].c_trace = tabPisteur[n_i].c_pisteur;
        plateau[tabPisteur[n_i].pos.n_x][tabPisteur[n_i].pos.n_y].n_trace = tabPisteur[n_i].n_trace;
    }
}



int verifCaseAutour(tPlateau plateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], int n_x, int n_y){
//BUT : Verifier les cases autours du pisteur
//ENTREE : /
//SORTIE : /

int n_i = 0, n_j = 0;
int n_cpt = 1;
char c_tir = ' ';
int n_tir = 0;

    for(n_i = -1; n_i <= 1; n_i++){
        for(n_j = -1; n_j <= 1; n_j++){
            if(plateau[n_x + n_i][n_y + n_j].c_statutCase == 'M'){
                printf("Le monk se trouve en %d. Voulez-vous que je lui tire dessus? ('T' ou 't' pour tirer puis valider avec ENTREE)\n", n_cpt);
                fflush(stdin);
                scanf("%c", &c_tir);
            }else if(plateau[n_x + n_i][n_y + n_j].c_trace == 'M' && plateau[n_x + n_i][n_y + n_j].c_statutCase != 'M' && c_tir == ' ' && plateau[n_x + n_i][n_y + n_j].n_trace >= 2 && plateau[n_x + n_i][n_y + n_j].n_trace <= 15){
                printf("Il y a une trace du monstre en %d de fraicheur %d.\n", n_cpt, plateau[n_x + n_i][n_y + n_j].n_trace);
            }else if (c_tir == ' '){
                printf("Il n'y a rien en %d.\n", n_cpt);
            }
            n_cpt++;
            if (c_tir == ' '){
                Sleep(500);
            }
        }
    }
    if(c_tir == 'T' || c_tir == 't'){
        n_tir = 1;
    }
    return n_tir;
}


void initMonk(tMonk *monk){
    monk->c_monk = 'M';
    monk->pos.n_x = 0;
    monk->pos.n_y = 0;
    monk->vie = VIEMONK;
}

int verifPlaceMonk(tPlateau plateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], int n_x, int n_y){
//BUT : vérifier que le monk ne spawn pas à côté d'un pisteur
//ENTREE : /
//SORTIE : /
int n_i = -1, n_j = -1;
int statut = 1;

    for(n_i = -1; n_i <= 1; n_i++){
        for(n_j = -1; n_j <= 1; n_j++){
            if(plateau[n_x + n_i][n_y + n_j].c_affichage == 'P'){
                statut = 0;
            }
        }
    }
    return statut;
}


void setMonk(tPlateau plateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tMonk *monk){
//BUT : setter les valeurs de x et y du monk
//ENTREE : /
//SORTIE : /
    do{
        monk->pos.n_x = (rand() % (TAILLEPLATEAULARGEUR - 2)) + 1;
        monk->pos.n_y = (rand() % (TAILLEPLATEAULONGUEUR - 2)) + 1;
    }while((plateau[monk->pos.n_x][monk->pos.n_y].c_affichage == 'P') || (verifPlacePlateau(monk->pos.n_x, monk->pos.n_y) == 0) || (verifPlaceMonk(plateau, monk->pos.n_x, monk->pos.n_y) == 0));
}



void placeMonk(tPlateau plateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tMonk monk){
//BUT : placer le monk dans le plateau
//ENTREE : /
//SORTIE : /
    plateau[monk.pos.n_x][monk.pos.n_y].c_affichage = monk.c_monk;
    plateau[monk.pos.n_x][monk.pos.n_y].c_statutCase = monk.c_monk;
    plateau[monk.pos.n_x][monk.pos.n_y].c_trace = monk.c_monk;
    plateau[monk.pos.n_x][monk.pos.n_y].n_trace = 16;
}



void initPlateau(tPlateau plateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tPisteur tabPisteur[], int n_nbPisteur, tMonk *monk){
//BUT : initialisation du plateau de jeu
//ENTREE : /
//SORTIE : /
int n_i = 0, n_j = 0;

    for(n_i = 0; n_i <= TAILLEPLATEAULARGEUR; n_i++){
        for(n_j = 0; n_j <= TAILLEPLATEAULONGUEUR; n_j++){
            if((n_i == 0 || n_j == 0) || (n_i == TAILLEPLATEAULARGEUR || n_j == TAILLEPLATEAULONGUEUR)){
                plateau[n_i][n_j].c_affichage = '*';
            }else{
                plateau[n_i][n_j].c_affichage = '.';
                plateau[n_i][n_j].c_statutCase = ' ';
                plateau[n_i][n_j].n_trace = 0;
                plateau[n_i][n_j].c_trace = ' ';
            }
        }
    }
    //On vérifie que le nombre de pisteur est supérieur ou égal à 1 et inférieur ou égale à 10
    setPisteur(tabPisteur, n_nbPisteur);
    placePisteur(plateau,tabPisteur, n_nbPisteur);
    setMonk(plateau, monk);
    placeMonk(plateau, *monk);
}



void affichPlateau(tPlateau plateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1]){
//BUT : Affichage du plateau
//ENTREE : /
//SORTIE : Le plateau avec les pisteurs positionnés

    int n_i = 0, n_j = 0;

    for(n_i = 0; n_i <= TAILLEPLATEAULARGEUR; n_i++){
        for(n_j = 0; n_j <= TAILLEPLATEAULONGUEUR; n_j++){
            printf("%c ", plateau[n_i][n_j].c_affichage);
        }
        printf("\n");
    }
}

void affichVue(char tabVue[3][3]){
//BUT : affichage de la vue de deplacement et ou de analyse du terrain
//ENTREE : /
//SORTIE : tableau d'affichage
    int n_i = 0, n_j = 0;

    for(n_i = 0; n_i < 3; n_i++){
        printf(" ");
        for(n_j = 0; n_j < 3; n_j++){
            printf("%c ", tabVue[n_i][n_j]);
        }
        printf("\n");
    }
}

void phase_un_pisteur(tPlateau tabPlateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tPisteur *pisteur, tMonk *monk){
//BUT : phase ! du pisteur
//ENTREE : si le pisteur tir sur le monstre ou non
//SORTIE : /
    int n_tir = 0;
    int nb_rand = 0;
    n_tir = verifCaseAutour(tabPlateau, pisteur->pos.n_x, pisteur->pos.n_y);
    if(n_tir == 1){
        nb_rand = (rand() % 10) + 1;
        if(nb_rand <= CHANCETIR){
            monk->vie = monk->vie - 1;
            printf("Pisteur : Je l'ai eu!\n Nous pouvons le suivre a la trace tant qu'il saigne !\n");
        }else{
            printf("Pisteur : Je suis desole, il semblerait que je l'ai rate... Il se deplace vite le bougre!\n");
        }
    }
}

void deplacementPisteur(tPlateau tabPlateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tPisteur *pisteur){
//BUT : Deplacement du pisteur
//ENTREE : un chiffre entre 1 et 4
//SORTIE : le deplacement du pisteur
    int deplacer = 0;

    do{
        scanf("%d", &deplacer);
        if(deplacer > 4 ||deplacer < 1){
            printf("Je suis desole, je ne connais pas cette position...\n");
        }
    }while(deplacer > 4 ||deplacer < 1);
    printf("Bien reçu !");
    Sleep(500);
    tabPlateau[pisteur->pos.n_x][pisteur->pos.n_y].c_affichage = '.';
    tabPlateau[pisteur->pos.n_x][pisteur->pos.n_y].c_statutCase = ' ';
    switch (deplacer){
        case 1 : pisteur->pos.n_x = pisteur->pos.n_x - 1; break;
        case 2 : pisteur->pos.n_y = pisteur->pos.n_y + 1; break;
        case 3 : pisteur->pos.n_x = pisteur->pos.n_x + 1; break;
        case 4 : pisteur->pos.n_y = pisteur->pos.n_y - 1; break;
    }
    tabPlateau[pisteur->pos.n_x][pisteur->pos.n_y].c_affichage = '?';
    if(tabPlateau[pisteur->pos.n_x][pisteur->pos.n_y].c_affichage != pisteur->c_pisteur){
        tabPlateau[pisteur->pos.n_x][pisteur->pos.n_y].c_statutCase = pisteur->c_pisteur;
        tabPlateau[pisteur->pos.n_x][pisteur->pos.n_y].c_trace = pisteur->c_pisteur;
        tabPlateau[pisteur->pos.n_x][pisteur->pos.n_y].n_trace = pisteur->n_trace;
    }
}

void tourPisteur(tPlateau tabPlateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tPisteur tabPisteur[], int n_nbPisteur, tMonk *monk, char vuePisteur[3][3], char vueDeplacement[3][3]){
//BUT : Jouer le tour des pisteurs
//ENTREE : Les déplacements, si le pisteur doit tirer
//SORTIE : Les déplacements, si le tir à réussi ou échouer
    int n_i = 0, n_j = 0;
    int deplacement = 1;

    for(n_i = 0; n_i < n_nbPisteur; n_i++){
        if(tabPisteur[n_i].n_vie == 1){
            tabPlateau[tabPisteur[n_i].pos.n_x][tabPisteur[n_i].pos.n_y].c_affichage = '!';
            system("cls");
            affichPlateau(tabPlateau);
            printf("Voici le tour du pisteur %d.\n", n_i + 1);
            Sleep(1000);
            printf("Que voyez-vous pisteur %d?\n\n", n_i + 1);
            affichVue(vuePisteur);
            printf("\n");
            Sleep(1000);
            phase_un_pisteur(tabPlateau, &tabPisteur[n_i], monk);
            tabPlateau[tabPisteur[n_i].pos.n_x][tabPisteur[n_i].pos.n_y].c_affichage = '?';
            system("cls");
            affichPlateau(tabPlateau);
            do{
                printf("Vous allez pouvoir deplacer le pisteur. De combien de case voulez-vous le deplacer? (Min %d - Max %d)\n", MINDEPLACEMENT, MAXDEPLACEMENT);
                scanf("%d", &deplacement);
            }while(deplacement > MAXDEPLACEMENT || deplacement < MINDEPLACEMENT);
            for (n_j = 0; n_j < deplacement; n_j++){
                system("cls");
                affichPlateau(tabPlateau);
                printf("\n");
                affichVue(vueDeplacement);
                if(n_j == 0){
                    printf("Pisteur %d : J'attend vos ordres de deplacements!\nJe peux me deplacer de %d cases. (1 : Nord ; 2 : Est ; 3 : Sud ; 4 : Ouest)\n", n_i + 1, deplacement);
                }else{
                    printf("Pisteur %d : Ou dois-je aller maintenant?\nJe peux encore me deplacer de %d cases. (1 : Nord ; 2 : Est ; 3 : Sud ; 4 : Ouest)\n", n_i + 1, deplacement - n_j);
                }
                Sleep(1000);
                deplacementPisteur(tabPlateau, &tabPisteur[n_i]);
            }
            tabPlateau[tabPisteur[n_i].pos.n_x][tabPisteur[n_i].pos.n_y].c_affichage = 'P';
            system("cls");
            affichPlateau(tabPlateau);
            printf("Pisteur %d : C'est tout pour moi.\n", n_i + 1);
        }
    }
    for(n_i = 0; n_i < TAILLEPLATEAULARGEUR; n_i++){
        for(n_j = 0; n_j < TAILLEPLATEAULONGUEUR; n_j++){
            if(tabPlateau[n_i][n_j].n_trace / 10 >= 2 && tabPlateau[n_i][n_j].n_trace / 10 <= 16){
                tabPlateau[n_i][n_j].n_trace = tabPlateau[n_i][n_j].n_trace - 10;
            }
        }
    }
}

int verifCaseMonk(tPlateau tabPlateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tMonk monk, tPosition *pos){
//BUT : vérifier les cases adjacentes (sauf diagonales) du monk pour trouver des pisteurs ou des traces
//ENTREE : /
//SORTIE : /
    int statut = 0;
    int trace = 0;

    if(tabPlateau[monk.pos.n_x - 1][monk.pos.n_y].c_affichage == 'P' ){
        statut = 1;
        pos->n_x = monk.pos.n_x - 1;
        pos->n_y = monk.pos.n_y;
    }
    if(tabPlateau[monk.pos.n_x][monk.pos.n_y + 1].c_affichage == 'P' && statut != 1){
        statut = 1;
        pos->n_x = monk.pos.n_x;
        pos->n_y = monk.pos.n_y + 1;
    }
    if(tabPlateau[monk.pos.n_x - 1][monk.pos.n_y].c_affichage == 'P' && statut != 1){
        statut = 1;
        pos->n_x = monk.pos.n_x - 1;
        pos->n_y = monk.pos.n_y;
    }
    if(tabPlateau[monk.pos.n_x][monk.pos.n_y - 1].c_affichage == 'P' && statut != 1){
        statut = 1;
        pos->n_x = monk.pos.n_x;
        pos->n_y = monk.pos.n_y - 1;
    }
    if(tabPlateau[monk.pos.n_x - 1][monk.pos.n_y].c_trace == 'P' && statut != 1 && tabPlateau[monk.pos.n_x - 1][monk.pos.n_y].n_trace >= 20 && tabPlateau[monk.pos.n_x - 1][monk.pos.n_y].n_trace <= 159){
        statut = 2;
        trace = tabPlateau[monk.pos.n_x - 1][monk.pos.n_y].n_trace;
        pos->n_x = monk.pos.n_x - 1;
        pos->n_y = monk.pos.n_y;
    }
    if(tabPlateau[monk.pos.n_x][monk.pos.n_y + 1].c_trace == 'P' && statut != 1 && tabPlateau[monk.pos.n_x][monk.pos.n_y + 1].n_trace > trace && tabPlateau[monk.pos.n_x][monk.pos.n_y + 1].n_trace >= 20 && tabPlateau[monk.pos.n_x][monk.pos.n_y + 1].n_trace <= 159){
        statut = 2;
        trace = tabPlateau[monk.pos.n_x][monk.pos.n_y + 1].n_trace;
        pos->n_x = monk.pos.n_x;
        pos->n_y = monk.pos.n_y + 1;
    }
    if(tabPlateau[monk.pos.n_x - 1][monk.pos.n_y].c_trace == 'P' && statut != 1 && tabPlateau[monk.pos.n_x - 1][monk.pos.n_y].n_trace > trace && tabPlateau[monk.pos.n_x - 1][monk.pos.n_y].n_trace >= 20 && tabPlateau[monk.pos.n_x - 1][monk.pos.n_y].n_trace <= 159){
        statut = 2;
        trace = tabPlateau[monk.pos.n_x - 1][monk.pos.n_y].n_trace;
        pos->n_x = monk.pos.n_x - 1;
        pos->n_y = monk.pos.n_y;
    }
    if(tabPlateau[monk.pos.n_x][monk.pos.n_y - 1].c_trace == 'P' && statut != 1 && tabPlateau[monk.pos.n_x][monk.pos.n_y - 1].n_trace > trace && tabPlateau[monk.pos.n_x][monk.pos.n_y - 1].n_trace >= 20 && tabPlateau[monk.pos.n_x][monk.pos.n_y - 1].n_trace <= 159){
        statut = 2;
        trace = tabPlateau[monk.pos.n_x][monk.pos.n_y - 1].n_trace;
        pos->n_x = monk.pos.n_x;
        pos->n_y = monk.pos.n_y - 1;
    }
    return statut;
}

void deplaceMonk(tPlateau tabPlateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tMonk *monk){
//BUT : deplacer le monk
//ENTREE: /
//SORTIE : /
    int pileFace = 0;
    int deplacement = 0;

    do{
        pileFace = (rand() % 2) + 1;
    }while(pileFace < 0 && pileFace >= 2);
    if(pileFace == 1){
        do{
            deplacement = (rand() % 3) - 1;
        }while((deplacement < -1 || deplacement > 1) || (tabPlateau[monk->pos.n_x + deplacement][monk->pos.n_y].n_trace > 14) || tabPlateau[monk->pos.n_x + deplacement][monk->pos.n_y].c_affichage == '*');
        printf("C'est le tour du monk.\n");
        monk->pos.n_x = monk->pos.n_x + deplacement;
    }else{
        do{
            deplacement = (rand() % 3) - 1;
        }while((deplacement < -1 || deplacement > 1) || (tabPlateau[monk->pos.n_x][monk->pos.n_y + deplacement].n_trace > 14) || tabPlateau[monk->pos.n_x][monk->pos.n_y + deplacement].c_affichage == '*');
        monk->pos.n_y = monk->pos.n_y + deplacement;
    }
    tabPlateau[monk->pos.n_x][monk->pos.n_y].c_affichage = monk->c_monk;
    tabPlateau[monk->pos.n_x][monk->pos.n_y].c_statutCase = monk->c_monk;
    tabPlateau[monk->pos.n_x][monk->pos.n_y].c_trace = monk->c_monk;
    tabPlateau[monk->pos.n_x][monk->pos.n_y].n_trace = 16;
}

void tourMonk(tPlateau tabPlateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1], tMonk *monk, tPisteur tabPisteur[], int *n_nbPisteur, int decompteVisible){
//BUT : jouer le tour du monk
//ENTREE : /
//SORTIE : S'il attaque un pisteur
    int n_deplacement = (rand () % 3) + 1;
    tPosition pos;
    int n_i = 0, n_j, cpt = 0;
    int nbPisteur = *n_nbPisteur;
    int n_tabTrace[nbPisteur];


    for(n_i = 0; n_i < n_deplacement; n_i++){
        if(decompteVisible > 0 && n_i == 0){
            tabPlateau[monk->pos.n_x][monk->pos.n_y].c_affichage = 'X';
            Sleep(2000);
            tabPlateau[monk->pos.n_x][monk->pos.n_y].c_affichage = '.';
        }
        if(verifCaseMonk(tabPlateau, *monk, &pos) == 1){
            tabPlateau[monk->pos.n_x][monk->pos.n_y].c_statutCase = ' ';
            tabPlateau[monk->pos.n_x][monk->pos.n_y].c_statutCase = '.';
            monk->pos = pos;
            tabPlateau[pos.n_x][pos.n_y].c_statutCase = monk->c_monk;
            tabPlateau[pos.n_x][pos.n_y].c_affichage = monk->c_monk;
            tabPlateau[pos.n_x][pos.n_y].c_trace = monk->c_monk;
            n_tabTrace[n_i] = tabPlateau[pos.n_x][pos.n_y].n_trace;
            tabPlateau[pos.n_x][pos.n_y].n_trace = 16;
            tabPisteur[n_tabTrace[n_i] % 10].n_vie = 0;
            printf("Pisteur %d : Non, la bete est la ! Aaaargh!\n Pisteur %d est mort...\n", n_tabTrace[n_i] % 10, n_tabTrace[n_i] % 10);
            n_nbPisteur = n_nbPisteur - 1;
            cpt++;
            Sleep(1000);
        }else if(verifCaseMonk(tabPlateau, *monk, &pos) == 2){
            tabPlateau[monk->pos.n_x][monk->pos.n_y].c_statutCase = ' ';
            tabPlateau[monk->pos.n_x][monk->pos.n_y].c_statutCase = 'M';
            monk->pos = pos;
            tabPlateau[pos.n_x][pos.n_y].c_statutCase = monk->c_monk;
            tabPlateau[pos.n_x][pos.n_y].c_affichage = monk->c_monk;
            tabPlateau[pos.n_x][pos.n_y].c_trace = monk->c_monk;
        }else{
            tabPlateau[monk->pos.n_x][monk->pos.n_y].c_statutCase = ' ';
            tabPlateau[monk->pos.n_x][monk->pos.n_y].c_affichage= '.';
            deplaceMonk(tabPlateau, monk);
        }
        system("cls");
        affichPlateau(tabPlateau);
    }
    for(cpt = cpt; cpt > 0; cpt--){
        for(n_i = 0; n_i < TAILLEPLATEAULARGEUR; n_i++){
            for(n_j = 0; n_j < TAILLEPLATEAULONGUEUR; n_j++){
                if(tabPlateau[n_i][n_j].n_trace % 10 == n_tabTrace[cpt] % 10){
                    tabPlateau[n_i][n_j].c_affichage = '.';
                    tabPlateau[n_i][n_j].c_trace = ' ';
                    tabPlateau[n_i][n_j].n_trace = 0;
                    tabPlateau[n_i][n_j].c_statutCase = ' ';
                }
            }
        }
    }
}
