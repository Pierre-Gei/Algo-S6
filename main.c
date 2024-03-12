//
// Created by Pierre Geiguer on 11/03/2024.
//

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "structures.h"
#include "save.h"
#include "traitement.h"
#include "backwards.h"
#include "forward.h"
#include "menu_terminal.h"

#define TAILLE_MAX 100

int main(void)
{
    menu();
    char *but = "pain_au_chocolat";
    liberer_liste_faits(&faits);
    return 0;
}