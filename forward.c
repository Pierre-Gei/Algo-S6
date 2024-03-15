//
// Created by Pierre Geiguer on 11/03/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "traitement.h"
#include "forward.h"

/* La fonction `ajout_fait` est chargée d'ajouter un fait à une liste de faits dans un système basé sur
des règles. Voici un aperçu de ce que fait la fonction : */
liste_faits *ajout_fait(liste_faits *liste, char *fait)
{
    if (liste == NULL)
    {
        liste = (liste_faits *)malloc(sizeof(liste_faits));
        if (liste == NULL)
        {
            printf("Erreur: Impossible d'allouer de la mémoire\n");
            exit(1);
        }
        liste->fait = (char *)malloc(strlen(fait) + 1);
        if (liste->fait == NULL)
        {
            printf("Erreur: Impossible d'allouer de la mémoire\n");
            exit(1);
        }
        strcpy(liste->fait, fait);
        liste->suivant = NULL;
        return liste;
    }
    liste_faits *temp = liste;
    if (doublon_fait(temp, fait) == 1)
        return liste;

    liste->suivant = ajout_fait(liste->suivant, fait);
    return liste;
}

/* La fonction `liste_reponses *ajout_reponse(liste_reponses *liste, char *reponse)` est chargée
d'ajouter une réponse à une liste de réponses dans un système basé sur des règles. Voici un aperçu
de ce que fait la fonction : */
liste_reponses *ajout_reponse(liste_reponses *liste, char *reponse)
{
    if (liste == NULL)
    {
        liste = (liste_reponses *)malloc(sizeof(liste_reponses));
        if (liste == NULL)
        {
            printf("Erreur: Impossible d'allouer de la mémoire\n");
            exit(1);
        }
        liste->name = (char *)malloc(strlen(reponse) + 1);
        if (liste->name == NULL)
        {
            printf("Erreur: Impossible d'allouer de la mémoire\n");
            exit(1);
        }
        strcpy(liste->name, reponse);
        liste->suivant = NULL;
        return liste;
    }
    liste_reponses *temp = liste;
   if (doublon_reponse(temp, reponse) == 1)
        return liste;
    liste->suivant = ajout_reponse(liste->suivant, reponse);
    return liste;
}

/* La fonction `int doublon_reponse (liste_reponses *liste, char *reponse)` vérifie les doublons dans
une liste de réponses. Il parcourt la liste des réponses et compare chaque réponse avec la « réponse
» donnée. Si une réponse en double est trouvée, elle renvoie 1 ; sinon, elle renvoie 0. Cette
fonction permet de garantir que la même réponse n'est pas ajoutée plusieurs fois à la liste des
réponses. */
int doublon_reponse (liste_reponses *liste, char *reponse)
{
    if (liste == NULL)
        return 0;
    if (strcmp(liste->name, reponse) == 0)
        return 1;
    return doublon_reponse(liste->suivant, reponse);
}

/* La fonction `int doublon_fait (liste_faits *liste, char *fait)` vérifie les doublons dans une liste
de faits. Il parcourt récursivement la liste des faits et compare chaque fait avec le « fait »
donné. Si un fait en double est trouvé, il renvoie 1 ; sinon, elle renvoie 0. Cette fonction
garantit que le même fait n'est pas ajouté plusieurs fois à la liste des faits. */
int doublon_fait (liste_faits *liste, char *fait)
{
    if (liste == NULL)
        return 0;
    if (strcmp(liste->fait, fait) == 0)
        return 1;
    return doublon_fait(liste->suivant, fait);
}

/* La fonction `verifier_faits` vérifie si une condition spécifique est présente dans une liste de
faits. Il prend en entrée un pointeur vers une liste de faits (« faits ») et une condition à
vérifier (« condition »). */
int verifier_faits(liste_faits *faits, char *condition)
{
    if (faits == NULL)
        return -1;
    if (strcmp(faits->fait, condition) == 0)
        return 1;
    else if (faits->suivant != NULL)
        return verifier_faits(faits->suivant, condition);
    else
        return 0;
}

