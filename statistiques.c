#ifndef STATISTIQUES_C
#define STATISTIQUES_C
#include "def.c"


void afficherDiffTemps(int *choixAthlete, int *choixEpreuve, char epreuve[MAX]){
    int compteur = 0;

    // Ouvrir le fichier de l'athlète choisi
    FILE *fichierAthlete = ouvrirFichierAthlete(*choixAthlete);
    if(fichierAthlete == NULL){
        printf("Impossible d'ouvrir le fichier de l'athlète.\n");
        exit(1);
    }

    printf("Date où il a effectué le %s\n\n", epreuve + 2);

    int dateCount = 0, choixDate1, choixDate2, compteurEpreuve = 0;
    Date dates[MAX];

    //si l'épreuve est celle choisie alors afficher l'entrainement
    while (fgetc(fichierAthlete) != '\n');
    while (fscanf(fichierAthlete, "%d %d %d %s %d %d %d %d", &entrainement.dateEntrainement.jour, &entrainement.dateEntrainement.mois, &entrainement.dateEntrainement.annee, entrainement.typeEpreuve, &entrainement.tempsAthlete.minute, &entrainement.tempsAthlete.seconde, &entrainement.tempsAthlete.milliseconde, &entrainement.position) != EOF) {
        if (strcmp(entrainement.typeEpreuve, epreuve + 2) == 0) {
            //afficher les dates des entraînements disponibles pour l'épreuve choisie
            dates[dateCount++] = entrainement.dateEntrainement;
            compteurEpreuve++;
        }
    }

    if(compteurEpreuve == 0){
        printf("Aucun entraînement pour cette épreuve n'a été trouvé.\n");
        printf("Veuillez choisir une autre épreuve.\n\n");

        choisirEpreuve(choixEpreuve, epreuve);
        afficherDiffTemps(choixAthlete, choixEpreuve, epreuve);
    } else if (compteurEpreuve == 1) {
        printf("Il n'y a qu'un seul entraînement pour cette épreuve.\n");
        printf("Veuillez choisir une autre épreuve.\n\n");

        choisirEpreuve(choixEpreuve, epreuve);
        afficherDiffTemps(choixAthlete, choixEpreuve, epreuve);
    }

    // Trier les dates
    qsort(dates, dateCount, sizeof(Date), compareDates);

    // Afficher les dates triées
    for (int i = 0; i < dateCount; i++) {
        printf("%d. %02d/%02d/%04d\n", i + 1, dates[i].jour, dates[i].mois, dates[i].annee);
    }
    printf("\n");

    printf("Choix de la première date (entre 1 et %d) : ", dateCount-1);
    scanf("%d", &choixDate1);
    while(choixDate1 < 1 || choixDate1 > dateCount-1){
        printf("Choix invalide. Veuillez choisir un numéro de date entre 1 et %d.\n\n", dateCount-1);
        printf("Choix de la première date (entre 1 et %d) : ", dateCount-1);
        scanf("%d", &choixDate1);
    }

    printf("Choix de la deuxième date (entre %d et %d) : ", choixDate1+1, dateCount);
    scanf("%d", &choixDate2);
    while(choixDate2 < choixDate1+1 || choixDate2 > dateCount){
        printf("Choix invalide. Veuillez choisir un numéro de date entre %d et %d.\n\n", choixDate1+1, dateCount);
        printf("Choix de la deuxième date (entre %d et %d) : ", choixDate1+1, dateCount);
        scanf("%d", &choixDate2);
    }

    //appliquer entrainement1 avec choixDate1 et entrainement2 avec choixDate2
    rewind(fichierAthlete);
    while (fgetc(fichierAthlete) != '\n');

    Entrainement entrainement1, entrainement2;

    while (fscanf(fichierAthlete, "%d %d %d %s %d %d %d %d", &entrainement.dateEntrainement.jour, &entrainement.dateEntrainement.mois, &entrainement.dateEntrainement.annee, entrainement.typeEpreuve, &entrainement.tempsAthlete.minute, &entrainement.tempsAthlete.seconde, &entrainement.tempsAthlete.milliseconde, &entrainement.position) != EOF) {
        if (strcmp(entrainement.typeEpreuve, epreuve + 2) == 0) {
            if (entrainement.dateEntrainement.jour == dates[choixDate1 - 1].jour && entrainement.dateEntrainement.mois == dates[choixDate1 - 1].mois && entrainement.dateEntrainement.annee == dates[choixDate1 - 1].annee) {
                entrainement1 = entrainement;
                compteur++;
            } else if (entrainement.dateEntrainement.jour == dates[choixDate2 - 1].jour && entrainement.dateEntrainement.mois == dates[choixDate2 - 1].mois && entrainement.dateEntrainement.annee == dates[choixDate2 - 1].annee) {
                entrainement2 = entrainement;
                compteur++;
            }
        }
    }

    if (compteur < 2) {
        exit(1);
    }

    printf("\nEntraînement du %02d/%02d/%04d\n", entrainement1.dateEntrainement.jour, entrainement1.dateEntrainement.mois, entrainement1.dateEntrainement.annee);
    printf("Temps de l'athlète : %02dmin %02dsec %03dms\n", entrainement1.tempsAthlete.minute, entrainement1.tempsAthlete.seconde, entrainement1.tempsAthlete.milliseconde);
    if(entrainement1.position != 0){
        if(entrainement1.position == 1){
           printf("Position au relais : %der coureur\n", entrainement1.position);
        } else {
            printf("Position au relais : %dème coureur\n", entrainement1.position);
        }
    }

    printf("\nEntraînement du %02d/%02d/%04d\n", entrainement2.dateEntrainement.jour, entrainement2.dateEntrainement.mois, entrainement2.dateEntrainement.annee);
    printf("Temps de l'athlète : %02dmin %02dsec %03dms\n", entrainement2.tempsAthlete.minute, entrainement2.tempsAthlete.seconde, entrainement2.tempsAthlete.milliseconde);
    if(entrainement2.position != 0){
        if(entrainement2.position == 1){
            printf("Position au relais : %der coureur\n", entrainement2.position);
        } else {
            printf("Position au relais : %dème coureur\n", entrainement2.position);
        }
    }
    printf("\n");

    int tempsEnMillisecondes1 = entrainement1.tempsAthlete.minute * 60000 + entrainement1.tempsAthlete.seconde * 1000 + entrainement1.tempsAthlete.milliseconde;
    int tempsEnMillisecondes2 = entrainement2.tempsAthlete.minute * 60000 + entrainement2.tempsAthlete.seconde * 1000 + entrainement2.tempsAthlete.milliseconde;
    int differenceTemps = tempsEnMillisecondes2 - tempsEnMillisecondes1;

    int minutes = abs(differenceTemps / 60000);
    int secondes = abs((differenceTemps % 60000) / 1000);
    int millisecondes = abs((differenceTemps % 60000) % 1000);

    if(differenceTemps < 0){
        printf("L'athlète a progressé de %02dmin %02dsec %03dms\n", minutes, secondes, millisecondes);
        exit(1);
    } else if(differenceTemps > 0){
        printf("L'athlète a régressé de %02dmin %02dsec %03dms\n", minutes, secondes, millisecondes);
        exit(1);
    } else {
        printf("L'athlète a gardé le même temps\n");
        exit(1);
    }

    fclose(fichierAthlete);
}

