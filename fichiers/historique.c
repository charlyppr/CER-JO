#include "../headers/historique.h"

void afficherEntrainementNom(Entrainement entrainement1, int choixAthlete) {
    int position;
    FILE *file = ouvrirFichierAthlete(choixAthlete);
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier choixAthlete\n");
        return;
    }

    // Sauter une ligne
    while (fgetc(file) != '\n');

    // Lire chaque ligne du fichier
    while (fscanf(file, "%d %d %d %s %d %d %d %d", &entrainement1.dateEntrainement.jour, &entrainement1.dateEntrainement.mois, &entrainement1.dateEntrainement.annee, entrainement1.typeEpreuve, &entrainement1.tempsAthlete.minute, &entrainement1.tempsAthlete.seconde, &entrainement1.tempsAthlete.milliseconde, &position) != EOF) {
        // Affichage des valeurs
        printf("Date de l'entraînement : %02d/%02d/%04d\n", entrainement1.dateEntrainement.jour, entrainement1.dateEntrainement.mois, entrainement1.dateEntrainement.annee);
        printf("Type d'épreuve :         %s\n", entrainement1.typeEpreuve);
        if(strcmp(entrainement1.typeEpreuve, "Relais") == 0){
            if(position == 0){
                continue;
            } else {
                if(position == 1) {
                    printf("Position au relais :     %der coureur\n", position);
                } else if(position > 1) {
                    printf("Position au relais :     %dème coureur\n", position);
                }
            }
        }
        printf("Temps de l'athlète :     %02dmin %02dsec %03dms\n", entrainement1.tempsAthlete.minute, entrainement1.tempsAthlete.seconde, entrainement1.tempsAthlete.milliseconde);
        printf("\n");
    }

    // Fermeture du fichier
    fclose(file);
}

void afficherEntrainementTypeEpreuve(Entrainement entrainement1, int choixEpreuve) {
    char epreuve[MAX];
    int numEpreuve, position;

    FILE *nomEpreuve = fopen(CHEMIN"/Liste/nomEpreuve.txt", "r");
    if(nomEpreuve == NULL){
        printf("Impossible d'ouvrir le fichier nomEpreuve.\n");
        exit(1);
    }

    while (fgets(epreuve, sizeof(epreuve), nomEpreuve)) {
        sscanf(epreuve, "%d", &numEpreuve);
        epreuve[strcspn(epreuve, "\n")] = 0;

        if(numEpreuve == choixEpreuve) {
            printf("%s :\n", epreuve + 2);
            break;
        }
    }

    // Fermeture du fichier nomEpreuve
    fclose(nomEpreuve);

    // Ouvrir le fichier de tous les athlètes
    FILE *nomAthletes = fopen(CHEMIN"/Liste/nomAthletes.txt", "r");
    if(nomAthletes == NULL){
        printf("Impossible d'ouvrir le fichier nomAthlètes 2.\n");
        exit(1);
    }

    char nomAthlete[MAX] = {0};
    int lignes = compterLignes(nomAthletes);
    rewind(nomAthletes);

    for(int i = 0; i < lignes; i++) {
        int entrainementTrouve = 0;

        // Lecture du nom de l'athlète
        fgets(nomAthlete, sizeof(nomAthlete), nomAthletes);
        nomAthlete[strcspn(nomAthlete, "\n")] = 0;

        // Ouvrir le fichier de l'athlète
        char fileName[MAX] = {0};
        sprintf(fileName, CHEMIN"/Athletes/%s.txt", nomAthlete + 2);
        FILE *file = fopen(fileName, "r");
        if (file == NULL) {
            printf("Impossible d'ouvrir le fichier de l'athlète.\n");
            exit(1);
        }

        // Sauter une ligne
        while (fgetc(file) != '\n');

        while (fscanf(file, "%d %d %d %s %d %d %d %d", &entrainement1.dateEntrainement.jour, &entrainement1.dateEntrainement.mois, &entrainement1.dateEntrainement.annee, entrainement1.typeEpreuve, &entrainement1.tempsAthlete.minute, &entrainement1.tempsAthlete.seconde, &entrainement1.tempsAthlete.milliseconde, &position) != EOF) {
            if (strcmp(entrainement1.typeEpreuve, epreuve + 2) == 0) {
                // Affichage des valeurs
                printf("Athlète :                %s\n", nomAthlete + 2);
                if(strcmp(entrainement1.typeEpreuve, "Relais") == 0){
                    if(position == 0){
                        continue;
                    } else {
                        if(position == 1) {
                            printf("Position au relais :     %der coureur\n", position);
                        } else if(position > 1) {
                            printf("Position au relais :     %dème coureur\n", position);
                        }
                    }
                }
                printf("Date de l'entraînement : %02d/%02d/%04d\n", entrainement1.dateEntrainement.jour, entrainement1.dateEntrainement.mois, entrainement1.dateEntrainement.annee);
                printf("Temps de l'athlète :     %02dmin %02dsec %03dms\n", entrainement1.tempsAthlete.minute, entrainement1.tempsAthlete.seconde, entrainement1.tempsAthlete.milliseconde);
                printf("\n");
                entrainementTrouve = 1;
            }
        }

        if (!entrainementTrouve) {
            printf("Aucun entraînement de ce type n'a été trouvé pour l'athlète %s.\n\n", nomAthlete + 2);
        }

        // Fermeture du fichier de l'athlète
        fclose(file);
    }

    // Fermeture du fichier nomAthlètes
    fclose(nomAthletes);
}

