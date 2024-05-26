#include "../headers/statistiques.h"

// Procédure pour afficher la différence de temps entre deux entraînements
void showDiffTime(int *athleteChoice, int *raceChoice, char race[MAX]){
    int count = 0;

    if(raceChoice == 0){
        return;
    }

    // Ouvrir le fichier de l'athlète choisi
    FILE *Athlete = openAthleteFile(*athleteChoice);
    if(Athlete == NULL){
        printf("Impossible d'ouvrir le fichier de l'athlète.\n");
        exit(0);
    }

    printf("Date où il a effectué le %s\n", race + 2);

    int dateCount = 0, dateChoice1, dateChoice2, raceCount = 0;
    Date dates[MAX];

    //si l'épreuve est celle choisie alors afficher l'entrainement
    while (fgetc(Athlete) != '\n');
    while (fscanf(Athlete, "%d %d %d %s %d %d %d %d %d", &training.trainingDate.day, &training.trainingDate.month, &training.trainingDate.year, training.raceType, &training.athleteTime.hour, &training.athleteTime.minute, &training.athleteTime.second, &training.athleteTime.millisecond, &training.position) != EOF) {
        if (strcmp(training.raceType, race + 2) == 0) {
            // Ajouter la date à un tableau
            dates[dateCount++] = training.trainingDate;
            raceCount++;
        }
    }

    // Si aucune date n'a été trouvée
    if(raceCount == 0){
        printf("Aucun entraînement pour cette épreuve n'a été trouvé.\n\n");
        return;
    } 
    // Si une seule date a été trouvée
    else if (raceCount == 1) {
        printf("Il n'y a qu'un seul entraînement pour cette épreuve.\n");
        return;
    }

    // Trier les dates
    qsort(dates, (size_t)dateCount, sizeof(Date), compareDates);

    // Afficher les dates triées
    for (int i = 0; i < dateCount; i++) {
        printf("%d. %02d/%02d/%04d\n", i + 1, dates[i].day, dates[i].month, dates[i].year);
    }
    printf("\n");

    // Demander à l'utilisateur de choisir deux dates
    printf("Choix de la première date (entre 1 et %d) : ", dateCount-1);
    scanf("%d", &dateChoice1);
    while(dateChoice1 < 1 || dateChoice1 > dateCount-1){
        while (getchar() != '\n');
        printf("\nChoix invalide. Veuillez choisir un numéro de date entre 1 et %d.\n", dateCount-1);
        printf("Choix de la première date (entre 1 et %d) : ", dateCount-1);
        scanf("%d", &dateChoice1);
    }

    printf("Choix de la deuxième date (entre %d et %d) : ", dateChoice1+1, dateCount);
    scanf("%d", &dateChoice2);
    while(dateChoice2 < dateChoice1+1 || dateChoice2 > dateCount){
        while (getchar() != '\n');
        printf("\nChoix invalide. Veuillez choisir un numéro de date entre %d et %d.\n", dateChoice1+1, dateCount);
        printf("Choix de la deuxième date (entre %d et %d) : ", dateChoice1+1, dateCount);
        scanf("%d", &dateChoice2);
    }
    printf("\n");

    rewind(Athlete);
    while (fgetc(Athlete) != '\n');

    Training training1, training2;
    // Lire le fichier de l'athlète pour trouver les deux dates
    while (fscanf(Athlete, "%d %d %d %s %d %d %d %d %d", &training.trainingDate.day, &training.trainingDate.month, &training.trainingDate.year, training.raceType, &training.athleteTime.hour, &training.athleteTime.minute, &training.athleteTime.second, &training.athleteTime.millisecond, &training.position) != EOF) {
        if (strcmp(training.raceType, race + 2) == 0) {
            if (training.trainingDate.day == dates[dateChoice1 - 1].day && training.trainingDate.month == dates[dateChoice1 - 1].month && training.trainingDate.year == dates[dateChoice1 - 1].year) {
                training1 = training;
                count++;
            } else if (training.trainingDate.day == dates[dateChoice2 - 1].day && training.trainingDate.month == dates[dateChoice2 - 1].month && training.trainingDate.year == dates[dateChoice2 - 1].year) {
                training2 = training;
                count++;
            }
        }
    }

    // Si les deux dates n'ont pas été trouvées, quitter le programme
    if (count < 2) {
        return;
    }

    // Afficher les deux entraînements
    if(training1.athleteTime.hour != 0) {
        printf("%02d/%02d/%04d | %02dh %02dmin %02dsec %03dms ", training1.trainingDate.day, training1.trainingDate.month, training1.trainingDate.year, training1.athleteTime.hour, training1.athleteTime.minute, training1.athleteTime.second, training1.athleteTime.millisecond);
    } else if(training1.athleteTime.minute != 0) {
        printf("%02d/%02d/%04d | %02dmin %02dsec %03dms ", training1.trainingDate.day, training1.trainingDate.month, training1.trainingDate.year, training1.athleteTime.minute, training1.athleteTime.second, training1.athleteTime.millisecond);
    } else {
        printf("%02d/%02d/%04d | %02dsec %03dms ", training1.trainingDate.day, training1.trainingDate.month, training1.trainingDate.year, training1.athleteTime.second, training1.athleteTime.millisecond);
    }
    if(training1.position != 0){
        if(training1.position == 1){
           printf("| %der coureur\n", training1.position);
        } else {
            printf("| %dème coureur\n", training1.position);
        }
    } else {
        printf("\n");
    }

    if(training2.athleteTime.hour != 0) {
        printf("%02d/%02d/%04d | %02dh %02dmin %02dsec %03dms ", training2.trainingDate.day, training2.trainingDate.month, training2.trainingDate.year, training2.athleteTime.hour, training2.athleteTime.minute, training2.athleteTime.second, training2.athleteTime.millisecond);
    } else if(training2.athleteTime.minute != 0) {
        printf("%02d/%02d/%04d | %02dmin %02dsec %03dms ", training2.trainingDate.day, training2.trainingDate.month, training2.trainingDate.year, training2.athleteTime.minute, training2.athleteTime.second, training2.athleteTime.millisecond);
    } else {
        printf("%02d/%02d/%04d | %02dsec %03dms ", training2.trainingDate.day, training2.trainingDate.month, training2.trainingDate.year, training2.athleteTime.second, training2.athleteTime.millisecond);
    }
    if(training2.position != 0){
        if(training2.position == 1){
            printf("| %der coureur\n", training2.position);
        } else {
            printf("| %dème coureur\n", training2.position);
        }
    } else {
        printf("\n");
    }
    printf("\n");

    // Calculer la différence de temps entre les deux entraînements
    int millisecondsTime1 = training1.athleteTime.hour * 3600000 + training1.athleteTime.minute * 60000 + training1.athleteTime.second * 1000 + training1.athleteTime.millisecond;
    int millisecondsTime2 = training2.athleteTime.hour * 3600000 + training2.athleteTime.minute * 60000 + training2.athleteTime.second * 1000 + training2.athleteTime.millisecond;
    int diffTime = millisecondsTime2 - millisecondsTime1;

    // Mettre la différence de temps en heures, minutes, secondes et millisecondes en valeur absolue
    int hours = abs(diffTime / 3600000);
    int minutes = abs(diffTime / 60000);
    int seconds = abs((diffTime % 60000) / 1000);
    int milliseconds = abs((diffTime % 60000) % 1000);

    // Si la différence de temps est négative, l'athlète a progressé
    if(diffTime < 0){
        if(hours != 0){
            printf("L'athlète a progressé de "); color("1"); printf("%02dh %02dmin %02dsec %03dms ", hours, minutes, seconds, milliseconds); color("0"); printf("entre le %02d/%02d/%04d et le %02d/%02d/%04d\n\n", training1.trainingDate.day, training1.trainingDate.month, training1.trainingDate.year, training2.trainingDate.day, training2.trainingDate.month, training2.trainingDate.year);
            return;
        } else if(minutes != 0){
            printf("L'athlète a progressé de "); color("1"); printf("%02dmin %02dsec %03dms ", minutes, seconds, milliseconds); color("0"); printf("entre le %02d/%02d/%04d et le %02d/%02d/%04d\n\n", training1.trainingDate.day, training1.trainingDate.month, training1.trainingDate.year, training2.trainingDate.day, training2.trainingDate.month, training2.trainingDate.year);
            return;
        } else {
            printf("L'athlète a progressé de "); color("1"); printf("%02dsec %03dms ", seconds, milliseconds); color("0"); printf("entre le %02d/%02d/%04d et le %02d/%02d/%04d\n\n", training1.trainingDate.day, training1.trainingDate.month, training1.trainingDate.year, training2.trainingDate.day, training2.trainingDate.month, training2.trainingDate.year);
            return;
        }
        return;
    } 
    // Si la différence de temps est positive, l'athlète a régressé
    else if(diffTime > 0){
        if(hours != 0){
            printf("L'athlète a regressé de "); color("1"); printf("%02dh %02dmin %02dsec %03dms ", hours, minutes, seconds, milliseconds); color("0"); printf("entre le %02d/%02d/%04d et le %02d/%02d/%04d\n\n", training1.trainingDate.day, training1.trainingDate.month, training1.trainingDate.year, training2.trainingDate.day, training2.trainingDate.month, training2.trainingDate.year);
            return;
        } else if(minutes != 0){
            printf("L'athlète a regressé de "); color("1"); printf("%02dmin %02dsec %03dms ", minutes, seconds, milliseconds); color("0"); printf("entre le %02d/%02d/%04d et le %02d/%02d/%04d\n\n", training1.trainingDate.day, training1.trainingDate.month, training1.trainingDate.year, training2.trainingDate.day, training2.trainingDate.month, training2.trainingDate.year);
            return;
        } else {
            printf("L'athlète a regressé de "); color("1"); printf("%02dsec %03dms ", seconds, milliseconds); color("0"); printf("entre le %02d/%02d/%04d et le %02d/%02d/%04d\n\n", training1.trainingDate.day, training1.trainingDate.month, training1.trainingDate.year, training2.trainingDate.day, training2.trainingDate.month, training2.trainingDate.year);
            return;
        }
        return;
    } 
    // Si la différence de temps est nulle, l'athlète a gardé le même temps
    else {
        printf("L'athlète a gardé le même temps\n\n");
        return;
    }

    fclose(Athlete);
}

