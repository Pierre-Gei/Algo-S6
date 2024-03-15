//
// Created by Pierre Geiguer on 11/03/2024.
//

#include "terminal_menu.h"
#include <string.h>

#define COLOR_RESET   "\x1b[0m"


int main(int argc, char *argv[]){
    if (argc > 1) {
        if (strcmp(argv[1], "-cli") == 0) {
            menu();
        }
    }
    return 0;
}