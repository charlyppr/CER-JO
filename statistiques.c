#ifndef STATISTIQUES_C
#define STATISTIQUES_C

#define INT_MAX 1000000000
#define INT_MIN 1
#define MAX 100

Entrainement entrainement;


void afficherDiffTempsEpreuve() {
    int choixAthlete, lignes, choixEpreuve, numEpreuve;
    Date dateEntrainement1, dateEntrainement2;
    char epreuve[MAX];
    // Ouvrir le fichier de tous les athlètes
    FILE *nomAthletes = fopen("/workspaces/CER-JO/Athletes/nomAthletes.txt", "r");
    if(nomAthletes == NULL){
        printf("Impossible d'ouvrir le fichier nomAthletes.\n");
        exit(1);
    }

    afficherListeAthlete(nomAthletes);
    printf("Choix : ");
    scanf("%d", &choixAthlete);
    printf("\n");

    rewind(nomAthletes);
    lignes = compterLignes(nomAthletes);

    while (choixAthlete < 1 || choixAthlete > lignes) {
        printf("Choix invalide. Veuillez choisir un numéro d'athlète entre 1 et %d.\n", lignes);
        printf("Choix : ");
        scanf("%d", &choixAthlete);
        printf("\n");
    }

    // Ouvrir le fichier de l'athlète choisi
    FILE *fichierAthlete = ouvrirFichierAthlete(choixAthlete);
    if(fichierAthlete == NULL){
        printf("Impossible d'ouvrir le fichier de l'athlète.\n");
        exit(1);
    }


    FILE *nomEpreuve = fopen("/workspaces/CER-JO/Athletes/nomEpreuve.txt", "r");
    if(nomEpreuve == NULL){
        printf("Impossible d'ouvrir le fichier nomEpreuve.\n");
        exit(1);
    }

    afficherListeEpreuve(nomEpreuve);
    printf("Choix : ");
    scanf("%d", &choixEpreuve);
    printf("\n");

    rewind(nomEpreuve);
    lignes = compterLignes(nomEpreuve);

    while (choixEpreuve < 1 || choixEpreuve > lignes) {
        printf("Choix invalide. Veuillez choisir un numéro d'épreuve entre 1 et %d.\n", lignes);
        printf("Choix : ");
        scanf("%d", &choixEpreuve);
        printf("\n");
    }

    rewind(nomEpreuve);
    while (fgets(epreuve, sizeof(epreuve), nomEpreuve)) {
        sscanf(epreuve, "%d", &numEpreuve);
        epreuve[strcspn(epreuve, "\n")] = 0;

        if(numEpreuve == choixEpreuve) {
            break;
        }
    }

    printf("La date du premier entraînement (jj mm aaaa) : ");
    scanf("%d %d %d", &dateEntrainement1.jour, &dateEntrainement1.mois, &dateEntrainement1.annee);
    printf("La date du deuxième entraînement (jj mm aaaa) : ");
    scanf("%d %d %d", &dateEntrainement2.jour, &dateEntrainement2.mois, &dateEntrainement2.annee);

    switch (choixEpreuve) {
        case 1:
            // Code pour afficher la différence de temps entre deux entraînements pour 100m
            break;

        case 2:
            // Code pour afficher la différence de temps entre deux entraînements pour 400m
            break;
        case 3:
            // Code pour afficher la différence de temps entre deux entraînements pour 5000m
            break;
        case 4:
            // Code pour afficher la différence de temps entre deux entraînements pour Marathon
            break;
        case 5:
            // Code pour afficher la différence de temps entre deux entraînements pour Relais 4x400m
            break;
        default:
            printf("Choix invalide.\n");
            afficherDiffTempsEpreuve();
    }
}


