#ifndef ENTRAINEMENT_C
#define ENTRAINEMENT_C
#include "def.c"

void ajouterEntrainement() {
    int choixAthlete, choixEpreuve, numEpreuve, positionRelais;
    int minutes, secondes, ms;
    char epreuve[MAX];
    Date date;

    FILE *fichierAthletes = fopen(CHEMIN"/Liste/nomAthletes.txt", "r");
    if (fichierAthletes == NULL) {
        printf("Impossible d'ouvrir le fichier nomAthletes\n");
        return;
    }
    afficherListeAthlete(fichierAthletes);
    printf("Choix : ");
    scanf("%d", &choixAthlete);
    printf("\n");

    FILE *fichierEpreuves = fopen(CHEMIN"/Liste/nomEpreuve.txt", "r");
    if (fichierEpreuves == NULL) {
        printf("Impossible d'ouvrir le fichier nomEpreuve\n");
        return;
    }

    afficherListeEpreuve(fichierEpreuves);
    printf("Choix : ");
    scanf("%d", &choixEpreuve);
    printf("\n");
    if(choixEpreuve == 5){
        printf("Position lors du relais : ");
        scanf("%d", &positionRelais);
        while (positionRelais < 1 || positionRelais > 4){
            printf("Position lors du relais : ");
            scanf("%d", &positionRelais);
        }
    } else {
        positionRelais = 0;
    }

    rewind(fichierEpreuves);
    // Lire le fichier epreuves jusqu'à trouver l'épreuve choisie
    while (fgets(epreuve, sizeof(epreuve), fichierEpreuves)) {
        sscanf(epreuve, "%d", &numEpreuve);
        epreuve[strcspn(epreuve, "\n")] = 0;

        if(numEpreuve == choixEpreuve) {
            break;
        }
    }

    fclose(fichierAthletes);
    fclose(fichierEpreuves);

    printf("Entrez la date de l'entrainement (JJ/MM/AAAA) : ");
    scanf("%d %d %d", &date.jour, &date.mois, &date.annee);
    while(!dateValide(date)){
        printf("Date invalide. Veuillez entrer une date valide.\n\n");
        printf("Entrez la date de l'entrainement (JJ/MM/AAAA) : ");
        scanf("%d %d %d", &date.jour, &date.mois, &date.annee);
    }
    printf("\n");

    printf("En combien de temps l'athlète a-t-il réalisé l'épreuve ?\n");
    printf("Minutes : ");
    scanf("%d", &minutes);
    while(minutes < 0 || minutes > 59){
        printf("Minutes : ");
        scanf("%d", &minutes);
    }
    printf("Secondes : ");
    scanf("%d", &secondes);
    while(secondes < 0 || secondes > 59){
        scanf("%d", &secondes);
    }
    printf("Millisecondes : ");
    scanf("%d", &ms);
    while(ms < 0 || ms > 999){
        printf("Millisecondes : ");
        scanf("%d", &ms);
    }

    FILE *Athlete = modifierFichierAthlete(choixAthlete);
    if (Athlete == NULL) {
        printf("Impossible d'ouvrir le fichier de l'athlète\n");
        return;
    }

    while (fgetc(Athlete) != '\n'); // Sauter une ligne

    // Ajouter une ligne dans le fichier de l'athlète
    fprintf(Athlete, "%d %d %d %s %d %d %d %d\n", date.jour, date.mois, date.annee, epreuve + 2, minutes, secondes, ms, positionRelais);
    printf("Entrainement ajouté avec succès.\n");

    fclose(Athlete);

}

