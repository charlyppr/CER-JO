#include "../headers/entrainement.h"

// Procédure pour ajouter un entrainement à un athlète
void addTraining(int athleteChoice) {
    int raceChoice, numRace, relayPosition;
    int hour, minutes, seconds, ms;
    char race[MAX];
    Date date;

    // Ouverture du fichier nomEpreuve.txt
    FILE *raceFile = fopen(PATH"/Liste/nomEpreuve.txt", "r");
    if (raceFile == NULL) {
        printf("Impossible d'ouvrir le fichier nomEpreuve\n");
        return;
    }

    // Afficher la liste des épreuves et demander le choix de l'utilisateur
    showRaceList(raceFile);
    printf("Choix : ");
    scanf("%d", &raceChoice);
    printf("\n");
    while(raceChoice < 1 || raceChoice > 5){
        printf("Choix invalide. Veuillez choisir un numéro d'épreuve entre 1 et 5.\n");
        printf("Choix : ");
        scanf("%d", &raceChoice);
        printf("\n");
    }

    // Si l'épreuve choisie est un relais, demander la position
    if(raceChoice == 5){
        printf("Position lors du relais : ");
        scanf("%d", &relayPosition);
        printf("\n");
        while (relayPosition < 1 || relayPosition > 4){
            printf("Choix invalide. Veuillez choisir une position entre 1 et 4.\n");
            printf("Position lors du relais : ");
            scanf("%d", &relayPosition);
            printf("\n");
        }
    } else {
        relayPosition = 0;
    }

    rewind(raceFile);
    // Lire le fichier epreuves jusqu'à trouver l'épreuve choisie
    while (fgets(race, sizeof(race), raceFile)) {
        sscanf(race, "%d", &numRace);
        race[strcspn(race, "\n")] = 0;

        if(numRace == raceChoice) {
            break;
        }
    }

    fclose(raceFile);

    // Demander la date de l'entrainement
    printf("Entrez la date de l'entrainement (JJ MM AAAA) : ");
    scanf("%d %d %d", &date.day, &date.month, &date.year);
    printf("\n");
    while(!validDate(date)){
        printf("Date invalide. Veuillez entrer une date valide.\n");
        printf("Entrez la date de l'entrainement (JJ MM AAAA) : ");
        scanf("%d %d %d", &date.day, &date.month, &date.year);
        printf("\n");
    }

    // Demander le temps de l'athlète
    printf("En combien de temps l'athlète a-t-il réalisé l'épreuve ?\n");
    if(raceChoice ==4){
        printf("Heures : ");
        scanf("%d", &hour);
        while(hour < 0 || hour > 23){
            printf("Heures (entre 0 et 23) : ");
            scanf("%d", &hour);
        }
    }

    if(raceChoice == 3 || raceChoice == 4){
        printf("Minutes : ");
        scanf("%d", &minutes);
        while(minutes < 0 || minutes > 59){
            printf("Minutes (entre 0 et 59) : ");
            scanf("%d", &minutes);
        }
    }

    printf("Secondes : ");
    scanf("%d", &seconds);
    while(seconds < 0 || seconds > 59){
        printf("Secondes (entre 0 et 59) : ");
        scanf("%d", &seconds);
    }
    printf("Millisecondes : ");
    scanf("%d", &ms);
    while(ms < 0 || ms > 999){
        printf("Millisecondes (entre 0 et 59) : ");
        scanf("%d", &ms);
    }
    printf("\n");

    // Ouvrir le fichier de l'athlète choisi en mode lecture et écriture
    FILE *Athlete = changeAthleteFile(athleteChoice);
    if (Athlete == NULL) {
        printf("Impossible d'ouvrir le fichier de l'athlète\n");
        return;
    }

    while (fgetc(Athlete) != '\n'); // Sauter une line

    // Ajouter l'entrainement à la fin du fichier
    fprintf(Athlete, "%d %d %d %s %d %d %d %d %d\n", date.day, date.month, date.year, race + 2, hour, minutes, seconds, ms, relayPosition);

    fclose(Athlete);

    printf("Entrainement ajouté avec succès.\n\n");

}

