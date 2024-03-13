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

int main(void)
{
    char *but = "pain_au_chocolat";
    liste_regles *liste = NULL;
    load_to_list("regles.kbs", &liste);
    liste_faits *faits = NULL;
    load_faits_to_list("faits.kbs", &faits);
    if(chainage_arriere(but, liste, faits) == true){
        printf("On peut atteindre %s \n", but);
    } else {
        printf("On ne peut pas atteindre %s \n", but);
    }

    liste_reponses *reponses = NULL;

    parcours(faits, liste, &reponses);
    affiche_liste_reponses(reponses);

    liberer_liste_reponses(&reponses);
    liberer_liste_faits(&faits);
    liberer_liste_regles(&liste);
    return 0;
}