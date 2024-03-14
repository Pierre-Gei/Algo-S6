#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include "../gfxlib/include/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "../gfxlib/include/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "../gfxlib/include/ESLib.h" // Pour utiliser valeurAleatoire()
#include "../include/affichage.h"
// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 1400
#define HauteurFenetre 800

/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement);



int affiche(int argc, char **argv)
{
    initialiseGfx(argc, argv);

    prepareFenetreGraphique("OpenGL", LargeurFenetre, HauteurFenetre);

    /* Lance la boucle qui aiguille les evenements sur la fonction gestionEvenement ci-apres,
        qui elle-meme utilise fonctionAffichage ci-dessous */
    lanceBoucleEvenements();

    return 0;
}


/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{
    static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas
    static DonneesImageRGB *image = NULL; // L'image a afficher au centre de l'ecran

    /* On va aussi animer une balle traversant l'ecran */
    static int xBalle;
    static int yBalle;
    static int vxBalle = 7;
    static int vyBalle = -7;

    switch (evenement)
    {
        case Initialisation:
            xBalle = largeurFenetre()*valeurAleatoire();
            yBalle = hauteurFenetre()*valeurAleatoire();
            image = lisBMPRGB("Image/mamie.bmp");

            /* Le message "Initialisation" est envoye une seule fois, au debut du
            programme : il permet de fixer "image" a la valeur qu'il devra conserver
            jusqu'a la fin du programme : soit "image" reste a NULL si l'image n'a
            pas pu etre lue, soit "image" pointera sur une structure contenant
            les caracteristiques de l'image "imageNB.bmp" */

            // Configure le systeme pour generer un message Temporisation
            // toutes les 20 millisecondes
            demandeTemporisation(20);
            break;

        case Temporisation:
            // On met a jour les coordonnees de la balle
            xBalle += vxBalle;
            yBalle += vyBalle;

            // On fait rebondir la balle si necessaire
            if (xBalle < 0 || xBalle >= largeurFenetre())
                vxBalle = -vxBalle;
            if (yBalle < 0 || yBalle >= hauteurFenetre())
                vyBalle = -vyBalle;
            // Les coordonnees de la balle ayant eventuellement change,
            // il faut redessiner la fenetre :
            rafraichisFenetre();
            break;

        case Affichage:

            // On part d'un fond d'ecran blanc
            effaceFenetre (255, 255, 255);

            // Affichage d'un texte vert sombre avec ombrage en police de taille 20
            // L'effet d'ombrage vient tout simplement du dessin du texte en gris clair
            // sous le texte voulu, avec un léger décalage
            couleurCourante(55, 250, 34);
            epaisseurDeTrait(3);
            afficheChaine("Les recettes de Mamie", 50, largeurFenetre() / 3.5, hauteurFenetre() * 5 / 6 + hauteurFenetre() * 1 / 32);

            // Affichage d'une image
            if (image != NULL) // Si l'image a pu etre lue
            {
                // On affiche l'image
                ecrisImage((largeurFenetre()-image->largeurImage)/2, (hauteurFenetre()-image->hauteurImage)/2, image->largeurImage, image->hauteurImage, image->donneesRGB);
            }
            break;

        case Clavier:
            printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

            switch (caractereClavier())
            {
                case 'Q': /* Pour sortir quelque peu proprement du programme */
                case 'q':
                    libereDonneesImageRGB(&image); /* On libere la structure image,
					c'est plus propre, meme si on va sortir du programme juste apres */
                    termineBoucleEvenements();
                    break;

                case 'F':
                case 'f':
                    pleinEcran = !pleinEcran; // Changement de mode plein ecran
                    if (pleinEcran)
                        modePleinEcran();
                    else
                        redimensionneFenetre(LargeurFenetre, HauteurFenetre);
                    break;

                case 'R':
                case 'r':
                    // Configure le systeme pour generer un message Temporisation
                    // toutes les 20 millisecondes (rapide)
                    demandeTemporisation(20);
                    break;

                case 'L':
                case 'l':
                    // Configure le systeme pour generer un message Temporisation
                    // toutes les 100 millisecondes (lent)
                    demandeTemporisation(100);
                    break;

                case 'S':
                case 's':
                    // Configure le systeme pour ne plus generer de message Temporisation
                    demandeTemporisation(-1);
                    break;
            }
            break;

        case ClavierSpecial:
            printf("ASCII %d\n", toucheClavier());
            break;

        case BoutonSouris:

            break;

        case Souris: // Si la souris est deplacee
            break;

        case Inactivite: // Quand aucun message n'est disponible
            break;

        case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran

            break;
    }
}
