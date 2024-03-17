#include <string.h>
#include <ctype.h>
#include "../include/save.h"
#include "stdio.h"
#include "stdlib.h"
#include "../include/structures.h"
#include "../include/traitement.h"

/**
 * Cette fonction charge une liste de règles à partir d'un fichier dans une liste chaînée de règles.
 * Chaque ligne du fichier doit représenter une règle, avec les conditions et le nom de la règle séparés par "->".
 * Les conditions doivent être séparées par des espaces.
 * Le nom de la règle doit être suivi d'un point-virgule et d'un saut de ligne.
 *
 * @param filename Le nom du fichier à partir duquel charger les règles.
 * @param liste Un pointeur vers la tête de la liste chaînée dans laquelle charger les règles.
 */
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
        char *condition = strtok(conditions, " "); 
        while (condition != NULL)
        {
            add_condition(&liste_conditions, condition);
            condition = strtok(NULL, " "); 
        }
        add_regle(liste, regle, liste_conditions);
    }
    free(line);
    fclose(file);
}

/**
 * Cette fonction charge une liste de faits à partir d'un fichier dans une liste chaînée de faits de manière récursive.
 * Chaque ligne du fichier doit représenter un fait, qui est une chaîne de caractères terminée par un point-virgule et un saut de ligne.
 *
 * @param file Un pointeur vers le fichier à partir duquel charger les faits.
 * @param liste Un pointeur vers la tête de la liste chaînée dans laquelle charger les faits.
 */
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

/**
 * Cette fonction charge une liste de faits à partir d'un fichier dans une liste chaînée de faits.
 * Chaque ligne du fichier doit représenter un fait, qui est une chaîne de caractères terminée par un point-virgule et un saut de ligne.
 *
 * @param filename Le nom du fichier à partir duquel charger les faits.
 * @param liste Un pointeur vers la tête de la liste chaînée dans laquelle charger les faits.
 */
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

/**
 * Cette fonction divise une chaîne de caractères contenant plusieurs faits en faits individuels et les ajoute à deux listes de faits.
 * Les faits dans la chaîne de caractères doivent être séparés par des espaces.
 *
 * @param liste Un pointeur vers la tête de la première liste de faits à laquelle ajouter les faits.
 * @param nouveaux_faits Un pointeur vers la tête de la deuxième liste de faits à laquelle ajouter les faits.
 * @param faits La chaîne de caractères contenant les faits à diviser et à ajouter aux listes.
 */
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

/**
 * Cette fonction ajoute un fait à un fichier.
 * Le fait est une chaîne de caractères qui est ajoutée à la fin du fichier, suivie d'un point-virgule.
 *
 * @param fait La chaîne de caractères représentant le fait à ajouter au fichier.
 * @param file Un pointeur vers le fichier dans lequel ajouter le fait.
 */
void ajoute_fait_fichier(char *fait, FILE *file)
{
    if (strcmp(fait, " ") == 0)
    {
        return; 
    }

    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
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

/**
 * Cette fonction enregistre une liste de faits dans un fichier de manière récursive.
 * Chaque fait est une chaîne de caractères qui est ajoutée à la fin du fichier, suivie d'un point-virgule.
 *
 * @param nouveaux_faits Un pointeur vers la tête de la liste de faits à enregistrer.
 * @param filename Le nom du fichier dans lequel enregistrer les faits.
 * @param file Un pointeur vers le fichier dans lequel enregistrer les faits.
 */
void enregistrer_liste_fait_recursif (liste_faits *nouveaux_faits, char *filename, FILE *file)
{
    if(nouveaux_faits == NULL)
    {
        return;
    }
    ajoute_fait_fichier(nouveaux_faits->fait, file);
    enregistrer_liste_fait_recursif(nouveaux_faits->suivant, filename, file);
}

/**
 * Cette fonction enregistre une liste de faits dans un fichier.
 * Chaque fait est une chaîne de caractères qui est ajoutée à la fin du fichier, suivie d'un point-virgule.
 *
 * @param nouveaux_faits Un pointeur vers la tête de la liste de faits à enregistrer.
 * @param filename Le nom du fichier dans lequel enregistrer les faits.
 */
void enregistrer_liste_fait(liste_faits *nouveaux_faits, char *filename)
{
    FILE *file = fopen(filename, "a+");
    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }
    enregistrer_liste_fait_recursif(nouveaux_faits, filename, file);
    fclose(file);
}

/**
 * Cette fonction enregistre une liste de règles dans un fichier.
 * Chaque règle est une chaîne de caractères qui est ajoutée à la fin du fichier, suivie d'un point-virgule.
 *
 * @param nouvelles_regles Un pointeur vers la tête de la liste de règles à enregistrer.
 * @param filename Le nom du fichier dans lequel enregistrer les règles.
 */
