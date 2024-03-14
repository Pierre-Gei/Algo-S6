//
// Created by Pierre Geiguer on 12/03/2024.
//

#include <stdio.h>
#include "terminal_menu.h"


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// ANSI color codes
#define COLOR_WHITE  "\x1b[38;5;255m"
#define COLOR_RED    "\x1b[38;5;196m"
#define COLOR_GREEN  "\x1b[38;5;46m"
#define COLOR_YELLOW "\x1b[38;5;226m"
#define COLOR_BLUE   "\x1b[38;5;21m"
#define COLOR_MAGENTA "\x1b[38;5;201m"
#define COLOR_CYAN   "\x1b[38;5;51m"
#define COLOR_BLACK  "\x1b[38;5;16m"



#define COLOR_RESET   "\x1b[0m"
#define BG "\x1b[48;5;92m"


void menu(void){
    int choice;
    bool quit = false;
    do{
        printf(COLOR_WHITE BG"╔═════════════════════════════════════════════════════════════════════════════════════════════════════╗\n"
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
               "║    "COLOR_RED"1."COLOR_WHITE" Saisie de règles                                                                              ║\n"
               "║    "COLOR_YELLOW"2."COLOR_WHITE" Saisie de faits                                                                               ║\n"
               "║    "COLOR_GREEN"3."COLOR_WHITE" Affichage des faits et règles actuelles                                                       ║\n"
               "║    "COLOR_MAGENTA"4."COLOR_WHITE" Chaînage avant                                                                                ║\n"
               "║    "COLOR_BLUE"5."COLOR_WHITE" Chaînage arrière                                                                              ║\n"
               "║    "COLOR_BLACK"6."COLOR_WHITE" Quitter                                                                                       ║\n"
               "║                                                                                                     ║\n"
               "╚═════════════════════════════════════════════════════════════════════════════════════════════════════╝\n"
               "\n"
               "Votre choix: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                system("clear");
                printf("Saisie de règles\n");
                //TODO: Implement the rules input
                break;
            case 2:
                system("clear");
                printf("Saisie de faits\n");
                //TODO: Implement the facts input
                break;
            case 3:
                system("clear");
                printf("Affichage des faits et règles actuelles\n");
                //TODO: Implement the display of the facts and rules
                break;
            case 4:
                system("clear");
                printf("Chaînage avant\n");
                //TODO: Implement the forward chaining
                break;
            case 5:
                system("clear");
                printf("Chaînage arrière\n");
                //TODO: Implement the backward chaining
                break;
            case 6:
                system("clear");
                printf("Quitter\n");
                quit = true;
                continue;
        }
        choice = 0;
    } while(quit == false);
}
