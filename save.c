//
// Created by Pierre Geiguer on 12/03/2024.
//

#include "save.h"

/* La fonction `load_to_list` est responsable du chargement des règles à partir d'un fichier spécifié
par `filename` dans une liste chaînée de règles pointées par `liste`. */
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

/* La fonction `load_faits_to_list_recursive(FILE *file, liste_faits **liste)` est chargée de lire
récursivement les lignes d'un fichier pointé par `file` et d'ajouter chaque ligne en tant que fait à
une liste chaînée de faits pointés par `liste`. */
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

/* La fonction `load_faits_to_list` est responsable du chargement des faits à partir d'un fichier
spécifié par `filename` dans une liste chaînée de faits pointée par `liste`. Il lit les lignes du
fichier de manière récursive et ajoute chaque ligne comme un fait à la liste chaînée. */
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

/* `divide_and_add_faits` est une fonction qui prend une chaîne de faits (`faits`), la divise en
    faits individuels en utilisant l'espace comme délimiteur, ajoute chaque fait individuel à une
    liste chaînée de faits pointée par `liste`, et ajoute également chaque fait vers un fichier
    spécifié par `filename` à l'aide de la fonction `ajoute_fait_fichier`. */
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

/* La fonction `ajoute_fait_fichier(char *filename, char *fait)` se charge d'ajouter un fait (`fait`) à
un fichier spécifié par `filename`. Voici un aperçu de ce que fait la fonction : */
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


/* La fonction `ajoute_regle_fichier(char *filename, char *regle)` est chargée d'ajouter une règle
(`regle`) à un fichier spécifié par `filename`. Il ouvre le fichier en mode ajout, supprime tous les
caractères de nouvelle ligne à la fin de la règle, puis écrit la règle suivie d'un point-virgule
dans le fichier. Enfin, il ferme le fichier. */
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