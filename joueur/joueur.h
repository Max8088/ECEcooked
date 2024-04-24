
//
// Created by pierr on 03/04/2024.
//

#ifndef ESCOOKED_JOUEUR_H
#define ESCOOKED_JOUEUR_H

#include "../constantes.h"
#include "../jeu/jeu.h"

typedef struct {
    char pseudo[13];
    ALLEGRO_BITMAP *image;
    int score, x, y, vx, vy;
    float angle;
} Joueur;

void InitialiserJoueur(Joueur *joueur, const char *cheminVersImage, float x, float y);

void ChoisirPseudos(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2, bool *lancerJeu);

#endif //ESCOOKED_JOUEUR_H
