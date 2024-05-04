
#include "../constantes.h"
#include "jeu.h"
#include "math.h"

void InitialiserFenetreFileTimer(ComposantsJeu *jeu) {
    jeu->fenetre = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    jeu->file = al_create_event_queue();
    jeu->timer = al_create_timer(1.0 / 60.0);
    jeu->DureePartie = 90;
    al_register_event_source(jeu->file, al_get_display_event_source(jeu->fenetre));
    al_register_event_source(jeu->file, al_get_keyboard_event_source());
    al_register_event_source(jeu->file, al_get_mouse_event_source());
    al_register_event_source(jeu->file, al_get_timer_event_source(jeu->timer));
    jeu->enPause= false;
}
void DessinerMenuPause(ComposantsJeu *jeu) {
    // Dessine un rectangle semi-transparent pour le fond du menu pause
    al_draw_filled_rectangle(DISPLAY_WIDTH / 4, DISPLAY_HEIGHT / 4, 3 * DISPLAY_WIDTH / 4, 3 * DISPLAY_HEIGHT / 4, al_map_rgba(0, 0, 0, 200));



    // Dessine le rectangle du bouton de reprise du jeu
    float bouton_x = DISPLAY_WIDTH / 3;
    float bouton_y = DISPLAY_HEIGHT / 4 + DISPLAY_HEIGHT / 12; // Déplacement vers le haut
    float bouton_width = DISPLAY_WIDTH / 3;
    float bouton_height = DISPLAY_HEIGHT / 6;
    al_draw_filled_rectangle(bouton_x, bouton_y, bouton_x + bouton_width, bouton_y + bouton_height, al_map_rgba(139, 71, 3, 200));

    // Dessine le texte "Reprendre le jeu" au centre du bouton
    float text_x = DISPLAY_WIDTH / 2;
    float text_y = bouton_y + bouton_height / 2 - al_get_font_ascent(jeu->policePseudo);
    al_draw_text(jeu->police, NOIR, text_x, text_y, ALLEGRO_ALIGN_CENTER, "Reprendre le jeu");
}



