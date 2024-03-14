//
// Created by Pierre Geiguer on 12/03/2024.
//

#include <string.h>
#include "traitement.h"
#include "stdio.h"
#include "stdlib.h"
#include "structures.h"

void add_regle(liste_regles **liste, char *name, liste_conditions *conditions)
{
    if (*liste == NULL) {
        // Si la liste est vide, créer un nouveau nœud et le placer en tête de liste
        liste_regles *new = malloc(sizeof(liste_regles));
        if (new == NULL) {
            printf("Erreur: Impossible d'allouer de la mémoire\n");
            exit(1);
        }

        new->name = malloc(strlen(name) + 1);
        if (new->name == NULL) {
            printf("Erreur: Impossible d'allouer de la mémoire\n");
            exit(1);
        }
        strcpy(new->name, name);

        new->conditions = conditions;
        new->suivant = NULL;

        *liste = new;
    } else {
        // Appel récursif pour ajouter la règle à la fin de la liste
        add_regle(&((*liste)->suivant), name, conditions);
    }
}


void add_condition(liste_conditions **liste, char *name)
{
    if (*liste == NULL) {
        // Si la liste est vide, créer un nouveau nœud et le placer en tête de liste
        liste_conditions *new = malloc(sizeof(liste_conditions));
        if (new == NULL) {
            printf("Erreur: Impossible d'allouer de la mémoire\n");
            exit(1);
        }
        new->name = malloc(strlen(name) + 1);
        if (new->name == NULL) {
            printf("Erreur: Impossible d'allouer de la mémoire\n");
            exit(1);
        }
        strcpy(new->name, name);
        new->suivant = NULL;
        *liste = new;
    } else {
        // Appel récursif pour ajouter la condition à la fin de la liste
        add_condition(&((*liste)->suivant), name);
    }
}



void add_condition_to_regle(liste_regles **liste, char *name_regle, char *name_condition)
{
    if (*liste == NULL) {
        printf("Erreur: La règle '%s' n'existe pas dans la liste.\n", name_regle);
        return;
    }

    if (strcmp((*liste)->name, name_regle) == 0) {
        add_condition(&((*liste)->conditions), name_condition);
        return;
    }

    // Appel récursif sur le prochain élément de la liste
    add_condition_to_regle(&((*liste)->suivant), name_regle, name_condition);
}



void print_liste_regles(liste_regles *liste) /////////// RENDRE RECURSIF
{
    if (liste == NULL)
    {
        printf("List is empty.\n");
        return;
    }
    liste_regles *tmp = liste;
    while (tmp != NULL)
    {
        if (tmp->conditions != NULL)
        {
            liste_conditions *tmp_conditions = tmp->conditions;
            while (tmp_conditions != NULL)
            {
                if (tmp_conditions->name != NULL)
                {
                    printf("%s ", tmp_conditions->name);
                }
                tmp_conditions = tmp_conditions->suivant;
            }
        }
        if (tmp->name != NULL)
        {
            printf("-> %s;", tmp->name);
        }
        printf("\n");
        tmp = tmp->suivant;
    }
}

void add_fait(liste_faits **liste, char *fait)
{
    if (*liste == NULL) {
        // Cas de base : la liste est vide, donc créer un nouveau noeud et le placer en tête de liste
        liste_faits *new = malloc(sizeof(liste_faits));
        if (new == NULL) {
            printf("Erreur: Impossible d'allouer de la mémoire\n");
            exit(1);
        }
        new->fait = malloc(strlen(fait) + 1);
        if (new->fait == NULL) {
            printf("Erreur: Impossible d'allouer de la mémoire\n");
            exit(1);
        }
        strcpy(new->fait, fait);
        new->suivant = NULL;
        *liste = new;
    } else {
        // Cas récursif : passer à l'élément suivant dans la liste
        add_fait(&((*liste)->suivant), fait);
    }
}

<<<<<<< HEAD

void print_liste_faits(liste_faits *liste)
{
    printf("Printing list of facts:\n");
    if (liste == NULL)
    {
=======
void print_liste_faits(liste_faits *liste){
    if(liste == NULL){
>>>>>>> 7062c6814f217e61e381e264626f00df74e95b23
        printf("List is empty.\n");
        return;
    }
    liste_faits *tmp = liste;
    while (tmp != NULL)
    {
        if (tmp->fait != NULL)
        {
            printf("%s;\n", tmp->fait);
        }
        tmp = tmp->suivant;
    }
}



void  liberer_liste_reponses(liste_reponses **liste)
{
    if (*liste == NULL)
        return;
    liberer_liste_reponses(&(*liste)->suivant);
    free((*liste)->name);
    free(*liste);
    *liste = NULL;
}

void liberer_liste_faits(liste_faits **liste)
{
    if (*liste == NULL)
        return;
    liberer_liste_faits(&(*liste)->suivant);
    free((*liste)->fait);
    free(*liste);
    *liste = NULL;
}

void liberer_liste_conditions(liste_conditions **liste)
{
    if (*liste == NULL)
        return;
    liberer_liste_conditions(&(*liste)->suivant);
    free((*liste)->name);
    free(*liste);
    *liste = NULL;
}

void liberer_liste_regles(liste_regles **liste)
{
    if (*liste == NULL)
        return;
    liberer_liste_regles(&(*liste)->suivant);
    liberer_liste_conditions(&(*liste)->conditions);
    free((*liste)->name);
    free(*liste);
    *liste = NULL;
}

