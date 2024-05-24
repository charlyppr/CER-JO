#include "../headers/athlete.h"
#include "../headers/entrainement.h"

int dernierNumeroAthlete(void){
    int dernierNumero = 0;
    char ligne[MAX];
    FILE *fichierAthletes = fopen(CHEMIN"/Liste/nomAthletes.txt", "r");
    if (fichierAthletes != NULL) {
        while (fgets(ligne, sizeof(ligne), fichierAthletes) != NULL) {
            sscanf(ligne, "%d", &dernierNumero);
        }
        fclose(fichierAthletes);
    }
    return dernierNumero;
}

void ajouterAthlete(void){
    char prenom[MAX/2], nom[MAX/2];
    int dernierNumero = dernierNumeroAthlete();
    char cheminComplet[MAX];

    FILE *fichierAthletes = fopen(CHEMIN"/Liste/nomAthletes.txt", "r");
    if (fichierAthletes == NULL) {
        printf("Erreur d'ouverture du fichier nomAthletes.txt\n");
        return;
    }

    int numero;
    char prenomExistant[50], nomExistant[50];

    while (1) {
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

        int existeDeja = 0;
        rewind(fichierAthletes);
        while (fscanf(fichierAthletes, "%d %s %s", &numero, prenomExistant, nomExistant) != EOF) {
            if (strcmp(prenom, prenomExistant) == 0 && strcmp(nom, nomExistant) == 0) {
                existeDeja = 1;
                break;
            }
        }

        if (existeDeja) {
            printf("\nL'athlète %s %s existe déjà. Veuillez entrer un autre prénom et nom.\n", prenom, nom);
        } else {
            break;
        }
    }

    fclose(fichierAthletes);

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

void supprimerAthlete(void){
    int numeroAthlete, choix, compteur = 1, numero;
    char prenom[MAX/2], nom[MAX/2];
    char newPrenom[MAX/2], newNom[MAX/2];
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
        if(numero == numeroAthlete){
            sprintf(nomFichier, "%s %s.txt", prenom, nom);
            break;
        }
    }
    printf("Êtes-vous sûr de vouloir supprimer l'athlète %s %s ?\n", prenom, nom);
    couleur("32"); printf("1. Oui\n"); couleur("0");
    couleur("31"); printf("2. Non\n"); couleur("0");
    printf("Choix : ");
    scanf("%d", &choix);
    printf("\n");
    if(choix == 2){
        return;
    }

    FILE *nouveauFichier = fopen(CHEMIN"/Liste/nomAthletesTemp.txt", "w");
    if (nouveauFichier == NULL) {
        printf("Impossible de créer le fichier temporaire\n");
        fclose(fichierAthletes);
        return;
    }

    rewind(fichierAthletes);
    while (fscanf(fichierAthletes, "%d %s %s", &numero, prenom, nom) != EOF) {
        if (numero != numeroAthlete) {
            fprintf(nouveauFichier, "%d %s %s\n", compteur, prenom, nom);
            compteur++;
        }
        else{
            strcpy(newPrenom, prenom);
            strcpy(newNom, nom);
        }
    }

    fclose(fichierAthletes);
    fclose(nouveauFichier);

    sprintf(cheminComplet, "%s/Athletes/%s", CHEMIN, nomFichier);

    remove(cheminComplet);
    remove(CHEMIN"/Liste/nomAthletes.txt");
    rename(CHEMIN"/Liste/nomAthletesTemp.txt", CHEMIN"/Liste/nomAthletes.txt");

    printf("L'athlète %s %s a été supprimé avec succès.\n\n", newPrenom, newNom);
}