int moyenneTemps(FILE *athlete, char typeEpreuve[MAX]){
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

    return moyenneTemps;
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
        printf("Date de l'entraînement : %02d/%02d/%04d\n", pireEntrainement.dateEntrainement.jour, pireEntrainement.dateEntrainement.mois, pireEntrainement.dateEntrainement.annee);
        printf("Temps de l'athlète :     %02dmin %02dsec %03dms\n", pireEntrainement.tempsAthlete.minute, pireEntrainement.tempsAthlete.seconde, pireEntrainement.tempsAthlete.milliseconde);
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
        printf("Date de l'entraînement : %02d/%02d/%04d\n", meilleurEntrainement.dateEntrainement.jour, meilleurEntrainement.dateEntrainement.mois, meilleurEntrainement.dateEntrainement.annee);
        printf("Temps de l'athlète :     %02dmin %02dsec %03dms\n", meilleurEntrainement.tempsAthlete.minute, meilleurEntrainement.tempsAthlete.seconde, meilleurEntrainement.tempsAthlete.milliseconde);
        if(meilleurEntrainement.position != 0){
            if(meilleurEntrainement.position == 1){
                printf("Position au relais :     %der coureur\n", meilleurEntrainement.position);
            } else {
                printf("Position au relais :     %dème coureur\n", meilleurEntrainement.position);
            }
        }
        printf("\n");
    }
}

