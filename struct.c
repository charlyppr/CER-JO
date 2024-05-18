#ifndef STRUCT_C
#define STRUCT_C

// Structure pour la date
typedef struct {
    int annee;
    int mois;
    int jour;
} Date;

// Structure pour le temps
typedef struct {
    int minute;
    int seconde;
    int milliseconde;
} Temps;


// Structure pour l'entraînement d'un athlète
typedef struct Entrainement {
    char nomAthlete[100];
    Date dateEntrainement;
    char typeEpreuve[100];
    Temps tempsAthlete;
    int position;
} Entrainement;

typedef struct {
    int moyenne;
    int index;
} MoyenneIndex;

#endif // STRUCT_C