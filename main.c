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
    // liste_regles *liste = NULL;
    // // rempli la liste
    // liste_conditions *conditions = NULL;
    // // remplis toi meme la liste conditions et ajoute la à la liste regles
    // conditions = ajout_condition(conditions, "tomate_sechee");
    // conditions = ajout_condition(conditions, "oignon");
    // conditions = ajout_condition(conditions, "epice");

    // liste = ajout_regle(liste, "sauce", conditions);

    // conditions = NULL;
    // conditions = ajout_condition(conditions, "plante");

    // liste = ajout_regle(liste, "tomate", conditions);

    // affiche_liste_regle(liste);

    // liste_faits *faits = NULL;
    // faits = ajout_fait(faits, "plante_aromatique");
    // faits = ajout_fait(faits, "oignon");
    // affiche_liste_faits(faits);

    liste_reponses *reponses = NULL;

    // char * but = "sauce";
    //  if(chainage_arriere(but, liste, faits) == true){
    //     printf("On peut atteindre %s \n", but);
    // } else {
    //     printf("On ne peut pas atteindre %s \n", but);
    // }

    parcours(faits, liste, &reponses);
    affiche_liste_reponses(reponses);

    // liberer_liste_reponses(&reponses);
    // liberer_liste_faits(&faits);
    // liberer_liste_regles(&liste);
    return 0;
}