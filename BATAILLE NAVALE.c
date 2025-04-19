#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void initialisationOCEAN(char OCEAN[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            OCEAN[i][j] = '~';
        }
    }
}

int demanderNombreBateaux() {
    int nombreBateaux;
    printf("Combien de bateaux voulez-vous placer (max 10) ? ");
    scanf("%d", &nombreBateaux);
    
    if (nombreBateaux > 10) {
        printf("Nombre de bateaux trop élevé, réduisez-le à 10 ou moins.\n");
        nombreBateaux = 10;
    }
    return nombreBateaux;
}

void afficherOCEAN(char OCEAN[10][10]) {
    printf("  0 1 2 3 4 5 6 7 8 9\n");
    for (int i = 0; i < 10; i++) {
        printf("%d ", i);
        for (int j = 0; j < 10; j++) {
            printf("%c ", OCEAN[i][j]);
        }
        printf("\n");
    }
}

void placerBateauxALEA(char OCEAN[10][10], int nombreBateaux) {
    srand(time(NULL)); 

    int moitieBateaux = nombreBateaux / 2;
    for (int i = 0; i < moitieBateaux; i++) {
        int pos_X = rand() % 10;
        int pos_Y = rand() % 10;

        if (OCEAN[pos_X][pos_Y] == '~') {
            OCEAN[pos_X][pos_Y] = 'B';
        } else {
            i--;
        }
    }

    int bateauxRestants = nombreBateaux - moitieBateaux;
    for (int i = 0; i < bateauxRestants; i++) {
        int pos_X, pos_Y;
        printf("Placez les bateaux %d (ligne colonne) : ", i + 1);
        scanf("%d %d", &pos_X, &pos_Y);

        if (OCEAN[pos_X][pos_Y] == '~') {
            OCEAN[pos_X][pos_Y] = 'B';
        } else {
            printf("Cette case est déjà occupée, veuillez choisir une autre position.\n");
            i--;
        }
    }
}

void tourJoueur(char OCEAN[10][10], char symbole, int *nombreTirs, int *bateauxTouches) {
    int x, y;
    printf("Joueur %c, TIREZ!!! (ligne colonne) : ", symbole);
    scanf("%d %d", &x, &y);

    if (OCEAN[x][y] == 'B') {
        printf("Touché !\n");
        OCEAN[x][y] = 'X';
        (*bateauxTouches)++;
    } else {
        printf("Manqué.\n");
        
        if (OCEAN[x][y] != 'X') {
            OCEAN[x][y] = 'O'; 
        }
    }
    (*nombreTirs)--;
    printf("Nombre de tirs restants : %d\n", *nombreTirs);
    if(*nombreTirs == 0){
    printf("Fin des tirs.\n");
    }
}


void placerBateauxALEAOrdinateur(char OCEAN[10][10], int nombreBateaux) {
    srand(time(NULL));

    for (int i = 0; i < nombreBateaux; i++) {
        int pos_X = rand() % 10;
        int pos_Y = rand() % 10;

        if (OCEAN[pos_X][pos_Y] == '~') {
            OCEAN[pos_X][pos_Y] = 'B';
        } else {
            i--;
        }
    }
}

void tourOrdinateur(char OCEAN_Attaque[10][10], char OCEANDefense[10][10], int *nombreTirs, int *bateauxTouches) {
    int x = rand() % 10;
    int y = rand() % 10;

    if (OCEANDefense[x][y] == 'B') {
        printf("L'Ordinateur a touché !\n");
        OCEANDefense[x][y] = 'X'; 
        OCEAN_Attaque[x][y] = 'X'; 
        (*bateauxTouches)++;
    } else {
        printf("L'Ordinateur a raté.\n");
        if (OCEANDefense[x][y] != 'X') {
            OCEANDefense[x][y] = 'O'; 
            OCEAN_Attaque[x][y] = 'O'; 
        }
    }
    (*nombreTirs)--;
    printf("Nombre de tirs restants de l'Ordinateur : %d\n", *nombreTirs);
}

int jeuTermine(char OCEAN[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (OCEAN[i][j] == 'B') {
                return 0; 
            }
        }
    }
    return 1; 
}