void supprimerEntrainement() {
    int choixAthlete;
    Entrainement entrainement1;
    int numero;
    char prenom[MAX/2];
    char nom[MAX/2];
    char nomFichier[MAX];
    char cheminComplet[MAX];

    FILE *fichierAthletes = fopen(CHEMIN"/Liste/nomAthletes.txt", "r");
    if (fichierAthletes == NULL) {
        printf("Impossible d'ouvrir le fichier nomAthletes\n");
        return;
    }
    afficherListeAthlete(fichierAthletes);
    printf("Choix : ");
    scanf("%d", &choixAthlete);
    printf("\n");

    rewind(fichierAthletes);
    while (fscanf(fichierAthletes, "%d %s %s", &numero, prenom, nom) != EOF) {
        if(choixAthlete == numero){
            sprintf(nomFichier, "%s %s.txt", prenom, nom);
            break;
        }
    }

    sprintf(cheminComplet, "%s/Athletes/%s", CHEMIN, nomFichier);

    int position, compteur = 1, choixEntrainement;
    FILE *file = modifierFichierAthlete(choixAthlete);
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier choixAthlete\n");
        return;
    }
    int ligne = compterLignes(file);
    if (ligne == 1) {
        printf("Aucun entrainement à supprimer\n");
        return;
    }

    rewind(file);
    while (fgetc(file) != '\n'); // Sauter une ligne

    printf("Choisissez l'entrainement à supprimer\n");
    // Lire chaque ligne du fichier
    while (fscanf(file, "%d %d %d %s %d %d %d %d", &entrainement1.dateEntrainement.jour, &entrainement1.dateEntrainement.mois, &entrainement1.dateEntrainement.annee, entrainement1.typeEpreuve, &entrainement1.tempsAthlete.minute, &entrainement1.tempsAthlete.seconde, &entrainement1.tempsAthlete.milliseconde, &position) != EOF) {
        // Affichage des valeurs
        printf("%d. %02d/%02d/%4d | %02dmin %02dsec %03dms | %s\n", compteur, entrainement1.dateEntrainement.jour, entrainement1.dateEntrainement.mois, entrainement1.dateEntrainement.annee, entrainement1.tempsAthlete.minute, entrainement1.tempsAthlete.seconde, entrainement1.tempsAthlete.milliseconde, entrainement1.typeEpreuve);
        compteur++;
    }

    printf("Choix : ");
    scanf("%d", &choixEntrainement);
    printf("\n");

    // Suppression de l'entrainement
    FILE *tempFile = fopen(CHEMIN"/Athletes/temp.txt", "w");
    if (tempFile == NULL) {
        printf("Impossible de créer le fichier temporaire\n");
        return;
    }
    
    // Copie de toutes les lignes sauf celle à supprimer
    fprintf(tempFile, "%s %s\n", prenom, nom); // Écrire le prénom et le nom de l'athlète
    
    rewind(file);
    while (fgetc(file) != '\n'); // Sauter une ligne

    compteur = 1;
    while (fscanf(file, "%d %d %d %s %d %d %d %d", &entrainement1.dateEntrainement.jour, &entrainement1.dateEntrainement.mois, &entrainement1.dateEntrainement.annee, entrainement1.typeEpreuve, &entrainement1.tempsAthlete.minute, &entrainement1.tempsAthlete.seconde, &entrainement1.tempsAthlete.milliseconde, &position) != EOF) {
        if (compteur != choixEntrainement) {
            fprintf(tempFile, "%d %d %d %s %d %d %d %d\n", entrainement1.dateEntrainement.jour, entrainement1.dateEntrainement.mois, entrainement1.dateEntrainement.annee, entrainement1.typeEpreuve, entrainement1.tempsAthlete.minute, entrainement1.tempsAthlete.seconde, entrainement1.tempsAthlete.milliseconde, position);
        }
        compteur++;
    }

    fclose(file);
    fclose(tempFile);
    fclose(fichierAthletes);

    remove(cheminComplet);  // Supprimez le fichier original
    rename(CHEMIN"/Athletes/temp.txt", cheminComplet);  // Renommez le fichier temporaire avec le nom du fichier original

    printf("Entrainement supprimé avec succès.\n");
}

