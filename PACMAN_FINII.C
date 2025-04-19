#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define LIGNE 15
#define COLONNE 17

int pacman_x, pacman_y;
int fantomes_x[10], fantomes_y[10]; 
char labyrinthe[LIGNE][COLONNE];
int score = 0;

//fonction pour afficher le labyrinthe avec la position de pacman et le score
void afficherLabyrinthe() {
    for (int i = 0; i < LIGNE; i++) {
        for (int j = 0; j < COLONNE; j++) {
            if (pacman_x == i && pacman_y == j) {
                printf("P");
            } else {
                printf("%c ", labyrinthe[i][j]);
            }
        }
        printf("\n");
    }
    printf("Score : %d", score);
}

//fonction pour placer pacman dans le labyrinthe et le placer au millieu de la map
void placerPacman() {
    pacman_x = 7;
    pacman_y = 8;
}

//fonction pour placer un nombre donné de fantomes dans le labyrinthe de maniere aleatoire
void placerFantomes(int nombre_fantome) {
    srand(time(NULL));
    int ghost = 0;
    int colonne, ligne;

    while (ghost < nombre_fantome) {
        colonne = rand() % COLONNE;
        ligne = rand() % LIGNE;

        if (labyrinthe[ligne][colonne] == '.') {//verif si la case est libre case libre= '.'
            labyrinthe[ligne][colonne] = 'F';//placer un fantome dans le labyrinthe 
            fantomes_x[ghost] = ligne;//enregistre la position de fantomes position x et y
            fantomes_y[ghost] = colonne;
            ghost++;
        }
    }
}

//fonction pour verifier si une position est un mur
bool Mur(int x, int y) {
    return (x < 0 || y < 0 || x >= LIGNE || y >= COLONNE || labyrinthe[x][y] == '#');// on definit ou peut se deplacer et ou on peut pas
}

//fonction pour deplacer pacman dans le labyrinthe en fonction de la direction fournie
void deplacerPacman(char direction) {
    int prochain_pas_x = pacman_x;
    int prochain_pas_y = pacman_y;

    switch (direction) {
        case 'h': // Haut
            prochain_pas_y++;
            break;
        case 'b': // Bas
            prochain_pas_y--;
            break;
        case 'g': // Gauche
            prochain_pas_x--;
            break;
        case 'd': // Droite
            prochain_pas_x++;
            break;
    }

    if (!Mur(prochain_pas_x, prochain_pas_y)) {
        if (labyrinthe[prochain_pas_x][prochain_pas_y] == '.') {//case avec pastille
            labyrinthe[pacman_x][pacman_y] = ' ';//case vide apres passage
            pacman_x = prochain_pas_x;
            pacman_y = prochain_pas_y;
            labyrinthe[pacman_x][pacman_y] = 'P';
            score += 10;//valeur pastille au score
        } else if (labyrinthe[prochain_pas_x][prochain_pas_y] == 'o') {//case avec grosse pastille
            labyrinthe[pacman_x][pacman_y] = ' ';
            pacman_x = prochain_pas_x;
            pacman_y = prochain_pas_y;
            labyrinthe[pacman_x][pacman_y] = 'P';
            score += 50;//valeur grosse pastille au score
        } else {
            labyrinthe[pacman_x][pacman_y] = ' ';//passage sur une case vide
            pacman_x = prochain_pas_x;
            pacman_y = prochain_pas_y;
            labyrinthe[pacman_x][pacman_y] = 'P';
        }
    }
}

//fonction pour detecter la collision de pacman avec un fantome
bool CollisionFantome(int nombre_fantome) {
    for (int i = 0; i < nombre_fantome; i++) {
        //on verifie si les coordonées de pacman correspond à celles d'un fantome
        if (pacman_x == fantomes_x[i] && pacman_y == fantomes_y[i]) {
            return true;
            //si il y a collision
        }
    }
    return false;//s'il n'y a pas de collision avec un fantome 
}

