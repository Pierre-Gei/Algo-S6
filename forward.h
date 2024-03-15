//
// Created by Pierre Geiguer on 11/03/2024.
//

#ifndef ALGO_S6_FORWARD_H
#define ALGO_S6_FORWARD_H

/*Ajouter un fait dans une liste de fait par le biais d'une chaine de caractères*/
liste_faits *ajout_fait(liste_faits *liste, char *fait);

/*Ajouter une condition dans une liste de condition par le biais d'une chaine de caractères*/
liste_reponses *ajout_reponse(liste_reponses *liste, char *reponse);

/*
Vérifier une condition avec tous les faits 
@return 1 si la condition est vérifiée, 0 sinon et -1 si la liste est vide
*/
int verifier_faits(liste_faits *faits, char *condition);

/*
Vérifier chaque condition avec tous les faits
@return 1 si toutes les conditions sont vérifiées, 0 sinon et -1 si la liste est vide
*/
int verifier_conditions(liste_faits *faits, liste_conditions *conditions);

/*Afficher toutes les réponses*/
void affiche_liste_reponses( liste_reponses * liste);

/*
Compléter la liste des réponses et des faits pendant le parcours
@return 1 si la liste de réponses est complétée, 0 sinon
*/
int verif_totale(liste_faits *faits, liste_regles *regles, liste_reponses **reponses);

/*Copier la liste des réponses dans une autre liste de réponses*/
void copier_liste_reponses(liste_reponses *src, liste_reponses **dest);

/*
Comparer deux listes de réponses pour savoir si identiques
@return 1 si les listes sont identiques, 0 sinon
*/
int compare_liste_reponses(liste_reponses *liste1, liste_reponses *liste2);

/*
Parcours de la liste de reglès tant que la liste de réponses n'est pas fixée
*/
int parcours(liste_faits *faits, liste_regles *regles, liste_reponses **reponses);

/*
Eviter les doublons dans une liste de réponses
@return 1 si la réponse est déjà dans la liste, 0 sinon
*/
int doublon_reponse (liste_reponses *liste, char *reponse);

/*
Eviter les doublons dans une liste de faits
@return 1 si le fait est déjà dans la liste, 0 sinon
*/
int doublon_fait (liste_faits *liste, char *fait);

void printf_recursive(liste_reponses *liste) ;


#endif //ALGO_S6_FORWARD_H
