#ifndef STATISTIQUES_H
#define STATISTIQUES_H

#include "struct.h"
#include "constants.h"
#include "def.h"

extern void afficherDiffTemps(int *choixAthlete, int *choixEpreuve, char epreuve[MAX]);

extern int moyenneTemps(FILE *athlete, char typeEpreuve[MAX]);

extern void pireTemps(FILE *athlete, char typeEpreuve[MAX]);

extern void meilleurTemps(FILE *athlete, char typeEpreuve[MAX]);

extern void resumerEntrainement(void);

extern void quiAuJO(void);

extern void statistiqueAthlete(Entrainement entrainement1, FILE *file);

#endif
