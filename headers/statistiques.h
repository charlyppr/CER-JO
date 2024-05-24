#ifndef STATISTIQUES_H
#define STATISTIQUES_H

#include "../PATH.h"
#include "struct.h"
#include "constants.h"
#include "def.h"

extern void showDiffTime(int *athleteChoice, int *raceChoice, char race[MAX]);

extern int averageTime(FILE *athlete, char raceType[MAX]);

extern void worstTime(FILE *athlete, char raceType[MAX]);

extern void bestTime(FILE *athlete, char raceType[MAX]);

extern void trainingResume(void);

extern void whoInOG(void);

extern void athleteStatistic(Training training1, FILE *file);

#endif
