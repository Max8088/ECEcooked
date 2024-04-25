//
// Created by pierr on 03/04/2024.
//

#ifndef ESCOOKED_JEU_H
#define ESCOOKED_JEU_H

#include "../constantes.h"
#include "../jeu+joueur/jeu+joueur.h"

#define NB_LIGNES 7
#define NB_COLONNES 13
#define TAILLE_CASE 60
#define MARGE_GAUCHE_DROITE 234
#define MARGE_HAUT_BAS 141


void InitialiserFenetreFileTimer(ComposantsJeu *jeu);

void ChargerFichierTxt(ComposantsJeu *jeu);

void DessinerElements(const ComposantsJeu *jeu);

void Jeu(ComposantsJeu *jeu,Joueur *joueur1,Joueur *joueur2);

#endif //ESCOOKED_JEU_H
