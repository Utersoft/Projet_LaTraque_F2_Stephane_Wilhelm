/*ALGORITHME : LA TRAQUE
//BUT : Reproduire le jeu de la traque
//ENTREE : les positions des pisteurs qui chassent le monk, leurs déplacements, les tirs
//SORTIE : La vision du pisteur, la réussite du tir, mort d'un pisteur, mort du monk, mort de tous les pisteurs, fin de la partie



type ENREGISTREMENT = tPosition
    ENTIER <- n_x
    ENTIER <- n_y
FINENREGISTREMENT

type ENREGISTREMENT = tPisteur
    tPosition <- pos
    CAR <- c_pisteur
FINENREGISTREMENT

type ENREGISTREMENT = tMonk
    tPosition <- pos
    ENTIER <- vie
    CAR <- c_monk
FINENREGISTEMENT

type ENREGISTEMENT = tPlateau
    CAR <- c_affichage
    CAR <- c_statutCase
    ENTIER <- n_trace
    CAR <- c_trace
FINENREGISTREMENT


PROCEDURE initPisteur(TABLEAU DE tPisteur : tabPisteur, ENTIER : n_nbPisteur)
//BUT : initialiser les pisteurs à leur valeur par défaut
//ENTREE : /
//SORTIE : /
var n_i <- 0 : ENTIER
DEBUT
    POUR n_i de 0 A n_nbPisteur - 1 FAIRE
    DEBUT
        tabPisteur[n_i].pos.n_x <- 0
        tabPisteur[n_i].pos.n_y <- 0
        tabPisteur[n_i].c_pisteur <- "P"
    FINPOUR
FINPROCEDURE



FONCTION verifEmplacementPisteur(TABLEAU DE tPisteur : pisteur, ENTIER : taille) : BOOLEEN
//BUT : Vérification que les positions ne sont pas déjà entrées lors du placement des pisteurs par le joueur
//ENTREE : /
//SORTIE : /
var n_i <- 0 : ENTIER
var place <- VRAI : BOOLEEN
DEBUT
    POUR n_i de 0 A taille - 1 FAIRE
    DEBUT
        SI((pisteur[taille].x = pisteur[n_i].x) ET (pisteur[taille].y = pisteur[n_i].y)) FAIRE
        DEBUT
            place <- FAUX
        FINSI
    FINPOUR
    verifPlacePlateau <- place
FINFONCTION


FONCTION verifPlacePlateau(ENTIER : n_x, ENTIER : n_y) : BOOLEEN
//BUT : vérifie que les coordonnées sont bien comprises dans le plateau
//ENTREE : les coordonnées x et y
//SORTIE : /
DEBUT
    SI((n_x >= TAILLEPLATEAULARGEUR OU n_x <= TAILLEPLATEAUORIGINE) OU (n_y >= TAILLEPLATEAULARGEUR OU n_y <= TAILLEPLATEAUORIGINE))FAIRE
    DEBUT
        verifPlacePlateau <- FAUX
    SINON
    DEBUT
        verifPlacePlateau <- VRAI
    FINSI
FINFONCTION



PROCEDURE setPisteur(TABLEAU DE tPisteur : tabPisteur, ENTIER : n_nbPisteur)
var n_i <- 0 : ENTIER
DEBUT
    FAIRE
    DEBUT
        ECRIRE "Entrez la coordonnée X du pisteur" + (n_i + 1)
        LIRE tabPisteur[n_i].x
        ECRIRE "Entrez la coorddonnée Y du pisteur" + (n_i + 1)
        LIRE tabPisteur[n_i].y
        SI ((verifEmplacementPisteur(tabPisteur, n_i) = VRAI) && (verifPlacePlateau(ENTIER : n_x, ENTIER : n_y) = VRAI))FAIRE
        DEBUT
            n_i++
        FINSI
    TANT QUE (n_i < n_nbPisteur)
FINPROCEDURE



PROCEDURE placePisteur(TABLEAU DE tPlateau : plateau, TABLEAU DE tPisteur : tabPisteur, ENTIER : n_nbPisteur)
var n_i : ENTIER
DEBUT
    POUR n_i DE 0 A n_nbPisteur FAIRE
    DEBUT
        plateau[tabPisteur[n_i].pos.n_x][tabPisteur[n_i].pos.n_y].c_affichage <- tabPisteur[n_i].c_pisteur
        plateau[tabPisteur[n_i].pos.n_x][tabPisteur[n_i].pos.n_y].c_statutCase <- tabPisteur[n_i].c_pisteur
        plateau[tabPisteur[n_i].pos.n_x][tabPisteur[n_i].pos.n_y].c_trace <- tabPisteur[n_i].c_pisteur
        plateau[tabPisteur[n_i].pos.n_x][tabPisteur[n_i].pos.n_y].n_trace <- 16
    FINPOUR
FINPROCEDURE



FONCTION verifCaseAutour(TABLEAU DE tplateau : plateau, ENTIER : n_x, ENTIER : n_y) : CAR
//BUT : Verifier les cases autours du pisteur
//ENTREE : /
//SORTIE : /

var n_i <- 0, n_j <- 0 : ENTIER
var n_cpt <- 1 : ENTIER
var c_tir <- " " : CAR
DEBUT
    POUR n_i DE -1 A 1 FAIRE
    DEBUT
        POUR n_j DE -1 A 1 FAIRE
        DEBUT
            SI(plateau[n_x + n_i][n_y + n_j].c_statut = "M")ALORS
            DEBUT
                ECRIRE "Le monk se trouve en " + cpt + ". Voulez-vous lui tirer dessus? ('T' ou 't' pour tirer puis valider avec ENTREE)"
                LIRE c_tir
            SINON SI(plateau[n_x + n_i][n_y + n_j].c_trace = "M" ET plateau[n_x + n_i][n_y + n_j].c_statut <> "M" ET c_tir = " ")ALORS
            DEBUT
                ECRIRE "Il y a une trace du monstre en " + cpt + " de fraicheur " + plateau[n_x + n_i][n_y + n_j].n_trace  + "."
            FINSI
        FINPOUR
    FINPOUR
    verifCaseAutour <- cTir
FINFONCTION


FONCTION verifPlaceMonk(TABLEAU DE tPlateau : plateau, ENTIER : n_x, ENTIER : n_y) : BOOLEEN
//BUT : vérifier que le monk ne spawn pas à côté d'un pisteur
//ENTREE : /
//SORTIE : /
var n_i <- -1, n_j <- -1 : ENTIER
var statut <- VRAI : BOOLEEN

DEBUT
    POUR n_i DE -1 A 1 FAIRE
    DEBUT
        POUR n_j DE -1 A 1 FAIRE
        FAIRE
            SI(plateau[n_x + n_i][n_y + n_j].c_affichage = "P")ALORS
            DEBUT
                statut <- FAUX
            FINSI
        FINPOUR
    FINPOUR
    verifPlaceMonk <- statut
FINFONCTION



PROCEDURE setMonk(TABLEAU DE tPlateau : plateau, tMonk : monk)
//BUT : setter les valeurs de x et y du monk
DEBUT
    FAIRE
    DEBUT
        monk.pos.n_x = (ALEATOIRE(TAILLEPLATEAULARGEUR - 2))+ 1
        monk.pos.n_y = (ALEATOIRE(TAILLEPLATEAULARGEUR - 2))+ 1
    TANT QUE ((plateau[monk.pos.n_x][monk.pos.n_y].c_affichage = "P") OU (verifPlacePlateau(monk.pos.n_x, monk.pos.n_y) = FAUX) OU (verifPlaceMonk(plateau,monk.pos.n_x, monk.pos.n_y))
FINPROCEDURE



PROCEDURE placeMonk(TABLEAU DE tPlateau : plateau, tMonk : monk)
//BUT : placer le monk dans le plateau
//ENTREE : /
//SORTIE : /
DEBUT
    plateau[monk.pos.n_x][monk.pos.n_y].c_statutCase = "M"
    plateau[monk.pos.n_x][monk.pos.n_y].c_trace = "M"
    plateau[monk.pos.n_x][monk.pos.n_y].n_trace = 16
FINPROCEDURE



PROCEDURE initPlateau(TABLEAU DE tPlateau : plateau, TABLEAU DE tPisteur : tabPisteur, ENTIER : n_nbPisteur, tMonk : monk)
//BUT : initialisation du plateau de jeu
//ENTREE : /
//SORTIE : /
var n_i <- 0, n_j <- 0 : ENTIER

DEBUT
    POUR n_i de 0 A TAILLEPLATEAULARGEUR FAIRE
    DEBUT
        POUR n_j de 0 A TAILLEPLATEAULONGUEUR FAIRE
        DEBUT
            SI ((n_i = 0 OU n_j = 0) OU (n_i = TAILLEPLATEAULARGEUR) OU (n_j = TAILLEPLATEAULONGUEUR)) FAIRE
            DEBUT
                plateau.c_affichage <- "*"
            SINON
            DEBUT
                plateau.c_affichage <- " "
                plateau.c_statutCase <- " "
                plateau.n_trace <- 0
                plateau.c_trace <- " "
            FINSI
        FINPOUR
    FINPOUR
    //On vérifie que le nombre de pisteur est supérieur ou égal à 1 et inférieur ou égale à 10
    FAIRE
        ECRIRE "Combien de pisteur desirez-vous avoir? (Max " + NBPISTEURMAX + "- Min " + NBPISTEURMIN + ")?"
        LIRE n_nbPisteur
    TANT QUE (n_nbPisteur < NBPISTEURMIN OU n_nbPisteur > NBPISTEURMAX)
    setPisteur(tabPisteur, n_nbPisteur)
    placePisteur(plateau,tabPisteur, n_nbPisteur)
    setMonk(plateau, monk)
    placeMonk(plateau, monk)
FINPROCDEDURE

PROCEDURE affichPlateau(TABLEAU DE tPlateau : plateau)
//BUT : Affichage du plateau
//ENTREE : /
//SORTIE : Le plateau avec les pisteurs positionnés

var n_i <- 0, n_j <- 0 : ENTIER

DEBUT
    POUR n_i DE 0 A TAILLEPLATEAULARGEUR FAIRE
    DEBUT
        POUR n_j DE 0 A TAILLEPLATEAULONGUEUR FAIRE
        DEBUT
            ECRIRE plateau[n_i][n_j].c_affichage
        FINPOUR
        ECRIRE "\n"
    FINPOUR
FINPROCEDURE




const TAILLEPLATEAULARGEUR <- 30
const TAILLEPLATEAULONGUEUR <- 15
const TAILLEPLATEAUORIGINE <- 0
const NBPISTEURMAX <- 10
const NBPISTEURMIN <- 1

*/

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


