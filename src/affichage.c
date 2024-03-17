#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../gfxlib/include/GfxLib.h"
#include "../gfxlib/include/BmpLib.h"
#include "../include/affichage.h"



#define LargeurFenetre 1400
#define HauteurFenetre 800

static StateAffichage state = MenuPrincipal;
int aff = 0;

char remplir[200] = " ";

void gestionEvenement(EvenementGfx evenement);

int affiche(int argc, char **argv)
{
    initialiseGfx(argc, argv);

    prepareFenetreGraphique("OpenGL", LargeurFenetre, HauteurFenetre);

    lanceBoucleEvenements();

    return 0;
}

void gestionEvenement(EvenementGfx evenement)
{
    static bool pleinEcran = false;       // Pour savoir si on est en mode plein ecran ou pas
    static DonneesImageRGB *image = NULL; // L'image a afficher au centre de l'ecran
    static DonneesImageRGB *image2 = NULL;
    static DonneesImageRGB *image3 = NULL;

    switch (evenement)
    {
        case Initialisation:
            image = lisBMPRGB("Image/Petitemamie.bmp");
            image2 = lisBMPRGB("Image/Petitemamie2.bmp");
            image3 = lisBMPRGB("Image/mamie.bmp");

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

                    effaceFenetre(255, 255, 255);

                    couleurCourante(55, 250, 34);
                    epaisseurDeTrait(3);
                    afficheChaine("Les Recettes de Mamie", 50, largeurFenetre() / 3.5, hauteurFenetre() * 5 / 6 + hauteurFenetre() * 1 / 32);
                    afficheChaine("Menu Principal", 50, largeurFenetre() / 3.5, hauteurFenetre() * 5 / 6 + hauteurFenetre() * 1 / 10);

                    if (image != NULL)
                    {
                        ecrisImage((largeurFenetre() - image->largeurImage) / 15, (hauteurFenetre() - image->hauteurImage) / 1.05, image->largeurImage, image->hauteurImage, image->donneesRGB);
                    }

                    if (image2 != NULL)
                    {
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

                    couleurCourante(55, 250, 34);
                    epaisseurDeTrait(3);
                    afficheChaine("Les Recettes de Mamie", 50, largeurFenetre() / 3.5, hauteurFenetre() * 5 / 6 + hauteurFenetre() * 1 / 32);
                    afficheChaine("Menu Questionnaire", 50, largeurFenetre() / 3.5, hauteurFenetre() * 5 / 6 + hauteurFenetre() * 1 / 10);


                    if (image3 != NULL)
                    {
                        ecrisImage((largeurFenetre() - image3->largeurImage) / 2, (hauteurFenetre() - image3->hauteurImage) / 2, image3->largeurImage, image3->hauteurImage, image3->donneesRGB);
                    }

                    // Question mamie

                    couleurCourante(192, 192, 192);
                    rectangle(largeurFenetre() / 15, hauteurFenetre() - hauteurFenetre() / 3, largeurFenetre() - largeurFenetre() / 1.45, hauteurFenetre() - hauteurFenetre() / 2);
                    couleurCourante(0, 0, 0);
                    afficheChaine("Tu as des ", 30, largeurFenetre() / 8, hauteurFenetre() - hauteurFenetre() / 2.5);

                    // Affichage des réponses

                    couleurCourante(192, 192, 192);
                    rectangle(largeurFenetre() / 1.05, hauteurFenetre() - hauteurFenetre() / 3, largeurFenetre() - largeurFenetre() / 3.5, hauteurFenetre() - hauteurFenetre() / 1.3);
                    couleurCourante(0, 0, 0);
                    afficheChaine("Tu peux faire: ", 30, largeurFenetre() / 1.34, hauteurFenetre() - hauteurFenetre() / 2.5);

                    // Affichage des boutons Oui /Non

                    couleurCourante(12, 245, 12);
                    rectangle(largeurFenetre() / 12, hauteurFenetre() - hauteurFenetre() / 1.76, largeurFenetre() - largeurFenetre() / 1.2, hauteurFenetre() - hauteurFenetre() / 1.58);
                    couleurCourante(199, 0, 57);
                    rectangle(largeurFenetre() / 5, hauteurFenetre() - hauteurFenetre() / 1.76, largeurFenetre() - largeurFenetre() / 1.4, hauteurFenetre() - hauteurFenetre() / 1.58);

                    couleurCourante(0, 0, 0);
                    afficheChaine("OUI", 30, largeurFenetre() / 9.7, hauteurFenetre() - hauteurFenetre() / 1.63);
                    afficheChaine("NON", 30, largeurFenetre() / 4.6, hauteurFenetre() - hauteurFenetre() / 1.63);

                    // Affichage des retour arriere
                    couleurCourante(192, 192, 192);
                    rectangle(largeurFenetre() / 11, hauteurFenetre() - hauteurFenetre() / 1.05, largeurFenetre() - largeurFenetre() / 1.8, hauteurFenetre() - hauteurFenetre() / 1.12);
                    rectangle(largeurFenetre() / 1.1, hauteurFenetre() - hauteurFenetre() / 1.05, largeurFenetre() - largeurFenetre() / 2.2, hauteurFenetre() - hauteurFenetre() / 1.12);

                    couleurCourante(0, 0, 0);
                    afficheChaine("Retour a la page precedente", 30, largeurFenetre() / 10, hauteurFenetre() - hauteurFenetre() / 1.07);
                    afficheChaine("Sortir du programme", 30, largeurFenetre() / 1.65, hauteurFenetre() - hauteurFenetre() / 1.07);

                    break;

                case Liste:
                    // On part d'un fond d'ecran blanc
                    effaceFenetre(255, 255, 255);

                    couleurCourante(55, 250, 34);
                    epaisseurDeTrait(3);
                    afficheChaine("Les Recettes de Mamie", 50, largeurFenetre() / 3.5, hauteurFenetre() * 5 / 6 + hauteurFenetre() * 1 / 32);
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

                    couleurCourante(0, 0, 0);
                    afficheChaine("Avant", 30, largeurFenetre() / 2.35, hauteurFenetre() - hauteurFenetre() / 2.07);
                    afficheChaine("Arriere", 30, largeurFenetre() / 2.55, hauteurFenetre() - hauteurFenetre() / 1.63);

                    // Affichage des retour arriere
                    couleurCourante(192, 192, 192);
                    rectangle(largeurFenetre() / 11, hauteurFenetre() - hauteurFenetre() / 1.43, largeurFenetre() - largeurFenetre() / 1.8, hauteurFenetre() - hauteurFenetre() / 1.30);
                    rectangle(largeurFenetre() / 1.1, hauteurFenetre() - hauteurFenetre() / 1.43, largeurFenetre() - largeurFenetre() / 2.2, hauteurFenetre() - hauteurFenetre() / 1.30);

                    couleurCourante(0, 0, 0);
                    afficheChaine("Retour a la page precedente", 30, largeurFenetre() / 10, hauteurFenetre() - hauteurFenetre() / 1.34);
                    afficheChaine("Sortir du programme", 30, largeurFenetre() / 1.65, hauteurFenetre() - hauteurFenetre() / 1.34);
                    break;

                case Avant:
                    effaceFenetre(255, 255, 255);

                    couleurCourante(55, 250, 34);
                    epaisseurDeTrait(3);
                    afficheChaine("Les Recettes de Mamie", 50, largeurFenetre() / 3.5, hauteurFenetre() * 5 / 6 + hauteurFenetre() * 1 / 32);
                    afficheChaine("Menu Chainage Avant", 50, largeurFenetre() / 3.5, hauteurFenetre() * 5 / 6 + hauteurFenetre() * 1 / 10);

                    // Affichage d'une image
                    if (image3 != NULL) // Si l'image a pu etre lue
                    {
                        // On affiche l'image
                        ecrisImage((largeurFenetre() - image3->largeurImage) / 2, (hauteurFenetre() - image3->hauteurImage) / 2, image3->largeurImage, image3->hauteurImage, image3->donneesRGB);
                    }
                    // Affichage Ingrédiant
                    couleurCourante(192, 192, 192);
                    rectangle(largeurFenetre() / 19, hauteurFenetre() - hauteurFenetre() / 3, largeurFenetre() - largeurFenetre() / 1.4, hauteurFenetre() - hauteurFenetre() / 1.3);

                    couleurCourante(0, 0, 0);
                    afficheChaine("Avec:", 30, largeurFenetre() / 15, hauteurFenetre() - hauteurFenetre() / 2.55);

                    // Affichage des réponses

                    couleurCourante(192, 192, 192);
                    rectangle(largeurFenetre() / 1.05, hauteurFenetre() - hauteurFenetre() / 3, largeurFenetre() - largeurFenetre() / 3.5, hauteurFenetre() - hauteurFenetre() / 1.3);
                    couleurCourante(0, 0, 0);
                    afficheChaine("Tu peux faire: ", 30, largeurFenetre() / 1.34, hauteurFenetre() - hauteurFenetre() / 2.5);

                    // Affichage des retour arriere
                    couleurCourante(192, 192, 192);
                    rectangle(largeurFenetre() / 11, hauteurFenetre() - hauteurFenetre() / 1.05, largeurFenetre() - largeurFenetre() / 1.8, hauteurFenetre() - hauteurFenetre() / 1.12);
                    rectangle(largeurFenetre() / 1.1, hauteurFenetre() - hauteurFenetre() / 1.05, largeurFenetre() - largeurFenetre() / 2.2, hauteurFenetre() - hauteurFenetre() / 1.12);

                    couleurCourante(0, 0, 0);
                    afficheChaine("Retour a la page precedente", 30, largeurFenetre() / 10, hauteurFenetre() - hauteurFenetre() / 1.07);
                    afficheChaine("Sortir du programme", 30, largeurFenetre() / 1.65, hauteurFenetre() - hauteurFenetre() / 1.07);
                    break;

                case Arriere:
                    effaceFenetre(255, 255, 255);

                    couleurCourante(55, 250, 34);
                    epaisseurDeTrait(3);
                    afficheChaine("Les Recettes de Mamie", 50, largeurFenetre() / 3.5, hauteurFenetre() * 5 / 6 + hauteurFenetre() * 1 / 32);
                    afficheChaine("Menu Chainage Arriere", 50, largeurFenetre() / 3.5, hauteurFenetre() * 5 / 6 + hauteurFenetre() * 1 / 10);

                    // Affichage d'une image
                    if (image3 != NULL) // Si l'image a pu etre lue
                    {
                        // On affiche l'image
                        ecrisImage((largeurFenetre() - image3->largeurImage) / 2, (hauteurFenetre() - image3->hauteurImage) / 2, image3->largeurImage, image3->hauteurImage, image3->donneesRGB);
                    }

                    // question mamie
                    couleurCourante(192, 192, 192);
                    rectangle(largeurFenetre() / 13, hauteurFenetre() - hauteurFenetre() / 2.9, largeurFenetre() - largeurFenetre() / 1.6, hauteurFenetre() - hauteurFenetre() / 2.35);
                    couleurCourante(0, 0, 0);
                    afficheChaine("Que veux tu manger ? ", 30, largeurFenetre() / 11, hauteurFenetre() - hauteurFenetre() / 2.5);

                    couleurCourante(12, 245, 12);
                    rectangle(largeurFenetre() / 13, hauteurFenetre() - hauteurFenetre() / 1.45, largeurFenetre() - largeurFenetre() / 1.2, hauteurFenetre() - hauteurFenetre() / 1.3);
                    couleurCourante(199, 0, 57);
                    rectangle(largeurFenetre() / 5, hauteurFenetre() - hauteurFenetre() / 1.45, largeurFenetre() - largeurFenetre() / 1.4, hauteurFenetre() - hauteurFenetre() / 1.3);

                    couleurCourante(0, 0, 0);
                    afficheChaine("Valider", 30, largeurFenetre() / 11.5, hauteurFenetre() - hauteurFenetre() / 1.35);
                    couleurCourante(0, 0, 0);
                    afficheChaine("Supp", 30, largeurFenetre() / 4.5, hauteurFenetre() - hauteurFenetre() / 1.35);

                    // Zone de texte

                    couleurCourante(192, 192, 192);
                    rectangle(largeurFenetre() / 13, hauteurFenetre() - hauteurFenetre() / 1.67, largeurFenetre() - largeurFenetre() / 1.4, hauteurFenetre() - hauteurFenetre() / 1.5);
                    couleurCourante(0, 0, 0);
                    afficheChaine("Je veux manger : ", 30, largeurFenetre() / 12.5, hauteurFenetre() - hauteurFenetre() / 1.75);

                    // Affichage des réponses

                    couleurCourante(192, 192, 192);
                    rectangle(largeurFenetre() / 1.05, hauteurFenetre() - hauteurFenetre() / 3, largeurFenetre() - largeurFenetre() / 3.5, hauteurFenetre() - hauteurFenetre() / 1.3);
                    couleurCourante(0, 0, 0);
                    afficheChaine("Il te manque: ", 30, largeurFenetre() / 1.34, hauteurFenetre() - hauteurFenetre() / 2.5);

                    // Affichage des retour arriere
                    couleurCourante(192, 192, 192);
                    rectangle(largeurFenetre() / 11, hauteurFenetre() - hauteurFenetre() / 1.05, largeurFenetre() - largeurFenetre() / 1.8, hauteurFenetre() - hauteurFenetre() / 1.12);
                    rectangle(largeurFenetre() / 1.1, hauteurFenetre() - hauteurFenetre() / 1.05, largeurFenetre() - largeurFenetre() / 2.2, hauteurFenetre() - hauteurFenetre() / 1.12);

                    couleurCourante(0, 0, 0);
                    afficheChaine("Retour a la page precedente", 30, largeurFenetre() / 10, hauteurFenetre() - hauteurFenetre() / 1.07);
                    afficheChaine("Sortir du programme", 30, largeurFenetre() / 1.65, hauteurFenetre() - hauteurFenetre() / 1.07);
                    afficheChaine(remplir, 30, largeurFenetre() / 13, hauteurFenetre() - hauteurFenetre() / 1.55);
                    break;
            }

            break;

        case Clavier:
            demandeTemporisation(100);
            char touche = caractereClavier();
            strcat(remplir,&touche);

            switch (caractereClavier())
            {
                case '*':
                    libereDonneesImageRGB(&image); /* On libere la structure image,
    c'est plus propre, meme si on va sortir du programme juste apres */
                    termineBoucleEvenements();
                    break;

                case '=':
                    pleinEcran = !pleinEcran; // Changement de mode plein ecran
                    if (pleinEcran)
                        modePleinEcran();
                    else
                        redimensionneFenetre(LargeurFenetre, HauteurFenetre);
                    break;

                default:
                    break;
            }
            break;
        case ClavierSpecial:
            printf("ASCII %d\n", toucheClavier());
            break;

        case BoutonSouris:
            if (etatBoutonSouris() == GaucheAppuye)
            {
                printf("appuyé");
            }
            else if (etatBoutonSouris() == GaucheRelache)
            {
                switch (state)
                {
                    case MenuPrincipal:
                        // Menu Principale
                        if (abscisseSouris() < 3.5 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 8 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 2.31 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 2)
                        {
                            state = Questionnaire;
                        }

                        if (abscisseSouris() < 3.5 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 8 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.76 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.58)
                        {
                            state = Liste;
                        }

                        if (abscisseSouris() < 3.5 * largeurFenetre() / 4 && abscisseSouris() > largeurFenetre() / 8 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.43 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.30)
                        {
                            exit(0);
                        }
                        break;

                    case Questionnaire:
                        // Menu Questionnaire

                        if (abscisseSouris() < 3.5 * largeurFenetre() / 7.89 && abscisseSouris() > largeurFenetre() / 11 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.15 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.05)
                        {
                            state = MenuPrincipal;
                        }

                        if (abscisseSouris() < 3.5 * largeurFenetre() / 3.85 && abscisseSouris() > largeurFenetre() / 1.835 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.15 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.05)
                        {
                            exit(0);
                        }
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

                        if (abscisseSouris() < 3.5 * largeurFenetre() / 7.89 && abscisseSouris() > largeurFenetre() / 11 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.43 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.30)
                        {
                            state = MenuPrincipal;
                        }

                        if (abscisseSouris() < 3.5 * largeurFenetre() / 3.85 && abscisseSouris() > largeurFenetre() / 1.835 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.43 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.30)
                        {
                            exit(0);
                        }
                        break;

                    case Avant:
                        // Menu Chainage avant
                        if (abscisseSouris() < 3.5 * largeurFenetre() / 7.89 && abscisseSouris() > largeurFenetre() / 11 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.15 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.05)
                        {
                            state = Liste;
                        }

                        if (abscisseSouris() < 3.5 * largeurFenetre() / 3.85 && abscisseSouris() > largeurFenetre() / 1.835 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.15 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.05)
                        {
                            exit(0);
                        }
                        break;

                    case Arriere:
                        // Menu Chainage arrière
                        if (abscisseSouris() < 3.5 * largeurFenetre() / 7.89 && abscisseSouris() > largeurFenetre() / 11 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.15 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.05)
                        {
                            state = Liste;
                            remplir[0] = '\0';
                        }

                        if (abscisseSouris() < 3.5 * largeurFenetre() / 3.85 && abscisseSouris() > largeurFenetre() / 1.835 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.15 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.05)
                        {
                            exit(0);
                        }
                        if (abscisseSouris() > largeurFenetre() / 13 && abscisseSouris() < largeurFenetre() - largeurFenetre() / 1.2 && ordonneeSouris() < hauteurFenetre() - hauteurFenetre() / 1.45 && ordonneeSouris() > hauteurFenetre() - hauteurFenetre() / 1.3)
                        {

                        }
                        break;
                }
            }

            break;

        case Souris: // Si la souris est deplacee
            break;

        case Inactivite: // Quand aucun message n'est disponible
            break;

        case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran

            break;
    }
}
