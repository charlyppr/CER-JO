#include "constants.h"
#include "struct.c"
#include "athlete.c"
#include "entrainement.c"
#include "historique.c"
#include "statistiques.c"


void debutProgramme(Entrainement entrainement, FILE *file) {
    int choix;
    printf("1. Ajouter/Supprimer un athlète\n");
    printf("2. Ajouter/supprimer/modifier un entrainement\n");
    printf("3. Voir l'historique des entrainements de l'athlète\n");
    printf("4. Consulter des statistiques de performances de chaque athlète\n");
    printf("5. Quitter\n");
    printf("Choix : ");
    scanf("%d", &choix);
    printf("\n");

    switch (choix) {
        case 1:
            // Code pour ajouter/supprimer un athlète
            new();
            break;
        case 2:
            // Code pour entrer et sauvegarder les informations/résultats d'un nouvel entrainement
            nouvelEntrainement();
            break;
        case 3:
            historiqueEntrainement(entrainement, file);
            break;
        case 4:
            // Code pour consulter des statistiques de performances de chaque athlète
            statistiqueAthlete(entrainement, file);
            break;
        case 5:
            // Code pour quitter le programme
            exit(0);
            break;
        default:
            printf("Choix invalide.\n");
            debutProgramme(entrainement, file);
    }
}


int main(){
    FILE *file = NULL;

    debutProgramme(entrainement, file);
    
    return 0;
}
