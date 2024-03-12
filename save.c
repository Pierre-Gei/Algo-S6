//
// Created by Pierre Geiguer on 12/03/2024.
//

#include <string.h>
#include "save.h"
#include "stdio.h"
#include "stdlib.h"
#include "structures.h"
#include "traitement.h"

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
        char *regle = strtok(NULL, "->");
        if(regle == NULL){
            continue;
        }
        regle = strtok(regle, "\n");
        if(regle == NULL){
            continue;
        }
        liste_conditions *liste_conditions = init_liste_conditions();
        char *condition = strtok(conditions, ";");
        while(condition != NULL){
            add_condition(liste_conditions, condition);
            condition = strtok(NULL, ";");
        }
        add_regle(liste, regle, liste_conditions);
    }
    free(line);
    fclose(file);
}