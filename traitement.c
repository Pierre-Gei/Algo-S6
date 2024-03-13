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
    liste_regles *new = malloc(sizeof(liste_regles));
    if (new == NULL) {
        printf("Erreur: Impossible d'allouer de la mémoire\n");
        exit(1);
    }

    new->name = malloc(strlen(name) + 1); // Allouer un octet supplémentaire pour le terminateur nul
    if (new->name == NULL) {
        printf("Erreur: Impossible d'allouer de la mémoire\n");
        exit(1);
    }
    strcpy(new->name, name);

    new->conditions = conditions;
    new->suivant = NULL;

    if (*liste == NULL) {
        *liste = new; // Si la liste est vide, le nouvel élément devient le premier
        return;
    }

    liste_regles *tmp = *liste;
    while (tmp->suivant != NULL) {
        tmp = tmp->suivant;
    }
    tmp->suivant = new; // Ajouter le nouvel élément à la fin de la liste
}


void add_condition(liste_conditions **liste, char *name)
{
    liste_conditions *new = malloc(sizeof(liste_conditions));
    if (new == NULL) {
        printf("Erreur: Impossible d'allouer de la mémoire\n");
        exit(1);
    }
    new->name = malloc(strlen(name) + 1); // Allouer un octet supplémentaire pour le terminateur nul
    if (new->name == NULL) {
        printf("Erreur: Impossible d'allouer de la mémoire\n");
        exit(1);
    }
    strcpy(new->name, name);
    new->suivant = NULL;

    if (*liste == NULL) {
        *liste = new; // Si la liste est vide, le nouvel élément devient le premier
        return;
    }

    liste_conditions *tmp = *liste;
    while (tmp->suivant != NULL) {
        tmp = tmp->suivant;
    }
    tmp->suivant = new; // Ajouter le nouvel élément à la fin de la liste
}


void add_condition_to_regle(liste_regles **liste, char *name_regle, char *name_condition)
{
    liste_regles *tmp = *liste;
    while (tmp != NULL)
    {
        if (strcmp(tmp->name, name_regle) == 0) // Utilisation de strcmp pour comparer les chaînes de caractères
        {
            add_condition(&(tmp->conditions), name_condition); // Passer l'adresse du pointeur de liste_conditions
            return; // Sortir de la fonction une fois que la condition est ajoutée à la règle
        }
        tmp = tmp->suivant;
    }
    printf("Erreur: La règle '%s' n'existe pas dans la liste.\n", name_regle);
}


void print_liste_regles(liste_regles *liste)
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
    liste_faits *new = malloc(sizeof(liste_faits));
    if (new == NULL) {
        printf("Erreur: Impossible d'allouer de la mémoire\n");
        exit(1);
    }
    new->fait = malloc(strlen(fait) + 1); // Allouer un octet supplémentaire pour le terminateur nul
    if (new->fait == NULL) {
        printf("Erreur: Impossible d'allouer de la mémoire\n");
        exit(1);
    }
    strcpy(new->fait, fait);
    new->suivant = NULL;

    if (*liste == NULL) {
        *liste = new; // Si la liste est vide, le nouvel élément devient le premier
        return;
    }

    liste_faits *tmp = *liste;
    while (tmp->suivant != NULL) {
        tmp = tmp->suivant;
    }
    tmp->suivant = new; // Ajouter le nouvel élément à la fin de la liste
}


void print_liste_faits(liste_faits *liste)
{
    printf("Printing list of facts:\n");
    if (liste == NULL)
    {
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

void free_liste_regles(liste_regles *liste)
{
    liste_regles *tmp = liste;
    while (tmp != NULL)
    {
        liste_regles *next = tmp->suivant;
        free(tmp->name);
        free_liste_conditions(tmp->conditions);
        free(tmp);
        tmp = next;
    }
}

void free_liste_conditions(liste_conditions *liste)
{
    liste_conditions *tmp = liste;
    while (tmp != NULL)
    {
        liste_conditions *next = tmp->suivant;
        free(tmp->name);
        free(tmp);
        tmp = next;
    }
}

void free_liste_faits(liste_faits *liste)
{
    liste_faits *tmp = liste;
    while (tmp != NULL)
    {
        liste_faits *next = tmp->suivant;
        free(tmp->fait);
        free(tmp);
        tmp = next;
    }
}

liste_conditions *ajout_condition(liste_conditions *liste, char *condition)
{
    // Si la liste est vide
    if (liste == NULL)
    {
        liste = (liste_conditions *)malloc(sizeof(liste_conditions));
        if (liste == NULL)
        {
            printf("Erreur: Impossible d'allouer de la mémoire\n");
            exit(1);
        }
        liste->name = (char *)malloc(strlen(condition) + 1);
        if (liste->name == NULL)
        {
            printf("Erreur: Impossible d'allouer de la mémoire\n");
            exit(1);
        }
        strcpy(liste->name, condition);
        liste->suivant = NULL;
        return liste;
    }

    // Si la liste n'est pas vide, parcourir récursivement jusqu'à la fin
    liste->suivant = ajout_condition(liste->suivant, condition);
    return liste;
}

liste_regles *ajout_regle(liste_regles *liste, char *regle, liste_conditions *conditions)
{
    // Si la liste est vide
    if (liste == NULL)
    {
        liste = (liste_regles *)malloc(sizeof(liste_regles));
        if (liste == NULL)
        {
            printf("Erreur: Impossible d'allouer de la mémoire\n");
            exit(1);
        }
        liste->name = (char *)malloc(strlen(regle) + 1);
        if (liste->name == NULL)
        {
            printf("Erreur: Impossible d'allouer de la mémoire\n");
            exit(1);
        }
        strcpy(liste->name, regle);
        liste->conditions = conditions;
        liste->suivant = NULL;
        return liste;
    }

    // Si la liste n'est pas vide, parcourir récursivement jusqu'à la fin
    liste->suivant = ajout_regle(liste->suivant, regle, conditions);
    return liste;
}

void affiche_liste_regle(liste_regles *liste)
{
    if (liste == NULL)
    {
        printf("Liste vide\n");
        return;
    }
    liste_regles *tmp = liste;
    while (tmp != NULL)
    {
        printf("%s\n", tmp->name);
        affiche_liste_condition(tmp->conditions);
        tmp = tmp->suivant;
    }
}

void affiche_liste_condition(liste_conditions *liste)
{
    if (liste == NULL)
    {
        printf("Liste vide\n");
        return;
    }
    liste_conditions *tmp = liste;
    while (tmp != NULL)
    {
        printf("%s\n", tmp->name);
        tmp = tmp->suivant;
    }
}
