#include "constants.h"
#include "struct.c"
#include "historique.c"
#include "statistiques.c"


void debutProgramme(Entrainement entrainement, FILE *file) {
    int choix;
    printf("1. Entrer et sauvegarder les informations/résultats d'un nouvel entrainement\n");
    printf("2. Voir l'historique des entrainements de l'athlète\n");
    printf("3. Consulter des statistiques de performances de chaque athlète\n");
    printf("Choix : ");
    scanf("%d", &choix);
    printf("\n");

    switch (choix) {
        case 1:
            // Code pour entrer et sauvegarder les informations/résultats d'un nouvel entrainement
            break;
        case 2:
            historiqueEntrainement(entrainement, file);
            break;
        case 3:
            // Code pour consulter des statistiques de performances de chaque athlète
            statistiqueAthlete(entrainement, file);
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