void modifierAthlete(void){
    int numeroAthlete, numero, compteur = 1;
    char ligne[MAX];
    char prenom[MAX/2], nom[MAX/2];
    char newPrenom[MAX/2], newNom[MAX/2];
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

    // Code pour modifier un athlète
    printf("Quel est le nouveau prénom de l'athlète ? ");
    scanf("%s", newPrenom);
    printf("Quel est le nouveau nom de l'athlète ? ");
    scanf("%s", newNom);
    if(newPrenom[0] >= 'a' && newPrenom[0] <= 'z'){
        newPrenom[0] = newPrenom[0] - 32;
    }
    if(newNom[0] >= 'a' && newNom[0] <= 'z'){
        newNom[0] = newNom[0] - 32;
    }
    sprintf(nomFichier, "%s/Athletes/%s %s.txt", CHEMIN, newPrenom, newNom);

    FILE *nouveauFichier = fopen(CHEMIN"/Liste/nomAthletesTemp.txt", "w");
    if (nouveauFichier == NULL) {
        printf("Impossible de créer le fichier temporaire\n");
        fclose(fichierAthletes);
        return;
    }

    rewind(fichierAthletes);
    while (fscanf(fichierAthletes, "%d %s %s", &numero, prenom, nom) != EOF) {
        if (numero == numeroAthlete) {
            fprintf(nouveauFichier, "%d %s %s\n", compteur, newPrenom, newNom);
            sprintf(cheminComplet, "%s/Athletes/%s %s.txt", CHEMIN, prenom, nom);
            compteur++;
        } else {
            fprintf(nouveauFichier, "%d %s %s\n", compteur, prenom, nom);
            compteur++;
        }
    }

    fclose(fichierAthletes);
    fclose(nouveauFichier); 

    FILE *AthleteTemp = fopen(CHEMIN"/Athletes/AthletesTemp.txt", "w");
    if (AthleteTemp == NULL) {
        printf("Impossible de créer le fichier temporaire\n");
        fclose(fichierAthletes);
        return;
    }

    FILE *Athlete = ouvrirFichierAthlete(numeroAthlete);
    if (Athlete == NULL) {
        printf("Impossible d'ouvrir le fichier Athlete\n");
        fclose(fichierAthletes);
        return;
    }

    // recopier le nouveau prenom et nom dans le fichier temporaire
    fprintf(AthleteTemp, "%s %s\n", newPrenom, newNom);

    while (fgetc(Athlete) != '\n');
    // recopier le reste du fichier Athlete dans le fichier temporaire
    while (fgets(ligne, sizeof(ligne), Athlete) != NULL) {
        fprintf(AthleteTemp, "%s", ligne);
    }

    fclose(Athlete);
    fclose(AthleteTemp);

    remove(cheminComplet);
    remove(CHEMIN"/Liste/nomAthletes.txt");
    rename(CHEMIN"/Liste/nomAthletesTemp.txt", CHEMIN"/Liste/nomAthletes.txt");
    rename(CHEMIN"/Athletes/AthletesTemp.txt", nomFichier);

    printf("L'athlète %s %s a été modifié avec succès.\n", newPrenom, newNom);

}

void modifAthlete(void) {
    int choix, dernierNumero = dernierNumeroAthlete();

    printf("1. Créer un nouvel athlète\n");
    printf("2. Supprimer un athlète\n");
    printf("3. Modifier un athlète\n");
    couleur("31"); printf("4. Quitter\n"); couleur("0");
    printf("Choix : ");
    scanf("%d", &choix);
    printf("\n");

    switch (choix) {
        case 1:
            // Code pour ajouter un athlète
            ajouterAthlete();

            printf("\nVoulez-vous ajouter un entrainement pour cet athlète ?\n");
            couleur("32"); printf("1. Oui\n"); couleur("0");
            couleur("31"); printf("2. Non\n"); couleur("0");
            printf("Choix : ");
            scanf("%d", &choix);
            printf("\n");

            if (choix == 1) {
                ajouterEntrainement(dernierNumero + 1);
            }
            else {
                return;
            }

            break;
        case 2:
            // Code pour supprimer un athlète
            supprimerAthlete();
            break;
        case 3:
            // Code pour modifier un athlète
            modifierAthlete();
            break;
        case 4:
            break;
        default:
            printf("Choix invalide.\n\n");
            modifAthlete();
    }
    
}