/* La fonction `verifier_conditions` vérifie si une condition spécifique est présente dans une liste de
faits. Il prend en entrée un pointeur vers une liste de faits (« faits ») et une condition à
vérifier (« conditions »). */
int verifier_conditions(liste_faits *faits, liste_conditions *conditions)
{
    if (conditions == NULL)
        return -1;
    if (verifier_faits(faits, conditions->name) == 1)
    {
        if (conditions->suivant == NULL)
            return 1;
        else if (conditions->suivant != NULL)
            return verifier_conditions(faits, conditions->suivant);
    }
    return 0;
}

/* La fonction `verif_totale` vérifie si toutes les conditions spécifiées dans une liste de règles
(`regles`) sont remplies en fonction des faits de la liste (`faits`). Si toutes les conditions d'une
règle sont satisfaites, la réponse associée à cette règle est ajoutée à la liste des réponses («
réponses »). De plus, le fait correspondant à la réponse est ajouté à la liste des faits. */
int verif_totale(liste_faits *faits, liste_regles *regles, liste_reponses **reponses)
{
    if (regles == NULL)
        return 0;
    if (verifier_conditions(faits, regles->conditions) == 1)
    {
        *reponses = ajout_reponse(*reponses, regles->name);
        faits = ajout_fait(faits, regles->name);
    }
    if (regles->suivant != NULL)
        return verif_totale(faits, regles->suivant, reponses);
    else
        return 1;
}

/* La fonction `parcours` parcourt récursivement une liste de règles (`regles`) et vérifie si toutes
les conditions spécifiées dans chaque règle sont remplies en fonction des faits de la liste
(`faits`). Si toutes les conditions d'une règle sont satisfaites, la réponse associée à cette règle
est ajoutée à la liste des réponses (« réponses »). De plus, le fait correspondant à la réponse est
ajouté à la liste des faits. */
int parcours(liste_faits *faits, liste_regles *regles, liste_reponses **reponses) 
{
    liste_reponses *anciennes_reponses = NULL;
    copier_liste_reponses(*reponses, &anciennes_reponses);

    int retour = verif_totale(faits, regles, reponses);
    if (retour == 0)
        return 0;

    if (compare_liste_reponses(anciennes_reponses, *reponses) == 0) {
        parcours(faits, regles, reponses);
    }

    liberer_liste_reponses(&anciennes_reponses);

    return 0;
}

/* La fonction `void copier_liste_reponses(liste_reponses *src, liste_reponses **dest)` est chargée de
copier une liste chaînée de réponses de la liste source `src` vers la liste de destination `dest`.
Il parcourt récursivement chaque nœud de la liste source et ajoute un nouveau nœud avec la même
réponse à la liste de destination. */
void copier_liste_reponses(liste_reponses *src, liste_reponses **dest)
{
    if (src == NULL)
        return;
    *dest = ajout_reponse(*dest, src->name);
    copier_liste_reponses(src->suivant, dest);
}

/* La fonction `compare_liste_reponses` compare deux listes chaînées de réponses (`liste1` et
`liste2`). Il vérifie récursivement si les réponses dans chaque nœud des deux listes sont les mêmes. */
int compare_liste_reponses(liste_reponses *liste1, liste_reponses *liste2)
{
    if (liste1 == NULL && liste2 == NULL)
        return 1;
    if (liste1 == NULL || liste2 == NULL)
        return 0;
    if (strcmp(liste1->name, liste2->name) != 0)
        return 0;
    return compare_liste_reponses(liste1->suivant, liste2->suivant);
}

/* La fonction `affiche_liste_reponses` se charge d'afficher le contenu d'une liste chaînée de
réponses. Il vérifie d'abord si la liste est vide et imprime un message si c'est le cas. Ensuite, il
parcourt la liste et imprime chaque réponse une par une jusqu'à atteindre la fin de la liste. Cette
fonction permet de visualiser les réponses stockées dans la liste chaînée à des fins de débogage ou
de sortie. */
void affiche_liste_reponses(liste_reponses *liste)
{
    if (liste == NULL)
    {
        printf("La liste est vide\n");
        return;
    }
    printf("Liste des réponses:\n");
    while (liste != NULL)
    {
        printf("%s\n", liste->name);
        liste = liste->suivant;
    }
}