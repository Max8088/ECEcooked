
#include "../constantes.h"
#include "jeu.h"
#include "math.h"

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

void VerifierPosJoueur(Joueur *joueur) {
    int joueur_width = al_get_bitmap_width(joueur->image);
    int joueur_height = al_get_bitmap_height(joueur->image);

    if (joueur->x < 0) { joueur->x = 0; }
    if (joueur->x + joueur_width > DISPLAY_WIDTH - MARGE_GAUCHE_DROITE) { joueur->x = DISPLAY_WIDTH - MARGE_GAUCHE_DROITE - joueur_width; }
    if (joueur->y < 0) { joueur->y = 0; }
    if (joueur->y + joueur_height > DISPLAY_HEIGHT) { joueur->y = DISPLAY_HEIGHT - joueur_height; }
}

void MAJAngleJoueur(Joueur *joueur) {
    if (joueur->vx != 0 || joueur->vy != 0) {
        joueur->angle = atan2(joueur->vy, joueur->vx) + M_PI / 2;
    }
}

void MAJPosJoueurs(Joueur *joueur1, Joueur *joueur2, bool *maj) {
    if (joueur1->vx != 0 || joueur1->vy != 0) {
        joueur1->x += joueur1->vx;
        joueur1->y += joueur1->vy;
        MAJAngleJoueur(joueur1);
        VerifierPosJoueur(joueur1);
        *maj = true;
    }
    if (joueur2->vx != 0 || joueur2->vy != 0) {
        joueur2->x += joueur2->vx;
        joueur2->y += joueur2->vy;
        MAJAngleJoueur(joueur2);
        VerifierPosJoueur(joueur2);
        *maj = true;
    }
}

void DessinerJoueur(Joueur *joueur) {
    float cx = al_get_bitmap_width(joueur->image) / 2;
    float cy = al_get_bitmap_height(joueur->image) / 2;
    al_draw_rotated_bitmap(joueur->image, cx, cy, joueur->x + cx, joueur->y + cy, joueur->angle, 0);
}

void GestionKeyDown(Joueur *joueur1, Joueur *joueur2, ALLEGRO_EVENT *event, bool *maj) {
    switch (event->keyboard.keycode) {
        case ALLEGRO_KEY_Z:
            joueur1->vy = -1;
            *maj = true;
            break;
        case ALLEGRO_KEY_S:
            joueur1->vy = 1;
            *maj = true;
            break;
        case ALLEGRO_KEY_Q:
            joueur1->vx = -1;
            *maj = true;
            break;
        case ALLEGRO_KEY_D:
            joueur1->vx = 1;
            *maj = true;
            break;
        case ALLEGRO_KEY_UP:
            joueur2->vy = -1;
            *maj = true;
            break;
        case ALLEGRO_KEY_DOWN:
            joueur2->vy = 1;
            *maj = true;
            break;
        case ALLEGRO_KEY_LEFT:
            joueur2->vx = -1;
            *maj = true;
            break;
        case ALLEGRO_KEY_RIGHT:
            joueur2->vx = 1;
            *maj = true;
            break;
    }
}

void GestionKeyUP(Joueur *joueur1, Joueur *joueur2, ALLEGRO_EVENT *event, bool *maj) {
    switch (event->keyboard.keycode) {
        case ALLEGRO_KEY_Z:
        case ALLEGRO_KEY_S:
            joueur1->vy = 0;
            *maj = true;
            break;
        case ALLEGRO_KEY_Q:
        case ALLEGRO_KEY_D:
            joueur1->vx = 0;
            *maj = true;
            break;
        case ALLEGRO_KEY_UP:
        case ALLEGRO_KEY_DOWN:
            joueur2->vy = 0;
            *maj = true;
            break;
        case ALLEGRO_KEY_RIGHT:
        case ALLEGRO_KEY_LEFT:
            joueur2->vx = 0;
            *maj = true;
            break;
    }
}

void Jeu(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2) {
    ALLEGRO_EVENT event;
    bool fini = false, maj = false;

    al_clear_to_color(NOIR);
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
            case ALLEGRO_EVENT_KEY_DOWN:
                GestionKeyDown(joueur1, joueur2, &event, &maj);
                break;
            case ALLEGRO_EVENT_KEY_UP:
                GestionKeyUP(joueur1, joueur2, &event, &maj);
                break;
            case ALLEGRO_EVENT_TIMER:
                MAJPosJoueurs(joueur1, joueur2, &maj);
                if (maj) {
                    al_clear_to_color(NOIR);
                    DessinerElements(jeu);
                    DessinerJoueur(joueur1);
                    DessinerJoueur(joueur2);
                    al_flip_display();
                    maj = false;
                }
                break;
        }
    }
}