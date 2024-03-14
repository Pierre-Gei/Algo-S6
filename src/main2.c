//
// Created by Pierre Geiguer on 11/03/2024.
//

#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "../include/structures.h"
#include "../include/save.h"
#include "../include/traitement.h"
#include "../include/backwards.h"
#include "../include/affichage.h"

int main(void){
    char *but = "pain_au_chocolat";
    liste_regles *liste = init_liste_regles();
    load_to_list("regles.kbs", liste);
    liste_faits *faits = init_liste_faits();
    liste_faits *faits_manquants = init_liste_faits();
    load_faits_to_list("faits.kbs", faits);
    if(chainage_arriere(but, liste, faits, faits_manquants) == true){
        printf("On peut atteindre %s \n", but);
    } else {
        printf("On ne peut pas atteindre %s \n", but);
    }
    printf("Faits manquants: \n");
    print_liste_faits(faits_manquants);
    free_liste_faits(faits_manquants);
    free_liste_regles(liste);
    free_liste_faits(faits);
    return 0;
}