void afficherEntrainementDate(Entrainement entrainement1) {
    int position;
    Date date;

    printf("Entrez la date de l'entrainement (JJ/MM/AAAA) : ");
    scanf("%d %d %d", &date.jour, &date.mois, &date.annee);
    printf("\n");
    while(!dateValide(date)){
        printf("Date invalide. Veuillez entrer une date valide.\n");
        printf("Entrez la date de l'entrainement (JJ/MM/AAAA) : ");
        scanf("%d %d %d", &date.jour, &date.mois, &date.annee);
        printf("\n");
    }

    FILE *nomAthletes = fopen(CHEMIN"/Liste/nomAthletes.txt", "r");
    if(nomAthletes == NULL){
        printf("Impossible d'ouvrir le fichier nomAthlètes 1.\n");
        exit(1);
    }

    char nomAthlete[MAX] = {0};
    int lignes = compterLignes(nomAthletes);
    rewind(nomAthletes);
    for(int i = 0; i < lignes; i++) {
        int entrainementTrouve = 0;
        fgets(nomAthlete, sizeof(nomAthlete), nomAthletes);
        nomAthlete[strcspn(nomAthlete, "\n")] = 0;

        char fileName[MAX] = {0};
        sprintf(fileName, CHEMIN"/Athletes/%s.txt", nomAthlete + 2);
        FILE *file = fopen(fileName, "r");
        if (file == NULL) {
            printf("Impossible d'ouvrir le fichier de l'athlète.\n");
            exit(1);
        }

        while (fgetc(file) != '\n');
        while (fscanf(file, "%d %d %d %s %d %d %d %d", &entrainement1.dateEntrainement.jour, &entrainement1.dateEntrainement.mois, &entrainement1.dateEntrainement.annee, entrainement1.typeEpreuve, &entrainement1.tempsAthlete.minute, &entrainement1.tempsAthlete.seconde, &entrainement1.tempsAthlete.milliseconde, &position) != EOF) {
            if (entrainement1.dateEntrainement.jour == date.jour && entrainement1.dateEntrainement.mois == date.mois && entrainement1.dateEntrainement.annee == date.annee) {
                printf("Athlète :                %s\n", nomAthlete + 2);
                printf("Type d'épreuve :         %s\n", entrainement1.typeEpreuve);
                if(strcmp(entrainement1.typeEpreuve, "Relais") == 0){
                    if(position == 0){
                        continue;
                    } else {
                        if(position == 1) {
                            printf("Position au relais :     %der coureur\n", position);
                        } else if(position > 1) {
                            printf("Position au relais :     %dème coureur\n", position);
                        }
                    }
                }
                printf("Temps de l'athlète :     %02dmin %02dsec %03dms\n", entrainement1.tempsAthlete.minute, entrainement1.tempsAthlete.seconde, entrainement1.tempsAthlete.milliseconde);
                printf("\n");
                entrainementTrouve = 1;
            }
        }

        if (!entrainementTrouve) {
            printf("Aucun entraînement n'a été trouvé pour l'athlète %s à la date %02d/%02d/%04d.\n\n", nomAthlete + 2, date.jour, date.mois, date.annee);
        }

        fclose(file);
    }

    fclose(nomAthletes);
}

void historiqueEntrainement(Entrainement entrainement1, FILE *file) {
    int choix, choixAthlete, choixEpreuve, lignes;

    FILE *nomAthlete = fopen(CHEMIN"/Liste/nomAthletes.txt", "r");
    if(nomAthlete == NULL){
        printf("Impossible d'ouvrir le fichier nomAthlète.\n");
        exit(1);
    }

    FILE *nomEpreuve = fopen(CHEMIN"/Liste/nomEpreuve.txt", "r");
    if(nomEpreuve == NULL){
        printf("Impossible d'ouvrir le fichier nomEpreuve.\n");
        exit(1);
    }

    printf("1. Voir par nom des Athlètes\n");
    printf("2. Voir par type d'épreuve\n");
    printf("3. Voir par date\n");
    couleur("31"); printf("4. Quitter\n"); couleur("0");
    printf("Choix : ");
    scanf("%d", &choix);
    printf("\n");

    switch (choix) {
        case 1:
            afficherListeAthlete(nomAthlete);
            printf("Choix : ");
            scanf("%d", &choixAthlete);
            printf("\n");

            rewind(nomAthlete);
            lignes = compterLignes(nomAthlete);

            while (choixAthlete < 1 || choixAthlete > lignes) {
                printf("Choix invalide. Veuillez choisir un numéro d'athlète entre 1 et %d.\n", lignes);
                printf("Choix : ");
                scanf("%d", &choixAthlete);
                printf("\n");
            }
            afficherEntrainementNom(entrainement1, choixAthlete);
            break;
        case 2:
            afficherListeEpreuve(nomEpreuve);
            printf("Choix : ");
            scanf("%d", &choixEpreuve);
            printf("\n");

            rewind(nomEpreuve);
            lignes = compterLignes(nomEpreuve);

            while (choixEpreuve < 1 || choixEpreuve > lignes) {
                printf("Choix invalide. Veuillez choisir un numéro d'athlète entre 1 et %d.\n", lignes);
                printf("Choix : ");
                scanf("%d", &choixEpreuve);
                printf("\n");
            }

            afficherEntrainementTypeEpreuve(entrainement1, choixEpreuve);
            break;
        case 3:
            afficherEntrainementDate(entrainement1);
            break;
        case 4:
            break;
        default:
            printf("Choix invalide.\n");
            historiqueEntrainement(entrainement1, file);
    }
    
}
