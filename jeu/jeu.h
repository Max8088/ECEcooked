//
// Created by pierr on 03/04/2024.
//

#ifndef ESCOOKED_JEU_H
#define ESCOOKED_JEU_H

#include "../constantes.h"
#include "../jeu+joueur/jeu+joueur.h"

#define NB_LIGNES 9
#define NB_COLONNES 17
#define TAILLE_CASE 60
#define MARGE_GAUCHE_DROITE 114
#define MARGE_HAUT_BAS 81
#define TYPE_SOL1 0
#define TYPE_SOL2 1


void InitialiserFenetreFileTimer(ComposantsJeu *jeu);

void DessinerBoutonMenuPause(BoutonJeu boutonJeu, ComposantsJeu *jeu, ALLEGRO_COLOR couleurRectangle,
                             ALLEGRO_COLOR couleurTexte);

bool EstDansLeBoutonMenuPause(BoutonJeu boutonJeu, float x, float y);

void DessinerMenuPause(ComposantsJeu *jeu, BoutonJeu *bouton);

void ChargerFichierTxt(ComposantsJeu *jeu);

void DessinerElements(const ComposantsJeu *jeu);

void DessinerTempsRestant(int tempsRestant, ComposantsJeu *jeu);

void VerifierPosJoueur(Joueur *joueur);

bool VerifierCollisionJoueur(Joueur *joueur, ComposantsJeu *jeu);

void MAJAngleJoueur(Joueur *joueur);

void MAJPosJoueurs(Joueur *joueur1, Joueur *joueur2, ComposantsJeu *jeu, bool *maj);

void DessinerJoueur(Joueur *joueur, ComposantsJeu *jeu);

void GestionKeyDown(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2, ALLEGRO_EVENT *event, bool *maj);

void GestionKeyUP(ComposantsJeu *jeu,Joueur *joueur1, Joueur *joueur2, ALLEGRO_EVENT *event, bool *maj);

void Jeu(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2);

#endif //ESCOOKED_JEU_H