// Fonction qui calcule la moyenne des temps de l'athlète pour une épreuve donnée et la retourne
int averageTime(FILE *athlete, char raceType[MAX]){
    int averageTime = 0; 
    int count = 0;

    rewind(athlete);
    while (fgetc(athlete) != '\n');
    // Lire le fichier de l'athlète pour trouver les entraînements de l'épreuve choisie
    while (fscanf(athlete, "%d %d %d %s %d %d %d %d %d", &training.trainingDate.day, &training.trainingDate.month, &training.trainingDate.year, training.raceType, &training.athleteTime.hour, &training.athleteTime.minute, &training.athleteTime.second, &training.athleteTime.millisecond, &training.position) != EOF) {
        if (strcmp(training.raceType, raceType) == 0) {
            int millisecondsTime = training.athleteTime.hour * 3600000 + training.athleteTime.minute * 60000 + training.athleteTime.second * 1000 + training.athleteTime.millisecond;

            averageTime += millisecondsTime;
            count++;
        }
    }
    // Si aucun entraînement n'a été trouvé, retourner 0
    if(count == 0){
        return 0;
    }

    // Calculer la moyenne des temps
    averageTime = averageTime/count;

    return averageTime;
}

// Procédure pour afficher le pire temps de l'athlète pour une épreuve donnée
void worstTime(FILE *athlete, char raceType[MAX]){
    int worstRaceTime = INT_MIN;
    Training worstTraining;

    rewind(athlete);
    while (fgetc(athlete) != '\n');
    // Lire le fichier de l'athlète pour trouver le pire temps de l'épreuve choisie
    while (fscanf(athlete, "%d %d %d %s %d %d %d %d %d", &training.trainingDate.day, &training.trainingDate.month, &training.trainingDate.year, training.raceType, &training.athleteTime.hour, &training.athleteTime.minute, &training.athleteTime.second, &training.athleteTime.millisecond, &training.position) != EOF) {
        if (strcmp(training.raceType, raceType) == 0) {
            int millisecondsTime = training.athleteTime.hour * 3600000 + training.athleteTime.minute * 60000 + training.athleteTime.second * 1000 + training.athleteTime.millisecond;

            // Si le temps est plus grand que le pire temps actuel, le remplacer
            if (millisecondsTime > worstRaceTime) {
                worstRaceTime = millisecondsTime;
                worstTraining = training;
            }
        }
    }

    // Si aucun entraînement n'a été trouvé, quitter le programme
    if (worstRaceTime == INT_MIN) {
        return;

    } 
    // Sinon, afficher le pire temps
    else {
        printf("Pire temps pour %s :\n", raceType);
        printf("Date de l'entraînement : %02d/%02d/%04d\n", worstTraining.trainingDate.day, worstTraining.trainingDate.month, worstTraining.trainingDate.year);
        if(worstTraining.athleteTime.hour != 0){
            printf("Temps de l'athlète :     "); color("1"); printf("%02dh %02dmin %02dsec %03dms\n", worstTraining.athleteTime.hour, worstTraining.athleteTime.minute, worstTraining.athleteTime.second, worstTraining.athleteTime.millisecond); color("0");
        } else if(worstTraining.athleteTime.minute != 0) {
            printf("Temps de l'athlète :     "); color("1"); printf("%02dmin %02dsec %03dms\n", worstTraining.athleteTime.minute, worstTraining.athleteTime.second, worstTraining.athleteTime.millisecond); color("0");
        } else {
            printf("Temps de l'athlète :     "); color("1"); printf("%02dsec %03dms\n", worstTraining.athleteTime.second, worstTraining.athleteTime.millisecond); color("0");
        }
        if(worstTraining.position != 0){
            if(worstTraining.position == 1){
                printf("Position au relais :     %der coureur\n", worstTraining.position);
            } else {
                printf("Position au relais :     %dème coureur\n", worstTraining.position);
            }
        }
        printf("\n");
    }
}

