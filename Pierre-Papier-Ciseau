#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int choixJoueur, choixOrdinateur;
    int scoreJoueur = 0, scoreOrdinateur = 0;
    char *options[] = {"Pierre", "Papier", "Ciseaux"};

    // Initialiser le générateur de nombres aléatoires
    srand(time(NULL));

    printf("Bienvenue au jeu Pierre, Papier, Ciseaux !\n");

    // Boucle principale du jeu
    while (scoreJoueur < 5 && scoreOrdinateur < 5) {
        printf("\nChoisissez une option :\n");
        printf("0 - Pierre\n");
        printf("1 - Papier\n");
        printf("2 - Ciseaux\n");
        printf("Entrez votre choix (0, 1 ou 2) : ");
        scanf("%d", &choixJoueur);

        // Vérifier si le choix du joueur est valide
        if (choixJoueur < 0 || choixJoueur > 2) {
            printf("Choix invalide. Veuillez entrer 0, 1 ou 2.\n");
            continue; // Recommencer la boucle si le choix est invalide
        }

        // Générer le choix de l'ordinateur
        choixOrdinateur = rand() % 3;

        printf("Vous avez choisi : %s\n", options[choixJoueur]);
        printf("L'ordinateur a choisi : %s\n", options[choixOrdinateur]);

        // Déterminer le gagnant
        if (choixJoueur == choixOrdinateur) {
            printf("C'est un match nul !\n");
        } else if ((choixJoueur == 0 && choixOrdinateur == 2) || 
                   (choixJoueur == 1 && choixOrdinateur == 0) || 
                   (choixJoueur == 2 && choixOrdinateur == 1)) {
            printf("Vous avez gagné ce round !\n");
            scoreJoueur++;
        } else {
            printf("L'ordinateur a gagné ce round !\n");
            scoreOrdinateur++;
        }

        // Afficher les scores
        printf("Score - Vous : %d, Ordinateur : %d\n", scoreJoueur, scoreOrdinateur);
    }

    // Annonce le gagnant final
    if (scoreJoueur == 5) {
        printf("\nFélicitations ! Vous avez gagné le jeu !\n");
    } else {
        printf("\nL'ordinateur a gagné le jeu !\n");
    }

    return 0;
}
