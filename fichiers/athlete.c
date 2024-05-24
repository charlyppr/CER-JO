#include "../headers/athlete.h"
#include "../headers/entrainement.h"

int lastNumberAthlete(void){
    int lastNumber = 0;
    char line[MAX];
    FILE *athletesFile = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if (athletesFile != NULL) {
        while (fgets(line, sizeof(line), athletesFile) != NULL) {
            sscanf(line, "%d", &lastNumber);
        }
        fclose(athletesFile);
    }
    return lastNumber;
}

void addAthlete(void){
    char name[MAX/2], lastname[MAX/2];
    int lastNumber = lastNumberAthlete();
    char completePath[MAX];

    FILE *athletesFile = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if (athletesFile == NULL) {
        printf("Erreur d'ouverture du fichier nomAthletes.txt\n");
        return;
    }

    int number;
    char existingName[50], existingLastname[50];

    while (1) {
        printf("Entrez le prénom de l'athlète : ");
        scanf("%s", name);

        // Mettre la première lettre du prénom en majuscule
        if (name[0] >= 'a' && name[0] <= 'z') {
            name[0] = name[0] - 32;
        }

        printf("Entrez le nom de l'athlète : ");
        scanf("%s", lastname);

        // Mettre la première lettre du lastname en majuscule
        if (lastname[0] >= 'a' && lastname[0] <= 'z') {
            lastname[0] = lastname[0] - 32;
        }

        int alreadyExist = 0;
        rewind(athletesFile);
        while (fscanf(athletesFile, "%d %s %s", &number, existingName, existingLastname) != EOF) {
            if (strcmp(name, existingName) == 0 && strcmp(lastname, existingLastname) == 0) {
                alreadyExist = 1;
                break;
            }
        }

        if (alreadyExist) {
            printf("\nL'athlète %s %s existe déjà. Veuillez entrer un autre prénom et nom.\n", name, lastname);
        } else {
            break;
        }
    }

    fclose(athletesFile);

    sprintf(completePath, "%s/Athletes/%s %s.txt", PATH, name, lastname);

    FILE *file = fopen(completePath, "w");
    if (file == NULL) {
        printf("Impossible de créer le fichier %s\n", completePath);
        return;
    }
    fprintf(file, "%s %s\n", name, lastname);

    fclose(file);

    athletesFile = fopen(PATH"/Liste/nomAthletes.txt", "a");
    if (athletesFile != NULL) {
        fprintf(athletesFile, "%d %s %s\n", lastNumber + 1, name, lastname);
        fclose(athletesFile);
    }

    printf("\nL'athlète %s %s a été créé avec succès.\n", name, lastname);
}

void removeAthlete(void){
    int athleteNumber, choice, count = 1, number;
    char name[MAX/2], lastname[MAX/2];
    char newName[MAX/2], newLastname[MAX/2];
    char fileName[MAX];
    char completePath[MAX];

    FILE *athletesFile = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if (athletesFile == NULL) {
        printf("Impossible d'ouvrir le fichier nomAthletes\n");
        return;
    }
    int lignes = countLine(athletesFile);

    rewind(athletesFile);
    showAthleteList(athletesFile);
    printf("Choix : ");
    scanf("%d", &athleteNumber);
    printf("\n");
    while(athleteNumber < 1 || athleteNumber > lignes){
        printf("Choix invalide. Entrez un nombre entre 1 et %d.\n", lignes);
        printf("Choix : ");
        scanf("%d", &athleteNumber);
        printf("\n");
    }


    rewind(athletesFile);
    while (fscanf(athletesFile, "%d %s %s", &number, name, lastname) != EOF) {
        if(number == athleteNumber){
            sprintf(fileName, "%s %s.txt", name, lastname);
            break;
        }
    }
    printf("Êtes-vous sûr de vouloir supprimer l'athlète %s %s ?\n", name, lastname);
    color("32"); printf("1. Oui\n"); color("0");
    color("31"); printf("2. Non\n"); color("0");
    printf("Choix : ");
    scanf("%d", &choice);
    printf("\n");
    if(choice == 2){
        return;
    }

    FILE *newFile = fopen(PATH"/Liste/nomAthletesTemp.txt", "w");
    if (newFile == NULL) {
        printf("Impossible de créer le fichier temporaire\n");
        fclose(athletesFile);
        return;
    }

    rewind(athletesFile);
    while (fscanf(athletesFile, "%d %s %s", &number, name, lastname) != EOF) {
        if (number != athleteNumber) {
            fprintf(newFile, "%d %s %s\n", count, name, lastname);
            count++;
        }
        else{
            strcpy(newName, name);
            strcpy(newLastname, lastname);
        }
    }

    fclose(athletesFile);
    fclose(newFile);

    sprintf(completePath, "%s/Athletes/%s", PATH, fileName);

    remove(completePath);
    remove(PATH"/Liste/nomAthletes.txt");
    rename(PATH"/Liste/nomAthletesTemp.txt", PATH"/Liste/nomAthletes.txt");

    printf("L'athlète %s %s a été supprimé avec succès.\n\n", newName, newLastname);
}

