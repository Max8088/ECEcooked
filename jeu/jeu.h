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
#define DISTANCEINTERACTION 60
#define DISTANCE_DE_PROXIMITE 10
#define RAYON_PROXIMITE 50
#define TYPE_SOL1 0
#define TYPE_SOL2 1
#define TYPE_FRIGOCITRON 2
#define TYPE_PLANDETRAVAIL 3
#define TYPE_FRIGOMENTHE 4
#define TYPE_FRIGOLIMONADE 5
#define TYPE_POUBELLE 6
#define TYPE_PLAQUEDECUISSON 7
#define TYPE_SORTIE 8
#define TYPE_STATIONDEDECOUPE 9
#define TYPE_FRIGOCANNEASUCRE 11
#define NOMBRE_RECETTES 3
#define NOMBRE_MAX_INGREDIENTS 5
#define MAX_ELEMENTS 100

void InitialiserFenetreFileTimer(ComposantsJeu *jeu);

void DessinerBoutonMenuPause(BoutonJeu boutonJeu, ComposantsJeu *jeu, ALLEGRO_COLOR couleurRectangle,
                             ALLEGRO_COLOR couleurTexte);

bool EstDansLeBoutonMenuPause(BoutonJeu boutonJeu, float x, float y);

void DessinerMenuPause(ComposantsJeu *jeu, BoutonJeu *bouton);

void ChargerFichierTxt(ComposantsJeu *jeu);

void AfficherFichierTxt(const ComposantsJeu *jeu);

void DessinerTempsRestant(int tempsRestant, ComposantsJeu *jeu);

void VerifierPosJoueur(Joueur *joueur);

bool VerifierCollisionJoueur(Joueur *joueur, ComposantsJeu *jeu);

void MAJAngleJoueur(Joueur *joueur);

void MAJPosJoueurs(Joueur *joueur1, Joueur *joueur2, ComposantsJeu *jeu, bool *maj);

void DessinerJoueur(Joueur *joueur, ComposantsJeu *jeu);

void GestionKeyDown(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2, ALLEGRO_EVENT *event, bool *maj);

void GestionKeyUP(ComposantsJeu *jeu,Joueur *joueur1, Joueur *joueur2, ALLEGRO_EVENT *event, bool *maj);

void Jeu(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2);

void ChargerImagesCommandes(ImagesCommandes *images);

void InitialiserRecettes(Recette recettes[], ComposantsJeu *jeu);

void InitialiserCommandes(Commande **listeDeCommandes, Recette recettes[]);

void AjouterCommande(Commande **liste, Commande *nouvelle);

Commande *CreerCommandeAleatoire(Recette recettes[]);

void TraiterCommandes(Commande **listeDeCommandes, Recette recettes[]);

void DessinerCommande(ComposantsJeu *jeu, Commande *commande, ImagesCommandes *images, float x, float y);

void DessinerToutesLesCommandes(ComposantsJeu *jeu, Commande *listeDeCommandes, ImagesCommandes *images);

void libererCommandes(Commande *liste);

#endif //ESCOOKED_JEU_H