void modifierEntrainement(){
    int choixAthlete;
    Entrainement entrainement1, newEntrainement;
    int numero, numEpreuve;
    char epreuve[MAX];
    char prenom[MAX/2];
    char nom[MAX/2];
    char nomFichier[MAX];
    char cheminComplet[MAX];

    FILE *fichierAthletes = fopen(CHEMIN"/Liste/nomAthletes.txt", "r");
    if (fichierAthletes == NULL) {
        printf("Impossible d'ouvrir le fichier nomAthletes\n");
        return;
    }
    afficherListeAthlete(fichierAthletes);
    printf("Choix : ");
    scanf("%d", &choixAthlete);
    printf("\n");

    rewind(fichierAthletes);
    while (fscanf(fichierAthletes, "%d %s %s", &numero, prenom, nom) != EOF) {
        if(choixAthlete == numero){
            sprintf(nomFichier, "%s %s.txt", prenom, nom);
            break;
        }
    }

    sprintf(cheminComplet, "%s/Athletes/%s", CHEMIN, nomFichier);

    int position, compteur = 1, choixEntrainement;
    FILE *file = modifierFichierAthlete(choixAthlete);
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier choixAthlete\n");
        return;
    }
    int ligne = compterLignes(file);
    if (ligne == 1) {
        printf("Aucun entrainement à modifier\n");
        return;
    }

    rewind(file);
    while (fgetc(file) != '\n'); // Sauter une ligne

    printf("Choisissez l'entrainement à modifier\n");
    // Lire chaque ligne du fichier
    while (fscanf(file, "%d %d %d %s %d %d %d %d", &entrainement1.dateEntrainement.jour, &entrainement1.dateEntrainement.mois, &entrainement1.dateEntrainement.annee, entrainement1.typeEpreuve, &entrainement1.tempsAthlete.minute, &entrainement1.tempsAthlete.seconde, &entrainement1.tempsAthlete.milliseconde, &position) != EOF) {
        // Affichage des valeurs
        printf("%d. %02d/%02d/%4d | %02dmin %02dsec %03dms | %s\n", compteur, entrainement1.dateEntrainement.jour, entrainement1.dateEntrainement.mois, entrainement1.dateEntrainement.annee, entrainement1.tempsAthlete.minute, entrainement1.tempsAthlete.seconde, entrainement1.tempsAthlete.milliseconde, entrainement1.typeEpreuve);
        compteur++;
    }
    printf("Choix : ");
    scanf("%d", &choixEntrainement);
    printf("\n");

    int newMinutes, newSecondes, newMs, choixModif, newTypeEpreuve;

    printf("Faut-il changer la date de l'entrainement ?\n");
    printf("1. Oui\n");
    printf("2. Non\n");
    printf("Choix : ");
    scanf("%d", &choixModif);
    printf("\n");
    while(choixModif != 1 && choixModif != 2){
        printf("Choix invalide. Veuillez entrer un choix valide.\n");
        printf("Faut-il changer la date de l'entrainement ?\n");
        printf("1. Oui\n");
        printf("2. Non\n");
        printf("Choix : ");
        scanf("%d", &choixModif);
        printf("\n");
    }
    

    if(choixModif == 1){
        printf("Entrez la nouvelle date de l'entrainement (JJ/MM/AAAA) : ");
        scanf("%d %d %d", &newEntrainement.dateEntrainement.jour, &newEntrainement.dateEntrainement.mois, &newEntrainement.dateEntrainement.annee);
        while(!dateValide(newEntrainement.dateEntrainement)){
            printf("Date invalide. Veuillez entrer une date valide.\n\n");
            printf("Entrez la date de l'entrainement (JJ/MM/AAAA) : ");
            scanf("%d %d %d", &newEntrainement.dateEntrainement.jour, &newEntrainement.dateEntrainement.mois, &newEntrainement.dateEntrainement.annee);
        }
        printf("\n");
    } else {
        newEntrainement.dateEntrainement.jour = entrainement1.dateEntrainement.jour;
        newEntrainement.dateEntrainement.mois = entrainement1.dateEntrainement.mois;
        newEntrainement.dateEntrainement.annee = entrainement1.dateEntrainement.annee;
    }

    printf("Faut-il changer le type d'épreuve de l'entrainement ?\n");
    printf("1. Oui\n");
    printf("2. Non\n");
    printf("Choix : ");
    scanf("%d", &choixModif);
    printf("\n");
    while(choixModif != 1 && choixModif != 2){
        printf("Choix invalide. Veuillez entrer un choix valide.\n");
        printf("Faut-il changer le type d'épreuve de l'entrainement ?\n");
        printf("1. Oui\n");
        printf("2. Non\n");
        printf("Choix : ");
        scanf("%d", &choixModif);
        printf("\n");
    }

    if(choixModif == 1){
        FILE *fichierEpreuves = fopen(CHEMIN"/Liste/nomEpreuve.txt", "r");
        if (fichierEpreuves == NULL) {
            printf("Impossible d'ouvrir le fichier nomEpreuve\n");
            return;
        }

        afficherListeEpreuve(fichierEpreuves);
        printf("Choix : ");
        scanf("%d", &newTypeEpreuve);
        printf("\n");

        rewind(fichierEpreuves);
        int lignes = compterLignes(fichierEpreuves);

        while (newTypeEpreuve < 1 || newTypeEpreuve > lignes) {
            printf("Choix invalide. Veuillez choisir un numéro d'épreuve entre 1 et %d.\n", lignes);
            printf("Choix : ");
            scanf("%d", &newTypeEpreuve);
            printf("\n");
        }

        if(newTypeEpreuve == 5){
            printf("Position lors du relais : ");
            scanf("%d", &newEntrainement.position);
            while (newEntrainement.position < 1 || newEntrainement.position > 4){
                printf("Choix invalide. Veuillez choisir une position entre 1 et 4.\n\n");
                printf("Position lors du relais : ");
                scanf("%d", &newEntrainement.position);
                printf("\n");
            }
        } else {
            newEntrainement.position = 0;
        }

        rewind(fichierEpreuves);
        // Lire le fichier epreuves jusqu'à trouver l'épreuve choisie
        while (fgets(epreuve, sizeof(epreuve), fichierEpreuves)) {
            sscanf(epreuve, "%d", &numEpreuve);
            epreuve[strcspn(epreuve, "\n")] = 0;

            if(numEpreuve == newTypeEpreuve) {
                break;
            }
        }

        fclose(fichierEpreuves);
    } else {
        strcpy(epreuve, entrainement1.typeEpreuve);
    }

    printf("Faut-il changer la durée de l'entrainement ?\n");
    printf("1. Oui\n");
    printf("2. Non\n");
    printf("Choix : ");
    scanf("%d", &choixModif);
    printf("\n");
    while(choixModif != 1 && choixModif != 2){
        printf("Choix invalide. Veuillez entrer un choix valide.\n");
        printf("Faut-il changer la durée de l'entrainement ?\n");
        printf("1. Oui\n");
        printf("2. Non\n");
        printf("Choix : ");
        scanf("%d", &choixModif);
        printf("\n");
    }

    if(choixModif == 1){
        printf("Entrez la nouvelle durée de l'entrainement\n");
        printf("Minutes : ");
        scanf("%d", &newMinutes);
        while(newMinutes < 0 || newMinutes > 59){
            printf("Minutes : ");
            scanf("%d", &newMinutes);
        }
        printf("Secondes : ");
        scanf("%d", &newSecondes);
        while(newSecondes < 0 || newSecondes > 59){
            scanf("%d", &newSecondes);
        }
        printf("Millisecondes : ");
        scanf("%d", &newMs);
        while(newMs < 0 || newMs > 999){
            printf("Millisecondes : ");
            scanf("%d", &newMs);
        }
        printf("\n");
    } else {
        newMinutes = entrainement1.tempsAthlete.minute;
        newSecondes = entrainement1.tempsAthlete.seconde;
        newMs = entrainement1.tempsAthlete.milliseconde;
    }

    // Modification de l'entrainement
    FILE *tempFile = fopen(CHEMIN"/Athletes/temp.txt", "w");
    if (tempFile == NULL) {
        printf("Impossible de créer le fichier temporaire\n");
        return;
    }

    // Copie de toutes les lignes et modification de celle à modifier
    fprintf(tempFile, "%s %s\n", prenom, nom); // Écrire le prénom et le nom de l'athlète

    rewind(file);
    while (fgetc(file) != '\n'); // Sauter une ligne

    compteur = 1;
    while (fscanf(file, "%d %d %d %s %d %d %d %d", &entrainement1.dateEntrainement.jour, &entrainement1.dateEntrainement.mois, &entrainement1.dateEntrainement.annee, entrainement1.typeEpreuve, &entrainement1.tempsAthlete.minute, &entrainement1.tempsAthlete.seconde, &entrainement1.tempsAthlete.milliseconde, &entrainement1.position) != EOF) {
        if (compteur != choixEntrainement) {
            fprintf(tempFile, "%d %d %d %s %d %d %d %d\n", entrainement1.dateEntrainement.jour, entrainement1.dateEntrainement.mois, entrainement1.dateEntrainement.annee, entrainement1.typeEpreuve, entrainement1.tempsAthlete.minute, entrainement1.tempsAthlete.seconde, entrainement1.tempsAthlete.milliseconde, entrainement1.position);
        } else if(compteur == choixEntrainement) {
            fprintf(tempFile, "%d %d %d %s %d %d %d %d\n", newEntrainement.dateEntrainement.jour, newEntrainement.dateEntrainement.mois, newEntrainement.dateEntrainement.annee, epreuve + 2, newMinutes, newSecondes, newMs, entrainement1.position);
        }
        compteur++;
    }

    fclose(file);
    fclose(tempFile);
    fclose(fichierAthletes);

    remove(cheminComplet);  // Supprimez le fichier original
    rename(CHEMIN"/Athletes/temp.txt", cheminComplet);  // Renommez le fichier temporaire avec le nom du fichier original

    printf("Entrainement modifier avec succès.\n");

}

void nouvelEntrainement() {
    int choix;
    printf("1. Ajouter un entrainement\n");
    printf("2. Supprimer un entrainement\n");
    printf("3. Modifier un entrainement\n");
    couleur("31"); printf("4. Quitter\n"); couleur("0");
    printf("Choix : ");
    scanf("%d", &choix);
    printf("\n");

    switch (choix) {
        case 1:
            // Code pour ajouter un entrainement
            ajouterEntrainement();
            break;
        case 2:
            // Code pour supprimer un entrainement
            supprimerEntrainement();
            break;
        case 3:
            // Code pour modifier un entrainement
            modifierEntrainement();
            break;
        case 4:
            // Code pour retourner au début du programme
            break;
        default:
            printf("Choix invalide.\n");
            nouvelEntrainement();
    }
}

#endif 