//fonction pour deplacer les fantomes dans le labyrinthe
void deplacerFantomes(int nombre_fantome) {
    // Nombre de fantômes qui suivent le Pacman
    int nombre_fantome_suiveurs = 2;//il y aura 2 poursuivant et les roles des fantomes changent en fonctions des deplacement du pacman

    for (int i = 0; i < nombre_fantome; i++) {
        printf("n°%d ( x: %d|y: %d) \n", i, fantomes_x[i], fantomes_y[i]);

        int destination_x, destination_y, deplacement_x = 0, deplacement_y = 0;

        if (i < nombre_fantome_suiveurs) {
            destination_x = pacman_x;//le fantome va poursuivre pacman en fonction de sa position
            destination_y = pacman_y;

            int diffX = destination_x - fantomes_x[i];//calcul des differences entre la position du fantomes et la destination
            int diffY = destination_y - fantomes_y[i];

            if (diffX < 0 && !Mur(fantomes_x[i] - 1, fantomes_y[i]))//permettre au fantome de se deplacer en evitant les murs
                deplacement_x = -1;
            else if (diffX > 0 && !Mur(fantomes_x[i] + 1, fantomes_y[i]))
                deplacement_x = 1;

            if (diffY < 0 && !Mur(fantomes_x[i], fantomes_y[i] - 1))
                deplacement_y = -1;
            else if (diffY > 0 && !Mur(fantomes_x[i], fantomes_y[i] + 1))
                deplacement_y = 1;
        } else {
            do {//si le fantome n'est pas suiveur , il se deplace aleatoirement
                int direction = rand() % 4;

                switch (direction) {
                    case 0: // Haut
                        deplacement_x = -1;
                        break;
                    case 1: // Bas
                        deplacement_x = 1;
                        break;
                    case 2: // Gauche
                        deplacement_y = -1;
                        break;
                    case 3: // Droite
                        deplacement_y = 1;
                        break;
                }
            } while (Mur(fantomes_x[i] + deplacement_x, fantomes_y[i] + deplacement_y));
        }
        labyrinthe[fantomes_x[i]][fantomes_y[i]] = ' ';//mettre à jours la position des fantomes suiveurs
        fantomes_x[i] += deplacement_x;
        fantomes_y[i] += deplacement_y;
        labyrinthe[fantomes_x[i]][fantomes_y[i]] = 'F';
    }
}  

int main() {
    srand(time(NULL));
    int nombre_fantome = 0;
    printf("Entrez le nombre de fantomes : ");
    scanf("%d", &nombre_fantome);

    do {
        printf("Entrez le nombre de fantomes (1-4) : ");
        scanf("%d", &nombre_fantome);

        if (nombre_fantome < 1 || nombre_fantome > 4) {
            printf("Nombre invalide. Veuillez choisir entre 1 et 4 fantomes.\n");
        }

    } while (nombre_fantome < 1 || nombre_fantome > 4);

//grille initiale du labyrinthe
    char grille[LIGNE][COLONNE] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', 'o', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'o', '#'},
        {'#', '.', '#', '.', '#', '.', '#', '#', '#', '#', '#', '.', '#', '.', '#', '.', '#'},
        {'#', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '#'},
        {'#', '#', '#', '.', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '#', '#', '#'},
        {'#', '#', '#', '.', '#', '.', '.', '.', '.', '.', '.', '.', '#', '.', '#', '#', '#'},
        {'#', '#', '#', '.', '#', '.', '#', '#', '.', '#', '#', '.', '#', '.', '#', '#', '#'},
        {'#', '.', '.', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '#'},
        {'#', '#', '#', '.', '#', '.', '#', '#', '#', '#', '#', '.', '#', '.', '#', '#', '#'},
        {'#', '#', '#', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#', '#', '#'},
        {'#', '#', '#', '.', '#', '.', '#', '#', '#', '#', '#', '.', '#', '.', '#', '#', '#'},
        {'#', '.', '.', '.', '#', '.', '.', '.', '#', '.', '.', '.', '.', '.', '.', '.', '#'},
        {'#', '.', '#', '.', '#', '#', '#', '.', '#', '.', '#', '#', '#', '.', '#', '.', '#'},
        {'#', 'o', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'o', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    };
//ici on copie la grille initiale dans le labyrinthe , on les superpose
    for (int i = 0; i < LIGNE; i++) {
        for (int j = 0; j < COLONNE; j++) {
            labyrinthe[i][j] = grille[i][j];
        }
    }
//mise en palce de pacman et pour placer les fantomes
    placerPacman();
    placerFantomes(nombre_fantome);

    char direction;
    bool finJeu = false;
//boucle principale du jeu
    while (!finJeu) {
        printf("P ( x: %d|y: %d) \n", pacman_x, pacman_y);//position de pacman apres chaque deplacement
        afficherLabyrinthe();//afffiche l'etat actuel du pacman
        printf("Touche Pacman |Haut=g, Bas=d, Gauche=b, Droite=h| : ");
        scanf(" %c", &direction);
        deplacerPacman(direction);//deplace pacman dans la direction spécifiée par l'utilisateur
//verifier la collision avec un fantome
        if (CollisionFantome(nombre_fantome)) {
            finJeu = true;
            printf("Collision avec un fantôme ! Partie terminée.\n");
        } else {
            deplacerFantomes(nombre_fantome);
        }
    }

    return 0;
}