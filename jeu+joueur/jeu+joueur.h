//
// Created by pierr on 25/04/2024.
//

#ifndef ESCOOKED_JEU_JOUEUR_H
#define ESCOOKED_JEU_JOUEUR_H

#include "../constantes.h"

typedef struct {
    char pseudo[13];
    ALLEGRO_BITMAP *image;
    int score, x, y, vx, vy;
    float angle;
} Joueur;


typedef struct {
    int type, x, y;
} Element;

typedef struct {
    ALLEGRO_DISPLAY *fenetre;
    ALLEGRO_EVENT_QUEUE *file;
    ALLEGRO_TIMER *timer;
    ALLEGRO_BITMAP *Z;
    ALLEGRO_BITMAP *Q;
    ALLEGRO_BITMAP *S;
    ALLEGRO_BITMAP *D;
    ALLEGRO_BITMAP *C;
    ALLEGRO_BITMAP *V;
    ALLEGRO_BITMAP *L;
    ALLEGRO_BITMAP *M;
    ALLEGRO_BITMAP *FlecheHaut;
    ALLEGRO_BITMAP *FlecheGauche;
    ALLEGRO_BITMAP *FlecheBas;
    ALLEGRO_BITMAP *FlecheDroite;
    ALLEGRO_BITMAP *ImageMenu;
    ALLEGRO_BITMAP *decor;
    ALLEGRO_BITMAP *sol1;
    ALLEGRO_BITMAP *sol2;
    ALLEGRO_BITMAP *plaqueDeCuisson;
    ALLEGRO_BITMAP *planDeDecoupe;
    ALLEGRO_BITMAP *planDeTravail;
    ALLEGRO_BITMAP *distributeurAssiette;
    ALLEGRO_BITMAP *poubelle;
    ALLEGRO_BITMAP *sortie;
    ALLEGRO_FONT *police;
    ALLEGRO_FONT *policeTitre;
    ALLEGRO_FONT *policePseudo;
    ALLEGRO_SAMPLE *musiqueFond;
    ALLEGRO_SAMPLE_INSTANCE *instanceMusique;
    ALLEGRO_SAMPLE *sonBoutonClique;
    Element *element;
    int nbElement;
} ComposantsJeu;

#endif //ESCOOKED_JEU_JOUEUR_H
