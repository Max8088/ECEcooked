//
// Created by pierr on 03/04/2024.
//

#ifndef ESCOOKED_MENU_H
#define ESCOOKED_MENU_H


#include "../constantes.h"
#include "../jeu/jeu.h"
#include "../joueur/joueur.h"

typedef struct {
    float x, y, width, height;
    char *texte;
    ALLEGRO_BITMAP *apercu;
} Bouton;

typedef struct {
    float x, y, width, height, min, max, value;
} Curseur;

void DessinerBouton1(Bouton bouton, ALLEGRO_FONT *police, ALLEGRO_COLOR couleurRectangle, ALLEGRO_COLOR couleurTexte);

void DessinerBouton2(Bouton bouton, ALLEGRO_FONT *police, ALLEGRO_COLOR couleurRectangle, ALLEGRO_COLOR couleurTexte);

bool EstDansLeBouton(Bouton bouton, float x, float y);

void SonBoutonClique(Sons *son);

void MenuCredits(ComposantsJeu ***jeu, Sons ***son);

void DessinerCurseur(const Curseur *curseur, ComposantsJeu ***jeu, float volume);

bool EstDansLeCurseurVolume(const Curseur *curseur, float mx, float my);

void MenuVolume(Sons ***son, ComposantsJeu ***jeu);

void ArreterMusiqueFondDeMenu(Sons *son);

void JouerMusiqueFondDeMenu(Sons *son);

void MenuRules(ComposantsJeu ***jeu, Sons **son);

void MenuOptions(ComposantsJeu **jeu, Sons **son);

void AfficherControls(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2);

void PremierAffichageMenu(ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police, int nbBoutons, Bouton *boutons);

void DessinerMenu(ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police, float mouseX, float mouseY, Bouton boutons[],
                  int nbBoutons);

void Menu(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2, Sons *son);

#endif //ESCOOKED_MENU_H
