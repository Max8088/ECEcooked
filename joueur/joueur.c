
//
// Created by pierr on 03/04/2024.
//
#include "../constantes.h"
#include "joueur.h"
#include "../menu/menu.h"

void
ChoisirPseudo(Joueur *joueur1, Joueur *joueur2, ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *ImageMenu,
              ALLEGRO_FONT *police, int *LancerJeu, ALLEGRO_SAMPLE *sonBoutonClique) {
    SoundCliquedButton(sonBoutonClique);
    ALLEGRO_EVENT_QUEUE *queue3 = NULL;
    char pseudoJoueur1[13] = "";
    char pseudoJoueur2[13] = "";
    bool joueur1_saisi = false;
    bool joueur2_saisi = false;
    bool done = false;
    Bouton boutons[] = {
            {-10,  612, 140, 70, "<-"},
            {1118, 612, 140, 70, "->"}
    };
    Bouton boutonPseudo1 = {300, 255, 650, 70, "Pseudo player 1:"};
    Bouton boutonPseudo2 = {300, 405, 650, 70, "Pseudo player 2:"};
    int nbBoutons = sizeof(boutons) / sizeof(boutons[0]);

    queue3 = al_create_event_queue();
    assert(queue3);

    al_register_event_source(queue3, al_get_display_event_source(display));
    al_register_event_source(queue3, al_get_keyboard_event_source());
    al_register_event_source(queue3, al_get_mouse_event_source());

    al_clear_to_color(NOIR);
    al_draw_bitmap(ImageMenu, 0, 0, 0);
    al_draw_text(police, BLANC, 624, 550, ALLEGRO_ALIGN_CENTER,
                 "(Press ENTER to confirm pseudos)");
    al_draw_text(police, NOIR, 345, 325, ALLEGRO_ALIGN_CENTER,
                 "-");
    al_draw_text(police, NOIR, 345, 475, ALLEGRO_ALIGN_CENTER,
                 "-");
    dessinerBouton2(boutonPseudo1, police, NOIR, BLANC);
    dessinerBouton1(boutonPseudo2, police, NOIR_TRANSPARENT, GRIS_CLAIR_TRANSPARENT);
    for (int i = 0; i < nbBoutons; ++i) {
        dessinerBouton1(boutons[i], police, NOIR, GRIS_CLAIR_TRANSPARENT);
    }
    al_draw_filled_triangle(220, 270, 220, 300, 260, 285, NOIR);
    al_draw_filled_triangle(1010, 632, 1010, 662, 1050, 647, ROUGE);
    al_flip_display();

    while (!done) {
        ALLEGRO_EVENT event3;
        al_wait_for_event(queue3, &event3);
        al_clear_to_color(NOIR);
        al_draw_bitmap(ImageMenu, 0, 0, 0);
        al_draw_text(police, BLANC, 624, 550, ALLEGRO_ALIGN_CENTER,
                     "(Press ENTER to confirm pseudos)");
        al_draw_text(police, NOIR, 345, 325, ALLEGRO_ALIGN_CENTER,
                     "-");
        al_draw_text(police, NOIR, 345, 475, ALLEGRO_ALIGN_CENTER,
                     "-");
        al_draw_text(police, NOIR, 360, 325, ALLEGRO_ALIGN_LEFT,
                     pseudoJoueur1);
        al_draw_text(police, NOIR, 360, 475, ALLEGRO_ALIGN_LEFT,
                     pseudoJoueur2);
        if (!joueur1_saisi) {
            dessinerBouton2(boutonPseudo1, police, NOIR, BLANC);
            dessinerBouton1(boutonPseudo2, police, NOIR_TRANSPARENT, GRIS_CLAIR_TRANSPARENT);
            al_draw_filled_triangle(220, 270, 220, 300, 260, 285, NOIR);
            al_draw_filled_triangle(1010, 632, 1010, 662, 1050, 647, ROUGE);
        }
        if (!joueur2_saisi && joueur1_saisi) {
            dessinerBouton1(boutonPseudo1, police, NOIR, VERT_CLAIR);
            dessinerBouton2(boutonPseudo2, police, NOIR, GRIS_CLAIR);
            al_draw_filled_triangle(220, 420, 220, 450, 260, 435, NOIR);
            al_draw_filled_triangle(1010, 632, 1010, 662, 1050, 647, ROUGE);
        }
        if (joueur1_saisi && joueur2_saisi) {
            dessinerBouton1(boutonPseudo1, police, NOIR, VERT_CLAIR);
            dessinerBouton1(boutonPseudo2, police, NOIR, VERT_CLAIR);
            al_draw_filled_triangle(1010, 632, 1010, 662, 1050, 647, VERT_CLAIR);
        }
        for (int i = 0; i < nbBoutons; ++i) {
            if (EstDansLeBouton(boutons[i], event3.mouse.x, event3.mouse.y)) {
                dessinerBouton2(boutons[i], police, NOIR, BLANC);
            } else {
                dessinerBouton1(boutons[i], police, NOIR, GRIS_CLAIR_TRANSPARENT);
            }
        }
        al_flip_display();
        switch (event3.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            case ALLEGRO_EVENT_KEY_CHAR:
                if (!joueur1_saisi) {
                    if (event3.keyboard.unichar >= 32 && event3.keyboard.unichar <= 126) {
                        if (strlen(pseudoJoueur1) < 12) {
                            char str[2] = {event3.keyboard.unichar, '\0'};
                            strcat(pseudoJoueur1, str);
                        }
                    } else if (event3.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(pseudoJoueur1) > 0) {
                        pseudoJoueur1[strlen(pseudoJoueur1) - 1] = '\0';
                    } else if (event3.keyboard.keycode == ALLEGRO_KEY_ENTER && strlen(pseudoJoueur1) > 0 &&
                               strlen(pseudoJoueur1) < 13) {
                        joueur1_saisi = true;
                        SoundCliquedButton(sonBoutonClique);
                    }
                } else if (!joueur2_saisi) {
                    if (event3.keyboard.unichar >= 32 && event3.keyboard.unichar <= 126) {
                        if (strlen(pseudoJoueur2) < 12) {
                            char str[2] = {event3.keyboard.unichar, '\0'};
                            strcat(pseudoJoueur2, str);
                        }
                    } else if (event3.keyboard.keycode == ALLEGRO_KEY_BACKSPACE && strlen(pseudoJoueur2) > 0) {
                        pseudoJoueur2[strlen(pseudoJoueur2) - 1] = '\0';
                    } else if (event3.keyboard.keycode == ALLEGRO_KEY_ENTER && strlen(pseudoJoueur2) > 0 &&
                               strlen(pseudoJoueur2) < 13) {
                        joueur2_saisi = true;
                        SoundCliquedButton(sonBoutonClique);
                    }
                }
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], event3.mouse.x, event3.mouse.y)) {
                        if (!(strcmp(boutons[i].texte, "<-"))) {
                            SoundCliquedButton(sonBoutonClique);
                            done = true;
                        }
                        if (!(strcmp(boutons[i].texte, "->")) && joueur1_saisi && joueur2_saisi) {
                            *LancerJeu = 1;
                            strcpy(joueur1->pseudo, pseudoJoueur1);
                            strcpy(joueur2->pseudo, pseudoJoueur2);
                            SoundCliquedButton(sonBoutonClique);
                            done = true;
                        }
                    }

                }
                break;
        }
    }
    al_destroy_event_queue(queue3);
    queue3 = NULL;
}
