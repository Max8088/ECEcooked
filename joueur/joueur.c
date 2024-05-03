
#include "../constantes.h"
#include "../menu/menu.h"
#include "joueur.h"


void InitialiserJoueur(Joueur *joueur, const char *cheminVersImage, float x, float y) {
    joueur->x = x;
    joueur->y = y;
    joueur->vx = 0;
    joueur->vy = 0;
    joueur->angle = 0;
    joueur->image = al_load_bitmap(cheminVersImage);
    strcpy(joueur->pseudo, "");
    assert(joueur->image);
}

void MAJpositionobjettenu(Joueur *joueur, Ingredient *ing) {
    ing->x = joueur->x;
    ing->y = joueur->y;
}

void ChoisirPseudos(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2, bool *lancerJeu, Sons *sons) {
    bool fini = false, joueur1_saisi = false, joueur2_saisi = false;
    Bouton boutons[] = {
            {-10,  612, 140, 70, "<-"},
            {1118, 612, 140, 70, "->"}
    };
    Bouton boutonPseudo1 = {300, 255, 650, 70, "Pseudo player 1:"};
    Bouton boutonPseudo2 = {300, 405, 650, 70, "Pseudo player 2:"};
    int nbBoutons = sizeof(boutons) / sizeof(boutons[0]);
    float mouseX = 0, mouseY = 0;
    ALLEGRO_EVENT event;

    al_clear_to_color(NOIR);
    al_draw_bitmap(jeu->ImageMenu, 0, 0, 0);
    al_draw_text(jeu->police, BLANC, 624, 550, ALLEGRO_ALIGN_CENTER, "(Press ENTER to confirm pseudos)");
    al_draw_text(jeu->police, NOIR, 345, 325, ALLEGRO_ALIGN_CENTER, "-");
    al_draw_text(jeu->police, NOIR, 345, 475, ALLEGRO_ALIGN_CENTER, "-");
    DessinerBouton2(boutonPseudo1, jeu->police, NOIR, BLANC);
    DessinerBouton1(boutonPseudo2, jeu->police, NOIR_TRANSPARENT, GRIS_CLAIR_TRANSPARENT);
    for (int i = 0; i < nbBoutons; ++i) {
        DessinerBouton1(boutons[i], jeu->police, NOIR, GRIS_CLAIR_TRANSPARENT);
    }
    al_draw_filled_triangle(220, 270, 220, 300, 260, 285, NOIR);
    al_flip_display();

    while (!fini) {
        al_wait_for_event(jeu->file, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;
            case ALLEGRO_EVENT_KEY_CHAR:
                if (!joueur1_saisi) {
                    if (event.keyboard.unichar >= 32 && event.keyboard.unichar <= 126) {
                        if (strlen(joueur1->pseudo) < 12) {
                            char str[2] = {event.keyboard.unichar, '\0'};
                            strcat(joueur1->pseudo, str);
                        }
                    } else if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(joueur1->pseudo) > 0) {
                        joueur1->pseudo[strlen(joueur1->pseudo) - 1] = '\0';
                    } else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER && strlen(joueur1->pseudo) > 0 &&
                               strlen(joueur1->pseudo) < 13) {
                        SonBoutonClique(sons);
                        joueur1_saisi = true;
                    }
                } else if (!joueur2_saisi) {
                    if (event.keyboard.unichar >= 32 && event.keyboard.unichar <= 126) {
                        if (strlen(joueur2->pseudo) < 12) {
                            char str[2] = {event.keyboard.unichar, '\0'};
                            strcat(joueur2->pseudo, str);
                        }
                    } else if (event.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(joueur2->pseudo) > 0) {
                        joueur2->pseudo[strlen(joueur2->pseudo) - 1] = '\0';
                    } else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER && strlen(joueur2->pseudo) > 0 &&
                               strlen(joueur2->pseudo) < 13) {
                        SonBoutonClique(sons);
                        joueur2_saisi = true;
                    }
                }
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], event.mouse.x, event.mouse.y)) {
                        if (!(strcmp(boutons[i].texte, "<-"))) {
                            SonBoutonClique(sons);
                            fini = true;
                        }
                        if (!(strcmp(boutons[i].texte, "->")) && joueur1_saisi && joueur2_saisi) {
                            *lancerJeu = true;
                            SonBoutonClique(sons);
                            fini = true;
                        }
                    }
                }
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                mouseX = event.mouse.x;
                mouseY = event.mouse.y;
                break;
            case ALLEGRO_EVENT_TIMER:
                al_clear_to_color(NOIR);
                al_draw_bitmap(jeu->ImageMenu, 0, 0, 0);
                al_draw_text(jeu->police, BLANC, 624, 550, ALLEGRO_ALIGN_CENTER, "(Press ENTER to confirm pseudos)");
                al_draw_text(jeu->police, NOIR, 345, 325, ALLEGRO_ALIGN_CENTER, "-");
                al_draw_text(jeu->police, NOIR, 345, 475, ALLEGRO_ALIGN_CENTER, "-");
                al_draw_text(jeu->police, NOIR, 360, 325, ALLEGRO_ALIGN_LEFT, joueur1->pseudo);
                al_draw_text(jeu->police, NOIR, 360, 475, ALLEGRO_ALIGN_LEFT, joueur2->pseudo);
                if (EstDansLeBouton(boutons[0], mouseX, mouseY)) {
                    DessinerBouton1(boutons[0], jeu->police, NOIR, BLANC);
                } else {
                    DessinerBouton2(boutons[0], jeu->police, NOIR, GRIS_CLAIR_TRANSPARENT);
                }
                if (!joueur1_saisi) {
                    DessinerBouton2(boutonPseudo1, jeu->police, NOIR, BLANC);
                    DessinerBouton1(boutonPseudo2, jeu->police, NOIR_TRANSPARENT, GRIS_CLAIR_TRANSPARENT);
                    DessinerBouton1(boutons[1], jeu->police, NOIR, ROUGE);
                    al_draw_filled_triangle(220, 270, 220, 300, 260, 285, NOIR);
                }
                if (!joueur2_saisi && joueur1_saisi) {
                    DessinerBouton1(boutonPseudo1, jeu->police, NOIR, VERT_CLAIR);
                    DessinerBouton2(boutonPseudo2, jeu->police, NOIR, GRIS_CLAIR);
                    DessinerBouton1(boutons[1], jeu->police, NOIR, ROUGE);
                    al_draw_filled_triangle(220, 420, 220, 450, 260, 435, NOIR);
                }
                if (joueur1_saisi && joueur2_saisi) {
                    DessinerBouton1(boutonPseudo1, jeu->police, NOIR, VERT_CLAIR);
                    DessinerBouton1(boutonPseudo2, jeu->police, NOIR, VERT_CLAIR);
                    DessinerBouton1(boutons[1], jeu->police, NOIR, VERT_CLAIR);
                }
                al_flip_display();
                break;
        }
    }
}