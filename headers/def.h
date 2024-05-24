#ifndef DEF_H
#define DEF_H

#include "constants.h"
#include "struct.h"

extern int compterLignes(FILE *file);

extern int dateValide(Date date);

extern int compareDates(const void *a, const void *b);

extern int comparer(const void *a, const void *b);

extern int faireChoixAthlete(void);

extern void afficherNomAthlete(FILE *file);

extern void afficherListeAthlete(FILE *nomAthlete);

extern void afficherNomEpreuve(FILE *nomEpreuve);

extern void afficherListeEpreuve(FILE *nomEpreuve);

extern FILE *ouvrirFichierAthlete(int choixAthlete);

extern FILE *modifierFichierAthlete(int choixAthlete);

extern void choisirAthlete(int *choixAthlete);

extern void choisirEpreuve(int *choixEpreuve, char epreuve[MAX]);

#endif
