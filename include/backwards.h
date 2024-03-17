#ifndef ALGO_S6_BACKWARDS_H
#define ALGO_S6_BACKWARDS_H

#include "structures.h"

bool chainage_arriere(char *But, liste_regles *Base_de_regles, liste_faits *Base_de_faits, liste_faits *Base_de_faits_manquants);
bool fait_exists(liste_faits *Base_de_faits, char *fait);

#endif //ALGO_S6_BACKWARDS_H
