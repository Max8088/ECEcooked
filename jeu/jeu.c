
#include "../constantes.h"
#include "jeu.h"
#include "../joueur/joueur.h"

void InitialiserFenetreFileTimer(ComposantsJeu *jeu) {
    jeu->fenetre = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    jeu->file = al_create_event_queue();
    jeu->timer = al_create_timer(1.0 / 120.0);
    al_register_event_source(jeu->file, al_get_display_event_source(jeu->fenetre));
    al_register_event_source(jeu->file, al_get_keyboard_event_source());
    al_register_event_source(jeu->file, al_get_mouse_event_source());
    al_register_event_source(jeu->file, al_get_timer_event_source(jeu->timer));
}

void ChargerFichierTxt(ComposantsJeu *jeu) {
    FILE *fichier = fopen("../images/FichierTexte", "r");
    if (!fichier) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }
    if (!jeu->decor || !jeu->sol || !jeu->plaqueDeCuisson || !jeu->planDeDecoupe || !jeu->planDeTravail ||
        !jeu->distributeurAssiette || !jeu->poubelle || !jeu->sortie) {
        fprintf(stderr, "Erreur lors du chargement des images.\n");
        exit(EXIT_FAILURE);
    }

    jeu->element = malloc(NB_LIGNES * NB_COLONNES * sizeof(Element));
    jeu->nbElement = 0;
    int TypeElement;

    for (int i = 0; i < NB_LIGNES; ++i) {
        for (int j = 0; j < NB_COLONNES; ++j) {
            fscanf(fichier, "%d", &TypeElement);
            if (TypeElement != -1) {
                jeu->element[jeu->nbElement].type = TypeElement;
                jeu->element[jeu->nbElement].x = MARGE_GAUCHE_DROITE + j * TAILLE_CASE;
                jeu->element[jeu->nbElement].y = MARGE_HAUT_BAS + i * TAILLE_CASE;
                jeu->nbElement++;
            }
        }
    }
    fclose(fichier);
}

void DessinerElements(const ComposantsJeu *jeu) {
    for (int i = 0; i < jeu->nbElement; i++) {
        ALLEGRO_BITMAP *bitmap = NULL;
        switch (jeu->element[i].type) {
            case 0:
                bitmap = jeu->sol;
                break;
            case 1:
                bitmap = jeu->planDeTravail;
                break;
            case 2:
                bitmap = jeu->planDeDecoupe;
                break;
            case 3:
                bitmap = jeu->plaqueDeCuisson;
                break;
            case 4:
                bitmap = jeu->poubelle;
                break;
            case 5:
                bitmap = jeu->distributeurAssiette;
                break;
            case 6:
                bitmap = jeu->sortie;
                break;
        }
        if (bitmap) {
            al_draw_bitmap(bitmap, jeu->element[i].x, jeu->element[i].y, 0);
        }
    }
}

void DessinerJoueur(Joueur *joueur) {
    float cx = al_get_bitmap_width(joueur->image) / 2;
    float cy = al_get_bitmap_height(joueur->image) / 2;
    al_draw_rotated_bitmap(joueur->image, cx, cy, joueur->x + cx, joueur->y + cy, joueur->angle, 0);
}

void Jeu(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2) {
    ALLEGRO_EVENT event;
    bool fini = false, maj = false;

    ChargerFichierTxt(jeu);
    DessinerElements(jeu);
    DessinerJoueur(joueur1);
    DessinerJoueur(joueur2);
    al_flip_display();

    while (!fini) {
        al_wait_for_event(jeu->file, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;
        }
    }
}