void enregistrer_liste_regle(liste_regles *nouvelles_regles, char *filename)
{
    FILE *file = fopen(filename, "a+");
    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }
    enregistrer_liste_regle_recursif(nouvelles_regles, file);
    fclose(file);
}

/**
 * Cette fonction enregistre une liste de règles dans un fichier de manière récursive.
 * Chaque règle est une chaîne de caractères qui est ajoutée à la fin du fichier, suivie d'un point-virgule.
 *
 * @param nouvelles_regles Un pointeur vers la tête de la liste de règles à enregistrer.
 * @param file Un pointeur vers le fichier dans lequel enregistrer les règles.
 */
void enregistrer_liste_regle_recursif (liste_regles *nouvelles_regles, FILE *file)
{
    if(nouvelles_regles == NULL)
    {
        return;
    }
    char * condition = regle_en_chaine("", nouvelles_regles->conditions);
    char *regle = strcat(condition, "-> ");
    regle = strcat(regle, nouvelles_regles->name);
    ajoute_regle_fichier(file, regle);
    enregistrer_liste_regle_recursif(nouvelles_regles->suivant, file);
}
/**
 * Cette fonction ajoute une règle à un fichier.
 * La règle est une chaîne de caractères qui est ajoutée à la fin du fichier, suivie d'un point-virgule.
 *
 * @param file Un pointeur vers le fichier dans lequel ajouter la règle.
 * @param regle La chaîne de caractères représentant la règle à ajouter au fichier.
 */
void ajoute_regle_fichier(FILE * file, char *regle)
{
    if (file == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }
    if (regle == NULL || regle[0] == '\0')
    {
        printf(" La règle est vide\n");
        return;
    }
    size_t length = strlen(regle);
    
    if (regle[length - 1] == '\n')
    {
        regle[length - 1] = '\0';
    }
    fprintf(file, "\n%s;", regle);
}

/**
 * Cette fonction convertit une règle et une liste de conditions en une seule chaîne de caractères.
 * Chaque condition est ajoutée à la règle, séparée par un espace.
 *
 * @param regle Une chaîne de caractères représentant la règle à laquelle ajouter les conditions.
 * @param conditions Un pointeur vers la tête de la liste de conditions à ajouter à la règle.
 * @return Une nouvelle chaîne de caractères contenant la règle et les conditions.
 */
char *regle_en_chaine(char *regle, liste_conditions *conditions) {
    
    if (conditions == NULL)
        return regle;
    
    size_t regle_len = strlen(regle);
    
    size_t total_len = regle_len;
    liste_conditions *cur_condition = conditions;
    while (cur_condition != NULL) {
        total_len += strlen(cur_condition->name) + 1; 
        cur_condition = cur_condition->suivant;
    }

    char *new_regle = (char *)malloc((total_len + 1) * sizeof(char)); 
    if (new_regle == NULL) {
        printf("Erreur d'allocation de mémoire\n");
        return NULL;
    }
    
    strcpy(new_regle, regle);
    
    cur_condition = conditions;
    while (cur_condition != NULL) {
        strcat(new_regle, cur_condition->name);
        strcat(new_regle, " ");
        cur_condition = cur_condition->suivant;
    }
    return new_regle;
}



/**
 * Cette fonction insère une règle dans une base de règles existante et une nouvelle liste de règles.
 * La règle est une chaîne de caractères qui est divisée en conditions et en nom de règle.
 * Les conditions et le nom de la règle sont séparés par "->".
 * Les conditions sont ajoutées à une liste chaînée de conditions.
 * Le nom de la règle et la liste de conditions sont utilisés pour créer une nouvelle règle qui est ajoutée aux deux listes de règles.
 *
 * @param regle Une chaîne de caractères représentant la règle à insérer.
 * @param regles Un pointeur vers la tête de la liste de règles existante dans laquelle insérer la règle.
 * @param nouvelles_regles Un pointeur vers la tête de la nouvelle liste de règles dans laquelle insérer la règle.
 */
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



/**
 * Cette fonction clone une liste de conditions.
 * Elle crée une nouvelle liste de conditions qui est une copie de la liste de conditions source.
 *
 * @param dest Un pointeur vers la tête de la liste de conditions de destination.
 * @param src Un pointeur vers la tête de la liste de conditions source.
 */
void clone_conditions(liste_conditions **dest, liste_conditions *src)
{
    if (src == NULL) 
    {
        return;
    }
    add_condition(dest, src->name);
    clone_conditions(dest, src->suivant);
}
