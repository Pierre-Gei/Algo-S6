#include <stdbool.h>
#include <string.h>
#include "../include/backwards.h"
#include "stdio.h"
#include "stdlib.h"
#include "../include/structures.h"
#include "../include/save.h"
#include "../include/traitement.h"

bool chainage_arriere(char *But, liste_regles *Base_de_regles, liste_faits *Base_de_faits, liste_faits *Base_de_faits_manquants){
    if(fait_exists(Base_de_faits, But)){
        // Print the fact and the Rule that makes it
        printf("Fact exists: %s\n", But);
        return true;
    }
    else{
        liste_regles *Regle = Base_de_regles;
        while(Regle != NULL){
            if(Regle->name != NULL && strcmp(Regle->name, But) == 0){
                liste_conditions *Hypothese = Regle->conditions;
                bool Continue = true;
                while(Hypothese != NULL){
                    if(Hypothese->name != NULL){
                        if(!chainage_arriere(Hypothese->name, Base_de_regles, Base_de_faits, Base_de_faits_manquants)){
                            add_fait(&Base_de_faits_manquants, Hypothese->name); // Add the missing fact to the missing facts list
                            // Check if there is a rule that can make the missing fact
                            if(chainage_arriere(Hypothese->name, Base_de_regles, Base_de_faits, Base_de_faits_manquants)){
                                printf("Found a rule to make the missing fact: %s\n", Hypothese->name);
                            } else {
                                Continue = false;
                            }
                        }
                    }
                    Hypothese = Hypothese->suivant;
                }
                if(Continue){
                    return true;
                }
            }
            Regle = Regle->suivant;
        }
    }
    return false;
}

bool fait_exists(liste_faits *Base_de_faits, char *fait){
    liste_faits *tmp = Base_de_faits;
    while(tmp != NULL){
        if(fait != NULL && tmp->fait != NULL && strcmp(tmp->fait, fait) == 0){
            return true;
        }
        tmp = tmp->suivant;
    }
    return false;
}