// Procédure pour supprimer un entrainement d'un athlète
void removeTraining(void) {
    Training training1;
    int number;
    char name[MAX/2], lastname[MAX/2];
    char fileName[MAX], completePath[MAX];

    int athleteChoice = makeAthleteChoice();

    // Ouvrir le fichier nomAthletes.txt
    FILE *athleteFile = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if (athleteFile == NULL) {
        printf("Impossible d'ouvrir le fichier nomAthletes\n");
        return;
    }

    // Lire chaque ligne du fichier et récupérer le prénom et le nom de l'athlète choisi
    rewind(athleteFile);
    while (fscanf(athleteFile, "%d %s %s", &number, name, lastname) != EOF) {
        if(athleteChoice == number){
            // Créer le nom du fichier de l'athlète choisi
            sprintf(fileName, "%s %s.txt", name, lastname);
            break;
        }
    }

    // Créer le chemin du fichier de l'athlète choisi
    sprintf(completePath, "%s/Athletes/%s", PATH, fileName);

    int position, count = 1, trainingChoice;
    FILE *file = changeAthleteFile(athleteChoice);
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier athleteChoice\n");
        return;
    }
    int line = countLine(file);
    if (line == 1) {
        printf("Aucun entrainement à supprimer\n");
        return;
    }

    rewind(file);
    while (fgetc(file) != '\n'); // Sauter une line

    printf("Choisissez l'entrainement à supprimer\n");
    // Lire chaque line du fichier
    while (fscanf(file, "%d %d %d %s %d %d %d %d %d", &training1.trainingDate.day, &training1.trainingDate.month, &training1.trainingDate.year, training1.raceType, &training1.athleteTime.hour, &training1.athleteTime.minute, &training1.athleteTime.second, &training1.athleteTime.millisecond, &position) != EOF) {
        // Affichage des valeurs
        printf("%02d. %02d/%02d/%4d | %02dh %02dmin %02dsec %03dms | %s\n", count, training1.trainingDate.day, training1.trainingDate.month, training1.trainingDate.year, training1.athleteTime.hour, training1.athleteTime.minute, training1.athleteTime.second, training1.athleteTime.millisecond, training1.raceType);
        count++;
    }

    // Demander le choix de l'entrainement à supprimer
    printf("Choix : ");
    scanf("%d", &trainingChoice);
    printf("\n");
    while(trainingChoice < 1 || trainingChoice > count - 1){
        printf("Choix invalide. Entrez un nombre entre 1 et %d.\n", count - 1);
        printf("Choix : ");
        scanf("%d", &trainingChoice);
        printf("\n");
    }

    // Suppression de l'entrainement
    FILE *tempFile = fopen(PATH"/Athletes/temp.txt", "w");
    if (tempFile == NULL) {
        printf("Impossible de créer le fichier temporaire\n");
        return;
    }
    
    // Copie de toutes les lines sauf celle à supprimer
    fprintf(tempFile, "%s %s\n", name, lastname); // Écrire le prénom et le lastname de l'athlète
    
    rewind(file);
    while (fgetc(file) != '\n'); // Sauter une line

    // Copie de toutes les lines sauf celle à supprimer
    count = 1;
    while (fscanf(file, "%d %d %d %s %d %d %d %d %d", &training1.trainingDate.day, &training1.trainingDate.month, &training1.trainingDate.year, training1.raceType, &training1.athleteTime.hour, &training1.athleteTime.minute, &training1.athleteTime.second, &training1.athleteTime.millisecond, &position) != EOF) {
        if (count != trainingChoice) {
            fprintf(tempFile, "%d %d %d %s %d %d %d %d %d\n", training1.trainingDate.day, training1.trainingDate.month, training1.trainingDate.year, training1.raceType, training1.athleteTime.hour, training1.athleteTime.minute, training1.athleteTime.second, training1.athleteTime.millisecond, position);
        }
        count++;
    }

    fclose(file);
    fclose(tempFile);
    fclose(athleteFile);

    remove(completePath);  // Supprimez le fichier original
    rename(PATH"/Athletes/temp.txt", completePath);  // Renommez le fichier temporaire avec le lastname du fichier original

    printf("Entrainement supprimé avec succès.\n\n");
}

