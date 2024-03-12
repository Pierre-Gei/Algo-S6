//
// Created by Pierre Geiguer on 11/03/2024.
//

#include "stdio.h"
#include "stdlib.h"
#include "structures.h"
#include "save.h"
#include "traitement.h"

int main(void){
    printf("Hello world");
    liste_regles *liste = init_liste_regles();
    printf("init_liste_regles\n");
    load_to_list("regles.kbs", liste);
    printf("load_to_list\n");
    print_liste_regles(liste);

    return 0;
}