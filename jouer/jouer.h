//
// Created by pierr on 03/04/2024.
//

#ifndef ESCOOKED_JOUER_H
#define ESCOOKED_JOUER_H

#include "../constantes.h"
#include "../joueur/joueur.h"


#define NB_LIGNES 7
#define NB_COLONNES 13
#define TAILLE_CASE 60
#define MARGE_GAUCHE_DROITE 234
#define MARGE_HAUT_BAS 141

typedef struct {
    ALLEGRO_BITMAP *image;
    int x, y;
} ElementCuisine;

void jeu(ALLEGRO_BITMAP *decor1, ALLEGRO_BITMAP *sol, ALLEGRO_BITMAP *personnage, ALLEGRO_BITMAP *cuisson,
         ALLEGRO_BITMAP *decoupe,
         ALLEGRO_BITMAP *distrib_assiette, ALLEGRO_BITMAP *poubelle, ALLEGRO_BITMAP *sortie,
         ALLEGRO_EVENT_QUEUE *queue1, ALLEGRO_BITMAP *planDeTravail,
         Joueur joueur1, Joueur joueur2);

void afficherJeuDepuisFichier(ALLEGRO_BITMAP *sol, ALLEGRO_BITMAP *personnage, ALLEGRO_BITMAP *cuisson,
                              ALLEGRO_BITMAP *decoupe, ALLEGRO_BITMAP *distrib_assiette, ALLEGRO_BITMAP *poubelle,
                              ALLEGRO_BITMAP *sortie, ALLEGRO_BITMAP *planDeTravail);

#endif //ESCOOKED_JOUER_H
