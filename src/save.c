//
// Created by Pierre Geiguer on 12/03/2024.
//

#include <string.h>
#include <ctype.h>
#include "../include/save.h"
#include "stdio.h"
#include "stdlib.h"
#include "../include/structures.h"
#include "../include/traitement.h"

void load_to_list(char *filename, liste_regles **liste)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Fichier inconnu\n");
        return;
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while ((read = getline(&line, &len, file)) != -1)
    {
        char *token = strtok(line, "->");
        if (token == NULL)
        {
            continue;
        }
        char *conditions = token;
        char *regle = strtok(NULL, ";\n");
        if (regle == NULL)
        {
            continue;
        }
        // Trim leading and trailing whitespace from the rule name
        while (isspace((unsigned char)*regle) || *regle == '>')
            regle++;
        if (*regle != 0)
        {
            char *end = regle + strlen(regle) - 1;
            while (end > regle && isspace((unsigned char)*end))
                end--;
            *(end + 1) = 0;
        }
        liste_conditions *liste_conditions = NULL;
        char *condition = strtok(conditions, " "); // Split conditions by space
        while (condition != NULL)
        {
            add_condition(&liste_conditions, condition);
            condition = strtok(NULL, " "); // Split conditions by space
        }
        add_regle(liste, regle, liste_conditions);
    }
    free(line);
    fclose(file);
}

void load_faits_to_list_recursive(FILE *file, liste_faits **liste)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    if ((read = getline(&line, &len, file)) != -1)
    {
        char *token = strtok(line, ";\n");
        if (token != NULL)
        {
            add_fait(liste, token);
        }
        free(line);
        load_faits_to_list_recursive(file, liste);
    }
    else
    {
        free(line);
        fclose(file);
    }
}

void load_faits_to_list(char *filename, liste_faits **liste)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Fichier inconnu \n");
        return;
    }
    load_faits_to_list_recursive(file, liste);
}

void divide_and_add_faits(liste_faits **liste,liste_faits **nouveaux_faits, char *faits)
{
    char *fait = strtok(faits, " ");
    while (fait != NULL)
    {
        add_fait(liste, fait);
        add_fait(nouveaux_faits, fait);
        fait = strtok(NULL, " ");
    }
}

void ajoute_fait_fichier(char *fait, FILE *file)
{
    if (strcmp(fait, " ") == 0)
    {
        return; // Skip saving if the word is a space
    }

    if (file == NULL)
    {
        printf("Error while opening file");
        return;
    }
    size_t length = strlen(fait);
    if (fait[length - 1] == '\n')
    {
        fait[length - 1] = '\0';
    }
    if (fait[0] == '\n')
    {
        fait++;
    }
    if (length > 0 && fait[length - 1] == ';')
    {
        fait[length - 1] = '\0';
    }
    fprintf(file, "\n%s;", fait);
}

void enregistrer_liste_fait_recursif (liste_faits *nouveaux_faits, char *filename, FILE *file)
{
    if(nouveaux_faits == NULL)
    {
        return;
    }
    ajoute_fait_fichier(nouveaux_faits->fait, file);
    enregistrer_liste_fait_recursif(nouveaux_faits->suivant, filename, file);
}

void enregistrer_liste_fait(liste_faits *nouveaux_faits, char *filename)
{
    FILE *file = fopen(filename, "a+");
    if (file == NULL)
    {
        printf("Error while opening file");
        return;
    }
    enregistrer_liste_fait_recursif(nouveaux_faits, filename, file);
    fclose(file);
}

void enregistrer_liste_regle(liste_regles *nouvelles_regles, char *filename)
{
    FILE *file = fopen(filename, "a+");
    if (file == NULL)
    {
        printf("Error while opening file");
        return;
    }
    enregistrer_liste_regle_recursif(nouvelles_regles, file);
    fclose(file);
}

void enregistrer_liste_regle_recursif (liste_regles *nouvelles_regles, FILE *file)
{
    printf("Enregistrement des regles\n");
    if(nouvelles_regles == NULL)
    {
        return;
    }
    char * condition = regle_en_chaine("", nouvelles_regles->conditions);
    char *regle = strcat(condition, "-> ");
    regle = strcat(regle, nouvelles_regles->name);
    printf("Regles : %s\n", regle);
    ajoute_regle_fichier(file, regle);
    enregistrer_liste_regle_recursif(nouvelles_regles->suivant, file);
}
void ajoute_regle_fichier(FILE * file, char *regle)
{
    if (file == NULL)
    {
        printf("Error while opening file");
        return;
    }
    if (regle == NULL || regle[0] == '\0')
    {
        printf("Empty rule provided");
        return;
    }
    size_t length = strlen(regle);
    
    if (regle[length - 1] == '\n')
    {
        regle[length - 1] = '\0';
    }
    fprintf(file, "\n%s;", regle);
}

char *regle_en_chaine(char *regle, liste_conditions *conditions) {
    printf("Regles en chaine\n");
    
    // Vérifier si les conditions sont nulles
    if (conditions == NULL)
        return regle;
    
    // Calculer la longueur de la règle actuelle
    size_t regle_len = strlen(regle);
    
    // Calculer la longueur totale de la règle avec les conditions
    size_t total_len = regle_len;
    liste_conditions *cur_condition = conditions;
    while (cur_condition != NULL) {
        total_len += strlen(cur_condition->name) + 1; // +1 pour l'espace
        cur_condition = cur_condition->suivant;
    }
    
    // Allouer de la mémoire pour la nouvelle règle
    char *new_regle = (char *)malloc((total_len + 1) * sizeof(char)); // +1 pour le caractère nul de fin de chaîne
    if (new_regle == NULL) {
        printf("Erreur d'allocation de mémoire\n");
        return NULL;
    }
    
    // Copier la règle existante dans la nouvelle chaîne
    strcpy(new_regle, regle);
    
    // Concaténer les noms des conditions à la règle
    cur_condition = conditions;
    while (cur_condition != NULL) {
        strcat(new_regle, cur_condition->name);
        strcat(new_regle, " ");
        cur_condition = cur_condition->suivant;
    }
    
    free(new_regle);
    
    return new_regle;
}



void insert_regle_base(char *regle, liste_regles **regles, liste_regles **nouvelles_regles)
{
    size_t length = strlen(regle);
    if (regle[length - 1] == '\n')
    {
        regle[length - 1] = '\0';
    }
    if (regle[0] == '\n')
    {
        regle++;
    }

    char * token = strtok(regle, " ");
    char * dernier = NULL;
    liste_conditions *conditions = NULL;
    while (token != NULL)
    {
        if (strcmp(token, "->") != 0)
        {
            add_condition(&conditions, token);
        }
        else
        {
            token = strtok(NULL, " ");
            if (token != NULL)
            {
                dernier = malloc(strlen(token) + 1);
                strcpy(dernier, token);
            }
        }
        token = strtok(NULL, " ");
    }
    if (dernier != NULL)
    {
        add_regle(regles, dernier, conditions);
        
        // Dupliquer la liste de conditions pour ajouter à nouvelles_regles
        liste_conditions *conditions_nouvelles = NULL;
        clone_conditions(&conditions_nouvelles, conditions);
        
        add_regle(nouvelles_regles, dernier, conditions_nouvelles);
        free(dernier);
    }
    else
    {
        printf("Erreur lors de la lecture de la règle\n");
    }
}



void clone_conditions(liste_conditions **dest, liste_conditions *src) 
{
    if (src == NULL) 
    {
        return;
    }
    add_condition(dest, src->name);
    clone_conditions(dest, src->suivant);
}
