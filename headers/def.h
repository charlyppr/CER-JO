#ifndef DEF_H
#define DEF_H

#include "../PATH.h"
#include "constants.h"
#include "struct.h"

extern void OGStart(void);

extern int continueProgramme(void);

extern int countLine(FILE *file);

extern int validDate(Date date);

extern int compareDates(const void *a, const void *b);

extern int compareAverage(const void *a, const void *b);

extern int makeAthleteChoice(void);

extern void print_padded_line(const char* prefix, const char* content);

extern void showAthleteName(FILE *file);

extern void showAthleteList(FILE *nomAthlete);

extern void showRaceName(FILE *nomEpreuve);

extern void showRaceList(FILE *nomEpreuve);

extern FILE *openAthleteFile(int choixAthlete);

extern FILE *changeAthleteFile(int choixAthlete);

extern void chooseAthlete(int *choixAthlete);

extern void chooseRace(int *choixEpreuve, char epreuve[MAX]);

#endif