void moyenneTemps(FILE *athlete, char typeEpreuve[MAX]){
    // Code pour afficher le meilleur temps de l'athlète pour une épreuve donnée
    int moyenneTemps = 0; 
    int compteur = 0;

    rewind(athlete);
    while (fgetc(athlete) != '\n');

    while (fscanf(athlete, "%d %d %d %s %d %d %d %d", &entrainement.dateEntrainement.jour, &entrainement.dateEntrainement.mois, &entrainement.dateEntrainement.annee, entrainement.typeEpreuve, &entrainement.tempsAthlete.minute, &entrainement.tempsAthlete.seconde, &entrainement.tempsAthlete.milliseconde, &entrainement.position) != EOF) {
        if (strcmp(entrainement.typeEpreuve, typeEpreuve) == 0) {
            int tempsEnMillisecondes = entrainement.tempsAthlete.minute * 60000 + entrainement.tempsAthlete.seconde * 1000 + entrainement.tempsAthlete.milliseconde;

            moyenneTemps += tempsEnMillisecondes;
            compteur++;
        }
    }

    moyenneTemps = moyenneTemps/compteur;

    if (moyenneTemps == 0) {
        printf("Aucun entraînement de ce type n'a été trouvé.\n");
    } else {
        printf("Moyenne temps pour %s :\n", typeEpreuve);
        printf("Moyenne de l'athlète :   %dmin %dsec %dms\n", moyenneTemps/60000, (moyenneTemps % 60000)/1000, (moyenneTemps % 1000));
        printf("\n");
    }
}

void pireTemps(FILE *athlete, char typeEpreuve[MAX]){
    // Code pour afficher le meilleur temps de l'athlète pour une épreuve donnée
    int pireTemps = INT_MIN; // INT_MAX est la valeur la plus élevée qu'un int peut avoir
    Entrainement pireEntrainement;

    rewind(athlete);
    while (fgetc(athlete) != '\n');

    while (fscanf(athlete, "%d %d %d %s %d %d %d %d", &entrainement.dateEntrainement.jour, &entrainement.dateEntrainement.mois, &entrainement.dateEntrainement.annee, entrainement.typeEpreuve, &entrainement.tempsAthlete.minute, &entrainement.tempsAthlete.seconde, &entrainement.tempsAthlete.milliseconde, &entrainement.position) != EOF) {
        if (strcmp(entrainement.typeEpreuve, typeEpreuve) == 0) {
            int tempsEnMillisecondes = entrainement.tempsAthlete.minute * 60000 + entrainement.tempsAthlete.seconde * 1000 + entrainement.tempsAthlete.milliseconde;

            if (tempsEnMillisecondes > pireTemps) {
                pireTemps = tempsEnMillisecondes;
                pireEntrainement = entrainement;
            }
        }
    }

    if (pireTemps == INT_MIN) {
        printf("Aucun entraînement de ce type n'a été trouvé.\n");
        exit(1);

    } else {
        printf("Pire temps pour %s :\n", typeEpreuve);
        printf("Date de l'entraînement : %d/%d/%d\n", pireEntrainement.dateEntrainement.jour, pireEntrainement.dateEntrainement.mois, pireEntrainement.dateEntrainement.annee);
        printf("Temps de l'athlète :     %dmin %dsec %dms\n", pireEntrainement.tempsAthlete.minute, pireEntrainement.tempsAthlete.seconde, pireEntrainement.tempsAthlete.milliseconde);
        if(pireEntrainement.position != 0){
            if(pireEntrainement.position == 1){
                printf("Position au relais :     %der coureur\n", pireEntrainement.position);
            } else {
                printf("Position au relais :     %dème coureur\n", pireEntrainement.position);
            }
        }
        printf("\n");
    }
}

void meilleurTemps(FILE *athlete, char typeEpreuve[MAX]){
    // Code pour afficher le meilleur temps de l'athlète pour une épreuve donnée
    int meilleurTemps = INT_MAX; // INT_MAX est la valeur la plus élevée qu'un int peut avoir
    Entrainement meilleurEntrainement;

    rewind(athlete);
    while (fgetc(athlete) != '\n');

    while (fscanf(athlete, "%d %d %d %s %d %d %d %d", &entrainement.dateEntrainement.jour, &entrainement.dateEntrainement.mois, &entrainement.dateEntrainement.annee, entrainement.typeEpreuve, &entrainement.tempsAthlete.minute, &entrainement.tempsAthlete.seconde, &entrainement.tempsAthlete.milliseconde, &entrainement.position) != EOF) {
        if (strcmp(entrainement.typeEpreuve, typeEpreuve) == 0) {
            int tempsEnMillisecondes = entrainement.tempsAthlete.minute * 60000 + entrainement.tempsAthlete.seconde * 1000 + entrainement.tempsAthlete.milliseconde;

            if (tempsEnMillisecondes < meilleurTemps) {
                meilleurTemps = tempsEnMillisecondes;
                meilleurEntrainement = entrainement;
            }
        }
    }

    if (meilleurTemps == INT_MAX) {
        printf("Aucun entraînement de ce type n'a été trouvé.\n");
        exit(1);

    } else {
        printf("Meilleur temps pour %s :\n", typeEpreuve);
        printf("Date de l'entraînement : %d/%d/%d\n", meilleurEntrainement.dateEntrainement.jour, meilleurEntrainement.dateEntrainement.mois, meilleurEntrainement.dateEntrainement.annee);
        printf("Temps de l'athlète :     %dmin %dsec %dms\n", meilleurEntrainement.tempsAthlete.minute, meilleurEntrainement.tempsAthlete.seconde, meilleurEntrainement.tempsAthlete.milliseconde);
        printf("\n");
    }
}