// Procédure pour afficher le meilleur temps de l'athlète pour une épreuve donnée
void bestTime(FILE *athlete, char raceType[MAX]){
    int bestRaceTime = INT_MAX;
    Training bestTraining;

    rewind(athlete);
    while (fgetc(athlete) != '\n');
    // Lire le fichier de l'athlète pour trouver le meilleur temps de l'épreuve choisie
    while (fscanf(athlete, "%d %d %d %s %d %d %d %d %d", &training.trainingDate.day, &training.trainingDate.month, &training.trainingDate.year, training.raceType, &training.athleteTime.hour, &training.athleteTime.minute, &training.athleteTime.second, &training.athleteTime.millisecond, &training.position) != EOF) {
        if (strcmp(training.raceType, raceType) == 0) {
            int millisecondsTime = training.athleteTime.hour * 3600000 + training.athleteTime.minute * 60000 + training.athleteTime.second * 1000 + training.athleteTime.millisecond;

            // Si le temps est plus petit que le meilleur temps actuel, le remplacer
            if (millisecondsTime < bestRaceTime) {
                bestRaceTime = millisecondsTime;
                bestTraining = training;
            }
        }
    }

    // Si aucun entraînement n'a été trouvé, quitter le programme
    if (bestRaceTime == INT_MAX) {
        printf("Aucun entraînement de ce type n'a été trouvé.\n\n");
        return;

    } 
    // Sinon, afficher le meilleur temps
    else {
        printf("Meilleur temps pour %s :\n", raceType);
        printf("Date de l'entraînement : %02d/%02d/%04d\n", bestTraining.trainingDate.day, bestTraining.trainingDate.month, bestTraining.trainingDate.year);
        if(bestTraining.athleteTime.hour != 0){
            printf("Temps de l'athlète :     "); color("1"); printf("%02dh %02dmin %02dsec %03dms\n", bestTraining.athleteTime.hour, bestTraining.athleteTime.minute, bestTraining.athleteTime.second, bestTraining.athleteTime.millisecond); color("0");
        } else if (bestTraining.athleteTime.minute != 0){
            printf("Temps de l'athlète :     "); color("1"); printf("%02dmin %02dsec %03dms\n", bestTraining.athleteTime.minute, bestTraining.athleteTime.second, bestTraining.athleteTime.millisecond); color("0");
        } else {
            printf("Temps de l'athlète :     "); color("1"); printf("%02dsec %03dms\n", bestTraining.athleteTime.second, bestTraining.athleteTime.millisecond); color("0");
        }
        if(bestTraining.position != 0){
            if(bestTraining.position == 1){
                printf("Position au relais :     %der coureur\n", bestTraining.position);
            } else {
                printf("Position au relais :     %dème coureur\n", bestTraining.position);
            }
        }
        printf("\n");
    }
}

