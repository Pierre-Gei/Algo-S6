//
// Created by Pierre Geiguer on 12/03/2024.
//

#include "structures.h"

#ifndef ALGO_S6_TRAITEMENT_H
#define ALGO_S6_TRAITEMENT_H

liste_regles *init_liste_regles();
liste_conditions *init_liste_conditions();
void add_regle(liste_regles *liste, char *name, liste_conditions *conditions);
void add_condition(liste_conditions *liste, char *name);
void add_condition_to_regle(liste_regles *liste, char *name_regle, char *name_condition);
void print_liste_regles(liste_regles *liste);
liste_faits *init_liste_faits();
void add_fait(liste_faits *liste, char *fait);
void print_liste_faits(liste_faits *liste);
void free_liste_faits(liste_faits *liste);
void free_liste_regles(liste_regles *liste);
void free_liste_conditions(liste_conditions *liste);

#endif //ALGO_S6_TRAITEMENT_H