//
// Created by Pierre Geiguer on 12/03/2024.
//

#ifndef ALGO_S6_SAVE_H
#define ALGO_S6_SAVE_H

<<<<<<< HEAD

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structures.h"
#include "traitement.h"


void load_to_list(char *filename, liste_regles **liste);
void load_faits_to_list(char *filename, liste_faits **liste);
void divide_and_add_faits(liste_faits **liste, char *faits, char * filename);
void ajoute_fait_fichier(char *filename, char *fait);
void ajoute_regle_fichier(char *filename, char *regle);
=======
#include "structures.h"

void load_to_list(char *filename, liste_regles *liste);
void load_faits_to_list(char *filename, liste_faits *liste);
>>>>>>> e362e3192e630f0fc21ed5cbaf4582788776f28f
#endif //ALGO_S6_SAVE_H