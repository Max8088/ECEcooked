
//
// Created by pierr on 03/04/2024.
//

#ifndef ESCOOKED_JOUER_H
#define ESCOOKED_JOUER_H

#include "../constantes.h"
#include "../joueur/joueur.h"

typedef struct {
    ALLEGRO_BITMAP *image;
    int x, y;
} ElementCuisine;

void jeu(ALLEGRO_BITMAP *decor1, ALLEGRO_BITMAP *sol, ALLEGRO_BITMAP *personnage,ALLEGRO_BITMAP *cuisson,ALLEGRO_BITMAP *decoupe,
         ALLEGRO_BITMAP *distrib_assiette,ALLEGRO_BITMAP *poubelle,ALLEGRO_BITMAP *sortie, ALLEGRO_EVENT_QUEUE *queue1,
         Joueur joueur1, Joueur joueur2);

void afficherJeuDepuisFichier(ALLEGRO_BITMAP *sol, ALLEGRO_BITMAP *personnage, ALLEGRO_BITMAP *cuisson,ALLEGRO_BITMAP *decoupe,ALLEGRO_BITMAP *distrib_assiette,ALLEGRO_BITMAP *poubelle,ALLEGRO_BITMAP *sortie );

#endif //ESCOOKED_JOUER_H