// Procédure pour afficher le pire, le meilleur et la moyenne des temps de l'athlète pour une épreuve donnée
void trainingResume(void) {
    int athleteChoice, lines, raceChoice, numRace;
    char race[MAX];

    // Ouvrir le fichier de tous les athlètes
    FILE *athleteName = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if(athleteName == NULL){
        printf("Impossible d'ouvrir le fichier nomAthlètes.\n");
        exit(0);
    }

    // Afficher la liste des athlètes et demander le choix de l'utilisateur
    showAthleteList(athleteName);
    printf("Choix : ");
    scanf("%d", &athleteChoice);
    printf("\n");

    rewind(athleteName);
    lines = countLine(athleteName);

    while (athleteChoice < 1 || athleteChoice > lines) {
        while (getchar() != '\n');
        printf("Choix invalide. Veuillez choisir un numéro d'athlète entre 1 et %d.\n", lines);
        printf("Choix : ");
        scanf("%d", &athleteChoice);
        printf("\n");
    }

    // Ouvrir le fichier de l'athlète choisi
    FILE *Athlete = openAthleteFile(athleteChoice);
    if(Athlete == NULL){
        printf("Impossible d'ouvrir le fichier de l'athlète.\n");
        exit(0);
    }

    // Ouvrir le fichier de toutes les épreuves
    FILE *raceName = fopen(PATH"/Liste/nomEpreuve.txt", "r");
    if(raceName == NULL){
        printf("Impossible d'ouvrir le fichier nomEpreuve.\n");
        exit(0);
    }

    // Afficher la liste des épreuves et demander le choix de l'utilisateur
    showRaceList(raceName);
    printf("Choix : ");
    scanf("%d", &raceChoice);
    printf("\n");

    rewind(raceName);
    lines = countLine(raceName);

    while (raceChoice < 1 || raceChoice > lines) {
        while (getchar() != '\n');
        printf("Choix invalide. Veuillez choisir un numéro d'épreuve entre 1 et %d.\n", lines);
        printf("Choix : ");
        scanf("%d", &raceChoice);
        printf("\n");
    }

    // Si l'épreuve est celle choisie alors sortir de la boucle
    rewind(raceName);
    while (fgets(race, sizeof(race), raceName)) {
        sscanf(race, "%d", &numRace);
        race[strcspn(race, "\n")] = 0;

        if(numRace == raceChoice) {
            break;
        }
    }

    // Afficher le pire, le meilleur et la moyenne des temps de l'athlète pour l'épreuve choisie
    bestTime(Athlete, race + 2);
    worstTime(Athlete, race + 2);
    int average = averageTime(Athlete, race + 2);
    if (average == 0) {
        return;
    } else {
        printf("Moyenne temps pour %s :\n", race + 2);
        if(average/3600000 != 0){
            printf("Moyenne de l'athlète :   "); color("1"); printf("%02dh %02dmin %02dsec %03dms\n", average/3600000, (average % 3600000)/60000, (average % 60000)/1000, (average % 1000)); color("0");
        } else if(average/60000 != 0){ 
            printf("Moyenne de l'athlète :   "); color("1"); printf("%02dmin %02dsec %03dms\n", average/60000, (average % 60000)/1000, (average % 1000)); color("0");
        } else {
            printf("Moyenne de l'athlète :   "); color("1"); printf("%02dsec %03dms\n", average/1000, (average % 1000)); color("0");
        }
        printf("\n");
    }

    fclose(athleteName);
    fclose(raceName);
}

