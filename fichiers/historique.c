#include "../headers/historique.h"

void showTrainingName(Training training1, int athleteChoice) {
    int position;

    FILE *file = openAthleteFile(athleteChoice);
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier athleteChoice\n");
        return;
    }

    // Sauter une ligne
    while (fgetc(file) != '\n');

    // Lire chaque ligne du fichier
    while (fscanf(file, "%d %d %d %s %d %d %d %d", &training1.trainingDate.day, &training1.trainingDate.month, &training1.trainingDate.year, training1.raceType, &training1.athleteTime.minute, &training1.athleteTime.second, &training1.athleteTime.millisecond, &position) != EOF) {
        // Affichage des valeurs
        printf("Date de l'entraînement : %02d/%02d/%04d\n", training1.trainingDate.day, training1.trainingDate.month, training1.trainingDate.year);
        printf("Type d'épreuve :         %s\n", training1.raceType);
        if(strcmp(training1.raceType, "Relais") == 0){
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
        printf("Temps de l'athlète :     %02dmin %02dsec %03dms\n", training1.athleteTime.minute, training1.athleteTime.second, training1.athleteTime.millisecond);
        printf("\n");
    }

    // Fermeture du fichier
    fclose(file);
}

void showTrainingRace(Training training1, int raceChoice) {
    char race[MAX];
    int numRace, position;

    FILE *raceName = fopen(PATH"/Liste/nomEpreuve.txt", "r");
    if(raceName == NULL){
        printf("Impossible d'ouvrir le fichier nomEpreuve.\n");
        exit(1);
    }

    while (fgets(race, sizeof(race), raceName)) {
        sscanf(race, "%d", &numRace);
        race[strcspn(race, "\n")] = 0;

        if(numRace == raceChoice) {
            printf("%s :\n", race + 2);
            break;
        }
    }

    // Fermeture du fichier raceName
    fclose(raceName);

    // Ouvrir le fichier de tous les athlètes
    FILE *athleteName = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if(athleteName == NULL){
        printf("Impossible d'ouvrir le fichier nomAthlètes 2.\n");
        exit(1);
    }

    char athlete[MAX] = {0};
    int lines = countLine(athleteName);
    rewind(athleteName);

    for(int i = 0; i < lines; i++) {
        int trainingFound = 0;

        // Lecture du nom de l'athlète
        fgets(athlete, sizeof(athlete), athleteName);
        athlete[strcspn(athlete, "\n")] = 0;

        // Ouvrir le fichier de l'athlète
        char fileName[MAX] = {0};
        sprintf(fileName, PATH"/Athletes/%s.txt", athlete + 2);
        FILE *file = fopen(fileName, "r");
        if (file == NULL) {
            printf("Impossible d'ouvrir le fichier de l'athlète.\n");
            exit(1);
        }

        // Sauter une ligne
        while (fgetc(file) != '\n');

        while (fscanf(file, "%d %d %d %s %d %d %d %d", &training1.trainingDate.day, &training1.trainingDate.month, &training1.trainingDate.year, training1.raceType, &training1.athleteTime.minute, &training1.athleteTime.second, &training1.athleteTime.millisecond, &position) != EOF) {
            if (strcmp(training1.raceType, race + 2) == 0) {
                // Affichage des valeurs
                printf("Athlète :                %s\n", athlete + 2);
                if(strcmp(training1.raceType, "Relais") == 0){
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
                printf("Date de l'entraînement : %02d/%02d/%04d\n", training1.trainingDate.day, training1.trainingDate.month, training1.trainingDate.year);
                printf("Temps de l'athlète :     %02dmin %02dsec %03dms\n", training1.athleteTime.minute, training1.athleteTime.second, training1.athleteTime.millisecond);
                printf("\n");
                trainingFound = 1;
            }
        }

        // Si aucun entraînement de ce type n'a été trouvé pour l'athlète
        if (!trainingFound) {
            printf("Aucun entraînement de ce type n'a été trouvé pour l'athlète %s.\n\n", athlete + 2);
        }

        // Fermeture du fichier de l'athlète
        fclose(file);
    }

    // Fermeture du fichier nomAthlètes
    fclose(athleteName);
}

void showTrainingDate(Training training1) {
    int position;
    Date date;

    printf("Entrez la date de l'entrainement (JJ MM AAAA) : ");
    scanf("%d %d %d", &date.day, &date.month, &date.year);
    printf("\n");
    while(!validDate(date)){
        printf("Date invalide. Veuillez entrer une date valide.\n");
        printf("Entrez la date de l'entrainement (JJ MM AAAA) : ");
        scanf("%d %d %d", &date.day, &date.month, &date.year);
        printf("\n");
    }

    FILE *athleteName = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if(athleteName == NULL){
        printf("Impossible d'ouvrir le fichier nomAthlètes 1.\n");
        exit(1);
    }

    char athlete[MAX] = {0};
    int lines = countLine(athleteName);
    rewind(athleteName);
    for(int i = 0; i < lines; i++) {
        int trainingFound = 0;
        fgets(athlete, sizeof(athlete), athleteName);
        athlete[strcspn(athlete, "\n")] = 0;

        char fileName[MAX] = {0};
        sprintf(fileName, PATH"/Athletes/%s.txt", athlete + 2);
        FILE *file = fopen(fileName, "r");
        if (file == NULL) {
            printf("Impossible d'ouvrir le fichier de l'athlète.\n");
            exit(1);
        }

        while (fgetc(file) != '\n');
        while (fscanf(file, "%d %d %d %s %d %d %d %d", &training1.trainingDate.day, &training1.trainingDate.month, &training1.trainingDate.year, training1.raceType, &training1.athleteTime.minute, &training1.athleteTime.second, &training1.athleteTime.millisecond, &position) != EOF) {
            if (training1.trainingDate.day == date.day && training1.trainingDate.month == date.month && training1.trainingDate.year == date.year) {
                printf("Athlète :                %s\n", athlete + 2);
                printf("Type d'épreuve :         %s\n", training1.raceType);
                if(strcmp(training1.raceType, "Relais") == 0){
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
                printf("Temps de l'athlète :     %02dmin %02dsec %03dms\n", training1.athleteTime.minute, training1.athleteTime.second, training1.athleteTime.millisecond);
                printf("\n");
                trainingFound = 1;
            }
        }

        // Si aucun entraînement n'a été trouvé pour l'athlète
        if (!trainingFound) {
            printf("Aucun entraînement n'a été trouvé pour l'athlète %s à la date %02d/%02d/%04d.\n\n", athlete + 2, date.day, date.month, date.year);
        }

        fclose(file);
    }

    fclose(athleteName);
}

void trainingHistory(Training training1, FILE *file) {
    int choice, athleteChoice, raceChoice, lines;

    FILE *athleteName = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if(athleteName == NULL){
        printf("Impossible d'ouvrir le fichier nomAthlète.\n");
        exit(1);
    }

    FILE *raceName = fopen(PATH"/Liste/nomEpreuve.txt", "r");
    if(raceName == NULL){
        printf("Impossible d'ouvrir le fichier nomEpreuve.\n");
        exit(1);
    }

    printf("1. Voir par nom des Athlètes\n");
    printf("2. Voir par type d'épreuve\n");
    printf("3. Voir par date\n");
    color("31"); printf("4. Quitter\n"); color("0");
    printf("Choix : ");
    scanf("%d", &choice);
    printf("\n");

    switch (choice) {
        case 1:
            showAthleteList(athleteName);
            printf("Choix : ");
            scanf("%d", &athleteChoice);
            printf("\n");

            rewind(athleteName);
            lines = countLine(athleteName);

            while (athleteChoice < 1 || athleteChoice > lines) {
                printf("Choix invalide. Veuillez choisir un numéro d'athlète entre 1 et %d.\n", lines);
                printf("Choix : ");
                scanf("%d", &athleteChoice);
                printf("\n");
            }
            showTrainingName(training1, athleteChoice);
            break;
        case 2:
            showRaceList(raceName);
            printf("Choix : ");
            scanf("%d", &raceChoice);
            printf("\n");

            rewind(raceName);
            lines = countLine(raceName);

            while (raceChoice < 1 || raceChoice > lines) {
                printf("Choix invalide. Veuillez choisir un numéro d'athlète entre 1 et %d.\n", lines);
                printf("Choix : ");
                scanf("%d", &raceChoice);
                printf("\n");
            }

            showTrainingRace(training1, raceChoice);
            break;
        case 3:
            showTrainingDate(training1);
            break;
        case 4:
            break;
        default:
            printf("Choix invalide.\n\n");
            trainingHistory(training1, file);
    }
    
}
