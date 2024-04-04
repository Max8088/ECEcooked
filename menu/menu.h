//
// Created by pierr on 03/04/2024.
//

#ifndef ESCOOKED_MENU_H
#define ESCOOKED_MENU_H

#include "../constantes.h"

typedef struct {
    float x, y, width, height;
    char *texte;
} Bouton;

void dessinerBouton1(Bouton bouton, ALLEGRO_FONT *police, ALLEGRO_COLOR couleurRectangle, ALLEGRO_COLOR couleurTexte);

void dessinerBouton2(Bouton bouton, ALLEGRO_FONT *police, ALLEGRO_COLOR couleurRectangle, ALLEGRO_COLOR couleurTexte);

bool EstDansLeBouton(Bouton bouton, float x, float y);

void menu(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police);

void menuScores(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police);

void menuOptions(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police);

void Credits(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police);

#endif //ESCOOKED_MENU_H
