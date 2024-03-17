#ifndef ALGO_S6_SAVE_H
#define ALGO_S6_SAVE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "structures.h"
#include "traitement.h"


void load_to_list(char *filename, liste_regles **liste);
void load_faits_to_list(char *filename, liste_faits **liste);
void divide_and_add_faits(liste_faits **liste,liste_faits **nouveaux_faits, char *faits);
void insert_regle_base(char *regle, liste_regles ** regles, liste_regles ** nouvelles_regles) ;
void ajoute_fait_fichier(char *fait, FILE *file);
void enregistrer_liste_fait_recursif (liste_faits *nouveaux_faits, char *filename, FILE *file);
void enregistrer_liste_fait(liste_faits *nouveaux_faits, char *filename);
void enregistrer_liste_regle(liste_regles *nouvelles_regles, char *filename);
void enregistrer_liste_regle_recursif (liste_regles *nouvelles_regles, FILE *file);
void ajoute_regle_fichier(FILE * file, char *regle);
char * regle_en_chaine(char * regle, liste_conditions *conditions);
void clone_conditions(liste_conditions **dest, liste_conditions *src) ;
#endif //ALGO_S6_SAVE_H