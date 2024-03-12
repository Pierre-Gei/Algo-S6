#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "GfxLib/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "GfxLib/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "GfxLib/ESLib.h" // Pour utiliser valeurAleatoire()
#include "affichage.h"

#define LargeurFenetre 1280
#define HauteurFenetre 720

int main(int argc, char **argv)
{
    initialiseGfx(argc, argv);

    prepareFenetreGraphique("GfxLib/GfxLib", LargeurFenetre, HauteurFenetre);

    /* Lance la boucle qui aiguille les evenements sur la fonction gestionEvenement ci-apres,
        qui elle-meme utilise fonctionAffichage ci-dessous */
    ///lanceBoucleEvenements();

    return 0;
}
