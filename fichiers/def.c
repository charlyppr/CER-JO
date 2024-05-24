#include "../headers/def.h"

int countLine(FILE *file) {
    int c;
    int lines = 0;

    // Compter le nombre de lignes
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            lines++;
        }
    }
    return lines;
}

int validDate(Date date) {
    if (date.year < 2000 || date.year > 2024) {
        return 0;
    }

    if (date.month < 1 || date.month > 12) {
        return 0;
    }

    if (date.day < 1 || date.day > 31) {
        return 0;
    }

    if (date.month == 2) {
        if (date.year % 4 == 0) {
            if (date.day > 29) {
                return 0;
            }
        } else {
            if (date.day > 28) {
                return 0;
            }
        }
    }

    if (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11) {
        if (date.day > 30) {
            return 0;
        }
    }

    return 1;
}

int compareDates(const void *a, const void *b) {
    Date *dateA = (Date *)a;
    Date *dateB = (Date *)b;

    if (dateA->year != dateB->year)
        return dateA->year - dateB->year;
    else if (dateA->month != dateB->month)
        return dateA->month - dateB->month;
    else
        return dateA->day - dateB->day;
}

int compareAverage(const void *a, const void *b) {
    AverageIndex *miA = (AverageIndex *)a;
    AverageIndex *miB = (AverageIndex *)b;
    if(miA->average == 0) return 1;
    if(miB->average == 0) return -1;
    return miA->average - miB->average;
}

void showAthleteName(FILE *file) {
    char athleteName[MAX];
    
    fseek(file, 2, SEEK_CUR); // Sauter le numéro de l'athlète
    
    fgets(athleteName, sizeof(athleteName), file); // Lecture du nom de l'athlète
    
    athleteName[strcspn(athleteName, "\n")] = 0; // Suppression de la nouvelle ligne
    printf("%s\n", athleteName);
}

void showAthleteList(FILE *athleteName) {
    int lines = countLine(athleteName);

    printf("Quelle athlètes parmis ces %d\n", lines);
    rewind(athleteName);

    // Affichage de la liste des athlètes
    for (int i = 0; i < lines; i++) {
        printf("%d. ", i + 1);
        showAthleteName(athleteName);
    }
}

int makeAthleteChoice(void){
    int athleteChoice;
    FILE *athleteFile = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if (athleteFile == NULL) {
        printf("Impossible d'ouvrir le fichier nomAthletes\n");
        exit(1);
    }
    int lines = countLine(athleteFile);

    rewind(athleteFile);
    showAthleteList(athleteFile);
    printf("Choix : ");
    scanf("%d", &athleteChoice);
    printf("\n");
    while(athleteChoice < 1 || athleteChoice > lines){
        printf("Choix invalide. Entrez un nombre entre 1 et %d.\n", lines);
        printf("Choix : ");
        scanf("%d", &athleteChoice);
        printf("\n");
    }

    fclose(athleteFile);

    return athleteChoice;
}

void showRaceName(FILE *raceFile) {
    char race[MAX];
    // Sauter le numéro de l'épreuve
    fseek(raceFile, 2, SEEK_CUR);
    // Lecture du nom de l'épreuve
    fgets(race, sizeof(race), raceFile);
    // Suppression de la nouvelle ligne
    race[strcspn(race, "\n")] = 0;
    printf("%s\n", race);
}

void showRaceList(FILE *raceFile) {
    int lines = countLine(raceFile);

    printf("Quelle épreuves parmis ces %d\n", lines);
    rewind(raceFile);

    // Affichage de la liste des épreuves
    for (int i = 0; i < lines; i++) {
        printf("%d. ", i + 1);
        showRaceName(raceFile);
    }
}

FILE *openAthleteFile(int athleteChoice) {
    int numAthlete;
    char fileName[MAX];
    char athleteName[MAX];

    // Ouvrir le fichier athleteFile
    FILE *athleteFile = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if(athleteFile == NULL){
        printf("Impossible d'ouvrir le fichier athleteName 2.\n");
        exit(1);
    }

    // Lire chaque ligne du fichier
    while (fgets(athleteName, sizeof(athleteName), athleteFile)) {
        sscanf(athleteName, "%d", &numAthlete);
        athleteName[strcspn(athleteName, "\n")] = 0;

        if(numAthlete == athleteChoice) {
            break;
        }
    }

    sprintf(fileName, PATH"/Athletes/%s.txt", athleteName + 2);
    
    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        printf("Impossible d'ouvrir le fichier %s.txt.\n", athleteName + 2);
        exit(1);
    }
    return file;
}

FILE *changeAthleteFile(int athleteChoice) {
    int numAthlete;
    char fileName[MAX];
    char athleteName[MAX];

    // Ouvrir le fichier athleteFile
    FILE *athleteFile = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if(athleteFile == NULL){
        printf("Impossible d'ouvrir le fichier athleteName 2.\n");
        exit(1);
    }

    // Lire chaque ligne du fichier
    while (fgets(athleteName, sizeof(athleteName), athleteFile)) {
        sscanf(athleteName, "%d", &numAthlete);
        athleteName[strcspn(athleteName, "\n")] = 0;

        if(numAthlete == athleteChoice) {
            break;
        }
    }

    sprintf(fileName, PATH"/Athletes/%s.txt", athleteName + 2);
    
    FILE *file = fopen(fileName, "r+");
    if(file == NULL){
        printf("Impossible d'ouvrir le fichier %s.txt.\n", athleteName + 2);
        exit(1);
    }
    return file;
}

void chooseAthlete(int *athleteChoice){
    int lines;
    // Ouvrir le fichier de tous les athlètes
    FILE *athleteFile = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if(athleteFile == NULL){
        printf("Impossible d'ouvrir le fichier nomAthletes.\n");
        exit(1);
    }

    showAthleteList(athleteFile);
    printf("Choix : ");
    scanf("%d", athleteChoice);
    printf("\n");

    rewind(athleteFile);
    lines = countLine(athleteFile);

    while (*athleteChoice < 1 || *athleteChoice > lines) {
        printf("Choix invalide. Veuillez choisir un numéro d'athlète entre 1 et %d.\n", lines);
        printf("Choix : ");
        scanf("%d", athleteChoice);
        printf("\n");
    }

    // Fermeture du fichier athleteFile
    fclose(athleteFile);
}

void chooseRace(int *raceChoice, char race[MAX]){
    int numRace;
    FILE *raceFile = fopen(PATH"/Liste/nomEpreuve.txt", "r");
    if(raceFile == NULL){
        printf("Impossible d'ouvrir le fichier raceFile.\n");
        exit(1);
    }

    showRaceList(raceFile);
    printf("Choix : ");
    scanf("%d", raceChoice);
    printf("\n");

    rewind(raceFile);
    int lines = countLine(raceFile);

    while (*raceChoice < 1 || *raceChoice > lines) {
        printf("Choix invalide. Veuillez choisir un numéro d'épreuve entre 1 et %d.\n", lines);
        printf("Choix : ");
        scanf("%d", raceChoice);
        printf("\n");
    }


    rewind(raceFile);
    while (fgets(race, MAX, raceFile)) {
        sscanf(race, "%d", &numRace);
        race[strcspn(race, "\n")] = 0;

        if(numRace == *raceChoice) {
            break;
        }
    }

    // Fermeture du fichier raceFile
    fclose(raceFile);

}

