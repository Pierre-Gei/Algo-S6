#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <string.h>
#include "../gfxlib/include/GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "../gfxlib/include/BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "../gfxlib/include/ESLib.h" // Pour utiliser valeurAleatoire()
#include "../include/affichage.h"
#include "../include/backwards.h"
#include "../include/save.h"
#include "../include/terminal_menu.h"

// Largeur et hauteur par defaut d'une image correspondant a nos criteres
#define LargeurFenetre 1400
#define HauteurFenetre 800

void gestionEvenement(EvenementGfx evenementchar);


/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
static StateAffichage state = MenuPrincipal;
int aff = 0;
int valider = 0;

char remplir[200] = " ";

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
    static bool pleinEcran = false;       // Pour savoir si on est en mode plein ecran ou pas
    static DonneesImageRGB *image = NULL; // L'image a afficher au centre de l'ecran
    static DonneesImageRGB *image2 = NULL;

    switch (evenement)
    {
        case Initialisation:
            image = lisBMPRGB("Image/Petitemamie.bmp");
            image2 = lisBMPRGB("Image/Petitemamie2.bmp");

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
            // il faut redessiner la fenetre :
            rafraichisFenetre();

            break;

        case Affichage:
            switch (state)
            {
                case MenuPrincipal:

                    // On part d'un fond d'ecran blanc
                    effaceFenetre(255, 255, 255);

                    couleurCourante(55, 250, 34);
                    epaisseurDeTrait(3);
                    afficheChaine("Les recettes de Mamie", 50, largeurFenetre() / 3.5, hauteurFenetre() * 5 / 6 + hauteurFenetre() * 1 / 32);
                    afficheChaine("Menu Principal", 50, largeurFenetre() / 3.5, hauteurFenetre() * 5 / 6 + hauteurFenetre() * 1 / 10);

                    // Affichage d'une image
                    if (image != NULL) // Si l'image a pu etre lue
                    {
                        // On affiche l'image
                        ecrisImage((largeurFenetre() - image->largeurImage) / 15, (hauteurFenetre() - image->hauteurImage) / 1.05, image->largeurImage, image->hauteurImage, image->donneesRGB);
                    }

                    if (image2 != NULL) // Si l'image a pu etre lue
                    {
                        // On affiche l'image
                        ecrisImage((largeurFenetre() - image2->largeurImage) / 1.07, (hauteurFenetre() - image2->hauteurImage) / 1.05, image2->largeurImage, image2->hauteurImage, image2->donneesRGB);
                    }

                    // Affichage des bouton
                    couleurCourante(192, 192, 192);
                    rectangle(largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 2.31, largeurFenetre() - largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 2);
                    rectangle(largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.76, largeurFenetre() - largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.58);
                    rectangle(largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.43, largeurFenetre() - largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.30);

                    couleurCourante(0, 0, 0);
                    afficheChaine("Questionnaire", 30, largeurFenetre() / 2.35, hauteurFenetre() - hauteurFenetre() / 2.07);
                    afficheChaine("Liste des ingrédients", 30, largeurFenetre() / 2.55, hauteurFenetre() - hauteurFenetre() / 1.63);
                    afficheChaine("Sortir du programme", 30, largeurFenetre() / 2.61, hauteurFenetre() - hauteurFenetre() / 1.34);
                    break;

                case Questionnaire:
                    effaceFenetre(255, 255, 255);
                    afficheChaine("Menu Questionnaire", 50, largeurFenetre() / 3.5, hauteurFenetre() * 5 / 6 + hauteurFenetre() * 1 / 25);
                    break;

                case Liste:
                    // On part d'un fond d'ecran blanc
                    effaceFenetre(255, 255, 255);

                    couleurCourante(55, 250, 34);
                    epaisseurDeTrait(3);
                    afficheChaine("Les recettes de Mamie", 50, largeurFenetre() / 3.5, hauteurFenetre() * 5 / 6 + hauteurFenetre() * 1 / 32);
                    afficheChaine("Menu Liste d'ingédients", 50, largeurFenetre() / 3.5, hauteurFenetre() * 5 / 6 + hauteurFenetre() * 1 / 10);

                    // Affichage d'une image
                    if (image != NULL) // Si l'image a pu etre lue
                    {
                        // On affiche l'image
                        ecrisImage((largeurFenetre() - image->largeurImage) / 15, (hauteurFenetre() - image->hauteurImage) / 1.05, image->largeurImage, image->hauteurImage, image->donneesRGB);
                    }

                    if (image2 != NULL) // Si l'image a pu etre lue
                    {
                        // On affiche l'image
                        ecrisImage((largeurFenetre() - image2->largeurImage) / 1.07, (hauteurFenetre() - image2->hauteurImage) / 1.05, image2->largeurImage, image2->hauteurImage, image2->donneesRGB);
                    }

                    // Affichage des bouton
                    couleurCourante(192, 192, 192);
                    rectangle(largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 2.31, largeurFenetre() - largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 2);
                    rectangle(largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.76, largeurFenetre() - largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.58);
                    rectangle(largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.43, largeurFenetre() - largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.30);

                    couleurCourante(0, 0, 0);
                    afficheChaine("Avant", 30, largeurFenetre() / 2.35, hauteurFenetre() - hauteurFenetre() / 2.07);
                    afficheChaine("Arrière", 30, largeurFenetre() / 2.55, hauteurFenetre() - hauteurFenetre() / 1.63);
                    afficheChaine("Retour arrière", 30, largeurFenetre() / 2.61, hauteurFenetre() - hauteurFenetre() / 1.34);
                    break;

                case Avant:
                    effaceFenetre(255, 255, 255);
                    afficheChaine("Menu Chainage Avant", 50, largeurFenetre() / 3.5, hauteurFenetre() * 5 / 6 + hauteurFenetre() * 1 / 25);

                    couleurCourante(192, 192, 192);
                    rectangle(largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.43, largeurFenetre() - largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.30);
                    afficheChaine("Retour arrière", 30, largeurFenetre() / 2.61, hauteurFenetre() - hauteurFenetre() / 1.34);
                    break;

                case Arriere:
                    effaceFenetre(255, 255, 255);

                    afficheChaine("Menu Chainage Arrière", 50, largeurFenetre() / 3.5, hauteurFenetre() * 5 / 6 + hauteurFenetre() * 1 / 25);

                    couleurCourante(192, 192, 192);
                    rectangle(largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.43, largeurFenetre() - largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 1.30);
                    couleurCourante(0, 0, 0);
                    afficheChaine("Retour arrière", 30, largeurFenetre() / 2.61, hauteurFenetre() - hauteurFenetre() / 1.34);


                    afficheChaine(remplir, 30, largeurFenetre() / 2.55, hauteurFenetre() - hauteurFenetre() / 1.63);


                    break;

                default:
                    break;
            }

            break;

        case Clavier:
            printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());
            char touche = caractereClavier();
            strcat(remplir,&touche);


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

                case 8:
                    demandeTemporisation(100);

                    size_t length = strlen(remplir);
                    if (length > 0) {
                        remplir[length] = '\0';
                        printf("%s",remplir);
                        afficheChaine(remplir, 30, largeurFenetre() / 2.55, hauteurFenetre() - hauteurFenetre() / 1.63);
                        demandeTemporisation(100);
                    }
                    break;

                case 13:
                    demandeTemporisation(100);
                    chainage_arriere(remplir, regles, faits,faits_manquants);

                default:
                    break;
            }
            break;

        case ClavierSpecial:
            printf("ASCII %d\n", toucheClavier());



            break;

        case BoutonSouris:
            switch (state)
            {
                case MenuPrincipal:
                    // Menu Principale
                    if (abscisseSouris() < 3.5 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 8 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 2.31 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 2)
                    {
                        state = Questionnaire;
                        printf("Questionnaire\n");
                    }

                    if (abscisseSouris() < 3.5 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 8 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.76 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.58)
                    {
                        state = Liste;
                        printf("Liste\n");
                    }

                    if (abscisseSouris() < 3.5 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 8 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.43 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.30)
                    {
                        exit(0);
                    }
                    break;

                case Questionnaire:

                    break;

                case Liste:
                    // Menu Liste Ingrdiant

                    if (abscisseSouris() < 3.5 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 8 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 2.31 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 2)
                    {
                        state = Avant;
                        printf("BOUTON gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
                    }

                    if (abscisseSouris() < 3.5 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 8 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.76 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.58)
                    {
                        state = Arriere;
                        printf("Bouton gauche relache en : (%d, %d)\n", abscisseSouris(), ordonneeSouris());
                    }

                    if (abscisseSouris() < 3.5 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 8 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.43 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.30)
                    {
                        state = MenuPrincipal;
                    }
                    break;

                case Avant:
                    if (abscisseSouris() < 3.5 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 8 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.43 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.30)
                    {
                        state = Liste;
                    }
                    break;

                case Arriere:
                    if (abscisseSouris() < 3.5 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 8 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.43 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.30)
                    {
                        state = Liste;
                    }
                    break;
            }
            break;

        case Souris: // Si la souris est deplacee
            break;

        case Inactivite: // Quand aucun message n'est disponible
            break;

        case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran

            break;

        default:
            break;
    }
}