// Procédure pour modifier un entrainement d'un athlète
void changeTraining(void){
    Training training1, newTraining;
    int number, numRace;
    char race[MAX];
    char name[MAX/2], lastname[MAX/2];
    char fileName[MAX], completePath[MAX];

    int athleteChoice = makeAthleteChoice();

    // Ouvrir le fichier nomAthletes.txt
    FILE *athleteFile = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if (athleteFile == NULL) {
        printf("Impossible d'ouvrir le fichier nomAthletes\n");
        return;
    }
    int lines = countLine(athleteFile);

    // Lire chaque ligne du fichier et récupérer le prénom et le nom de l'athlète choisi
    rewind(athleteFile);
    while (fscanf(athleteFile, "%d %s %s", &number, name, lastname) != EOF) {
        if(athleteChoice == number){
            // Créer le nom du fichier de l'athlète choisi
            sprintf(fileName, "%s %s.txt", name, lastname);
            break;
        }
    }

    // Créer le chemin du fichier de l'athlète choisi
    sprintf(completePath, "%s/Athletes/%s", PATH, fileName);

    // Ouvrir le fichier de l'athlète choisi en mode lecture et écriture
    int position, count = 1, trainingChoice;
    FILE *file = changeAthleteFile(athleteChoice);
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier athleteChoice\n\n");
        return;
    }
    int line = countLine(file);
    if (line == 1) {
        printf("Aucun entrainement à modifier\n\n");
        return;
    }

    rewind(file);
    while (fgetc(file) != '\n'); // Sauter une line

    printf("Choisissez l'entrainement à modifier\n");
    // Lire chaque line du fichier
    while (fscanf(file, "%d %d %d %s %d %d %d %d %d", &training1.trainingDate.day, &training1.trainingDate.month, &training1.trainingDate.year, training1.raceType, &training1.athleteTime.hour, &training1.athleteTime.minute, &training1.athleteTime.second, &training1.athleteTime.millisecond, &position) != EOF) {
        // Affichage des valeurs
        printf("%02d. %02d/%02d/%4d | %02dh %02dmin %02dsec %03dms | %s\n", count, training1.trainingDate.day, training1.trainingDate.month, training1.trainingDate.year, training1.athleteTime.hour, training1.athleteTime.minute, training1.athleteTime.second, training1.athleteTime.millisecond, training1.raceType);
        count++;
    }

    // Demander le choix de l'entrainement à modifier
    printf("Choix : ");
    scanf("%d", &trainingChoice);
    printf("\n");
    while(trainingChoice < 1 || trainingChoice > count - 1){
        printf("Choix invalide. Entrez un nombre entre 1 et %d.\n", count - 1);
        printf("Choix : ");
        scanf("%d", &trainingChoice);
        printf("\n");
    }

    int newHour, newMinutes, newSeconds, newMs, changeChoice, newRaceType;

    // Demander les nouvelles valeurs
    printf("Faut-il changer la date de l'entrainement ?\n");
    color("32"); printf("1. Oui\n"); color("0");
    color("31"); printf("2. Non\n"); color("0");
    printf("Choix : ");
    scanf("%d", &changeChoice);
    printf("\n");
    while(changeChoice != 1 && changeChoice != 2){
        printf("Choix invalide. Veuillez entrer un choice valide.\n");
        printf("Faut-il changer la date de l'entrainement ?\n");
        color("32"); printf("1. Oui\n"); color("0");
        color("31"); printf("2. Non\n"); color("0");
        printf("Choix : ");
        scanf("%d", &changeChoice);
        printf("\n");
    }    

    if(changeChoice == 1){
        printf("Entrez la nouvelle date de l'entrainement (JJ MM AAAA) : ");
        scanf("%d %d %d", &newTraining.trainingDate.day, &newTraining.trainingDate.month, &newTraining.trainingDate.year);
        printf("\n");
        while(!validDate(newTraining.trainingDate)){
            printf("Date invalide. Veuillez entrer une date valide.\n");
            printf("Entrez la date de l'entrainement (JJ MM AAAA) : ");
            scanf("%d %d %d", &newTraining.trainingDate.day, &newTraining.trainingDate.month, &newTraining.trainingDate.year);
            printf("\n");
        }
    } else {
        newTraining.trainingDate.day = training1.trainingDate.day;
        newTraining.trainingDate.month = training1.trainingDate.month;
        newTraining.trainingDate.year = training1.trainingDate.year;
    }

    // Demander si l'utilisateur veut changer le type de l'épreuve
    printf("Faut-il changer le type d'épreuve de l'entrainement ?\n");
    color("32"); printf("1. Oui\n"); color("0");
    color("31"); printf("2. Non\n"); color("0");
    printf("Choix : ");
    scanf("%d", &changeChoice);
    printf("\n");
    while(changeChoice != 1 && changeChoice != 2){
        printf("Choix invalide. Veuillez entrer un choice valide.\n");
        printf("Faut-il changer le type d'épreuve de l'entrainement ?\n");
        color("32"); printf("1. Oui\n"); color("0");
        color("31"); printf("2. Non\n"); color("0");
        printf("Choix : ");
        scanf("%d", &changeChoice);
        printf("\n");
    }

    // Si l'utilisateur veut changer le type de l'épreuve, afficher la liste des épreuves et demander le choix
    if(changeChoice == 1){
        // Ouvrir le fichier nomEpreuve.txt
        FILE *raceFile = fopen(PATH"/Liste/nomEpreuve.txt", "r");
        if (raceFile == NULL) {
            printf("Impossible d'ouvrir le fichier nomEpreuve\n");
            return;
        }
        lines = countLine(raceFile);

        // Afficher la liste des épreuves et demander le choix de l'utilisateur
        rewind(raceFile);
        showRaceList(raceFile);
        printf("Choix : ");
        scanf("%d", &newRaceType);
        printf("\n");
        while (newRaceType < 1 || newRaceType > lines) {
            printf("Choix invalide. Veuillez choisir un numéro d'épreuve entre 1 et %d.\n", lines);
            printf("Choix : ");
            scanf("%d", &newRaceType);
            printf("\n");
        }

        // Si l'épreuve choisie est un relais, demander la position
        if(newRaceType == 5){
            printf("Position lors du relais : ");
            scanf("%d", &newTraining.position);
            printf("\n");
            while (newTraining.position < 1 || newTraining.position > 4){
                printf("Choix invalide. Veuillez choisir une position entre 1 et 4.\n");
                printf("Position lors du relais : ");
                scanf("%d", &newTraining.position);
                printf("\n");
            }
        } else {
            // Si l'épreuve n'est pas un relais, la position est 0
            newTraining.position = 0;
        }

        rewind(raceFile);
        // Lire le fichier race jusqu'à trouver l'épreuve choisie
        while (fgets(race, sizeof(race), raceFile)) {
            sscanf(race, "%d", &numRace); // Lire le numéro de l'épreuve
            race[strcspn(race, "\n")] = 0; // Supprimer le retour à la ligne

            if(numRace == newRaceType) {
                break;
            }
        }

        fclose(raceFile);
    } else {
        strcpy(race, training1.raceType); // Copier le type de l'épreuve actuelle si l'utilisateur ne veut pas le changer
    }

    // Demander si l'utilisateur veut changer le temps de l'entrainement
    printf("Faut-il changer la durée de l'entrainement ?\n");
    color("32"); printf("1. Oui\n"); color("0");
    color("31"); printf("2. Non\n"); color("0");
    printf("Choix : ");
    scanf("%d", &changeChoice);
    printf("\n");
    while(changeChoice != 1 && changeChoice != 2){
        printf("Choix invalide. Veuillez entrer un choice valide.\n");
        printf("Faut-il changer la durée de l'entrainement ?\n");
        color("32"); printf("1. Oui\n"); color("0");
        color("31"); printf("2. Non\n"); color("0");
        printf("Choix : ");
        scanf("%d", &changeChoice);
        printf("\n");
    }

    // Si l'utilisateur veut changer la durée de l'entrainement, demander les nouvelles valeurs
    if(changeChoice == 1){
        printf("Entrez la nouvelle durée de l'entrainement\n");
        printf("Heures : ");
        scanf("%d", &newHour);
        while(newHour < 0 || newHour > 23){
            printf("Heures : ");
            scanf("%d", &newHour);
        }

        printf("Minutes : ");
        scanf("%d", &newMinutes);
        while(newMinutes < 0 || newMinutes > 59){
            printf("Minutes : ");
            scanf("%d", &newMinutes);
        }
        printf("Secondes : ");
        scanf("%d", &newSeconds);
        while(newSeconds < 0 || newSeconds > 59){
            scanf("%d", &newSeconds);
        }
        printf("Millisecondes : ");
        scanf("%d", &newMs);
        while(newMs < 0 || newMs > 999){
            printf("Millisecondes : ");
            scanf("%d", &newMs);
        }
        printf("\n");
    } else {
        // Si l'utilisateur ne veut pas changer la durée de l'entrainement, copier les valeurs actuelles
        newHour = training1.athleteTime.hour;
        newMinutes = training1.athleteTime.minute;
        newSeconds = training1.athleteTime.second;
        newMs = training1.athleteTime.millisecond;
    }

    // Modification de l'entrainement
    FILE *tempFile = fopen(PATH"/Athletes/temp.txt", "w");
    if (tempFile == NULL) {
        printf("Impossible de créer le fichier temporaire\n");
        return;
    }

    fprintf(tempFile, "%s %s\n", name, lastname); // Écrire le prénom et le nom de l'athlète

    rewind(file);
    while (fgetc(file) != '\n'); // Sauter une line

    // Copie de toutes les lignes sauf celle à modifier
    count = 1;
    while (fscanf(file, "%d %d %d %s %d %d %d %d %d", &training1.trainingDate.day, &training1.trainingDate.month, &training1.trainingDate.year, training1.raceType, &training1.athleteTime.hour, &training1.athleteTime.minute, &training1.athleteTime.second, &training1.athleteTime.millisecond, &training1.position) != EOF) {
        if (count != trainingChoice) {
            fprintf(tempFile, "%d %d %d %s %d %d %d %d %d\n", training1.trainingDate.day, training1.trainingDate.month, training1.trainingDate.year, training1.raceType, training1.athleteTime.hour, training1.athleteTime.minute, training1.athleteTime.second, training1.athleteTime.millisecond, training1.position);
        } else if(count == trainingChoice) {
            fprintf(tempFile, "%d %d %d %s %d %d %d %d %d\n", newTraining.trainingDate.day, newTraining.trainingDate.month, newTraining.trainingDate.year, race + 2, newHour, newMinutes, newSeconds, newMs, training1.position);
        }
        count++;
    }

    fclose(file);
    fclose(tempFile);
    fclose(athleteFile);

    remove(completePath);  // Supprimez le fichier original
    rename(PATH"/Athletes/temp.txt", completePath);  // Renommez le fichier temporaire avec le prenom et nom du fichier original

    printf("Entrainement modifier avec succès.\n\n");

}

// Procédure principale pour ajouter, supprimer ou modifier un entrainement
void modifEntrainement(void) {
    int choice, athleteChoice;
    printf("1. Ajouter un entrainement\n");
    printf("2. Supprimer un entrainement\n");
    printf("3. Modifier un entrainement\n");
    color("31"); printf("4. Quitter\n"); color("0");
    printf("Choix : ");
    scanf("%d", &choice);
    printf("\n");

    switch (choice) {
        case 1:
            // Code pour ajouter un entrainement
            athleteChoice = makeAthleteChoice();
            addTraining(athleteChoice);
            break;
        case 2:
            // Code pour supprimer un entrainement
            removeTraining();
            break;
        case 3:
            // Code pour modifier un entrainement
            changeTraining();
            break;
        case 4:
            // Retourner au menu principal
            break;
        default:
            printf("Choix invalide.\n\n");
            modifEntrainement();
    }
}