void changeAthlete(void){
    int athleteNumber, number, count = 1, choice;
    char line[MAX];
    char name[MAX/2], lastname[MAX/2];
    char newName[MAX/2], newLastname[MAX/2];
    char fileName[MAX];
    char completePath[MAX];

    athleteNumber = makeAthleteChoice();
    FILE *athleteName = openAthleteFile(athleteNumber);
    if (athleteName == NULL) {
        printf("Impossible d'ouvrir le fichier Athlete\n");
        return;
    }

    fgets(line, sizeof(line), athleteName);
    sscanf(line, "%s %s", name, lastname);

    fclose(athleteName);

    printf("Faut-il modifier le prénom de l'athlète ?\n");
    color("32"); printf("1. Oui\n"); color("0");
    color("31"); printf("2. Non\n"); color("0");
    printf("Choix : ");
    scanf("%d", &choice);
    printf("\n");

    if (choice == 1) {
        // Code pour modifier un athlète
        printf("Quel est le nouveau prénom de l'athlète ? ");
        scanf("%s", newName);
        if(newName[0] >= 'a' && newName[0] <= 'z'){
            newName[0] = newName[0] - 32;
        }
        printf("\n");
    } else if(choice < 1 || choice > 2){
        printf("Choix invalide.\n");
        printf("Quel est le nouveau prénom de l'athlète ? ");
        scanf("%s", newName);
        if(newName[0] >= 'a' && newName[0] <= 'z'){
            newName[0] = newName[0] - 32;
        }
        printf("\n");
    } else {
        strcpy(newName, name);
    }

    printf("Faut-il modifier le nom de l'athlète ?\n");
    color("32"); printf("1. Oui\n"); color("0");
    color("31"); printf("2. Non\n"); color("0");
    printf("Choix : ");
    scanf("%d", &choice);
    printf("\n");

    if (choice == 1) {
        // Code pour modifier un athlète
        printf("Quel est le nouveau nom de l'athlète ? ");
        scanf("%s", newLastname);
        if(newLastname[0] >= 'a' && newLastname[0] <= 'z'){
            newLastname[0] = newLastname[0] - 32;
        }
        printf("\n");
    } else if(choice < 1 || choice > 2){
        printf("Choix invalide.\n");
        printf("Quel est le nouveau nom de l'athlète ? ");
        scanf("%s", newLastname);
        if(newLastname[0] >= 'a' && newLastname[0] <= 'z'){
            newLastname[0] = newLastname[0] - 32;
        }
        printf("\n");
    } else {
        strcpy(newLastname, lastname);
    }

    sprintf(fileName, "%s/Athletes/%s %s.txt", PATH, newName, newLastname);

    FILE *athletesFile = fopen(PATH"/Liste/nomAthletes.txt", "r");
    if (athletesFile == NULL) {
        printf("Impossible d'ouvrir le fichier nomAthletes\n");
        return;
    }

    FILE *newFile = fopen(PATH"/Liste/nomAthletesTemp.txt", "w");
    if (newFile == NULL) {
        printf("Impossible de créer le fichier temporaire\n");
        return;
    }

    rewind(athletesFile);
    while (fscanf(athletesFile, "%d %s %s", &number, name, lastname) != EOF) {
        if (number == athleteNumber) {
            fprintf(newFile, "%d %s %s\n", count, newName, newLastname);
            sprintf(completePath, "%s/Athletes/%s %s.txt", PATH, name, lastname);
            count++;
        } else {
            fprintf(newFile, "%d %s %s\n", count, name, lastname);
            count++;
        }
    }

    fclose(athletesFile);
    fclose(newFile); 

    FILE *AthleteTemp = fopen(PATH"/Athletes/AthletesTemp.txt", "w");
    if (AthleteTemp == NULL) {
        printf("Impossible de créer le fichier temporaire\n");
        fclose(athletesFile);
        return;
    }

    FILE *Athlete = openAthleteFile(athleteNumber);
    if (Athlete == NULL) {
        printf("Impossible d'ouvrir le fichier Athlete\n");
        fclose(athletesFile);
        return;
    }

    // recopier le nouveau name et lastname dans le fichier temporaire
    fprintf(AthleteTemp, "%s %s\n", newName, newLastname);

    while (fgetc(Athlete) != '\n');
    // recopier le reste du fichier Athlete dans le fichier temporaire
    while (fgets(line, sizeof(line), Athlete) != NULL) {
        fprintf(AthleteTemp, "%s", line);
    }

    fclose(Athlete);
    fclose(AthleteTemp);

    remove(completePath);
    remove(PATH"/Liste/nomAthletes.txt");
    rename(PATH"/Liste/nomAthletesTemp.txt", PATH"/Liste/nomAthletes.txt");
    rename(PATH"/Athletes/AthletesTemp.txt", fileName);

    printf("L'athlète %s %s a été modifié avec succès.\n\n", newName, newLastname);

}

void modifAthlete(void) {
    int choice, lastNumber = lastNumberAthlete();

    printf("1. Créer un nouvel athlète\n");
    printf("2. Supprimer un athlète\n");
    printf("3. Modifier un athlète\n");
    color("31"); printf("4. Quitter\n"); color("0");
    printf("Choix : ");
    scanf("%d", &choice);
    printf("\n");

    switch (choice) {
        case 1:
            // Code pour ajouter un athlète
            addAthlete();

            printf("\nVoulez-vous ajouter un entrainement pour cet athlète ?\n");
            color("32"); printf("1. Oui\n"); color("0");
            color("31"); printf("2. Non\n"); color("0");
            printf("Choix : ");
            scanf("%d", &choice);
            printf("\n");

            if (choice == 1) {
                addTraining(lastNumber + 1);
            }
            else {
                return;
            }

            break;
        case 2:
            // Code pour supprimer un athlète
            removeAthlete();
            break;
        case 3:
            // Code pour modifier un athlète
            changeAthlete();
            break;
        case 4:
            break;
        default:
            printf("Choix invalide.\n\n");
            modifAthlete();
    }
    
}
