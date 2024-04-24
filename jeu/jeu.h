//
// Created by pierr on 03/04/2024.
//

#ifndef ESCOOKED_JEU_H
#define ESCOOKED_JEU_H

#include "../constantes.h"
#include "../joueur/joueur.h"

#define NB_LIGNES 7
#define NB_COLONNES 13
#define TAILLE_CASE 60
#define MARGE_GAUCHE_DROITE 234
#define MARGE_HAUT_BAS 141

typedef struct {
    int type, x, y;
} Element;

typedef struct {
    ALLEGRO_DISPLAY *fenetre;
    ALLEGRO_EVENT_QUEUE *file;
    ALLEGRO_TIMER *timer;
    ALLEGRO_BITMAP *ImageMenu;
    ALLEGRO_BITMAP *decor;
    ALLEGRO_BITMAP *sol;
    ALLEGRO_BITMAP *plaqueDeCuisson;
    ALLEGRO_BITMAP *planDeDecoupe;
    ALLEGRO_BITMAP *planDeTravail;
    ALLEGRO_BITMAP *distributeurAssiette;
    ALLEGRO_BITMAP *poubelle;
    ALLEGRO_BITMAP *sortie;
    ALLEGRO_FONT *police;
    ALLEGRO_FONT *policeTitre;
    ALLEGRO_SAMPLE *musiqueFond;
    ALLEGRO_SAMPLE_INSTANCE *instanceMusique;
    ALLEGRO_SAMPLE *sonBoutonClique;
    Element *element;
    int nbElement;
} ComposantsJeu;

void InitialiserFenetreFileTimer(ComposantsJeu *jeu);

void ChargerFichierTxt(ComposantsJeu *jeu);

void DessinerElements(const ComposantsJeu *jeu);

void Jeu(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2);

#endif //ESCOOKED_JEU_H
