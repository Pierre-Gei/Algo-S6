//
// Created by quent on 14/03/2024.
//

#include "../include/terminal_menu.h"
#include "../include/affichage.h"
#include <string.h>

#define COLOR_RESET   "\x1b[0m"


int main(int argc, char *argv[]){
    if (argc > 1) {
        if (strcmp(argv[1], "-cli") == 0) {
            menu();
        }
    }
    else{
        affiche(argc, argv);
    }
    return 0;
}