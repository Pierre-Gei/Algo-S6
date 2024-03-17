#include <stdbool.h>
#include <string.h>
#include "../include/backwards.h"
#include "stdio.h"
#include "stdlib.h"
#include "../include/structures.h"
#include "../include/save.h"
#include "../include/traitement.h"

/**
 * La fonction "chainage_arriere" vérifie si un objectif peut être atteint par chaînage arrière en
 * utilisant un ensemble de règles et de faits.
 * 
 * @param But Le paramètre «But» est un pointeur vers un tableau de caractères, qui représente
 * probablement le but ou la cible que nous essayons d'atteindre dans l'algorithme de chaînage arrière.
 * Il peut s'agir d'un fait ou d'une déclaration spécifique que nous essayons de prouver ou de déduire
 * en utilisant les règles et les faits disponibles dans la base de connaissances.
 * @param Base_de_regles Le paramètre `Base_de_regles` est un pointeur vers une liste chaînée de
 * règles. Chaque règle de la liste contient des informations sur une règle logique, telles que ses
 * antécédents (conditions) et ses conséquences (action). Cette liste est utilisée dans le chaînage
 * arrière pour déterminer les règles qui peuvent être appliquées à
 * @param Base_de_faits Le paramètre `Base_de_faits` semble être une liste de faits actuellement connus
 * ou établis dans le système. Cette liste contient probablement des informations qui ont été
 * précédemment déduites ou fournies en entrée.
 * @param Base_de_faits_manquants Le paramètre `Base_de_faits_manquants` semble être une liste de faits
 * manquants nécessaires au processus de chaînage arrière. Cette liste contient probablement des faits
 * nécessaires pour atteindre l'objectif spécifié par le paramètre `Mais` mais qui ne sont pas
 * actuellement présents dans la `Base_de_faits`.
 */
bool chainage_arriere(char *But, liste_regles *Base_de_regles, liste_faits *Base_de_faits, liste_faits *Base_de_faits_manquants){
    if(fait_exists(Base_de_faits, But)){
        printf("Fait existant: %s\n", But);
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
                            add_fait(&Base_de_faits_manquants, Hypothese->name);
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

/**
 * La fonction vérifie si un fait donné existe dans une liste de faits.
 * 
 * @param Base_de_faits Il semble que l'extrait de code que vous avez fourni soit incomplet.
 * Pourriez-vous s'il vous plaît fournir plus d'informations sur le paramètre `Base_de_faits` et le
 * contexte global de la fonction `fait_exists` ? Cela m'aidera à mieux comprendre le code et vous
 * fournira l'aide dont vous avez besoin.
 * @param fait La fonction `fait_exists` que vous avez fournie semble incomplète. Il semble que vous
 * étiez sur le point de définir une fonction qui vérifie si un fait donné existe dans une liste de
 * faits. Le paramètre `Base_de_faits` est probablement un pointeur vers une liste de faits, et le
 * paramètre `fait`
 */
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