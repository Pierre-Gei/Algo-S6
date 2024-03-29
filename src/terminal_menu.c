#include <stdio.h>
#include "../include/terminal_menu.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/terminal_menu.h"
#include "../include/structures.h"
#include "../include/forward.h"
#include "../include/save.h"
#include "../include/backwards.h"
#include "../include/traitement.h"
#include "../include/affichage.h"

#define TAILLE_MAX 256

// ANSI color codes
#define COLOR_WHITE "\x1b[38;5;255m"
#define COLOR_RED "\x1b[38;5;196m"
#define COLOR_GREEN "\x1b[38;5;46m"
#define COLOR_YELLOW "\x1b[38;5;226m"
#define COLOR_BLUE "\x1b[38;5;21m"
#define COLOR_MAGENTA "\x1b[38;5;201m"
#define COLOR_CYAN "\x1b[38;5;51m"
#define COLOR_BLACK "\x1b[38;5;16m"

#define COLOR_RESET "\x1b[0m"
#define BG "\x1b[48;5;92m"

void menu(int argc, char **argv)
{
    int choice;
    bool quit = false;
    char *nom_base_regles = malloc(TAILLE_MAX * sizeof(char));
    char *nom_base_faits = malloc(TAILLE_MAX * sizeof(char));
    liste_regles *regles = NULL;
    liste_regles *nouvelles_regles = NULL;
    liste_faits *faits = NULL;
    liste_faits *nouveaux_faits = NULL;
    do
    {
        printf(COLOR_WHITE BG "╔═════════════════════════════════════════════════════════════════════════════════════════════════════╗\n"
                              "║                                                                                                     ║\n"
                              "║                                                                                                     ║\n"
                              "║   ________  ________  ___  __    _______   ________  ________  ___  ________   _______              ║\n"
                              "║  |\\   __  \\|\\   __  \\|\\  \\|\\  \\ |\\  ___ \\ |\\   ___ \\|\\   __  \\|\\  \\|\\   ___  \\|\\  ___ \\             ║\n"
                              "║  \\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\/  /|\\ \\   __/|\\ \\  \\_|\\ \\ \\  \\|\\  \\ \\  \\ \\  \\\\ \\  \\ \\   __/|            ║\n"
                              "║   \\ \\   ____\\ \\  \\\\\\  \\ \\   ___  \\ \\  \\_|/_\\ \\  \\ \\\\ \\ \\   __  \\ \\  \\ \\  \\\\ \\  \\ \\  \\_|/__          ║\n"
                              "║    \\ \\  \\___|\\ \\  \\\\\\  \\ \\  \\\\ \\  \\ \\  \\_|\\ \\ \\  \\_\\\\ \\ \\  \\ \\  \\ \\  \\ \\  \\\\ \\  \\ \\  \\_|\\ \\         ║\n"
                              "║     \\ \\__\\    \\ \\_______\\ \\__\\\\ \\__\\ \\_______\\ \\_______\\ \\__\\ \\__\\ \\__\\ \\__\\\\ \\__\\ \\_______\\        ║\n"
                              "║      \\|__|     \\|_______|\\|__| \\|__|\\|_______|\\|_______|\\|__|\\|__|\\|__|\\|__| \\|__|\\|_______|        ║\n"
                              "║                                                                                                     ║\n"
                              "║                                                                                                     ║\n"
                              "║                                                                                                     ║\n"
                              "║   ___  ________   ________  ___  ___  ________  _________  ________  ___  _______   ________        ║\n"
                              "║  |\\  \\|\\   ___  \\|\\   ___ \\|\\  \\|\\  \\|\\   ____\\|\\___   ___\\\\   __  \\|\\  \\|\\  ___ \\ |\\   ____\\       ║\n"
                              "║  \\ \\  \\ \\  \\\\ \\  \\ \\  \\_|\\ \\ \\  \\\\\\  \\ \\  \\___|\\|___ \\  \\_\\ \\  \\|\\  \\ \\  \\ \\   __/|\\ \\  \\___|_      ║\n"
                              "║   \\ \\  \\ \\  \\\\ \\  \\ \\  \\ \\\\ \\ \\  \\\\\\  \\ \\_____  \\   \\ \\  \\ \\ \\   _  _\\ \\  \\ \\  \\_|/_\\ \\_____  \\     ║\n"
                              "║    \\ \\  \\ \\  \\\\ \\  \\ \\  \\_\\\\ \\ \\  \\\\\\  \\|____|\\  \\   \\ \\  \\ \\ \\  \\\\  \\\\ \\  \\ \\  \\_|\\ \\|____|\\  \\    ║\n"
                              "║     \\ \\__\\ \\__\\\\ \\__\\ \\_______\\ \\_______\\____\\_\\  \\   \\ \\__\\ \\ \\__\\\\ _\\\\ \\__\\ \\_______\\____\\_\\  \\   ║\n"
                              "║      \\|__|\\|__| \\|__|\\|_______|\\|_______|\\_________\\   \\|__|  \\|__|\\|__|\\|__|\\|_______|\\_________\\  ║\n"
                              "║                                         \\|_________|                                  \\|_________|  ║\n"
                              "║                                                                                                     ║\n"
                              "║                                                                                                     ║\n"
                              "╠═════════════════════════════════════════════════════════════════════════════════════════════════════╣\n"
                              "║                                                                                                     ║\n"
                              "║    " COLOR_RED "1." COLOR_WHITE " Choisir une base de règles                                                                    ║\n"
                              "║    " COLOR_YELLOW "2." COLOR_WHITE " Choisir une base de faits                                                                     ║\n"
                              "║    " COLOR_CYAN "3." COLOR_WHITE " Ajouter des faits à la base de faits                                                          ║\n"
                              "║    " COLOR_MAGENTA "4." COLOR_WHITE " Ajouter des règles à la base de règles                                                        ║\n"
                              "║    " COLOR_GREEN "5." COLOR_WHITE " Affichage des faits et règles actuelles                                                       ║\n"
                              "║    " COLOR_MAGENTA "6." COLOR_WHITE " Chaînage avant                                                                                ║\n"
                              "║    " COLOR_BLUE "7." COLOR_WHITE " Chaînage arrière                                                                              ║\n"
                              "║    " COLOR_BLACK "8." COLOR_WHITE " Enregister la base de faits                                                                   ║\n"
                              "║    " COLOR_YELLOW "9." COLOR_WHITE " Enregister la base de règles                                                                  ║\n"
                              "║    " COLOR_YELLOW "10." COLOR_WHITE " Affichage                                                                                    ║\n"
                              "║    " COLOR_RED "11." COLOR_WHITE " Quitter                                                                                      ║\n"
                              "║                                                                                                     ║\n"
                              "╚═════════════════════════════════════════════════════════════════════════════════════════════════════╝\n"
                              "\n"
                              "Votre choix: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            system("clear");
            printf("Saisie de règles\n");
            printf("Choisir une base de règles (nom.extension) :\n");
            scanf("%s", nom_base_regles);
            load_to_list(nom_base_regles, &regles);
            break;
            break;
        case 2:
            system("clear");
            printf("Saisie de faits\n");
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
            char *fait = malloc(TAILLE_MAX * sizeof(char));
            printf("Ajouter des faits à la base de faits :\n ex : fait1 fait2 fait3\n");
            clear_buffer();
            fgets(fait, TAILLE_MAX, stdin);
            divide_and_add_faits(&faits, &nouveaux_faits, fait);
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
            insert_regle_base(regle, &regles, &nouvelles_regles);
            free(regle);
            break;
        case 5:
            system("clear");
            printf("Affichage des faits et règles actuelles\n");
            affiche_liste_faits(faits);
            printf("\n");
            print_liste_regles(regles);
            break;
        case 6:
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
        case 7:
            system("clear");
            if (faits == NULL || regles == NULL)
            {
                printf("Veuillez choisir une base de faits et une base de règles avant de continuer\n");
                break;
            }
            char *temp_fait = malloc(TAILLE_MAX * sizeof(char));
            liste_faits *faits_manquants = NULL;
            affiche_faits_possibles(regles);
            printf("Que voulez-vous vérifier \n");
            scanf("%s", temp_fait);
            if (chainage_arriere(temp_fait, regles, faits, faits_manquants))
            {
                printf("Le fait %s est atteint \n", temp_fait);
            }
            else
            {
                printf("Le fait %s n'est pas atteint \n", temp_fait);
            }
            free(temp_fait);

            break;

        case 8:
            system("clear");
            if (nouveaux_faits == NULL)
            {
                printf("Base de faits non modifiée ou vide\n");
                break;
            }
            enregistrer_liste_fait(nouveaux_faits, nom_base_faits);
            printf("Base de faits enregistrée\n");
            if (nouveaux_faits != NULL)
                liberer_liste_faits(&nouveaux_faits);
            nouveaux_faits = NULL;
            break;
        case 9:
            system("clear");
            if (nouvelles_regles == NULL)
            {
                printf("Base de règles non modifiée ou vide\n");
                break;
            }
            enregistrer_liste_regle(nouvelles_regles, nom_base_regles);
            printf("Base de règles enregistrée\n");
            if (nouvelles_regles != NULL)
                liberer_liste_regles(&nouvelles_regles);
            nouvelles_regles = NULL;
            break;

        case 10:
            affiche(argc, argv);
            break;


        case 11:
            system("clear");
            printf("Au revoir \n");
                liberer_liste_faits(&nouveaux_faits);

                liberer_liste_regles(&nouvelles_regles);

                liberer_liste_faits(&faits);

                liberer_liste_regles(&regles);

                free(nom_base_faits);
                free(nom_base_regles);
            quit = true;
            continue;
        }
        choice = 0;
    } while (quit == false);
    printf(COLOR_RESET "\n");
}

void clear_buffer()
{
    int c = getchar();
    if (c != '\n' && c != EOF)
    {
        clear_buffer(); // Appel récursif
    }
}