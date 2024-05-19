#include "def.c"
#include "athlete.c"
#include "entrainement.c"
#include "historique.c"
#include "statistiques.c"


void debutProgramme(Entrainement entrainement, FILE *file) {    
    int choix;
    printf("\n");
    couleur("1"); couleur("32"); printf("Bienvenue dans le programme de gestion des entrainements des athlètes.\n\n"); couleur("0");
    printf("1. Ajouter/Supprimer un athlète\n");
    printf("2. Ajouter/supprimer/modifier un entrainement\n");
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
    clrscr();
    FILE *file = NULL;

    debutProgramme(entrainement, file);
    
    return 0;
}
