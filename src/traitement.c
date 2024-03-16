//
// Created by Pierre Geiguer on 12/03/2024.
//


#include <string.h>
#include "../include/traitement.h"
#include "stdio.h"
#include "stdlib.h"
#include "../include/structures.h"

/* `add_regle` est une fonction qui ajoute une nouvelle règle à une liste de règles. Il prend
l'adresse de la tête de liste, le nom de la règle et une liste de conditions associées à la
règle. Si la liste est vide, il crée un nouveau nœud pour la règle et le place au début de la
liste. Si la liste n'est pas vide, il ajoute récursivement la règle à la fin de la liste. */
void add_regle(liste_regles **liste, char *name, liste_conditions *conditions)
{
    if (*liste == NULL) {
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
        add_regle(&((*liste)->suivant), name, conditions);
    }
}


/* La fonction `add_condition` est chargée d'ajouter une nouvelle condition à une liste de conditions.
Il faut un pointeur vers la tête de la liste (« liste ») et le nom de la condition à ajouter (« nom
»). */
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



/* La fonction `add_condition_to_regle` est chargée d'ajouter une nouvelle condition à une règle
spécifique dans une liste de règles. Il prend l'adresse du tête de liste des règles, le nom de la
règle à laquelle la condition doit être ajoutée et le nom de la condition à ajouter. */
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



/* La fonction `print_liste_regles` se charge d'imprimer la liste des règles de manière récursive. Cela
commence par vérifier si la liste est vide. Si la liste n'est pas vide, elle parcourt chaque règle
de la liste. Pour chaque règle, il imprime les conditions associées puis le nom de la règle
elle-même. Ce processus se poursuit de manière récursive jusqu'à ce que toutes les règles de la
liste aient été imprimées. */
void print_liste_regles(liste_regles *liste) /////////// RENDRE RECURSIF
{
    printf("Liste de regles :\n");
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

/* La fonction `add_fait` est chargée d'ajouter un nouveau fait à une liste de faits. Il faut un
pointeur vers la tête de liste (« liste ») et le nom du fait à ajouter (« fait »). */
void add_fait(liste_faits **liste, char *fait)
{
    if (*liste == NULL) {
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
        add_fait(&((*liste)->suivant), fait);
    }
}

/* La fonction `affiche_liste_faits` se charge d'afficher la liste des faits. Il prend en paramètre un
pointeur vers la tête de la liste de faits (`liste`). */
void affiche_liste_faits(liste_faits *liste)
{
    if (liste == NULL)
    {
        printf("La liste est vide\n");
        return;
    }
    printf("Liste des faits:\n");
    while (liste != NULL)
    {
        printf("%s\n", liste->fait);
        liste = liste->suivant;
    }
}



/* La fonction `liberer_liste_reponses` se charge de libérer la mémoire allouée pour une liste chaînée
de réponses. Il prend un pointeur vers la tête de la liste en tant que paramètre et parcourt la
liste de manière récursive pour libérer chaque nœud. */
void  liberer_liste_reponses(liste_reponses **liste)
{
    if (*liste == NULL)
        return;
    liberer_liste_reponses(&(*liste)->suivant);
    free((*liste)->name);
    free(*liste);
    *liste = NULL;
}

/* La fonction `liberer_liste_faits(liste_faits **liste)` se charge de libérer la mémoire allouée pour
une liste chaînée de faits. Il parcourt la liste de manière récursive et libère chaque nœud ainsi
que sa mémoire associée.*/
void liberer_liste_faits(liste_faits **liste)
{
    if (*liste == NULL)
        return;
    liberer_liste_faits(&(*liste)->suivant);
    free((*liste)->fait);
    free(*liste);
    *liste = NULL;
}


/* La fonction `liberer_liste_conditions(liste_conditions **liste)` se charge de libérer la mémoire
 * allouée pour une liste chaînée de conditions. Elle parcourt la liste de manière récursive et
 * libère chaque nœud ainsi que sa mémoire associée.*/
void liberer_liste_conditions(liste_conditions **liste)
{
    if (*liste == NULL)
        return;

    liberer_liste_conditions(&((*liste)->suivant));

    free((*liste)->name);

    liste_conditions *suivant = (*liste)->suivant;

    free(*liste);

    *liste = suivant;
}

/* La fonction `liberer_liste_regles(liste_regles **liste)` se charge de libérer la mémoire allouée pour
 * une liste chaînée de règles. Elle parcourt la liste de manière récursive et libère chaque nœud
 * ainsi que sa mémoire associée.*/
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

/* La fonction `affiche_faits_possibles` est chargée d'afficher les faits possibles en fonction de la
 * base de faits. Elle prend une liste de règles en paramètre et parcourt chaque règle pour extraire
 * les faits possibles. Elle utilise une liste de réponses pour éviter d'afficher plusieurs fois le
 * même fait. */
void affiche_faits_possibles(liste_regles *liste) {
    liste_reponses *liste_reponses = NULL;
    printf("Liste des faits possibles d'après la base de faits : \n");

    while (liste != NULL) {
        liste_conditions *conditions = liste->conditions;
        while (conditions != NULL) {
            if (conditions->name != NULL) {
                if (!reponse_deja_donnee(liste_reponses, conditions->name)) {
                    printf("  -%s\n", conditions->name);
                    ajouter_reponse(&liste_reponses, conditions->name);
                }
            }
            conditions = conditions->suivant;
        }

        if (liste->name != NULL) {
            if (!reponse_deja_donnee(liste_reponses, liste->name)) {
                printf("  -%s\n", liste->name);
                ajouter_reponse(&liste_reponses, liste->name);
            }
        }

        liste = liste->suivant;
    }

    liberer_liste_reponses(&liste_reponses);
}

/* La fonction `reponse_deja_donnee` vérifie si une réponse a déjà été donnée. Elle prend une liste de
 * réponses et une réponse en paramètre et parcourt la liste pour vérifier si la réponse est déjà
 * présente. */
bool reponse_deja_donnee(liste_reponses *liste, char *reponse) {
    while (liste != NULL) {
        if (strcmp(liste->name, reponse) == 0) {
            return true;
        }
        liste = liste->suivant;
    }
    return false;
}

/* La fonction `ajouter_reponse` est chargée d'ajouter une réponse à une liste de réponses. Elle prend
 * un pointeur vers la tête de la liste de réponses et une réponse en paramètre. */
void ajouter_reponse(liste_reponses **liste, char *reponse) {
    liste_reponses *nouvelle_reponse = malloc(sizeof(liste_reponses));
    nouvelle_reponse->name = strdup(reponse);
    nouvelle_reponse->suivant = *liste;
    *liste = nouvelle_reponse;
}