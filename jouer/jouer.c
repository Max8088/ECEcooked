//
// Created by pierr on 03/04/2024.
//
#include "../constantes.h"
#include "../joueur/joueur.h"
#include "jouer.h"

#define NB_LIGNES 9
#define NB_COLONNES 17
#define TAILLE_CASE 60
#define MARGE_GAUCHE_DROITE 114
#define MARGE_HAUT_BAS 81

void afficherJeuDepuisFichier(ALLEGRO_BITMAP *sol, ALLEGRO_BITMAP *personnage) {
    FILE *fichier = fopen("../FichierTexte", "r");
    if (!fichier) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }
    if (!sol || !personnage) {
        fprintf(stderr, "Erreur lors du chargement des images.\n");
        exit(EXIT_FAILURE);
    }

    int x, y;
    int entier;

    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            if (fscanf(fichier, "%d", &entier) == EOF) {
                fprintf(stderr, "Erreur : Fin de fichier prématurée.\n");
                exit(EXIT_FAILURE);
            }

            x = MARGE_GAUCHE_DROITE + j * TAILLE_CASE;
            y = MARGE_HAUT_BAS + i * TAILLE_CASE;

            switch (entier) {
                case 0:
                    al_draw_bitmap(sol, x, y, 0);
                    break;
                case 1:
                    al_draw_bitmap(personnage, x, y, 0);
                    break;
                default:
                    break;
            }
        }
    }
    al_flip_display();
    fclose(fichier);
}

void jeu(ALLEGRO_BITMAP *decor1, ALLEGRO_BITMAP *sol, ALLEGRO_BITMAP *personnage, ALLEGRO_EVENT_QUEUE *queue1,
         Joueur joueur1, Joueur joueur2) {
    bool fini = false;

    al_clear_to_color(BLANC);
    al_draw_bitmap(decor1, 0, 0, 0);
    al_flip_display();

    while (!fini) {
        ALLEGRO_EVENT event4;
        al_wait_for_event(queue1, &event4);
        afficherJeuDepuisFichier(sol, personnage);
        switch (event4.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;
        }
    }
}