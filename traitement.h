//
// Created by Pierre Geiguer on 12/03/2024.
//

#include "structures.h"
#include <stdbool.h>

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

/*Afficher une liste de réponses*/
void affiche_faits_possibles(liste_regles *liste);

/*Ajouter une réponse à une liste de réponses*/
void ajouter_reponse(liste_reponses **liste, char *reponse);

/*Vérifier si une réponse a déjà été donnée*/
bool reponse_deja_donnee(liste_reponses *liste, char *reponse);




#endif //ALGO_S6_TRAITEMENT_H