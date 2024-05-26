#include "../headers/def.h"

void OGStart(void){
    // Obtenir le temps actuel
    time_t now;
    time(&now);

    // Définir le temps de l'événement
    struct tm eventTime = *localtime(&now);
    eventTime.tm_year = 2024 - 1900; // Année de l'événement
    eventTime.tm_mon = 7 - 1; // Mois de l'événement
    eventTime.tm_mday = 26; // Jour de l'événement

    // Calculez la différence en secondes
    double seconds = difftime(mktime(&eventTime), now);

    // Convertir en jours
    int days = (int)seconds / (24 * 60 * 60);

    color("33"); printf("Les JO commencent dans %d jours !\n\n", days); color("0");
}

// Fonction qui permet de continuer le programme ou de quitter
int continueProgramme(void){
    int continueProg;
    color("32"); printf("1. Retour au menu principal\n"); color("0");
    color("31"); printf("2. Quitter\n"); color("0");
    printf("Choix : ");
    scanf("%d", &continueProg);
    printf("\n");

    while(continueProg < 1 || continueProg > 2){
        while (getchar() != '\n');
        printf("Choix invalide. Veuillez saisir 1 ou 2.\n");
        printf("Choix : ");
        scanf("%d", &continueProg);
        printf("\n");
    }

    if(continueProg == 1){
        // Code pour continuer le programme
        return 1;  
    }
    else if(continueProg == 2){
        return 0;
    }
    else{
        printf("Choix invalide.\n");
        return continueProgramme();
    }
}

// Fonction qui compte le nombre de lignes dans un fichier
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

// Fonction qui vérifie si une date est valide
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

// Fonction qui compare deux dates
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

// Fonction qui compare deux temps
int compareAverage(const void *a, const void *b) {
    AverageIndex *miA = (AverageIndex *)a;
    AverageIndex *miB = (AverageIndex *)b;
    if(miA->average == 0) return 1;
    if(miB->average == 0) return -1;
    return miA->average - miB->average;
}

// Procédure qui permet de remplir des caractère selon la taille de la fenêtre
void print_padded_line(const char* prefix, const char* content) {
    int padding = FRAME_WIDTH - (int)strlen(prefix) - (int)strlen(content) - 2; // Calculer le nombre de caractères à ajouter pour remplir la ligne
    printf("%s%s%*s", prefix, content, padding, ""); // Afficher la ligne
}

// Procédure qui affiche le nom de l'athlète
void showAthleteName(FILE *file) {
    char athleteName[MAX];
    int athleteNumber;
    
    fscanf(file, "%d", &athleteNumber); // Lecture du numéro de l'athlète
    fseek(file, 1, SEEK_CUR); // Sauter l'espace

    fgets(athleteName, sizeof(athleteName), file); // Lecture du nom de l'athlète
    
    athleteName[strcspn(athleteName, "\n")] = 0; // Suppression de la nouvelle ligne
    printf("%s\n", athleteName); // Affichage du nom de l'athlète
}

// Procédure qui affiche la liste des athlètes grace à showAthleteName
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

// Fonction qui permet de choisir un athlète
int makeAthleteChoice(void){
    int athleteChoice;
    FILE *athleteFile = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if (athleteFile == NULL) {
        printf("Impossible d'ouvrir le fichier nomAthletes\n");
        exit(0);
    }
    int lines = countLine(athleteFile);

    rewind(athleteFile);
    showAthleteList(athleteFile);
    printf("Choix : ");
    scanf("%d", &athleteChoice);
    printf("\n");
    while(athleteChoice < 1 || athleteChoice > lines){
        while (getchar() != '\n');
        printf("Choix invalide. Entrez un nombre entre 1 et %d.\n", lines);
        printf("Choix : ");
        scanf("%d", &athleteChoice);
        printf("\n");
    }

    fclose(athleteFile);

    return athleteChoice;
}

// Procédure qui affiche le nom de l'épreuve
void showRaceName(FILE *raceFile) {
    char race[MAX];
    
    fseek(raceFile, 2, SEEK_CUR); // Sauter le numéro de l'épreuve

    fgets(race, sizeof(race), raceFile); // Lecture du nom de l'épreuve
    race[strcspn(race, "\n")] = 0; // Suppression de la nouvelle ligne

    printf("%s\n", race); // Affichage du nom de l'épreuve
}

// Procédure qui affiche la liste des épreuves grace à showRaceName
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