int main()
{
    tPisteur tabPisteur[NBPISTEURMAX];
    tPlateau tabPlateau[TAILLEPLATEAULARGEUR + 1][TAILLEPLATEAULONGUEUR + 1];
    char tabVuePisteur[3][3] = {{'1', '2', '3'},{'4', 'P', '6'}, {'7', '8', '9'}};
    char tabVueDeplacementPisteur[3][3] = {{' ', '1', ' '}, {'4', 'P', '2'}, {' ', '3', ' '}};
    int n_nbPisteur = 0;
    tMonk monk;
    int decompteVisible = 0;
    int vieMonk = 0;

    srand(GetTickCount());

    printf("Bienvenu dans la Traque. Vous allez devoir chasser le monk, une creature dangeureuse qui n'hesitera pas a vous tuer, grace a l'aide de vos Pisteurs.\n");

    initPisteur(tabPisteur, &n_nbPisteur);
    printf("Maintenant, vous allez devoir placer vos pisteurs sur le plateau.\n");
    initMonk(&monk);
    initPlateau(tabPlateau, tabPisteur, n_nbPisteur, &monk);
    system("cls");

    affichPlateau(tabPlateau);
    do{
        vieMonk = monk.vie;
        tourPisteur(tabPlateau, tabPisteur, n_nbPisteur, &monk, tabVuePisteur, tabVueDeplacementPisteur);
        if(vieMonk > monk.vie){
            decompteVisible = 4;
        }
        if(monk.vie > 0){
            printf("C'est le tour du monk.\n");
            tourMonk(tabPlateau, &monk, tabPisteur, &n_nbPisteur, decompteVisible);
        }
    }while(n_nbPisteur > 0 && monk.vie > 0);
    system("cls");

    printf("La partie est finie.");


    return 0;
}





