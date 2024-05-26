#include "headers/athlete.h"
#include "headers/entrainement.h"
#include "headers/historique.h"
#include "headers/statistiques.h"


#define TERMINAL_WIDTH 80 // La largeur du terminal (vous pouvez ajuster cette valeur)

void afficherCentrer(const char *texte) {
    int longueur = strlen(texte);
    int espaces = (TERMINAL_WIDTH - longueur) / 2;

    for (int i = 0; i < espaces; i++) {
        printf(" ");
    }
    printf("%s\n", texte);
}

void afficherMenu() {
    afficherCentrer("*******************************************************************\n");
    afficherCentrer("*                          Menu Principal                         *\n");
    afficherCentrer("*******************************************************************\n");
    afficherCentrer("* 1. Ajouter/Supprimer/Modifier un athlète                        *\n");
    afficherCentrer("* 2. Ajouter/Supprimer/Modifier un entrainement                   *\n");
    afficherCentrer("* 3. Voir l'historique des entrainements de l'athlète             *\n");
    afficherCentrer("* 4. Consulter des statistiques de performances de chaque athlète *\n");
    afficherCentrer("*");color("31"); printf("5. Quitter                                                      "); color("0"); printf("*\n");
    afficherCentrer("*******************************************************************\n");
    afficherCentrer("Choix : ");
}



void startProgramme(Training training1, FILE *file) {    
    int choice, continueProg;
    afficherMenu();
    scanf("%d", &choice);
    printf("\n");

    if(choice == 5){
        return;
    }

    else {
        if(choice == 1){
            // Code pour ajouter/supprimer un athlète
            modifAthlete();
            continueProg = continueProgramme();
            if(continueProg == 1){
                startProgramme(training1, file);
            }
            else{
                return;
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
                return;
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
                return;
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
                return;
            }
        }
        else{
            printf("Choix invalide.\n");
        }
    }
    return;
}

int main(void){
    clrscr();
    FILE *fileN = NULL;
    int start = 0;

    printf("\nVerification que PATH est bien correct ...\n");
    printf("PATH = %s\n\n", PATH);
    FILE *file = fopen(PATH"/Liste/nomEpreuve.txt", "r");
    if(file == NULL){
        color("5"); color("31"); printf("PATH n'est pas correct !\n"); color("0");
        printf("Corriger sa valeur en copiant le chemin d'accès du dossier directement dans le fichier PATH.h\n\n");
        exit(0);
    } else {
        color("32"); printf("PATH est correct !.\n"); color("0");
        start = 1;
    }
    fclose(file);

    if(start == 1){
        clrscr();
        color("1"); color("32"); printf("\nBienvenue dans le programme de gestion des entrainements des athlètes.\n"); color("0");
        OGStart();

        startProgramme(training, fileN);

        color("1"); color("32"); printf("\nMerci d'avoir utilisé le programme de gestion des entrainements des athlètes !\n"); color("0");
        color("1"); printf("A bientôt ! %s\n\n", "🥳"); color("0");
    }
    
    return 0;
}
