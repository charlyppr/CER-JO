#include "../headers/statistiques.h"

void showDiffTime(int *athleteChoice, int *raceChoice, char race[MAX]){
    int count = 0;

    // Ouvrir le fichier de l'athlète choisi
    FILE *Athlete = openAthleteFile(*athleteChoice);
    if(Athlete == NULL){
        printf("Impossible d'ouvrir le fichier de l'athlète.\n");
        exit(1);
    }

    printf("Date où il a effectué le %s\n", race + 2);

    int dateCount = 0, dateChoice1, dateChoice2, raceCount = 0;
    Date dates[MAX];

    //si l'épreuve est celle choisie alors afficher l'training
    while (fgetc(Athlete) != '\n');
    while (fscanf(Athlete, "%d %d %d %s %d %d %d %d %d", &training.trainingDate.day, &training.trainingDate.month, &training.trainingDate.year, training.raceType, &training.athleteTime.hour, &training.athleteTime.minute, &training.athleteTime.second, &training.athleteTime.millisecond, &training.position) != EOF) {
        if (strcmp(training.raceType, race + 2) == 0) {
            //afficher les dates des entraînements disponibles pour l'épreuve choisie
            dates[dateCount++] = training.trainingDate;
            raceCount++;
        }
    }

    if(raceCount == 0){
        printf("Aucun entraînement pour cette épreuve n'a été trouvé.\n");
        printf("Veuillez choisir une autre épreuve.\n\n");

        chooseRace(raceChoice, race);
        showDiffTime(athleteChoice, raceChoice, race);
    } else if (raceCount == 1) {
        printf("Il n'y a qu'un seul entraînement pour cette épreuve.\n");
        printf("Veuillez choisir une autre épreuve.\n\n");

        chooseRace(raceChoice, race);
        showDiffTime(athleteChoice, raceChoice, race);
    }

    // Trier les dates
    qsort(dates, (size_t)dateCount, sizeof(Date), compareDates);

    // Afficher les dates triées
    for (int i = 0; i < dateCount; i++) {
        printf("%d. %02d/%02d/%04d\n", i + 1, dates[i].day, dates[i].month, dates[i].year);
    }
    printf("\n");

    printf("Choix de la première date (entre 1 et %d) : ", dateCount-1);
    scanf("%d", &dateChoice1);
    while(dateChoice1 < 1 || dateChoice1 > dateCount-1){
        printf("\nChoix invalide. Veuillez choisir un numéro de date entre 1 et %d.\n", dateCount-1);
        printf("Choix de la première date (entre 1 et %d) : ", dateCount-1);
        scanf("%d", &dateChoice1);
    }

    printf("Choix de la deuxième date (entre %d et %d) : ", dateChoice1+1, dateCount);
    scanf("%d", &dateChoice2);
    while(dateChoice2 < dateChoice1+1 || dateChoice2 > dateCount){
        printf("\nChoix invalide. Veuillez choisir un numéro de date entre %d et %d.\n", dateChoice1+1, dateCount);
        printf("Choix de la deuxième date (entre %d et %d) : ", dateChoice1+1, dateCount);
        scanf("%d", &dateChoice2);
    }
    printf("\n");

    //appliquer training1 avec dateChoice1 et training2 avec dateChoice2
    rewind(Athlete);
    while (fgetc(Athlete) != '\n');

    Training training1, training2;

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

    if (count < 2) {
        exit(1);
    }

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

    int millisecondsTime1 = training1.athleteTime.hour * 3600000 + training1.athleteTime.minute * 60000 + training1.athleteTime.second * 1000 + training1.athleteTime.millisecond;
    int millisecondsTime2 = training2.athleteTime.hour * 3600000 + training2.athleteTime.minute * 60000 + training2.athleteTime.second * 1000 + training2.athleteTime.millisecond;
    int diffTime = millisecondsTime2 - millisecondsTime1;

    int hours = abs(diffTime / 3600000);
    int minutes = abs(diffTime / 60000);
    int seconds = abs((diffTime % 60000) / 1000);
    int milliseconds = abs((diffTime % 60000) % 1000);

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
    } else if(diffTime > 0){
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
    } else {
        printf("L'athlète a gardé le même temps\n\n");
        return;
    }

    fclose(Athlete);
}