void resumerEntrainement() {
    int choixAthlete, lignes, choixEpreuve, numEpreuve;
    char epreuve[MAX];
    // Ouvrir le fichier de tous les athlètes
    FILE *nomAthletes = fopen("/workspaces/CER-JO/Athletes/nomAthletes.txt", "r");
    if(nomAthletes == NULL){
        printf("Impossible d'ouvrir le fichier nomAthlètes.\n");
        exit(1);
    }

    afficherListeAthlete(nomAthletes);
    printf("Choix : ");
    scanf("%d", &choixAthlete);
    printf("\n");

    rewind(nomAthletes);
    lignes = compterLignes(nomAthletes);

    while (choixAthlete < 1 || choixAthlete > lignes) {
        printf("Choix invalide. Veuillez choisir un numéro d'athlète entre 1 et %d.\n", lignes);
        printf("Choix : ");
        scanf("%d", &choixAthlete);
        printf("\n");
    }

    // Ouvrir le fichier de l'athlète choisi
    FILE *fichierAthlete = ouvrirFichierAthlete(choixAthlete);
    if(fichierAthlete == NULL){
        printf("Impossible d'ouvrir le fichier de l'athlète.\n");
        exit(1);
    }


    FILE *nomEpreuve = fopen("/workspaces/CER-JO/Athletes/nomEpreuve.txt", "r");
    if(nomEpreuve == NULL){
        printf("Impossible d'ouvrir le fichier nomEpreuve.\n");
        exit(1);
    }

    afficherListeEpreuve(nomEpreuve);
    printf("Choix : ");
    scanf("%d", &choixEpreuve);
    printf("\n");

    rewind(nomEpreuve);
    lignes = compterLignes(nomEpreuve);

    while (choixEpreuve < 1 || choixEpreuve > lignes) {
        printf("Choix invalide. Veuillez choisir un numéro d'épreuve entre 1 et %d.\n", lignes);
        printf("Choix : ");
        scanf("%d", &choixEpreuve);
        printf("\n");
    }

    rewind(nomEpreuve);
    while (fgets(epreuve, sizeof(epreuve), nomEpreuve)) {
        sscanf(epreuve, "%d", &numEpreuve);
        epreuve[strcspn(epreuve, "\n")] = 0;

        if(numEpreuve == choixEpreuve) {
            break;
        }
    }


    meilleurTemps(fichierAthlete, epreuve + 2);
    pireTemps(fichierAthlete, epreuve + 2);
    moyenneTemps(fichierAthlete, epreuve + 2);

    fclose(nomAthletes);
    fclose(nomEpreuve);
}

void statistiqueAthlete(Entrainement entrainement1, FILE *file) {
    // Code pour consulter des statistiques de performances de chaque athlète
    int choix;
    printf("1. Consulter un résumer des statistiques de performances d'un athlète\n");
    printf("2. Qui envoyer au Jeux Olympiques\n");
    printf("3. Progression de l'athlète\n");
    printf("Choix : ");
    scanf("%d", &choix);
    printf("\n");

    switch (choix) {
        case 1:
            // Code pour consulter les statistiques de performances d'un athlète
            resumerEntrainement();
            break;
        case 2:
            // Code pour déterminer qui envoyer aux Jeux Olympiques
            break;
        case 3:
            // Code pour afficher la progression de l'athlète
            
            afficherDiffTempsEpreuve();
            break;
        default:
            printf("Choix invalide.\n");
            statistiqueAthlete(entrainement1, file);
    }
}

#endif
