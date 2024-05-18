#include "constants.h"
#include "struct.c"
#include "historique.c"
#include "statistiques.c"

#include <stdio.h>

#include <stdio.h>

void ajouterAthlete(){
    char prenom[50];
    char nom[50];
    int dernierNumero = 0;
    char ligne[100];
    char cheminComplet[100];

    FILE *fichierAthletes = fopen(CHEMIN"/Liste/nomAthletes.txt", "r");
    if (fichierAthletes != NULL) {
        while (fgets(ligne, sizeof(ligne), fichierAthletes) != NULL) {
            sscanf(ligne, "%d", &dernierNumero);
        }
        fclose(fichierAthletes);
    }

    printf("Entrez le prénom de l'athlète: ");
    scanf("%s", prenom);

    // Mettre la première lettre du prénom en majuscule
    if (prenom[0] >= 'a' && prenom[0] <= 'z') {
        prenom[0] = prenom[0] - 32;
    }

    printf("Entrez le nom de l'athlète: ");
    scanf("%s", nom);

    // Mettre la première lettre du nom en majuscule
    if (nom[0] >= 'a' && nom[0] <= 'z') {
        nom[0] = nom[0] - 32;
    }

    sprintf(cheminComplet, "%s/Athletes/%s %s.txt", CHEMIN, prenom, nom);

    FILE *fichier = fopen(cheminComplet, "w");
    if (fichier == NULL) {
        printf("Impossible de créer le fichier %s\n", cheminComplet);
        return;
    }

    fclose(fichier);

    fichierAthletes = fopen(CHEMIN"/Liste/nomAthletes.txt", "a");
    if (fichierAthletes != NULL) {
        fprintf(fichierAthletes, "%d %s %s\n", dernierNumero + 1, prenom, nom);
        fclose(fichierAthletes);
    }

    printf("L'athlète %s %s créé avec succès.\n", prenom, nom);
}

void supprimerAthlete(){
    int numeroAthlete;
    char ligne[100];
    int numero;
    char prenom[50];
    char nom[50];
    char nomFichier[100];
    char cheminComplet[100];

    FILE *fichierAthletes = fopen(CHEMIN"/Liste/nomAthletes.txt", "r");
    if (fichierAthletes == NULL) {
        printf("Impossible d'ouvrir le fichier nomAthletes\n");
        return;
    }

    afficherListeAthlete(fichierAthletes);
    printf("Choix : ");
    scanf("%d", &numeroAthlete);

    rewind(fichierAthletes);
    while (fscanf(fichierAthletes, "%d %s %s", &numero, prenom, nom) != EOF) {
        if(numeroAthlete == numero){
            sprintf(nomFichier, "%s %s.txt", prenom, nom);
        }
    }

    FILE *nouveauFichier = fopen(CHEMIN"/Liste/nomAthletesTemp.txt", "w");
    if (nouveauFichier == NULL) {
        printf("Impossible de créer le fichier temporaire\n");
        fclose(fichierAthletes);
        return;
    }

    rewind(fichierAthletes);
    while (fgets(ligne, sizeof(ligne), fichierAthletes) != NULL) {
        sscanf(ligne, "%d %s %s", &numero, prenom, nom);
        if (numero != numeroAthlete) {
            fprintf(nouveauFichier, "%s", ligne);
        }
    }

    fclose(fichierAthletes);
    fclose(nouveauFichier);

    sprintf(cheminComplet, "%s/Athletes/%s", CHEMIN, nomFichier);

    remove(cheminComplet);
    remove(CHEMIN"/Liste/nomAthletes.txt");
    rename(CHEMIN"/Liste/nomAthletesTemp.txt", CHEMIN"/Liste/nomAthletes.txt");

    printf("L'athlète %s %s supprimé avec succès.\n", prenom, nom);
}


void new(){
    int choix;
    printf("1. Créer un nouvel athlète\n");
    printf("2. Supprimer un athlète\n");
    printf("Choix : ");
    scanf("%d", &choix);
    printf("\n");

    switch (choix) {
        case 1:
            // Code pour ajouter un athlète
            ajouterAthlete();
            break;
        case 2:
            // Code pour supprimer un athlète
            supprimerAthlete();
            break;
        default:
            printf("Choix invalide.\n");
            new();
    }
    
}


void debutProgramme(Entrainement entrainement, FILE *file) {
    int choix;
    printf("1. Ajouter/Supprimer un athlète\n");
    printf("2. Entrer et sauvegarder les informations/résultats d'un nouvel entrainement\n");
    printf("3. Voir l'historique des entrainements de l'athlète\n");
    printf("4. Consulter des statistiques de performances de chaque athlète\n");
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
            break;
        case 3:
            historiqueEntrainement(entrainement, file);
            break;
        case 4:
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
