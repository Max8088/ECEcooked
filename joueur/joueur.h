
//
// Created by pierr on 03/04/2024.
//

#ifndef ESCOOKED_JOUEUR_H
#define ESCOOKED_JOUEUR_H

#include "../constantes.h"
#include "../jeu/jeu.h"
#include "../jeu+joueur/jeu+joueur.h"


void InitialiserJoueur(Joueur *joueur, const char *cheminVersImage, float x, float y);

void ChoisirPseudos(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2, bool *lancerJeu, Sons *sons);

#endif //ESCOOKED_JOUEUR_H