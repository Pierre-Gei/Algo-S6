<#include "stdio.h"
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
            case 2:

                break;
            case 3:


            case 5:

                break;
            case 6:

            case 7:

            default:
                system("clear");
                printf("Choix invalide \n");
                break;
        }

    } while (choix < 7);


}