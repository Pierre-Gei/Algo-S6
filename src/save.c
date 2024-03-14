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

void load_to_list(char *filename, liste_regles *liste){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Error while opening file");
        exit(1);
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while((read = getline(&line, &len, file)) != -1){
        char *token = strtok(line, "->");
        if(token == NULL){
            continue;
        }
        char *conditions = token;
        char *regle = strtok(NULL, ";\n");
        if(regle == NULL){
            continue;
        }
        // Trim leading and trailing whitespace from the rule name
        while(isspace((unsigned char)*regle) || *regle == '>') regle++;
        if(*regle != 0) {
            char *end = regle + strlen(regle) - 1;
            while(end > regle && isspace((unsigned char)*end)) end--;
            *(end+1) = 0;
        }
        liste_conditions *liste_conditions = init_liste_conditions();
        char *condition = strtok(conditions, " "); // Split conditions by space
        while(condition != NULL){
            add_condition(liste_conditions, condition);
            condition = strtok(NULL, " "); // Split conditions by space
        }
        add_regle(liste, regle, liste_conditions);
    }
    free(line);
    fclose(file);
}


void load_faits_to_list(char *filename, liste_faits *liste){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Error while opening file");
        exit(1);
    }
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    while((read = getline(&line, &len, file)) != -1){
        char *token = strtok(line, ";\n");
        if(token == NULL){
            continue;
        }
        add_fait(liste, token);
    }
    free(line);
    fclose(file);
}