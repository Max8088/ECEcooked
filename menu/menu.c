//
// Created by pierr on 03/04/2024.
//
#include "../constantes.h"
#include "menu.h."
#include "../joueur/joueur.h"
#include "../jouer/jouer.h"

void dessinerBouton1(Bouton bouton, ALLEGRO_FONT *police, ALLEGRO_COLOR couleurRectangle, ALLEGRO_COLOR couleurTexte) {
    al_draw_filled_rounded_rectangle(bouton.x, bouton.y, bouton.x + bouton.width, bouton.y + bouton.height, 10, 10, couleurRectangle);
    float text_x = bouton.x + (bouton.width - al_get_text_width(police, bouton.texte)) / 2;
    float text_y = bouton.y + (bouton.height - al_get_font_ascent(police)) / 2;
    text_y -= 5;
    al_draw_text(police, couleurTexte, text_x, text_y, 0, bouton.texte);
}

void dessinerBouton2(Bouton bouton, ALLEGRO_FONT *police, ALLEGRO_COLOR couleurRectangle, ALLEGRO_COLOR couleurTexte) {
    al_draw_filled_rounded_rectangle(bouton.x, bouton.y, bouton.x + bouton.width, bouton.y + bouton.height, 10, 10, couleurRectangle);
    float text_x = bouton.x + (bouton.width - al_get_text_width(police, bouton.texte)) / 2;
    float text_y = bouton.y + (bouton.height - al_get_font_ascent(police)) / 2;
    text_y -= 9;
    al_draw_text(police, couleurTexte, text_x, text_y, 0, bouton.texte);
}

bool EstDansLeBouton(Bouton bouton, float x, float y) {
    return (x >= bouton.x && x <= bouton.x + bouton.width &&
            y >= bouton.y && y <= bouton.y + bouton.height);
}

void menuOptions(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police) {
    ALLEGRO_EVENT_QUEUE *queue6 = NULL;
    bool done = false;
    Bouton boutons[] = {
            {80, 612, 130, 70, "<"},
    };
    int nbBoutons = sizeof(boutons) / sizeof(boutons[0]);

    queue6 = al_create_event_queue();
    assert(queue6);

    al_register_event_source(queue6, al_get_display_event_source(display));
    al_register_event_source(queue6, al_get_mouse_event_source());

    al_clear_to_color(NOIR);
    al_draw_bitmap(ImageMenu, 0, 0, 0);
    for (int i = 0; i < nbBoutons; ++i) {
        dessinerBouton1(boutons[i], police, NOIR, GRIS_CLAIR_TRANSPARENT);
    }
    al_draw_filled_triangle(80, 612, 20, 647, 80, 682, NOIR);
    al_flip_display();

    while (!done) {
        ALLEGRO_EVENT event6;
        al_wait_for_event(queue6, &event6);
        switch (event6.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                al_clear_to_color(BLANC);
                al_draw_bitmap(ImageMenu, 0, 0, 0);
                al_draw_filled_triangle(80, 612, 20, 647, 80, 682, NOIR);
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], event6.mouse.x, event6.mouse.y)) {
                        dessinerBouton2(boutons[i], police, NOIR, BLANC);
                    } else {
                        dessinerBouton1(boutons[i], police, NOIR, GRIS_CLAIR_TRANSPARENT);
                    }
                }
                al_flip_display();
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], event6.mouse.x, event6.mouse.y)) {
                        if (!(strcmp(boutons[i].texte, "<"))) {
                            done = true;
                        }
                    }
                }
                break;
        }
    }
    al_destroy_event_queue(queue6);
    queue6 = NULL;
}

