#include "headers/athlete.h"
#include "headers/entrainement.h"
#include "headers/historique.h"
#include "headers/statistiques.h"



void debutProgramme(Entrainement entrainement1, FILE *file) {    
    int choix;
    printf("\n");
    couleur("1"); couleur("32"); printf("Bienvenue dans le programme de gestion des entrainements des athlètes.\n\n"); couleur("0");
    printf("1. Ajouter/Supprimer/Modifier un athlète\n");
    printf("2. Ajouter/Supprimer/Modifier un entrainement\n");
    printf("3. Voir l'historique des entrainements de l'athlète\n");
    printf("4. Consulter des statistiques de performances de chaque athlète\n");
    couleur("31"); printf("5. Quitter\n"); couleur("0");
    printf("Choix : ");
    scanf("%d", &choix);
    printf("\n");

    switch (choix) {
        case 1:
            // Code pour ajouter/supprimer un athlète
            modifAthlete();
            break;
        case 2:
            // Code pour entrer et sauvegarder les informations/résultats d'un nouvel entrainement
            modifEntrainement();
            break;
        case 3:
            historiqueEntrainement(entrainement1, file);
            break;
        case 4:
            // Code pour consulter des statistiques de performances de chaque athlète
            statistiqueAthlete(entrainement1, file);
            break;
        case 5:
            // Code pour quitter le programme
            exit(0);
            break;
        default:
            printf("Choix invalide.\n");
            debutProgramme(entrainement1, file);
    }
}


int main(void){
    clrscr();
    FILE *file = NULL;

    debutProgramme(entrainement, file);
    
    return 0;
}
