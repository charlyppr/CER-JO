#include "headers/athlete.h"
#include "headers/entrainement.h"
#include "headers/historique.h"
#include "headers/statistiques.h"

int continueProgramme(){
    int continueProg;
    color("32"); printf("1. Retour au menu principal\n"); color("0");
    color("31"); printf("2. Quitter\n"); color("0");
    printf("Choix : ");
    scanf("%d", &continueProg);
    printf("\n");

    if(continueProg == 1){
        // Code pour continuer le programme
        return 1;  
    }
    else if(continueProg == 2){
        return 0;
    }
    else{
        printf("Choix invalide.\n");
        return continueProgramme();
    }
}

void startProgramme(Training training1, FILE *file) {    
    int choice, continueProg;
    printf("1. Ajouter/Supprimer/Modifier un athlète\n");
    printf("2. Ajouter/Supprimer/Modifier un entrainement\n");
    printf("3. Voir l'historique des entrainements de l'athlète\n");
    printf("4. Consulter des statistiques de performances de chaque athlète\n");
    color("31"); printf("5. Quitter\n"); color("0");
    printf("Choix : ");
    scanf("%d", &choice);
    printf("\n");

    while (choice != 5) {
        if(choice == 1){
            // Code pour ajouter/supprimer un athlète
            modifAthlete();
            continueProg = continueProgramme();
            if(continueProg == 1){
                startProgramme(training1, file);
            }
            else{
                exit(0);
            }
        }
        else if(choice == 2){
            // Code pour entrer et sauvegarder les informations/résultats d'un nouvel entrainement
            modifEntrainement();
            continueProg = continueProgramme();
            if(continueProg == 1){
                startProgramme(training1, file);
            }
            else{
                exit(0);
            }
        }
        else if(choice == 3){
            // Code pour consulter l'historique des entrainements de l'athlète
            trainingHistory(training1, file);
            continueProg = continueProgramme();
            if(continueProg == 1){
                startProgramme(training1, file);
            }
            else{
                exit(0);
            }
        }
        else if(choice == 4){
            // Code pour consulter des statistiques de performances de chaque athlète
            athleteStatistic(training1, file);
            continueProg = continueProgramme();
            if(continueProg == 1){
                startProgramme(training1, file);
            }
            else{
                exit(0);
            }
        }
        else{
            printf("Choix invalide.\n");
        }
    }
    exit(0);
}


int main(void){
    clrscr();
    FILE *fileN = NULL;

    printf("\n");
    color("1"); color("32"); printf("Bienvenue dans le programme de gestion des entrainements des athlètes.\n\n"); color("0");

    startProgramme(training, fileN);
    
    return 0;
}
