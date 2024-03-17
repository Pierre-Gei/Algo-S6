//
// Created by Pierre Geiguer on 11/03/2024.
//

#ifndef ALGO_S6_STRUCTURES_H
#define ALGO_S6_STRUCTURES_H

typedef struct liste_regles {
    char *name;
    struct liste_conditions *conditions;
    struct liste_regles *suivant;
} liste_regles;

typedef struct liste_conditions {
    char *name;
    struct liste_conditions *suivant;
} liste_conditions;

typedef struct liste_faits {
    char *fait;
    struct liste_faits *suivant;
} liste_faits;

typedef struct liste_reponses {
    char *name;
    struct liste_reponses *suivant;
} liste_reponses;

#endif //ALGO_S6_STRUCTURES_H