void resumerEntrainement() {
    int choixAthlete, lignes, choixEpreuve, numEpreuve;
    char epreuve[MAX];
    // Ouvrir le fichier de tous les athlètes
    FILE *nomAthletes = fopen(CHEMIN"/Liste/nomAthletes.txt", "r");
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


    FILE *nomEpreuve = fopen(CHEMIN"/Liste/nomEpreuve.txt", "r");
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
    int moyenne = moyenneTemps(fichierAthlete, epreuve + 2);
    if (moyenne == 0) {
        printf("Aucun entraînement de ce type n'a été trouvé.\n");
    } else {
        printf("Moyenne temps pour %s :\n", epreuve + 2);
        printf("Moyenne de l'athlète :   %02dmin %02dsec %03dms\n", moyenne/60000, (moyenne % 60000)/1000, (moyenne % 1000));
        printf("\n");
    }

    fclose(nomAthletes);
    fclose(nomEpreuve);
}

void quiAuJO(){
    int lignes, choixEpreuve;
    // Code pour déterminer qui envoyer aux Jeux Olympiques
    FILE *nomEpreuve = fopen(CHEMIN"/Liste/nomEpreuve.txt", "r");
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
    char epreuve[MAX];
    while (fgets(epreuve, sizeof(epreuve), nomEpreuve)) {
        int numEpreuve;
        sscanf(epreuve, "%d", &numEpreuve);
        epreuve[strcspn(epreuve, "\n")] = 0;

        if(numEpreuve == choixEpreuve) {
            break;
        }
    }

    // Ouvrir le fichier de tous les athlètes
    FILE *nomAthletes = fopen(CHEMIN"/Liste/nomAthletes.txt", "r");
    if(nomAthletes == NULL){
        printf("Impossible d'ouvrir le fichier nomAthlètes.\n");
        exit(1);
    }
    lignes = compterLignes(nomAthletes);

    rewind(nomAthletes);
    //mettre le nom des athlètes dans un tableau
    char athletes[MAX][MAX];
    for(int i = 0; i < lignes; i++){
        fseek(nomAthletes, 2, SEEK_CUR); // Sauter le numéro de l'athlète
        fgets(athletes[i], sizeof(athletes[i]), nomAthletes);
        athletes[i][strcspn(athletes[i], "\n")] = 0;
    }
    
    //mettre moyenne temps de chaque athlète dans un tableau
    int moyennes[MAX];
    for(int i = 0; i < lignes; i++){
        FILE *fichierAthlete = ouvrirFichierAthlete(i+1);
        moyennes[i] = moyenneTemps(fichierAthlete, epreuve + 2);
        fclose(fichierAthlete);
    }

    // Afficher les 3 meilleurs moyennes
    MoyenneIndex moyennesIndex[lignes];
    for(int i = 0; i < lignes; i++){
        moyennesIndex[i].moyenne = moyennes[i];
        moyennesIndex[i].index = i;
    }

    qsort(moyennesIndex, lignes, sizeof(MoyenneIndex), comparer);

    printf("\nLes 3 meilleurs moyennes pour le %s sont :\n", epreuve + 2);

    printf("%s  %s avec une moyenne de %02dmin %02dsec %03dms\n", "🥇", athletes[moyennesIndex[0].index], moyennes[moyennesIndex[0].index]/60000, (moyennes[moyennesIndex[0].index] % 60000)/1000, (moyennes[moyennesIndex[0].index] % 1000));
    printf("%s  %s avec une moyenne de %02dmin %02dsec %03dms\n", "🥈", athletes[moyennesIndex[1].index], moyennes[moyennesIndex[1].index]/60000, (moyennes[moyennesIndex[1].index] % 60000)/1000, (moyennes[moyennesIndex[1].index] % 1000));
    printf("%s  %s avec une moyenne de %02dmin %02dsec %03dms\n", "🥉", athletes[moyennesIndex[2].index], moyennes[moyennesIndex[2].index]/60000, (moyennes[moyennesIndex[2].index] % 60000)/1000, (moyennes[moyennesIndex[2].index] % 1000));

}

void statistiqueAthlete(Entrainement entrainement1, FILE *file) {
    // Code pour consulter des statistiques de performances de chaque athlète
    int choix, choixAthlete, choixEpreuve;
    char epreuve[MAX];

    printf("1. Consulter un résumer des statistiques de performances d'un athlète\n");
    printf("2. Qui envoyer au Jeux Olympiques\n");
    printf("3. Progression de l'athlète\n");
    couleur("31"); printf("4. Quitter\n"); couleur("0");
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
            quiAuJO();
            break;
        case 3:
            // Code pour afficher la progression de l'athlète
            choisirAthlete(&choixAthlete);
            choisirEpreuve(&choixEpreuve, epreuve);
            afficherDiffTemps(&choixAthlete, &choixEpreuve, epreuve);
            break;
        case 4:
            // Code pour retourner au début du programme
            
            break;
        default:
            printf("Choix invalide.\n");
            statistiqueAthlete(entrainement1, file);
    }
}

#endif
