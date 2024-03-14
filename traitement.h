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
void affiche_liste_faits(liste_faits *liste);

/*Libérer la mémoire d'une liste de faits*/
void liberer_liste_faits(liste_faits **liste);

/*Libérer la mémoire d'une liste de conditions*/
void liberer_liste_conditions(liste_conditions **liste);

/*Libérer la mémoire d'une liste de règles*/
void liberer_liste_regles(liste_regles **liste);


/*Libérer la mémoire d'une liste de réponses*/
void  liberer_liste_reponses(liste_reponses **liste);

#endif //ALGO_S6_TRAITEMENT_H