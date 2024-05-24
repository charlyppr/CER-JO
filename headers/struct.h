#ifndef STRUCT_H
#define STRUCT_H

// Structure pour la date
typedef struct {
    int year;
    int month;
    int day;
} Date;

// Structure pour le temps
typedef struct {
    int minute;
    int second;
    int millisecond;
} Time;


// Structure pour l'entraînement d'un athlète
typedef struct {
    int position;
    char athleteName[100];
    char raceType[100];
    Date trainingDate;
    Time athleteTime;
} Training;

Training training;  // Variable globale pour l'entraînement

// Structure pour la moyenne et l'index
typedef struct {
    int average;
    int index;
} AverageIndex;

#endif
