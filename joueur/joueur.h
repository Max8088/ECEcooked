
//
// Created by pierr on 03/04/2024.
//

#ifndef ESCOOKED_JOUEUR_H
#define ESCOOKED_JOUEUR_H

#include "../constantes.h"

typedef struct {
    char pseudo[13];
    ALLEGRO_BITMAP *image;
} Joueur;

void ChoisirPseudo(Joueur *joueur1, Joueur *joueur2, ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *ImageMenu,
                   ALLEGRO_FONT *police, int *pLancerJeu);

#endif //ESCOOKED_JOUEUR_H
