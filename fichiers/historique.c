#include "../headers/historique.h"

// Procédure qui permet d'afficher les entraînements d'un athlète
void showTrainingName(Training training1, int athleteChoice) {
    int position, trainingFound = 0;

    // Ouvrir le fichier de l'athlète
    FILE *file = openAthleteFile(athleteChoice);
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier athleteChoice\n");
        return;
    }

    // Sauter une ligne
    while (fgetc(file) != '\n');
    // Lire chaque ligne du fichier
    while (fscanf(file, "%d %d %d %s %d %d %d %d %d", &training1.trainingDate.day, &training1.trainingDate.month, &training1.trainingDate.year, training1.raceType, &training1.athleteTime.hour, &training1.athleteTime.minute, &training1.athleteTime.second, &training1.athleteTime.millisecond, &position) != EOF) {
        // Affichage des valeurs
        printf("\n");
        printf("  Date de l'entraînement : %02d/%02d/%04d\n", training1.trainingDate.day, training1.trainingDate.month, training1.trainingDate.year);
        printf("  Type d'épreuve :         %s\n", training1.raceType);
        if(strcmp(training1.raceType, "Relais") == 0){
            if(position == 0){
                continue;
            } else {
                if(position == 1) {
                    printf("  Position au relais :     %der coureur\n", position);
                } else if(position > 1) {
                    printf("  Position au relais :     %dème coureur\n", position);
                }
            }
        }
        // Si le type d'épreuve est un marathon, afficher les heures
        if(strcmp(training1.raceType, "Marathon") == 0){
            printf("  Temps de l'athlète :     %02dh %02dmin %02dsec %03dms\n", training1.athleteTime.hour, training1.athleteTime.minute, training1.athleteTime.second, training1.athleteTime.millisecond);
            printf("\n");
            color("2"); printf("   ————————————————————————————————————————    \n"); color("0");
        } 
        // Si le type d'épreuve est un 5000m, afficher les minutes
        else if(strcmp(training1.raceType, "5000m") == 0) {
            printf("  Temps de l'athlète :     %02dmin %02dsec %03dms\n", training1.athleteTime.minute, training1.athleteTime.second, training1.athleteTime.millisecond);
            printf("\n");
            color("2"); printf("   ————————————————————————————————————————    \n"); color("0");
        } 
        
        else {
            printf("  Temps de l'athlète :     %02dsec %03dms\n", training1.athleteTime.second, training1.athleteTime.millisecond);
            print_padded_line(" ", " "); printf("   \n");
            color("2"); printf("   ————————————————————————————————————————    \n"); color("0");
        }
        trainingFound = 1;
    }

    // Si aucun entraînement de ce type n'a été trouvé pour l'athlète
    if (!trainingFound) {
        printf("Aucun entraînement de ce type n'a été trouvé pour l'athlète.\n\n");
        return;
    }

    // Fermeture du fichier
    fclose(file);
}