// Fonction qui ouvre le fichier de l'athlète choisi
FILE *openAthleteFile(int athleteChoice) {
    int numAthlete;
    char fileName[MAX];
    char athleteName[MAX];

    // Ouvrir le fichier athleteFile
    FILE *athleteFile = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if(athleteFile == NULL){
        printf("Impossible d'ouvrir le fichier athleteName 2.\n");
        exit(0);
    }

    // Lire chaque ligne du fichier
    while (fgets(athleteName, sizeof(athleteName), athleteFile)) {
        sscanf(athleteName, "%d", &numAthlete); // Lecture du numéro de l'athlète
        athleteName[strcspn(athleteName, "\n")] = 0; // Suppression de la nouvelle ligne

        if(numAthlete == athleteChoice) {
            break;
        }
    }

    // Créer le chemin du fichier de l'athlète choisi
    sprintf(fileName, PATH"/Athletes/%s.txt", athleteName + 3);
    
    // Ouvrir le fichier de l'athlète choisi
    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        printf("Impossible d'ouvrir le fichier %s.txt.\n", athleteName + 3);
        color("32"); printf("Verifier qu'il y a des zéro devant les chiffres du fichier nomAthletes.txt\n\n"); color("0");
        exit(0);
    }
    return file;
}

// Fonction qui permet de modifier le fichier de l'athlète choisi
FILE *changeAthleteFile(int athleteChoice) {
    int numAthlete;
    char fileName[MAX];
    char athleteName[MAX];

    // Ouvrir le fichier athleteFile
    FILE *athleteFile = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if(athleteFile == NULL){
        printf("Impossible d'ouvrir le fichier nomAthlete.\n");
        exit(0);
    }

    // Lire chaque ligne du fichier
    while (fgets(athleteName, sizeof(athleteName), athleteFile)) {
        // Lecture du numéro de l'athlète
        sscanf(athleteName, "%d", &numAthlete);
        athleteName[strcspn(athleteName, "\n")] = 0;

        if(numAthlete == athleteChoice) {
            break;
        }
    }

    // Créer le chemin du fichier de l'athlète choisi
    sprintf(fileName, PATH"/Athletes/%s.txt", athleteName + 3);
    
    // Ouvrir le fichier de l'athlète choisi en mode lecture et écriture
    FILE *file = fopen(fileName, "r+");
    if(file == NULL){
        printf("Impossible d'ouvrir le fichier %s.txt.\n", athleteName + 3);
        color("32"); printf("Verifier qu'il y a des zéros deant les chiffres du fichier nomAthletes.txt\n\n"); color("0");
        exit(0);
    }
    return file;
}

// Procédure qui permet de choisir une un athlète
void chooseAthlete(int *athleteChoice){
    int lines;

    // Ouvrir le fichier de tous les athlètes
    FILE *athleteFile = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if(athleteFile == NULL){
        printf("Impossible d'ouvrir le fichier nomAthletes.\n");
        exit(0);
    }

    // Afficher la liste des athlètes et demander le choix de l'utilisateur
    showAthleteList(athleteFile);
    printf("Choix : ");
    scanf("%d", athleteChoice);
    printf("\n");

    rewind(athleteFile);
    lines = countLine(athleteFile);

    while (*athleteChoice < 1 || *athleteChoice > lines) {
        while (getchar() != '\n');
        printf("Choix invalide. Veuillez choisir un numéro d'athlète entre 1 et %d.\n", lines);
        printf("Choix : ");
        scanf("%d", athleteChoice);
        printf("\n");
    }

    // Fermeture du fichier athleteFile
    fclose(athleteFile);
}

// Procédure qui permet de choisir une épreuve
void chooseRace(int *raceChoice, char race[MAX]){
    int numRace;

    // Ouvrir le fichier de toutes les épreuves
    FILE *raceFile = fopen(PATH"/Liste/nomEpreuve.txt", "r");
    if(raceFile == NULL){
        printf("Impossible d'ouvrir le fichier raceFile.\n");
        exit(0);
    }

    // Afficher la liste des épreuves et demander le choix de l'utilisateur
    showRaceList(raceFile);
    printf("Choix : ");
    scanf("%d", raceChoice);
    printf("\n");

    rewind(raceFile);
    int lines = countLine(raceFile);

    while (*raceChoice < 1 || *raceChoice > lines) {
        while (getchar() != '\n');
        printf("Choix invalide. Veuillez choisir un numéro d'épreuve entre 1 et %d.\n", lines);
        printf("Choix : ");
        scanf("%d", raceChoice);
        printf("\n");
    }

    rewind(raceFile);
    // Lire le fichier epreuves jusqu'à trouver l'épreuve choisie
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
