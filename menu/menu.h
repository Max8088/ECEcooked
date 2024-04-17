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

typedef struct {
    float x, y, width, height;
} CurseurSon;

void dessinerBouton1(Bouton bouton, ALLEGRO_FONT *police, ALLEGRO_COLOR couleurRectangle, ALLEGRO_COLOR couleurTexte);

void dessinerBouton2(Bouton bouton, ALLEGRO_FONT *police, ALLEGRO_COLOR couleurRectangle, ALLEGRO_COLOR couleurTexte);

void
dessinerMenu(ALLEGRO_BITMAP *ImageMenu, int nbBoutons, Bouton boutons[], ALLEGRO_EVENT event2, ALLEGRO_FONT *police);

bool EstDansLeBouton(Bouton bouton, float x, float y);

bool EstDansLeCurseur(CurseurSon curseurSon, float x, float y);

void dessinerCurseur(CurseurSon curseurSon, float volume, ALLEGRO_FONT* police);

void ajusterVolume(ALLEGRO_SAMPLE_INSTANCE *sampleInstance, float volume);

void menuVolume(ALLEGRO_EVENT_QUEUE* queue1, ALLEGRO_SAMPLE_INSTANCE* sampleInstance, ALLEGRO_FONT* police);

void menu(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *ImageMenu, ALLEGRO_BITMAP *decor1, ALLEGRO_BITMAP *sol,
          ALLEGRO_BITMAP *personnage, ALLEGRO_BITMAP *cuisson, ALLEGRO_BITMAP *decoupe, ALLEGRO_BITMAP *planDeTravail,
          ALLEGRO_BITMAP *distrib_assiette, ALLEGRO_BITMAP *poubelle, ALLEGRO_BITMAP *sortie, ALLEGRO_FONT *police,
          ALLEGRO_EVENT_QUEUE *queue1, ALLEGRO_SAMPLE_INSTANCE* sonBouton);

void menuScores(ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police, ALLEGRO_EVENT_QUEUE *queue1);

void menuOptions(ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police, ALLEGRO_EVENT_QUEUE *queue1);

void Credits(ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police, ALLEGRO_EVENT_QUEUE *queue1);



#endif //ESCOOKED_MENU_H
