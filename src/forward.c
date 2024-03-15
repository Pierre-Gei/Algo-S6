//
// Created by Pierre Geiguer on 11/03/2024.
//

#include "../include/forward.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/traitement.h"
#include "../include/structures.h"
#include "../include/forward.h"

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

int doublon_reponse (liste_reponses *liste, char *reponse)
{
    if (liste == NULL)
        return 0;
    if (strcmp(liste->name, reponse) == 0)
        return 1;
    return doublon_reponse(liste->suivant, reponse);
}

int doublon_fait (liste_faits *liste, char *fait)
{
    if (liste == NULL)
        return 0;
    if (strcmp(liste->fait, fait) == 0)
        return 1;
    return doublon_fait(liste->suivant, fait);
}

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

void copier_liste_reponses(liste_reponses *src, liste_reponses **dest)
{
    if (src == NULL)
        return;
    *dest = ajout_reponse(*dest, src->name);
    copier_liste_reponses(src->suivant, dest);
}

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