// Procédure qui permet d'afficher les entraînements d'un type d'épreuve
void showTrainingRace(Training training1, int raceChoice) {
    char race[MAX];
    int numRace, position;

    // Ouvrir le fichier de toutes les épreuves
    FILE *raceName = fopen(PATH"/Liste/nomEpreuve.txt", "r");
    if(raceName == NULL){
        printf("Impossible d'ouvrir le fichier nomEpreuve.\n");
        exit(0);
    }

    // Lire le fichier epreuves jusqu'à trouver l'épreuve choisie (raceChoice)
    while (fgets(race, sizeof(race), raceName)) {
        sscanf(race, "%d", &numRace); // Récupérer le numéro de l'épreuve
        race[strcspn(race, "\n")] = 0; // Supprimer le retour à la ligne

        // Si l'épreuve choisie est trouvée, afficher le type d'épreuve et sortir de la boucle
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
        exit(0);
    }

    char athlete[MAX] = {0};
    int lines = countLine(athleteName);
    rewind(athleteName);

    // Lire chaque ligne du fichier nomAthlètes
    for(int i = 0; i < lines; i++) {
        int trainingFound = 0;
        
        fgets(athlete, sizeof(athlete), athleteName); // Lecture du nom de l'athlète
        athlete[strcspn(athlete, "\n")] = 0; // Supprimer le retour à la ligne

        // Ouvrir le fichier de l'athlète
        char fileName[MAX] = {0};
        sprintf(fileName, PATH"/Athletes/%s.txt", athlete + 3);
        FILE *file = fopen(fileName, "r");
        if (file == NULL) {
            printf("Impossible d'ouvrir le fichier de l'athlète.\n");
            exit(0);
        }

        printf("+—————————————————————————————————————————————————+\n");
        printf("|"); color("1"); color("36");  print_padded_line(" Athlète : ", athlete + 3); color("0"); printf("  |\n");

        while (fgetc(file) != '\n'); // Sauter une ligne
        // Lire chaque ligne du fichier de l'athlète et afficher les entraînements de l'épreuve choisie
        while (fscanf(file, "%d %d %d %s %d %d %d %d %d", &training1.trainingDate.day, &training1.trainingDate.month, &training1.trainingDate.year, training1.raceType, &training1.athleteTime.hour, &training1.athleteTime.minute, &training1.athleteTime.second, &training1.athleteTime.millisecond, &position) != EOF) {
            if (strcmp(training1.raceType, race + 2) == 0) {
                // Affichage des valeurs
                if(strcmp(training1.raceType, "Relais") == 0){
                    if(position == 0){
                        continue;
                    } else {
                        if(position == 1) {
                            printf("| Position au relais :     %der coureur            |\n", position);
                        } else if(position > 1) {
                            printf("| Position au relais :     %dème coureur           |\n", position);
                        }
                    }
                }

                if(strcmp(training1.raceType, "Marathon") == 0){
                    print_padded_line("|", " "); printf("  |\n");
                    printf("| Date de l'entraînement : %02d/%02d/%04d             |\n", training1.trainingDate.day, training1.trainingDate.month, training1.trainingDate.year);
                    printf("| Temps de l'athlète :     %02dh %02dmin %02dsec %03dms  |\n", training1.athleteTime.hour, training1.athleteTime.minute, training1.athleteTime.second, training1.athleteTime.millisecond);
                    print_padded_line("|", " "); printf("  |\n");
                    printf("|"); color("2"); printf("    —————————————————————————————————————————    "); color("0"); printf("|\n");
                } 
                else if(strcmp(training1.raceType, "5000m") == 0) {
                    print_padded_line("|", " "); printf("  |\n");
                    printf("| Date de l'entraînement : %02d/%02d/%04d             |\n", training1.trainingDate.day, training1.trainingDate.month, training1.trainingDate.year);                    
                    printf("| Temps de l'athlète :     %02dmin %02dsec %03dms      |\n", training1.athleteTime.minute, training1.athleteTime.second, training1.athleteTime.millisecond);
                    print_padded_line("|", " "); printf("  |\n");
                    printf("|"); color("2"); printf("    —————————————————————————————————————————    "); color("0"); printf("|\n");
                } else {
                    printf("|"); color("2"); printf("    —————————————————————————————————————————    "); color("0"); printf("|\n");
                    print_padded_line("|", " "); printf("  |\n");
                    printf("| Date de l'entraînement : %02d/%02d/%04d             |\n", training1.trainingDate.day, training1.trainingDate.month, training1.trainingDate.year);
                    printf("| Temps de l'athlète :     %02dsec %03dms            |\n", training1.athleteTime.second, training1.athleteTime.millisecond);
                    print_padded_line("|", " "); printf("  |\n");
                }
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

// Procédure qui permet d'afficher les entraînements d'une date
void showTrainingDate(Training training1) {
    int position;
    Date date;

    // Demander la date de l'entraînement
    printf("Entrez la date de l'entrainement (JJ MM AAAA) : ");
    scanf("%d %d %d", &date.day, &date.month, &date.year);
    printf("\n");
    while(!validDate(date)){
        while (getchar() != '\n');
        printf("Date invalide. Veuillez entrer une date valide.\n");
        printf("Entrez la date de l'entrainement (JJ MM AAAA) : ");
        scanf("%d %d %d", &date.day, &date.month, &date.year);
        printf("\n");
    }

    // Ouvrir le fichier nomAthlètes
    FILE *athleteName = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if(athleteName == NULL){
        printf("Impossible d'ouvrir le fichier nomAthlètes 1.\n");
        exit(0);
    }

    char athlete[MAX] = {0};
    int lines = countLine(athleteName);
    rewind(athleteName);
    for(int i = 0; i < lines; i++) {
        int trainingFound = 0;
        fgets(athlete, sizeof(athlete), athleteName);
        athlete[strcspn(athlete, "\n")] = 0;

        char fileName[MAX] = {0};
        sprintf(fileName, PATH"/Athletes/%s.txt", athlete + 3); // Créer le chemin du fichier de l'athlète
        FILE *file = fopen(fileName, "r"); // Ouvrir le fichier de l'athlète en mode lecture
        if (file == NULL) {
            printf("Impossible d'ouvrir le fichier de l'athlète.\n");
            exit(0);
        }

        printf("+—————————————————————————————————————————————————+\n");
        printf("|"); color("1"); color("36");  print_padded_line(" Athlète : ", athlete + 3); color("0"); printf("  |");
        printf("\n|                                                 |\n");

        while (fgetc(file) != '\n'); // Sauter une ligne
        // Lire chaque ligne du fichier de l'athlète et afficher les entraînements à la date choisie
        while (fscanf(file, "%d %d %d %s %d %d %d %d %d", &training1.trainingDate.day, &training1.trainingDate.month, &training1.trainingDate.year, training1.raceType, &training1.athleteTime.hour, &training1.athleteTime.minute, &training1.athleteTime.second, &training1.athleteTime.millisecond, &position) != EOF) {
            if (training1.trainingDate.day == date.day && training1.trainingDate.month == date.month && training1.trainingDate.year == date.year) {
                
                print_padded_line("| Type d'épreuve :         ", training1.raceType); printf("   |\n");
                if(strcmp(training1.raceType, "Relais") == 0){
                    if(position == 0){
                        continue;
                    } else {
                        if(position == 1) {
                            printf("| Position au relais :     %der coureur            |\n", position);
                        } else if(position > 1) {
                            printf("| Position au relais :     %dème coureur           |\n", position);
                        }
                    }
                }
                // Si le type d'épreuve est un marathon, afficher les heures
                if(strcmp(training1.raceType, "Marathon") == 0){
                    printf("| Temps de l'athlète :     %02dh %02dmin %02dsec %03dms  |\n", training1.athleteTime.hour, training1.athleteTime.minute, training1.athleteTime.second, training1.athleteTime.millisecond);
                
                } 
                // Si le type d'épreuve est un 5000m, afficher les minutes
                else if(strcmp(training1.raceType, "5000m") == 0) {
                    printf("| Temps de l'athlète :     %02dmin %02dsec %03dms      |\n", training1.athleteTime.minute, training1.athleteTime.second, training1.athleteTime.millisecond);
                } 
                
                else {
                    printf("| Temps de l'athlète :     %02dsec %03dms            |\n", training1.athleteTime.second, training1.athleteTime.millisecond);
                }
                printf("|                                                 |\n");
                trainingFound = 1;
            }
        }

        // Si aucun entraînement n'a été trouvé pour l'athlète
        if (!trainingFound) {
            printf("|"); color("31"); printf(" Aucun entraînement trouvé pour l'athlète        "); color("0"); printf("|\n|");
            color("31"); print_padded_line(athlete + 2, " à la date choisie"); color("0");printf("  |\n|");
            print_padded_line("", " "); printf(" |\n");
        }

        fclose(file);
    }

    fclose(athleteName);
}

// Procédure principale qui permet de choisir comment afficher les entraînements
void trainingHistory(Training training1) {
    int choice = 0, athleteChoice, raceChoice, lines;

    // Ouvrir le fichier nomAthlètes
    FILE *athleteName = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if(athleteName == NULL){
        printf("Impossible d'ouvrir le fichier nomAthlète.\n");
        exit(0);
    }

    // Ouvrir le fichier nomEpreuve
    FILE *raceName = fopen(PATH"/Liste/nomEpreuve.txt", "r");
    if(raceName == NULL){
        printf("Impossible d'ouvrir le fichier nomEpreuve.\n");
        exit(0);
    }

    printf("1. Voir par nom des Athlètes\n");
    printf("2. Voir par type d'épreuve\n");
    printf("3. Voir par date\n");
    color("31"); printf("4. Quitter\n"); color("0");
    printf("Choix : ");
    scanf("%d", &choice);
    printf("\n");

    while(choice < 1 || choice > 4){
        while (getchar() != '\n');
        printf("Choix invalide. Veuillez choisir un numéro entre 1 et 4 : ");
        scanf("%d", &choice);
        printf("\n");
    }

    if(choice == 4){
        return;
    }

    else if(choice == 1){
        // Code pour afficher les entraînements par nom d'athlète
        showAthleteList(athleteName);
        printf("Choix : ");
        scanf("%d", &athleteChoice);
        printf("\n");

        rewind(athleteName);
        lines = countLine(athleteName);

        while (athleteChoice < 1 || athleteChoice > lines) {
            while (getchar() != '\n');
            printf("Choix invalide. Veuillez choisir un numéro d'athlète entre 1 et %d : ", lines);
            scanf("%d", &athleteChoice);
            printf("\n");
        }
        showTrainingName(training1, athleteChoice);
        printf("\n");
    }
    else if(choice == 2){
        // Code pour afficher les entraînements par type d'épreuve
        showRaceList(raceName);
        printf("Choix : ");
        scanf("%d", &raceChoice);
        printf("\n\n");

        rewind(raceName);
        lines = countLine(raceName);

        while (raceChoice < 1 || raceChoice > lines) {
            while (getchar() != '\n');
            printf("Choix invalide. Veuillez choisir un numéro d'athlète entre 1 et %d : ", lines);
            scanf("%d", &raceChoice);
            printf("\n\n");
        }

        showTrainingRace(training1, raceChoice);
        printf("+—————————————————————————————————————————————————+\n\n");
    }

    else if(choice == 3){
        // Code pour afficher les entraînements par date
        showTrainingDate(training1);
        printf("+—————————————————————————————————————————————————+\n\n");
    }
    
}
