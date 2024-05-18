#ifndef ATHLETE_C
#define ATHLETE_C
#include "def.c"

void ajouterAthlete(){
    char prenom[MAX/2];
    char nom[MAX/2];
    int dernierNumero = 0;
    char ligne[MAX];
    char cheminComplet[MAX];

    FILE *fichierAthletes = fopen(CHEMIN"/Liste/nomAthletes.txt", "r");
    if (fichierAthletes != NULL) {
        while (fgets(ligne, sizeof(ligne), fichierAthletes) != NULL) {
            sscanf(ligne, "%d", &dernierNumero);
        }
        fclose(fichierAthletes);
    }

    printf("Entrez le prénom de l'athlète : ");
    scanf("%s", prenom);

    // Mettre la première lettre du prénom en majuscule
    if (prenom[0] >= 'a' && prenom[0] <= 'z') {
        prenom[0] = prenom[0] - 32;
    }

    printf("Entrez le nom de l'athlète : ");
    scanf("%s", nom);

    // Mettre la première lettre du nom en majuscule
    if (nom[0] >= 'a' && nom[0] <= 'z') {
        nom[0] = nom[0] - 32;
    }

    sprintf(cheminComplet, "%s/Athletes/%s %s.txt", CHEMIN, prenom, nom);

    FILE *fichier = fopen(cheminComplet, "w");
    if (fichier == NULL) {
        printf("Impossible de créer le fichier %s\n", cheminComplet);
        return;
    }
    fprintf(fichier, "%s %s\n", prenom, nom);

    fclose(fichier);

    fichierAthletes = fopen(CHEMIN"/Liste/nomAthletes.txt", "a");
    if (fichierAthletes != NULL) {
        fprintf(fichierAthletes, "%d %s %s\n", dernierNumero + 1, prenom, nom);
        fclose(fichierAthletes);
    }

    printf("\nL'athlète %s %s a été créé avec succès.\n", prenom, nom);
}

void supprimerAthlete(){
    int numeroAthlete;
    char ligne[MAX];
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
    int lignes = compterLignes(fichierAthletes);

    rewind(fichierAthletes);
    afficherListeAthlete(fichierAthletes);
    printf("Choix : ");
    scanf("%d", &numeroAthlete);
    printf("\n");
    while(numeroAthlete < 1 || numeroAthlete > lignes){
        printf("Choix invalide. Entrez un nombre entre 1 et %d.\n", lignes);
        printf("Choix : ");
        scanf("%d", &numeroAthlete);
        printf("\n");
    }


    rewind(fichierAthletes);
    while (fscanf(fichierAthletes, "%d %s %s", &numero, prenom, nom) != EOF) {
        if(numeroAthlete == numero){
            sprintf(nomFichier, "%s %s.txt", prenom, nom);
        }
    }

    FILE *nouveauFichier = fopen(CHEMIN"/Liste/nomAthletesTemp.txt", "w");
    if (nouveauFichier == NULL) {
        printf("Impossible de créer le fichier temporaire\n");
        fclose(fichierAthletes);
        return;
    }

    rewind(fichierAthletes);
    while (fgets(ligne, sizeof(ligne), fichierAthletes) != NULL) {
        sscanf(ligne, "%d %s %s", &numero, prenom, nom);
        if (numero != numeroAthlete) {
            fprintf(nouveauFichier, "%s", ligne);
        }
    }

    fclose(fichierAthletes);
    fclose(nouveauFichier);

    sprintf(cheminComplet, "%s/Athletes/%s", CHEMIN, nomFichier);

    remove(cheminComplet);
    remove(CHEMIN"/Liste/nomAthletes.txt");
    rename(CHEMIN"/Liste/nomAthletesTemp.txt", CHEMIN"/Liste/nomAthletes.txt");

    printf("L'athlète %s %s a été supprimé avec succès.\n", prenom, nom);
}

void modifAthlete() {
    int choix;
    printf("1. Créer un nouvel athlète\n");
    printf("2. Supprimer un athlète\n");
    couleur("31"); printf("3. Quitter\n"); couleur("0");
    printf("Choix : ");
    scanf("%d", &choix);
    printf("\n");

    switch (choix) {
        case 1:
            // Code pour ajouter un athlète
            ajouterAthlete();
            break;
        case 2:
            // Code pour supprimer un athlète
            supprimerAthlete();
            break;
        case 3:
            break;
        default:
            printf("Choix invalide.\n");
            modifAthlete();
    }
    
}

#endif