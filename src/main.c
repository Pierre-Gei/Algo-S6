//
// Created by quent on 14/03/2024.
//

#include "terminal_menu.h"
#include "../include/affichage.h"

#define COLOR_RESET   "\x1b[0m"


int main(void){
    menu();
    affiche(argc,argv);
    return 0;
}