#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include "struct.h"
#include "constants.h"
#include "def.h"


extern void afficherEntrainementNom(Entrainement entrainement1, int choixAthlete);

extern void afficherEntrainementTypeEpreuve(Entrainement entrainement1, int choixEpreuve);

extern void afficherEntrainementDate(Entrainement entrainement1);

extern void historiqueEntrainement(Entrainement entrainement1, FILE *file);

#endif
