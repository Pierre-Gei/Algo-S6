//
// Created by Pierre Geiguer on 12/03/2024.
//

#include <string.h>
#include "traitement.h"
#include "stdio.h"
#include "stdlib.h"
#include "structures.h"

liste_regles *init_liste_regles(){
    liste_regles *liste = malloc(sizeof(liste_regles));
    liste->name = NULL;
    liste->conditions = NULL;
    liste->suivant = NULL;
    return liste;
}

liste_conditions *init_liste_conditions(){
    liste_conditions *liste = malloc(sizeof(liste_conditions));
    liste->name = NULL;
    liste->suivant = NULL;
    return liste;
}
void add_regle(liste_regles *liste, char *name, liste_conditions *conditions){
    liste_regles *new = malloc(sizeof(liste_regles));
    new->name = malloc(strlen(name) + 1);  // Allocate an extra byte for the null terminator
    strncpy(new->name, name, strlen(name) + 1);  // Copy the string and the null terminator
    new->conditions = conditions;
    new->suivant = NULL;
    liste_regles *tmp = liste;
    while(tmp->suivant != NULL){
        tmp = tmp->suivant;
    }
    tmp->suivant = new;
}

void add_condition(liste_conditions *liste, char *name){
    liste_conditions *new = malloc(sizeof(liste_conditions));
    new->name = malloc(strlen(name) + 1);  // Allocate an extra byte for the null terminator
    strncpy(new->name, name, strlen(name) + 1);  // Copy the string and the null terminator
    new->suivant = NULL;
    liste_conditions *tmp = liste;
    while(tmp->suivant != NULL){
        tmp = tmp->suivant;
    }
    tmp->suivant = new;
}

void add_condition_to_regle(liste_regles *liste, char *name_regle, char *name_condition){
    liste_regles *tmp = liste;
    while(tmp->suivant != NULL){
        if(tmp->name == name_regle){
            add_condition(tmp->conditions, name_condition);
        }
        tmp = tmp->suivant;
    }
}

void print_liste_regles(liste_regles *liste){
    if(liste == NULL){
        printf("List is empty.\n");
        return;
    }
    liste_regles *tmp = liste;
    while(tmp != NULL){
        if(tmp->conditions != NULL){
            liste_conditions *tmp_conditions = tmp->conditions;
            while(tmp_conditions != NULL){
                if(tmp_conditions->name != NULL){
                    printf("%s", tmp_conditions->name);
                }
                tmp_conditions = tmp_conditions->suivant;
            }
        }
        if(tmp->name != NULL){
            printf("->%s", tmp->name);
        }
        printf("\n");
        tmp = tmp->suivant;
    }
}