void ChargerFichierTxt(ComposantsJeu *jeu) {
    FILE *fichier = fopen("../images/FichierTexte", "r");
    if (!fichier) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier.\n");
        exit(EXIT_FAILURE);
    }
    if (!jeu->decor || !jeu->sol1 || !jeu->sol2 || !jeu->plaqueDeCuisson || !jeu->planDeDecoupe ||
        !jeu->planDeTravail ||
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
                bitmap = jeu->sol1;
                break;
            case 1:
                bitmap = jeu->sol2;
                break;
            case 2:
                bitmap = jeu->planDeDecoupe;
                break;
            case 3:
                bitmap = jeu->planDeTravail;
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

void DessinerTempsRestant(int tempsRestant, ComposantsJeu *jeu) {
    char text[10];
    sprintf(text, "%02d:%02d", tempsRestant / 60, tempsRestant % 60);

    float cx = al_get_bitmap_width(jeu->sablier) / 2.0;
    float cy = al_get_bitmap_height(jeu->sablier) / 2.0;
    float x = 1090 + cx;
    float y = 10 + cy;

    int secondesEcoulees = jeu->DureePartie - tempsRestant;
    float angle = (secondesEcoulees % 2) * M_PI;

    al_draw_rotated_bitmap(jeu->sablier, cx, cy, x, y, angle, 0);
    if (tempsRestant > 30) {
        al_draw_text(jeu->policeRegle, NOIR, 1050, 20, ALLEGRO_ALIGN_CENTER, text);
    } else {
        al_draw_text(jeu->policeRegle, ROUGE, 1050, 20, ALLEGRO_ALIGN_CENTER, text);
    }
}

void VerifierPosJoueur(Joueur *joueur) {
    int joueur_width = al_get_bitmap_width(joueur->image);
    int joueur_height = al_get_bitmap_height(joueur->image);

    if (joueur->x < MARGE_GAUCHE_DROITE) { joueur->x = MARGE_GAUCHE_DROITE; }
    if (joueur->x + joueur_width > DISPLAY_WIDTH - MARGE_GAUCHE_DROITE) {
        joueur->x =
                DISPLAY_WIDTH - MARGE_GAUCHE_DROITE -
                joueur_width;
    }
    if (joueur->y < MARGE_HAUT_BAS) { joueur->y = MARGE_HAUT_BAS; }
    if (joueur->y + joueur_height > DISPLAY_HEIGHT - MARGE_HAUT_BAS) {
        joueur->y = DISPLAY_HEIGHT - MARGE_HAUT_BAS -
                    joueur_height;
    }
}

bool VerifierCollisionJoueur(Joueur *joueur, ComposantsJeu *jeu) {
    int joueur_width = al_get_bitmap_width(joueur->image);
    int joueur_height = al_get_bitmap_height(joueur->image);

    for (int i = 0; i < jeu->nbElement; i++) {
        if (jeu->element[i].type != TYPE_SOL1 && jeu->element[i].type != TYPE_SOL2) {
            if (joueur->x < jeu->element[i].x + TAILLE_CASE &&
                joueur->x + joueur_width > jeu->element[i].x &&
                joueur->y < jeu->element[i].y + TAILLE_CASE &&
                joueur->y + joueur_height > jeu->element[i].y) {
                return true;
            }
        }
    }
    return false;
}

void MAJAngleJoueur(Joueur *joueur) {
    if (joueur->vx != 0 || joueur->vy != 0) {
        joueur->angle = atan2(joueur->vy, joueur->vx) + M_PI / 2;
    }
}

void MAJPosJoueurs(Joueur *joueur1, Joueur *joueur2, ComposantsJeu *jeu, bool *maj) {
    int ancienXjoueur1 = joueur1->x, ancienYjoueur1 = joueur1->y;
    int ancienXjoueur2 = joueur2->x, ancienYjoueur2 = joueur2->y;

    if (joueur1->vx != 0 || joueur1->vy != 0) {
        joueur1->x += joueur1->vx;
        joueur1->y += joueur1->vy;
        MAJAngleJoueur(joueur1);
        if (VerifierCollisionJoueur(joueur1, jeu)) {
            joueur1->x = ancienXjoueur1;
            joueur1->y = ancienYjoueur1;
        }
        VerifierPosJoueur(joueur1);
        *maj = true;
    }
    if (joueur2->vx != 0 || joueur2->vy != 0) {
        joueur2->x += joueur2->vx;
        joueur2->y += joueur2->vy;
        MAJAngleJoueur(joueur2);
        if (VerifierCollisionJoueur(joueur2, jeu)) {
            joueur2->x = ancienXjoueur2;
            joueur2->y = ancienYjoueur2;
        }
        VerifierPosJoueur(joueur2);
        *maj = true;
    }
}

void DessinerJoueur(Joueur *joueur, ComposantsJeu *jeu) {
    float cx = al_get_bitmap_width(joueur->image) / 2;
    float cy = al_get_bitmap_height(joueur->image) / 2;
    al_draw_rotated_bitmap(joueur->image, cx, cy, joueur->x + cx, joueur->y + cy, joueur->angle, 0);
    float text_x = joueur->x + cx;
    float text_y = joueur->y - al_get_font_ascent(jeu->policePseudo);
    al_draw_text(jeu->policePseudo, BLANC, text_x, text_y, ALLEGRO_ALIGN_CENTER, joueur->pseudo);
}

void GestionKeyDown(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2, ALLEGRO_EVENT *event, bool *maj) {
    if (!jeu->enPause) {
    switch (event->keyboard.keycode) {
        case ALLEGRO_KEY_Z:
            joueur1->vy = -2;
            *maj = true;
            break;
        case ALLEGRO_KEY_S:
            joueur1->vy = 2;
            *maj = true;
            break;
        case ALLEGRO_KEY_Q:
            joueur1->vx = -2;
            *maj = true;
            break;
        case ALLEGRO_KEY_D:
            joueur1->vx = 2;
            *maj = true;
            break;
        case ALLEGRO_KEY_UP:
            joueur2->vy = -2;
            *maj = true;
            break;
        case ALLEGRO_KEY_DOWN:
            joueur2->vy = 2;
            *maj = true;
            break;
        case ALLEGRO_KEY_LEFT:
            joueur2->vx = -2;
            *maj = true;
            break;
        case ALLEGRO_KEY_RIGHT:
            joueur2->vx = 2;
            *maj = true;
            break;
        case ALLEGRO_KEY_P:
            jeu->enPause = !jeu->enPause;

            *maj = true;
            break;
        case ALLEGRO_KEY_C:
        case ALLEGRO_KEY_L:
            //bool vérifie la collision entre objet et joeur si true prendre
            break;

        case ALLEGRO_KEY_V:
        case ALLEGRO_KEY_M:
            //bool vérifie la collision entre objet et joeur si true lacher
            break;
    }
    }
}

void GestionKeyUP(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2, ALLEGRO_EVENT *event, bool *maj) {
    if (!jeu->enPause) {

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
}

void Jeu(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2) {
    ALLEGRO_EVENT event;
    bool fini = false, maj = false;
    int tempsRestant = jeu->DureePartie;
    int compteurTickDuTimer = 0;

    al_clear_to_color(NOIR);
    al_draw_bitmap(jeu->ImageFondDeJeu, 0, 0, 0);
    ChargerFichierTxt(jeu);
    DessinerElements(jeu);
    DessinerJoueur(joueur1, jeu);
    DessinerJoueur(joueur2, jeu);
    DessinerTempsRestant(tempsRestant, jeu);
    al_flip_display();

    while (!fini) {
        al_wait_for_event(jeu->file, &event);

        switch (event.type) {

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;

            case ALLEGRO_EVENT_KEY_DOWN:
                GestionKeyDown(jeu, joueur1, joueur2, &event, &maj);
                break;
            case ALLEGRO_EVENT_KEY_UP:
                GestionKeyUP(jeu,joueur1, joueur2, &event, &maj);
                break;

            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if (jeu->enPause && event.mouse.button == 1) {
                    // Vérifie si les coordonnées du clic sont à l'intérieur du rectangle du bouton
                    float mouse_x = event.mouse.x;
                    float mouse_y = event.mouse.y;
                    float bouton_x = DISPLAY_WIDTH / 3;
                    float bouton_y = DISPLAY_HEIGHT / 4 + DISPLAY_HEIGHT / 12; // Position du bouton
                    float bouton_width = DISPLAY_WIDTH / 3;
                    float bouton_height = DISPLAY_HEIGHT / 6;

                    if (mouse_x >= bouton_x && mouse_x <= bouton_x + bouton_width &&
                        mouse_y >= bouton_y && mouse_y <= bouton_y + bouton_height) {
                        // Si le clic est à l'intérieur du rectangle, reprendre le jeu
                        jeu->enPause = false;
                        maj = true;
                    }
                }
                break;



            case ALLEGRO_EVENT_TIMER:
                if (++compteurTickDuTimer >= 60) {
                    tempsRestant--;
                    compteurTickDuTimer = 0;
                }
                if (tempsRestant < 0) {
                    fini = true;
                }
                MAJPosJoueurs(joueur1, joueur2, jeu, &maj);
                if (maj) {
                    al_clear_to_color(NOIR);
                    al_draw_bitmap(jeu->ImageFondDeJeu, 0, 0, 0);
                    DessinerElements(jeu);
                    DessinerTempsRestant(tempsRestant, jeu);
                    DessinerJoueur(joueur1, jeu);
                    DessinerJoueur(joueur2, jeu);

                    if (jeu->enPause) {
                        DessinerMenuPause(jeu);
                    }
                    al_flip_display();
                    maj = false;
                }
                break;


        }

    }


}

