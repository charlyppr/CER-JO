#ifndef DEF_C
#define DEF_C
#include "constants.h"

Entrainement entrainement;

int compterLignes(FILE *file) {
    int c;
    int lignes = 0;

    // Compter le nombre de lignes
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            lignes++;
        }
    }
    return lignes;
}

int dateValide(Date date) {
    if (date.annee < 2000 || date.annee > 2024) {
        return 0;
    }

    if (date.mois < 1 || date.mois > 12) {
        return 0;
    }

    if (date.jour < 1 || date.jour > 31) {
        return 0;
    }

    if (date.mois == 2) {
        if (date.annee % 4 == 0) {
            if (date.jour > 29) {
                return 0;
            }
        } else {
            if (date.jour > 28) {
                return 0;
            }
        }
    }

    if (date.mois == 4 || date.mois == 6 || date.mois == 9 || date.mois == 11) {
        if (date.jour > 30) {
            return 0;
        }
    }

    return 1;
}

int compareDates(const void *a, const void *b) {
    Date *dateA = (Date *)a;
    Date *dateB = (Date *)b;

    if (dateA->annee != dateB->annee)
        return dateA->annee - dateB->annee;
    else if (dateA->mois != dateB->mois)
        return dateA->mois - dateB->mois;
    else
        return dateA->jour - dateB->jour;
}

void afficherNomAthlete(FILE *file) {
    char nomAthlete[MAX];
    // Sauter le numéro de l'athlète
    fseek(file, 2, SEEK_CUR);
    // Lecture du nom de l'athlète
    fgets(nomAthlete, sizeof(nomAthlete), file);
    // Suppression de la nouvelle ligne
    nomAthlete[strcspn(nomAthlete, "\n")] = 0;
    printf("%s\n", nomAthlete);
}

void afficherListeAthlete(FILE *nomAthlete) {
    int lignes = compterLignes(nomAthlete);

    printf("Quelle athlètes parmis ces %d\n", lignes);
    rewind(nomAthlete);

    // Affichage de la liste des athlètes
    for (int i = 0; i < lignes; i++) {
        printf("%d. ", i + 1);
        afficherNomAthlete(nomAthlete);
    }
}

void afficherNomEpreuve(FILE *nomEpreuve) {
    char epreuve[MAX];
    // Sauter le numéro de l'épreuve
    fseek(nomEpreuve, 2, SEEK_CUR);
    // Lecture du nom de l'épreuve
    fgets(epreuve, sizeof(epreuve), nomEpreuve);
    // Suppression de la nouvelle ligne
    epreuve[strcspn(epreuve, "\n")] = 0;
    printf("%s\n", epreuve);
}

void afficherListeEpreuve(FILE *nomEpreuve) {
    int lignes = compterLignes(nomEpreuve);

    printf("Quelle épreuves parmis ces %d\n", lignes);
    rewind(nomEpreuve);

    // Affichage de la liste des épreuves
    for (int i = 0; i < lignes; i++) {
        printf("%d. ", i + 1);
        afficherNomEpreuve(nomEpreuve);
    }
}

FILE *ouvrirFichierAthlete(int choixAthlete) {
    int numAthlete;
    char fileName[MAX];
    char nomAthlete[MAX];

    // Ouvrir le fichier nomAthletes
    FILE *nomAthletes = fopen(CHEMIN"/Liste/nomAthletes.txt", "r");
    if(nomAthletes == NULL){
        printf("Impossible d'ouvrir le fichier nomAthlete 2.\n");
        exit(1);
    }

    // Lire chaque ligne du fichier
    while (fgets(nomAthlete, sizeof(nomAthlete), nomAthletes)) {
        sscanf(nomAthlete, "%d", &numAthlete);
        nomAthlete[strcspn(nomAthlete, "\n")] = 0;

        if(numAthlete == choixAthlete) {
            printf("%s :\n", nomAthlete + 2);
            break;
        }
    }

    sprintf(fileName, CHEMIN"/Athletes/%s.txt", nomAthlete + 2);
    
    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        printf("Impossible d'ouvrir le fichier %s.txt.\n", nomAthlete + 2);
        exit(1);
    }
    return file;
}

FILE *modifierFichierAthlete(int choixAthlete) {
    int numAthlete;
    char fileName[MAX];
    char nomAthlete[MAX];

    // Ouvrir le fichier nomAthletes
    FILE *nomAthletes = fopen(CHEMIN"/Liste/nomAthletes.txt", "r");
    if(nomAthletes == NULL){
        printf("Impossible d'ouvrir le fichier nomAthlete 2.\n");
        exit(1);
    }

    // Lire chaque ligne du fichier
    while (fgets(nomAthlete, sizeof(nomAthlete), nomAthletes)) {
        sscanf(nomAthlete, "%d", &numAthlete);
        nomAthlete[strcspn(nomAthlete, "\n")] = 0;

        if(numAthlete == choixAthlete) {
            break;
        }
    }

    sprintf(fileName, CHEMIN"/Athletes/%s.txt", nomAthlete + 2);
    
    FILE *file = fopen(fileName, "r+");
    if(file == NULL){
        printf("Impossible d'ouvrir le fichier %s.txt.\n", nomAthlete + 2);
        exit(1);
    }
    return file;
}


#endif