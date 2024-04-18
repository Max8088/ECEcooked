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

void
dessinerMenu(ALLEGRO_BITMAP *ImageMenu, int nbBoutons, Bouton boutons[], ALLEGRO_EVENT event2, ALLEGRO_FONT *police);

bool EstDansLeBouton(Bouton bouton, float x, float y);

int getBestScore();

void menuVolume(ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police, ALLEGRO_MIXER *mixer, ALLEGRO_EVENT_QUEUE *queue1,
                ALLEGRO_SAMPLE_INSTANCE *instanceMusique, ALLEGRO_SAMPLE *sonBoutonClique);

void menu(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *ImageMenu, ALLEGRO_BITMAP *decor1, ALLEGRO_BITMAP *sol,
          ALLEGRO_BITMAP *personnage, ALLEGRO_BITMAP *cuisson, ALLEGRO_BITMAP *decoupe, ALLEGRO_BITMAP *planDeTravail,
          ALLEGRO_BITMAP *distrib_assiette, ALLEGRO_BITMAP *poubelle, ALLEGRO_BITMAP *sortie, ALLEGRO_FONT *police,
          ALLEGRO_EVENT_QUEUE *queue1, ALLEGRO_MIXER *mixer, ALLEGRO_SAMPLE_INSTANCE *instanceMusique, ALLEGRO_SAMPLE
          *sonBoutonClique);

void menuScores(ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police, ALLEGRO_EVENT_QUEUE *queue1, ALLEGRO_SAMPLE *sonBoutonClique);

void menuOptions(ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police, ALLEGRO_EVENT_QUEUE *queue1, ALLEGRO_MIXER *mixer,
                 ALLEGRO_SAMPLE_INSTANCE *instanceMusique, ALLEGRO_SAMPLE *sonBoutonclique);

void Credits(ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police, ALLEGRO_EVENT_QUEUE *queue1, ALLEGRO_SAMPLE *sonBoutonClique);

void SoundCliquedButton(ALLEGRO_SAMPLE *sonBoutonClique);


#endif //ESCOOKED_MENU_H
