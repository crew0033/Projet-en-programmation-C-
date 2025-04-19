#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAILLE 8       // Taille de la grille (8x8)
#define NB_MINES 10    // Nombre de mines

typedef struct {
    int mine;
    int decouverte;
    int drapeau;
    int nb_mines_autour;
} Case;

Case grille[TAILLE][TAILLE];

void initialiser_grille() {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            grille[i][j].mine = 0;
            grille[i][j].decouverte = 0;
            grille[i][j].drapeau = 0;
            grille[i][j].nb_mines_autour = 0;
        }
    }
}

void placer_mines() {
    int mines_placees = 0;
    while (mines_placees < NB_MINES) {
        int x = rand() % TAILLE;
        int y = rand() % TAILLE;
        if (!grille[x][y].mine) {
            grille[x][y].mine = 1;
            mines_placees++;
        }
    }
}

void calculer_mines_autour() {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (grille[i][j].mine) continue;
            int count = 0;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int nx = i + dx;
                    int ny = j + dy;
                    if (nx >= 0 && nx < TAILLE && ny >= 0 && ny < TAILLE) {
                        if (grille[nx][ny].mine) count++;
                    }
                }
            }
            grille[i][j].nb_mines_autour = count;
        }
    }
}

void afficher_grille() {
    printf("   ");
    for (int j = 0; j < TAILLE; j++) printf("%d ", j);
    printf("\n");

    for (int i = 0; i < TAILLE; i++) {
        printf("%d |", i);
        for (int j = 0; j < TAILLE; j++) {
            if (grille[i][j].drapeau) {
                printf("F ");
            } else if (!grille[i][j].decouverte) {
                printf(". ");
            } else if (grille[i][j].mine) {
                printf("* ");
            } else {
                printf("%d ", grille[i][j].nb_mines_autour);
            }
        }
        printf("\n");
    }
}

void devoiler_case(int x, int y) {
    if (x < 0 || x >= TAILLE || y < 0 || y >= TAILLE) return;
    if (grille[x][y].decouverte || grille[x][y].drapeau) return;

    grille[x][y].decouverte = 1;

    if (grille[x][y].nb_mines_autour == 0 && !grille[x][y].mine) {
        for (int dx = -1; dx <= 1; dx++)
            for (int dy = -1; dy <= 1; dy++)
                if (dx != 0 || dy != 0)
                    devoiler_case(x + dx, y + dy);
    }
}

int a_gagne() {
    for (int i = 0; i < TAILLE; i++)
        for (int j = 0; j < TAILLE; j++)
            if (!grille[i][j].mine && !grille[i][j].decouverte)
                return 0;
    return 1;
}

void jouer() {
    int x, y;
    char action;
    int perdu = 0;

    while (!perdu) {
        afficher_grille();
        printf("Entrez votre action (d x y pour découvrir, f x y pour flag) : ");
        scanf(" %c %d %d", &action, &x, &y);

        if (x < 0 || x >= TAILLE || y < 0 || y >= TAILLE) {
            printf("Coordonnées invalides !\n");
            continue;
        }

        if (action == 'd') {
            if (grille[x][y].mine) {
                printf("BOOM ! Vous avez perdu !\n");
                grille[x][y].decouverte = 1;
                perdu = 1;
            } else {
                devoiler_case(x, y);
                if (a_gagne()) {
                    printf("🎉 Bravo ! Vous avez gagné !\n");
                    break;
                }
            }
        } else if (action == 'f') {
            grille[x][y].drapeau = !grille[x][y].drapeau;
        } else {
            printf("Action invalide !\n");
        }
    }

    afficher_grille();
}

int main() {
    srand(time(NULL));
    initialiser_grille();
    placer_mines();
    calculer_mines_autour();
    jouer();
    return 0;
}