int averageTime(FILE *athlete, char raceType[MAX]){
    // Code pour afficher le meilleur temps de l'athlète pour une épreuve donnée
    int averageTime = 0; 
    int count = 0;

    rewind(athlete);
    while (fgetc(athlete) != '\n');

    while (fscanf(athlete, "%d %d %d %s %d %d %d %d %d", &training.trainingDate.day, &training.trainingDate.month, &training.trainingDate.year, training.raceType, &training.athleteTime.hour, &training.athleteTime.minute, &training.athleteTime.second, &training.athleteTime.millisecond, &training.position) != EOF) {
        if (strcmp(training.raceType, raceType) == 0) {
            int millisecondsTime = training.athleteTime.hour * 3600000 + training.athleteTime.minute * 60000 + training.athleteTime.second * 1000 + training.athleteTime.millisecond;

            averageTime += millisecondsTime;
            count++;
        }
    }
    if(count == 0){
        return 0;
    }

    averageTime = averageTime/count;

    return averageTime;
}

void worstTime(FILE *athlete, char raceType[MAX]){
    // Code pour afficher le meilleur temps de l'athlète pour une épreuve donnée
    int worstRaceTime = INT_MIN; // INT_MAX est la valeur la plus élevée qu'un int peut avoir
    Training worstTraining;

    rewind(athlete);
    while (fgetc(athlete) != '\n');

    while (fscanf(athlete, "%d %d %d %s %d %d %d %d %d", &training.trainingDate.day, &training.trainingDate.month, &training.trainingDate.year, training.raceType, &training.athleteTime.hour, &training.athleteTime.minute, &training.athleteTime.second, &training.athleteTime.millisecond, &training.position) != EOF) {
        if (strcmp(training.raceType, raceType) == 0) {
            int millisecondsTime = training.athleteTime.hour * 3600000 + training.athleteTime.minute * 60000 + training.athleteTime.second * 1000 + training.athleteTime.millisecond;

            if (millisecondsTime > worstRaceTime) {
                worstRaceTime = millisecondsTime;
                worstTraining = training;
            }
        }
    }

    if (worstRaceTime == INT_MIN) {
        printf("Aucun entraînement de ce type n'a été trouvé.\n");
        exit(1);

    } else {
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

void bestTime(FILE *athlete, char raceType[MAX]){
    // Code pour afficher le meilleur temps de l'athlète pour une épreuve donnée
    int bestRaceTime = INT_MAX; // INT_MAX est la valeur la plus élevée qu'un int peut avoir
    Training bestTraining;

    rewind(athlete);
    while (fgetc(athlete) != '\n');

    while (fscanf(athlete, "%d %d %d %s %d %d %d %d %d", &training.trainingDate.day, &training.trainingDate.month, &training.trainingDate.year, training.raceType, &training.athleteTime.hour, &training.athleteTime.minute, &training.athleteTime.second, &training.athleteTime.millisecond, &training.position) != EOF) {
        if (strcmp(training.raceType, raceType) == 0) {
            int millisecondsTime = training.athleteTime.hour * 3600000 + training.athleteTime.minute * 60000 + training.athleteTime.second * 1000 + training.athleteTime.millisecond;

            if (millisecondsTime < bestRaceTime) {
                bestRaceTime = millisecondsTime;
                bestTraining = training;
            }
        }
    }

    if (bestRaceTime == INT_MAX) {
        printf("Aucun entraînement de ce type n'a été trouvé.\n");
        exit(1);

    } else {
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

void trainingResume(void) {
    int athleteChoice, lines, raceChoice, numRace;
    char race[MAX];
    // Ouvrir le fichier de tous les athlètes
    FILE *athleteName = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if(athleteName == NULL){
        printf("Impossible d'ouvrir le fichier nomAthlètes.\n");
        exit(1);
    }

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

    // Ouvrir le fichier de l'athlète choisi
    FILE *Athlete = openAthleteFile(athleteChoice);
    if(Athlete == NULL){
        printf("Impossible d'ouvrir le fichier de l'athlète.\n");
        exit(1);
    }


    FILE *raceName = fopen(PATH"/Liste/nomEpreuve.txt", "r");
    if(raceName == NULL){
        printf("Impossible d'ouvrir le fichier nomEpreuve.\n");
        exit(1);
    }

    showRaceList(raceName);
    printf("Choix : ");
    scanf("%d", &raceChoice);
    printf("\n");

    rewind(raceName);
    lines = countLine(raceName);

    while (raceChoice < 1 || raceChoice > lines) {
        printf("Choix invalide. Veuillez choisir un numéro d'épreuve entre 1 et %d.\n", lines);
        printf("Choix : ");
        scanf("%d", &raceChoice);
        printf("\n");
    }

    rewind(raceName);
    while (fgets(race, sizeof(race), raceName)) {
        sscanf(race, "%d", &numRace);
        race[strcspn(race, "\n")] = 0;

        if(numRace == raceChoice) {
            break;
        }
    }


    bestTime(Athlete, race + 2);
    worstTime(Athlete, race + 2);
    int average = averageTime(Athlete, race + 2);
    if (average == 0) {
        printf("Aucun entraînement de ce type n'a été trouvé.\n");
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

void whoInOG(void){
    int lines, raceChoice;
    // Code pour déterminer qui envoyer aux Jeux Olympiques
    FILE *raceName = fopen(PATH"/Liste/nomEpreuve.txt", "r");
    if(raceName == NULL){
        printf("Impossible d'ouvrir le fichier nomEpreuve.txt.\n");
        exit(1);
    }

    showRaceList(raceName);
    printf("Choix : ");
    scanf("%d", &raceChoice);
    printf("\n");

    rewind(raceName);
    lines = countLine(raceName);

    while (raceChoice < 1 || raceChoice > lines) {
        printf("Choix invalide. Veuillez choisir un numéro d'épreuve entre 1 et %d.\n", lines);
        printf("Choix : ");
        scanf("%d", &raceChoice);
        printf("\n");
    }

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
        exit(1);
    }
    lines = countLine(athleteName);

    rewind(athleteName);
    //mettre le nom des athlètes dans un tableau
    char athletes[MAX][MAX]; int athleteNumber;
    for(int i = 0; i < lines; i++){
        fscanf(athleteName, "%d", &athleteNumber); // Lecture du numéro de l'athlète
        fseek(athleteName, 1, SEEK_CUR); // Sauter le numéro de l'athlète

        fgets(athletes[i], sizeof(athletes[i]), athleteName);
        athletes[i][strcspn(athletes[i], "\n")] = 0;
    }
    
    //mettre average temps de chaque athlète dans un tableau
    int averages[MAX];
    for(int i = 0; i < lines; i++){
        FILE *Athlete = openAthleteFile(i+1);
        averages[i] = averageTime(Athlete, race + 2);
        fclose(Athlete);
    }

    // Afficher les 3 meilleurs averages
    AverageIndex averageIndex[lines];
    for(int i = 0; i < lines; i++){
        averageIndex[i].average = averages[i];
        averageIndex[i].index = i;
    }

    qsort(averageIndex, (size_t)lines, sizeof(AverageIndex), compareAverage);

    // Si l'epreuve est marathon, afficher les 3 meilleurs moyennes
    if(averages[averageIndex[2].index]/3600000 != 0){
        printf("\nLes 3 meilleurs moyenne pour le %s sont :\n", race + 2);
        color("1"); printf("%s %s ", "🥇", athletes[averageIndex[0].index]); color("0"); printf("avec une moyenne de %02dh %02dmin %02dsec %03dms\n", averages[averageIndex[0].index]/3600000, (averages[averageIndex[0].index] % 3600000)/60000, (averages[averageIndex[0].index] % 60000)/1000, (averages[averageIndex[0].index] % 1000));
        color("1"); printf("%s %s ", "🥈", athletes[averageIndex[1].index]); color("0"); printf("avec une moyenne de %02dh %02dmin %02dsec %03dms\n", averages[averageIndex[1].index]/3600000, (averages[averageIndex[1].index] % 3600000)/60000, (averages[averageIndex[1].index] % 60000)/1000, (averages[averageIndex[1].index] % 1000));
        color("1"); printf("%s %s ", "🥉", athletes[averageIndex[2].index]); color("0"); printf("avec une moyenne de %02dh %02dmin %02dsec %03dms\n", averages[averageIndex[2].index]/3600000, (averages[averageIndex[2].index] % 3600000)/60000, (averages[averageIndex[2].index] % 60000)/1000, (averages[averageIndex[2].index] % 1000));
        printf("\n");
    }
    else if (averages[averageIndex[2].index]/60000 != 0) {
        printf("\nLes 3 meilleurs moyenne pour le %s sont :\n", race + 2);
        color("1"); printf("%s %s ", "🥇", athletes[averageIndex[0].index]); color("0"); printf("avec une moyenne de %02dmin %02dsec %03dms\n", averages[averageIndex[0].index]/60000, (averages[averageIndex[0].index] % 60000)/1000, (averages[averageIndex[0].index] % 1000));
        color("1"); printf("%s %s ", "🥈", athletes[averageIndex[1].index]); color("0"); printf("avec une moyenne de %02dmin %02dsec %03dms\n", averages[averageIndex[1].index]/60000, (averages[averageIndex[1].index] % 60000)/1000, (averages[averageIndex[1].index] % 1000));
        color("1"); printf("%s %s ", "🥉", athletes[averageIndex[2].index]); color("0"); printf("avec une moyenne de %02dmin %02dsec %03dms\n", averages[averageIndex[2].index]/60000, (averages[averageIndex[2].index] % 60000)/1000, (averages[averageIndex[2].index] % 1000));
        printf("\n");
    } else {
        printf("\nLes 3 meilleurs moyenne pour le %s sont : \n", race + 2);
        color("1"); printf("%s %s ", "🥇", athletes[averageIndex[0].index]); color("0"); printf("avec une moyenne de %02dsec %03dms\n", averages[averageIndex[0].index]/1000, (averages[averageIndex[0].index] % 1000));
        color("1"); printf("%s %s ", "🥈", athletes[averageIndex[1].index]); color("0"); printf("avec une moyenne de %02dsec %03dms\n", averages[averageIndex[1].index]/1000, (averages[averageIndex[1].index] % 1000));
        color("1"); printf("%s %s ", "🥉", athletes[averageIndex[2].index]); color("0"); printf("avec une moyenne de %02dsec %03dms\n", averages[averageIndex[2].index]/1000, (averages[averageIndex[2].index] % 1000));
        printf("\n");
    }
}

void athleteStatistic(Training training1, FILE *file) {
    // Code pour consulter des statistiques de performances de chaque athlète
    int choice, athleteChoice, raceChoice;
    char race[MAX];

    printf("1. Consulter un résumer des statistiques de performances d'un athlète\n");
    printf("2. Qui envoyer au Jeux Olympiques\n");
    printf("3. Progression de l'athlète\n");
    color("31"); printf("4. Quitter\n"); color("0");
    printf("Choix : ");
    scanf("%d", &choice);
    printf("\n");

    switch (choice) {
        case 1:
            // Code pour consulter les statistiques de performances d'un athlète
            trainingResume();
            break;
        case 2:
            // Code pour déterminer qui envoyer aux Jeux Olympiques
            whoInOG();
            break;
        case 3:
            // Code pour afficher la progression de l'athlète
            chooseAthlete(&athleteChoice);
            chooseRace(&raceChoice, race);
            showDiffTime(&athleteChoice, &raceChoice, race);
            break;
        case 4:
            // Code pour retourner au début du programme
            break;
        default:
            printf("Choix invalide.\n\n");
            athleteStatistic(training1, file);
    }
}
