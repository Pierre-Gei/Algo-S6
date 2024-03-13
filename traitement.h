//
// Created by Pierre Geiguer on 12/03/2024.
//

#include "structures.h"

#ifndef ALGO_S6_TRAITEMENT_H
#define ALGO_S6_TRAITEMENT_H

void add_regle(liste_regles **liste, char *name, liste_conditions *conditions);
void add_condition(liste_conditions **liste, char *name);
void add_condition_to_regle(liste_regles **liste, char *name_regle, char *name_condition);
void print_liste_regles(liste_regles *liste);
void add_fait(liste_faits **liste, char *fait);
void print_liste_faits(liste_faits *liste);
void free_liste_faits(liste_faits *liste);
void free_liste_regles(liste_regles *liste);
void free_liste_conditions(liste_conditions *liste);
liste_conditions * ajout_condition(liste_conditions *liste, char *condition);
liste_regles * ajout_regle (liste_regles * liste, char * regle, liste_conditions * conditions);
void affiche_liste_regle (liste_regles * liste);
void affiche_liste_condition (liste_conditions * liste);

#endif //ALGO_S6_TRAITEMENT_H