int main() {
    char OCEANJoueur[10][10]; 
    char OCEANOrdinateur[10][10]; 
    char OCEAN1[10][10]; 
    char OCEAN2[10][10]; 
    int nombreTirs; 
    int nombreBateaux; 

    char symboleJoueur1 = '1'; 
    char symboleJoueur2 = '2'; 

    int choixJoueur;
    printf("Choisissez le mode de jeu : \n1. Jouer seul\n2. Jouer à deux\n");
    scanf("%d", &choixJoueur);

    if (choixJoueur == 1) {
        initialisationOCEAN(OCEANJoueur);
        initialisationOCEAN(OCEANOrdinateur);
        nombreBateaux = demanderNombreBateaux();
        nombreTirs = nombreBateaux; 
        placerBateauxALEA(OCEANJoueur, nombreBateaux);
        placerBateauxALEAOrdinateur(OCEANOrdinateur, nombreBateaux); 
    } else if (choixJoueur == 2) {
        initialisationOCEAN(OCEAN1); 
        initialisationOCEAN(OCEAN2); 
        nombreBateaux = demanderNombreBateaux(); 
        nombreTirs = nombreBateaux * 2; 
        placerBateauxALEA(OCEAN1, nombreBateaux); 
        placerBateauxALEA(OCEAN2, nombreBateaux); 
    } else {
        printf("Choix invalide.\n");
        return 1;
    }

    int bateauxTouchesJoueur1 = 0;
    int bateauxTouchesJoueur2 = 0;

    if (choixJoueur == 2) {
        while (nombreTirs > 0 && !jeuTermine(OCEAN1) && !jeuTermine(OCEAN2)) {
            printf("OCEAN du Joueur 1 :\n");
            afficherOCEAN(OCEAN1);
            tourJoueur(OCEAN2, symboleJoueur1, &nombreTirs, &bateauxTouchesJoueur1);

            if (!jeuTermine(OCEAN2) && nombreTirs > 0) {
                printf("OCEAN du Joueur 2 :\n");
                afficherOCEAN(OCEAN2);
                tourJoueur(OCEAN1, symboleJoueur2, &nombreTirs, &bateauxTouchesJoueur2);
            }
        }

        if (bateauxTouchesJoueur1 > bateauxTouchesJoueur2) {
            printf("Le Joueur 1 a gagné avec %d bateaux touchés !\n", bateauxTouchesJoueur1);
        } else if (bateauxTouchesJoueur2 > bateauxTouchesJoueur1) {
            printf("Le Joueur 2 a gagné avec %d bateaux touchés !\n", bateauxTouchesJoueur2);
        } else {
            printf("Match nul ! Chaque joueur a touché %d bateaux.\n", bateauxTouchesJoueur1);
        }
    }

    if (choixJoueur == 1) {
        int bateauxTouchesOrdinateur = 0;

        while (nombreTirs >= 0 && !jeuTermine(OCEANJoueur) && !jeuTermine(OCEANOrdinateur)) {
            printf("OCEAN du Joueur :\n");
            afficherOCEAN(OCEANJoueur);
            tourJoueur(OCEANOrdinateur, '1', &nombreTirs, &bateauxTouchesJoueur1);

            if (jeuTermine(OCEANOrdinateur)) {
                printf("Le Joueur a gagné !\n");
                break;
            }

            printf("OCEAN de l'Ordinateur :\n");
            tourOrdinateur(OCEANOrdinateur, OCEANJoueur, &nombreTirs, &bateauxTouchesOrdinateur);

            if (jeuTermine(OCEANJoueur)) {
                printf("L'Ordinateur a gagné !\n");
                break;
            }
        }

        if (bateauxTouchesJoueur1 > bateauxTouchesOrdinateur) {
            printf("Le Joueur a gagné avec %d bateaux touchés !\n", bateauxTouchesJoueur1);
        } else if (bateauxTouchesOrdinateur > bateauxTouchesJoueur1) {
            printf("L'Ordinateur a gagné avec %d bateaux touchés !\n", bateauxTouchesOrdinateur);
        } else {
            printf("Match nul ! Chaque côté a touché %d bateaux.\n", bateauxTouchesJoueur1);
        }
    }

    return 0;
}