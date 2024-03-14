#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "structures.h"
#include "save.h"
#include "traitement.h"
#include "backwards.h"
#include "forward.h"
#include "menu_terminal.h"
#define TAILLE_MAX 256


void clear_buffer() {
    int c = getchar();
    if (c != '\n' && c != EOF) {
        clear_buffer(); // Appel récursif
    }
}


void menu()
{
    int choix = 0;
    char *nom_base_regles = malloc(TAILLE_MAX * sizeof(char));
    char *nom_base_faits = malloc(TAILLE_MAX * sizeof(char));
    liste_regles * regles = NULL;
    liste_faits *faits = NULL;
    do 
    {
        printf("1. Choisir une base de règles \n");
        printf("2. Choisir une base de faits \n");
        printf("3. AJouter des faits à la base de faits\n");
        printf("4. Ajouter des règles à la base de règles \n");
        printf("5. Afficher les règles atteintes \n");
        printf("6. Que voulez-vous vérifier \n");
        printf("7. Quitter \n");

        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
                system("clear");
                printf("Choisir une base de règles (nom.extension) :\n");
                scanf("%s", nom_base_regles);
                load_to_list(nom_base_regles, &regles);
                break;
            case 2:
                system("clear");
                printf("Choisir une base de faits (nom.extension) :\n");
                scanf("%s", nom_base_faits);
                load_faits_to_list(nom_base_faits, &faits);
                break;
            case 3:
                system("clear");
                if (nom_base_faits == NULL)
                {
                    printf("Veuillez choisir une base de faits avant d'ajouter des faits\n");
                    break;
                }
                char * fait = malloc(TAILLE_MAX * sizeof(char));
                printf("Ajouter des faits à la base de faits :\n ex : fait1 fait2 fait3\n");
                clear_buffer();
                fgets(fait, TAILLE_MAX, stdin);
                divide_and_add_faits(&faits, fait, nom_base_faits);
                free(fait);
                break;
            case 4:
                system("clear");
                if (nom_base_regles == NULL)
                {
                    printf("Veuillez choisir une base de règles avant d'ajouter des règles\n");
                    break;
                }
                printf("Ajouter des règles à la base de règles : \n ex : fait1 fait2 -> fait3\n");
                char *regle = malloc(TAILLE_MAX * sizeof(char));
                clear_buffer();
                fgets(regle, TAILLE_MAX, stdin);
                ajoute_regle_fichier(nom_base_regles, regle);
                break;
            case 5:
                system("clear");
                if (faits == NULL || regles == NULL)
                {
                    printf("Veuillez choisir une base de faits et une base de règles avant de continuer\n");
                    break;
                }
                liste_reponses *reponses = NULL;
                printf("Règles atteintes d'après la base de faits \n");
                parcours(faits, regles, &reponses);
                affiche_liste_reponses(reponses);
                liberer_liste_reponses(&reponses);
                break;
            case 6:
                system("clear");
                if (faits == NULL || regles == NULL)
                {
                    printf("Veuillez choisir une base de faits et une base de règles avant de continuer\n");
                    break;
                }
                char *temp_fait = malloc(TAILLE_MAX * sizeof(char));
                printf("Que voulez-vous vérifier \n");
                scanf("%s", temp_fait);
                if(chainage_arriere(temp_fait, regles, faits))
                {
                    printf("Le fait %s est atteint \n", temp_fait);
                }
                else
                {
                    printf("Le fait %s n'est pas atteint \n", temp_fait);
                }
                free(temp_fait);

                break;
            case 7:
                system("clear");
                printf("Au revoir \n");
                liberer_liste_faits(&faits);
                liberer_liste_regles(&regles);
                free(nom_base_faits);
                free(nom_base_regles);
                break;
            default:
                system("clear");
                printf("Choix invalide \n");
                break;
        }

    } while (choix < 7);


}