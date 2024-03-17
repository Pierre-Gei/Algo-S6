//
// Created by quent on 14/03/2024.
//



#ifndef ALGO_S6_AFFICHAGE_H
#define ALGO_S6_AFFICHAGE_H

#endif //ALGO_S6_AFFICHAGE_H

#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "../gfxlib/include/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "../gfxlib/include/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "../gfxlib/include/ESLib.h" // Pour utiliser valeurAleatoire()
#include "structures.h"
#include "backwards.h"
#include "traitement.h"
#include "terminal_menu.h"

typedef enum {MenuPrincipal, Questionnaire, Liste, Arriere, Avant}
        StateAffichage;

void cercle(float centreX, float centreY, float rayon);
void gestionEvenement(EvenementGfx evenement);
int affiche(int argc, char **argv);