// Procédure pour afficher les 3 meilleurs moyennes de temps pour une épreuve donnée
void whoInOG(void){
    int lines, raceChoice;

    // Ouvrir le fichier de toutes les épreuves
    FILE *raceName = fopen(PATH"/Liste/nomEpreuve.txt", "r");
    if(raceName == NULL){
        printf("Impossible d'ouvrir le fichier nomEpreuve.txt.\n");
        exit(0);
    }

    // Afficher la liste des épreuves et demander le choix de l'utilisateur
    showRaceList(raceName);
    printf("Choix : ");
    scanf("%d", &raceChoice);
    printf("\n");

    rewind(raceName);
    lines = countLine(raceName);

    while (raceChoice < 1 || raceChoice > lines) {
        while (getchar() != '\n');
        printf("Choix invalide. Veuillez choisir un numéro d'épreuve entre 1 et %d.\n", lines);
        printf("Choix : ");
        scanf("%d", &raceChoice);
        printf("\n");
    }

    // Si l'épreuve est celle choisie alors sortir de la boucle
    rewind(raceName);
    char race[MAX];
    while (fgets(race, sizeof(race), raceName)) {
        int numRace;
        sscanf(race, "%d", &numRace);
        race[strcspn(race, "\n")] = 0;

        if(numRace == raceChoice) {
            break;
        }
    }

    // Ouvrir le fichier de tous les athlètes
    FILE *athleteName = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if(athleteName == NULL){
        printf("Impossible d'ouvrir le fichier nomAthlètes.\n");
        exit(0);
    }
    lines = countLine(athleteName);

    rewind(athleteName);
    // Mettre le nom des athlètes dans un tableau
    char athletes[MAX][MAX]; int athleteNumber;
    for(int i = 0; i < lines; i++){
        fscanf(athleteName, "%d", &athleteNumber); // Lecture du numéro de l'athlète
        fseek(athleteName, 1, SEEK_CUR); // Sauter le numéro de l'athlète

        fgets(athletes[i], sizeof(athletes[i]), athleteName);
        athletes[i][strcspn(athletes[i], "\n")] = 0;
    }
    
    // Mettre la moyenne de chaque athlète dans un tableau de l'épreuve choisie
    int averages[MAX];
    for(int i = 0; i < lines; i++){
        FILE *Athlete = openAthleteFile(i+1); // Ouvrir le fichier de l'athlète
        averages[i] = averageTime(Athlete, race + 2); // Calculer la moyenne de l'athlète
        fclose(Athlete);
    }

    // Créer un tableau de structures pour pouvoir trier les moyennes
    AverageIndex averageIndex[lines];
    for(int i = 0; i < lines; i++){
        averageIndex[i].average = averages[i];
        averageIndex[i].index = i;
    }

    // Trier les moyennes avec le tableau de structures
    qsort(averageIndex, (size_t)lines, sizeof(AverageIndex), compareAverage);

    // Si l'epreuve est Marathon, afficher les 3 meilleurs moyennes 
    if(averages[averageIndex[2].index]/3600000 != 0){
        printf("\nLes 3 meilleurs moyenne pour le %s sont :\n", race + 2);
        color("1"); printf("%s %s ", "🥇", athletes[averageIndex[0].index]); color("0"); printf("avec une moyenne de %02dh %02dmin %02dsec %03dms\n", averages[averageIndex[0].index]/3600000, (averages[averageIndex[0].index] % 3600000)/60000, (averages[averageIndex[0].index] % 60000)/1000, (averages[averageIndex[0].index] % 1000));
        color("1"); printf("%s %s ", "🥈", athletes[averageIndex[1].index]); color("0"); printf("avec une moyenne de %02dh %02dmin %02dsec %03dms\n", averages[averageIndex[1].index]/3600000, (averages[averageIndex[1].index] % 3600000)/60000, (averages[averageIndex[1].index] % 60000)/1000, (averages[averageIndex[1].index] % 1000));
        color("1"); printf("%s %s ", "🥉", athletes[averageIndex[2].index]); color("0"); printf("avec une moyenne de %02dh %02dmin %02dsec %03dms\n", averages[averageIndex[2].index]/3600000, (averages[averageIndex[2].index] % 3600000)/60000, (averages[averageIndex[2].index] % 60000)/1000, (averages[averageIndex[2].index] % 1000));
        printf("\n");
    }
    // Si l'épreuve est 5000m, afficher les 3 meilleurs moyennes sans les heures
    else if (averages[averageIndex[2].index]/60000 != 0) {
        printf("\nLes 3 meilleurs moyenne pour le %s sont :\n", race + 2);
        color("1"); printf("%s %s ", "🥇", athletes[averageIndex[0].index]); color("0"); printf("avec une moyenne de %02dmin %02dsec %03dms\n", averages[averageIndex[0].index]/60000, (averages[averageIndex[0].index] % 60000)/1000, (averages[averageIndex[0].index] % 1000));
        color("1"); printf("%s %s ", "🥈", athletes[averageIndex[1].index]); color("0"); printf("avec une moyenne de %02dmin %02dsec %03dms\n", averages[averageIndex[1].index]/60000, (averages[averageIndex[1].index] % 60000)/1000, (averages[averageIndex[1].index] % 1000));
        color("1"); printf("%s %s ", "🥉", athletes[averageIndex[2].index]); color("0"); printf("avec une moyenne de %02dmin %02dsec %03dms\n", averages[averageIndex[2].index]/60000, (averages[averageIndex[2].index] % 60000)/1000, (averages[averageIndex[2].index] % 1000));
        printf("\n");
    } 
    // Si l'épreuve est autre que Marathon ou 5000m, afficher les 3 meilleurs moyennes sans les heures et les minutes
    else {
        printf("\nLes 3 meilleurs moyenne pour le %s sont : \n", race + 2);
        color("1"); printf("%s %s ", "🥇", athletes[averageIndex[0].index]); color("0"); printf("avec une moyenne de %02dsec %03dms\n", averages[averageIndex[0].index]/1000, (averages[averageIndex[0].index] % 1000));
        color("1"); printf("%s %s ", "🥈", athletes[averageIndex[1].index]); color("0"); printf("avec une moyenne de %02dsec %03dms\n", averages[averageIndex[1].index]/1000, (averages[averageIndex[1].index] % 1000));
        color("1"); printf("%s %s ", "🥉", athletes[averageIndex[2].index]); color("0"); printf("avec une moyenne de %02dsec %03dms\n", averages[averageIndex[2].index]/1000, (averages[averageIndex[2].index] % 1000));
        printf("\n");
    }

    fclose(raceName);
    fclose(athleteName);

}

// Procédure principale pour consulter des statistiques de performances de chaque athlète
void athleteStatistic(void) {
    int choice = 0, athleteChoice, raceChoice;
    char race[MAX];

    printf("1. Consulter un résumer des statistiques de performances d'un athlète\n");
    printf("2. Qui envoyer aux Jeux Olympiques\n");
    printf("3. Progression de l'athlète\n");
    color("31"); printf("4. Quitter\n"); color("0");
    printf("Choix : ");
    scanf("%d", &choice);
    printf("\n");

    while(choice < 1 || choice > 4){
        while (getchar() != '\n');
        printf("Choix invalide. Veuillez saisir un chiffre entre 1 et 4 : ");
        scanf("%d", &choice);
        printf("\n");
    }

    if(choice == 4){
        return;
    }

    else if(choice == 1){
        trainingResume();
    }

    else if(choice == 2){
        whoInOG();
    }

    else if(choice == 3){
        chooseAthlete(&athleteChoice);
        chooseRace(&raceChoice, race);
        showDiffTime(&athleteChoice, &raceChoice, race);
    }

}
