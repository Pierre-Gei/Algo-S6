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

void divide_and_add_faits(liste_faits **liste, char *faits, char *filename)
{
    char *fait = strtok(faits, " ");
    while (fait != NULL)
    {
        add_fait(liste, fait);
        ajoute_fait_fichier(filename, fait);
        fait = strtok(NULL, " ");
    }
}

void ajoute_fait_fichier(char *filename, char *fait)
{
    if (strcmp(fait, " ") == 0)
    {
        return; // Skip saving if the word is a space
    }

    FILE *file = fopen(filename, "a+");
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
    fclose(file);
}

void ajoute_regle_fichier(char *filename, char *regle)
{
    FILE *file = fopen(filename, "a+");
    if (file == NULL)
    {
        printf("Error while opening file");
        return;
    }
    size_t length = strlen(regle);
    if (regle[length - 1] == '\n')
    {
        regle[length - 1] = '\0';
    }
    fprintf(file, "\n%s;", regle);
    fclose(file);
}