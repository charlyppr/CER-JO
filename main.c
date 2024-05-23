#include "headers/athlete.h"
#include "headers/entrainement.h"
#include "headers/historique.h"
#include "headers/statistiques.h"


int continuerProgramme(){
    int continuer;
    couleur("32"); printf("1. Retour au menu principal\n"); couleur("0");
    couleur("31"); printf("2. Quitter\n"); couleur("0");
    printf("Choix : ");
    scanf("%d", &continuer);
    printf("\n");

    if(continuer == 1){
        // Code pour continuer
        return 1;  
    }
    else if(continuer == 2){
        return 0;
    }
    else{
        printf("Choix invalide.\n");
        return continuerProgramme();
    }
}

void debutProgramme(Entrainement entrainement1, FILE *file) {    
    int choix, continuer;
    printf("1. Ajouter/Supprimer/Modifier un athlète\n");
    printf("2. Ajouter/Supprimer/Modifier un entrainement\n");
    printf("3. Voir l'historique des entrainements de l'athlète\n");
    printf("4. Consulter des statistiques de performances de chaque athlète\n");
    couleur("31"); printf("5. Quitter\n"); couleur("0");
    printf("Choix : ");
    scanf("%d", &choix);
    printf("\n");

    while (choix != 5) {
        if(choix == 1){
            // Code pour ajouter/supprimer un athlète
            modifAthlete();
            continuer = continuerProgramme();
            if(continuer == 1){
                debutProgramme(entrainement1, file);
            }
            else{
                exit(0);
            }
        }
        else if(choix == 2){
            // Code pour entrer et sauvegarder les informations/résultats d'un nouvel entrainement
            modifEntrainement();
            continuer = continuerProgramme();
            if(continuer == 1){
                debutProgramme(entrainement1, file);
            }
            else{
                exit(0);
            }
        }
        else if(choix == 3){
            // Code pour consulter l'historique des entrainements de l'athlète
            historiqueEntrainement(entrainement1, file);
            continuer = continuerProgramme();
            if(continuer == 1){
                debutProgramme(entrainement1, file);
            }
            else{
                exit(0);
            }
        }
        else if(choix == 4){
            // Code pour consulter des statistiques de performances de chaque athlète
            statistiqueAthlete(entrainement1, file);
            continuer = continuerProgramme();
            if(continuer == 1){
                debutProgramme(entrainement1, file);
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
    couleur("1"); couleur("32"); printf("Bienvenue dans le programme de gestion des entrainements des athlètes.\n\n"); couleur("0");

    debutProgramme(entrainement, fileN);
    
    return 0;
}
