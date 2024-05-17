#ifndef HISTORIQUE_C
#define HISTORIQUE_C
#define MAX 100
#define CHEMIN "/Users/charly/Documents/École/Info/CER-JO"

int compterLignes(FILE *file) {
    int c;
    int lignes = 0;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            lignes++;
        }
    }
    return lignes;
}

void afficherNomAthlete(FILE *file) {
    char nomAthlete[MAX];
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
    for (int i = 0; i < lignes; i++) {
        printf("%d. ", i + 1);
        afficherNomAthlete(nomAthlete);
    }
}

void afficherNomEpreuve(FILE *nomEpreuve) {
    char epreuve[MAX];
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
    for (int i = 0; i < lignes; i++) {
        printf("%d. ", i + 1);
        afficherNomEpreuve(nomEpreuve);
    }
}

FILE *ouvrirFichierAthlete(int choixAthlete) {
    int numAthlete;
    char fileName[MAX];
    char nomAthlete[MAX];

    FILE *nomAthletes = fopen(CHEMIN"/Athletes/nomAthletes.txt", "r");
    if(nomAthletes == NULL){
        printf("Impossible d'ouvrir le fichier nomAthlete 2.\n");
        exit(1);
    }

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


void epreuveRelais(Entrainement entrainement1, FILE *file, int position) {
    rewind(file);

    // Sauter une ligne dans le fichier
    while (fgetc(file) != '\n');

    while (fscanf(file, "%d %d %d %s %d %d %d %d", &entrainement1.dateEntrainement.jour, &entrainement1.dateEntrainement.mois, &entrainement1.dateEntrainement.annee, entrainement1.typeEpreuve, &entrainement1.tempsAthlete.minute, &entrainement1.tempsAthlete.seconde, &entrainement1.tempsAthlete.milliseconde, &position) != EOF) {
        if(position == 0){
            continue;
        }else{
            if(position == 1) {
                printf("Position au relais :     %der coureur\n", position);
            } else if(position > 1) {
                printf("Position au relais :     %dème coureur\n", position);
            }
        }
        
    }

    

    fclose(file);
}

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
        printf("Date de l'entraînement : %d/%d/%d\n", entrainement1.dateEntrainement.jour, entrainement1.dateEntrainement.mois, entrainement1.dateEntrainement.annee);
        printf("Type d'épreuve :         %s\n", entrainement1.typeEpreuve);
        if(strcmp(entrainement1.typeEpreuve, "Relais") == 0){
            epreuveRelais(entrainement1, file, position);
        }
        printf("Temps de l'athlète :     %dmin %dsec %dms\n", entrainement1.tempsAthlete.minute, entrainement1.tempsAthlete.seconde, entrainement1.tempsAthlete.milliseconde);
        printf("\n");
    }

    // Fermeture du fichier
    fclose(file);
}

void afficherEntrainementTypeEpreuve(Entrainement entrainement1, int choixEpreuve) {
    char epreuve[MAX];
    int numEpreuve, position;

    FILE *nomEpreuve = fopen(CHEMIN"/Athletes/nomEpreuve.txt", "r");
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
    FILE *nomAthletes = fopen(CHEMIN"/Athletes/nomAthletes.txt", "r");
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
                if(strcmp(entrainement1.typeEpreuve, "Relais") == 0) {
                    epreuveRelais(entrainement1, file, position);
                }
                printf("Date de l'entraînement : %d/%d/%d\n", entrainement1.dateEntrainement.jour, entrainement1.dateEntrainement.mois, entrainement1.dateEntrainement.annee);
                printf("Temps de l'athlète :     %dmin %dsec %dms\n", entrainement1.tempsAthlete.minute, entrainement1.tempsAthlete.seconde, entrainement1.tempsAthlete.milliseconde);
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
    int jour, mois, annee, position;
    printf("Entrez la date (jj mm aaaa) : ");
    scanf("%d %d %d", &jour, &mois, &annee);
    printf("\n");

    while(jour < 1 || jour > 31 || mois < 1 || mois > 12 || annee < 2000 || annee > 2024) {
        printf("Date invalide. Veuillez entrer une date valide (jj mm aaaa) : ");
        scanf("%d %d %d", &jour, &mois, &annee);
        printf("\n");
    }

    FILE *nomAthletes = fopen(CHEMIN"/Athletes/nomAthletes.txt", "r");
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
            if (entrainement1.dateEntrainement.jour == jour && entrainement1.dateEntrainement.mois == mois && entrainement1.dateEntrainement.annee == annee) {
                printf("Athlète :                %s\n", nomAthlete + 2);
                printf("Type d'épreuve :         %s\n", entrainement1.typeEpreuve);
                if(strcmp(entrainement1.typeEpreuve, "Relais") == 0) {
                    epreuveRelais(entrainement1, file, i + 1);
                }
                printf("Temps de l'athlète :     %dmin %dsec %dms\n", entrainement1.tempsAthlete.minute, entrainement1.tempsAthlete.seconde, entrainement1.tempsAthlete.milliseconde);
                printf("\n");
                entrainementTrouve = 1;
            }
        }

        if (!entrainementTrouve) {
            printf("Aucun entraînement n'a été trouvé pour l'athlète %s à la date %d/%d/%d.\n\n", nomAthlete + 2, jour, mois, annee);
        }

        fclose(file);
    }

    fclose(nomAthletes);
}

void historiqueEntrainement(Entrainement entrainement1, FILE *file) {
    int choix, choixAthlete, choixEpreuve, lignes;

    FILE *nomAthlete = fopen(CHEMIN"/Athletes/nomAthletes.txt", "r");
    if(nomAthlete == NULL){
        printf("Impossible d'ouvrir le fichier nomAthlète.\n");
        exit(1);
    }

    FILE *nomEpreuve = fopen(CHEMIN"/Athletes/nomEpreuve.txt", "r");
    if(nomEpreuve == NULL){
        printf("Impossible d'ouvrir le fichier nomEpreuve.\n");
        exit(1);
    }

    printf("1. Voir par nom des Athlètes\n");
    printf("2. Voir par type d'épreuve\n");
    printf("3. Voir par date\n");
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
        default:
            printf("Choix invalide.\n");
            printf("\n");
            historiqueEntrainement(entrainement1, file);
    }
    
}

#endif // Historique_H