void menuScores(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police) {
    ALLEGRO_EVENT_QUEUE *queue5 = NULL;
    bool done = false;
    Bouton boutons[] = {
            {80, 612, 130, 70, "<"}
    };
    int nbBoutons = sizeof(boutons) / sizeof(boutons[0]);

    queue5 = al_create_event_queue();
    assert(queue5);

    al_register_event_source(queue5, al_get_display_event_source(display));
    al_register_event_source(queue5, al_get_mouse_event_source());

    al_clear_to_color(NOIR);
    al_draw_bitmap(ImageMenu, 0, 0, 0);
    for (int i = 0; i < nbBoutons; ++i) {
        dessinerBouton1(boutons[i], police, NOIR, GRIS_CLAIR);
    }
    al_draw_filled_triangle(80, 612, 20, 647, 80, 682, NOIR);
    al_flip_display();

    while (!done) {
        ALLEGRO_EVENT event5;
        al_wait_for_event(queue5, &event5);
        al_clear_to_color(BLANC);
        al_draw_bitmap(ImageMenu, 0, 0, 0);
        al_draw_filled_triangle(80, 612, 20, 647, 80, 682, NOIR);
        switch (event5.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], event5.mouse.x, event5.mouse.y)) {
                        dessinerBouton2(boutons[i], police, NOIR, BLANC);
                    } else {
                        dessinerBouton1(boutons[i], police, NOIR, GRIS_CLAIR_TRANSPARENT);
                    }
                }
                al_flip_display();
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], event5.mouse.x, event5.mouse.y)) {
                        if (!(strcmp(boutons[i].texte, "<"))) {
                            done = true;
                        }
                    }
                }
                break;
        }
    }
    al_destroy_event_queue(queue5);
    queue5 = NULL;
}

void menu(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police) {
    ALLEGRO_EVENT_QUEUE *queue2 = NULL;
    Joueur joueur1;
    Joueur joueur2;
    int LancerJeu = 0;
    Bouton boutons[] = {
            {425, 235, 400, 70, "Play"},
            {425, 335, 400, 70, "Options"},
            {425, 435, 400, 70, "Scores"},
            {425, 535, 400, 70, "Exit"}
    };
    int nbBoutons = sizeof(boutons) / sizeof(boutons[0]);
    bool QuitterMenu = false;

    queue2 = al_create_event_queue();
    assert(queue2);

    al_register_event_source(queue2, al_get_display_event_source(display));
    al_register_event_source(queue2, al_get_mouse_event_source());

    al_clear_to_color(BLANC);
    al_draw_bitmap(ImageMenu, 0, 0, 0);
    for (int i = 0; i < nbBoutons; ++i) {
        dessinerBouton1(boutons[i], police, NOIR, GRIS_CLAIR);
    }
    al_flip_display();

    while (!QuitterMenu) {
        ALLEGRO_EVENT event2;
        al_wait_for_event(queue2, &event2);

        switch (event2.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                QuitterMenu = true;
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                al_clear_to_color(BLANC);
                al_draw_bitmap(ImageMenu, 0, 0, 0);
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], event2.mouse.x, event2.mouse.y)) {
                        dessinerBouton2(boutons[i], police, NOIR_TRANSPARENT, GRIS_CLAIR_TRANSPARENT);
                    } else {
                        dessinerBouton1(boutons[i], police, NOIR, GRIS_CLAIR);
                    }
                }
                al_flip_display();
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], event2.mouse.x, event2.mouse.y)) {
                        if (!(strcmp(boutons[i].texte, "Play"))) {
                            ChoisirPseudo(&joueur1, &joueur2, display, ImageMenu, police, &LancerJeu);
                            if (LancerJeu) {
                                jeu(display, ImageMenu, police);
                            }
                        }
                        if (!(strcmp(boutons[i].texte, "Options"))) {
                            menuOptions(display, ImageMenu, police);
                        }
                        if (!(strcmp(boutons[i].texte, "Scores"))) {
                            menuScores(display, ImageMenu, police);
                        }
                        if (!(strcmp(boutons[i].texte, "Exit"))) {
                            QuitterMenu = true;
                        }
                    }
                }
                break;
        }
    }
    al_destroy_event_queue(queue2);
    queue2 = NULL;
}