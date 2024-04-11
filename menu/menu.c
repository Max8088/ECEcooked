//
// Created by pierr on 03/04/2024.
//
#include "../constantes.h"
#include "menu.h."
#include "../joueur/joueur.h"
#include "../jouer/jouer.h"

void dessinerBouton1(Bouton bouton, ALLEGRO_FONT *police, ALLEGRO_COLOR couleurRectangle, ALLEGRO_COLOR couleurTexte) {
    al_draw_filled_rounded_rectangle(bouton.x, bouton.y, bouton.x + bouton.width, bouton.y + bouton.height, 10, 10,
                                     couleurRectangle);
    float text_x = bouton.x + (bouton.width - al_get_text_width(police, bouton.texte)) / 2;
    float text_y = bouton.y + (bouton.height - al_get_font_ascent(police)) / 2;
    text_y -= 5;
    al_draw_text(police, couleurTexte, text_x, text_y, 0, bouton.texte);
}

void dessinerBouton2(Bouton bouton, ALLEGRO_FONT *police, ALLEGRO_COLOR couleurRectangle, ALLEGRO_COLOR couleurTexte) {
    al_draw_filled_rounded_rectangle(bouton.x, bouton.y, bouton.x + bouton.width, bouton.y + bouton.height, 10, 10,
                                     couleurRectangle);
    float text_x = bouton.x + (bouton.width - al_get_text_width(police, bouton.texte)) / 2;
    float text_y = bouton.y + (bouton.height - al_get_font_ascent(police)) / 2;
    text_y -= 9;
    al_draw_text(police, couleurTexte, text_x, text_y, 0, bouton.texte);
}

bool EstDansLeBouton(Bouton bouton, float x, float y) {
    return (x >= bouton.x && x <= bouton.x + bouton.width &&
            y >= bouton.y && y <= bouton.y + bouton.height);
}

void dessinerMenu(ALLEGRO_BITMAP* ImageMenu, int nbBoutons, Bouton boutons[], ALLEGRO_EVENT event2, ALLEGRO_FONT* police){
    al_clear_to_color(BLANC);
    al_draw_bitmap(ImageMenu, 0, 0, 0);
    for (int i = 0; i < nbBoutons; ++i) {
        if (EstDansLeBouton(boutons[i], event2.mouse.x, event2.mouse.y)) {
            dessinerBouton2(boutons[i], police, NOIR_TRANSPARENT, GRIS_CLAIR_TRANSPARENT);
        } else {
            dessinerBouton1(boutons[i], police, NOIR, BLANC);
        }
    }
    al_flip_display();
}

void Credits(ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police, ALLEGRO_EVENT_QUEUE* queue1) {
    bool done = false;
    Bouton boutons[] = {
            {-10, 612, 130, 70, "<-"}
    };
    int nbBoutons = sizeof(boutons) / sizeof(boutons[0]);

    al_clear_to_color(BLANC);
    al_draw_bitmap(ImageMenu, 0, 0, 0);
    for (int i = 0; i < nbBoutons; ++i) {
        dessinerBouton1(boutons[i], police, NOIR, GRIS_CLAIR_TRANSPARENT);
    }
    al_draw_text(police, NOIR, 624, 225, ALLEGRO_ALIGN_CENTRE, "-PIERRE-");
    al_draw_text(police, NOIR, 624, 325, ALLEGRO_ALIGN_CENTRE, "-MAXIME-");
    al_draw_text(police, NOIR, 624, 425, ALLEGRO_ALIGN_CENTRE, "-NIKITA-");
    al_draw_text(police, NOIR, 624, 525, ALLEGRO_ALIGN_CENTRE, "-FANIRY-");
    al_flip_display();

    while (!done) {
        ALLEGRO_EVENT event7;
        al_wait_for_event(queue1, &event7);
        switch (event7.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                al_clear_to_color(BLANC);
                al_draw_bitmap(ImageMenu, 0, 0, 0);
                al_draw_text(police, NOIR, 624, 225, ALLEGRO_ALIGN_CENTRE, "-PIERRE-");
                al_draw_text(police, NOIR, 624, 325, ALLEGRO_ALIGN_CENTRE, "-MAXIME-");
                al_draw_text(police, NOIR, 624, 425, ALLEGRO_ALIGN_CENTRE, "-NIKITA-");
                al_draw_text(police, NOIR, 624, 525, ALLEGRO_ALIGN_CENTRE, "-FANIRY-");
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], event7.mouse.x, event7.mouse.y)) {
                        dessinerBouton2(boutons[i], police, NOIR, BLANC);
                    } else {
                        dessinerBouton1(boutons[i], police, NOIR, GRIS_CLAIR_TRANSPARENT);
                    }
                }
                al_flip_display();
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], event7.mouse.x, event7.mouse.y)) {
                        if (!(strcmp(boutons[i].texte, "<-"))) {
                            done = true;
                        }
                    }
                }
                break;
        }
    }
}

void menuOptions(ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police, ALLEGRO_EVENT_QUEUE* queue1) {
    bool done = false;
    Bouton boutons[] = {
            {-10, 612, 130, 70, "<-"}
    };
    Bouton boutonsSousMenu[] = {
            {425, 235, 400, 70, "Controls"},
            {425, 335, 400, 70, "Credits"},
            {425, 435, 400, 70, "Volume"}
    };
    int nbBoutons = sizeof(boutons) / sizeof(boutons[0]);
    int nbBoutonsSousMenu = sizeof(boutonsSousMenu) / sizeof(boutonsSousMenu[0]);

    al_clear_to_color(NOIR);
    al_draw_bitmap(ImageMenu, 0, 0, 0);
    for (int i = 0; i < nbBoutons; ++i) {
        dessinerBouton1(boutons[i], police, NOIR, GRIS_CLAIR);
    }
    for (int i = 0; i < nbBoutonsSousMenu; ++i) {
        dessinerBouton1(boutonsSousMenu[i], police, NOIR, BLANC);
    }
    al_flip_display();

    while (!done) {
        ALLEGRO_EVENT event6;
        al_wait_for_event(queue1, &event6);
        switch (event6.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                done = true;
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                al_clear_to_color(BLANC);
                al_draw_bitmap(ImageMenu, 0, 0, 0);
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], event6.mouse.x, event6.mouse.y)) {
                        dessinerBouton2(boutons[i], police, NOIR, BLANC);
                    } else {
                        dessinerBouton1(boutons[i], police, NOIR, GRIS_CLAIR);
                    }
                }
                for (int i = 0; i < nbBoutonsSousMenu; ++i) {
                    if (EstDansLeBouton(boutonsSousMenu[i], event6.mouse.x, event6.mouse.y)) {
                        dessinerBouton2(boutonsSousMenu[i], police, NOIR_TRANSPARENT, GRIS_CLAIR);
                    } else {
                        dessinerBouton1(boutonsSousMenu[i], police, NOIR, BLANC);
                    }
                }
                al_flip_display();
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], event6.mouse.x, event6.mouse.y)) {
                        if (!(strcmp(boutons[i].texte, "<-"))) {
                            done = true;
                        }
                    }
                }
                for (int i = 0; i < nbBoutonsSousMenu; ++i) {
                    if (EstDansLeBouton(boutonsSousMenu[i], event6.mouse.x, event6.mouse.y)) {
                        if (!(strcmp(boutonsSousMenu[i].texte, "Credits"))) {
                            Credits(ImageMenu, police, queue1);
                            al_clear_to_color(BLANC);
                            al_draw_bitmap(ImageMenu, 0, 0, 0);
                            for (i = 0; i < nbBoutons; ++i) {
                                if (EstDansLeBouton(boutons[i], event6.mouse.x, event6.mouse.y)) {
                                    dessinerBouton2(boutons[i], police, NOIR, BLANC);
                                } else {
                                    dessinerBouton1(boutons[i], police, NOIR, GRIS_CLAIR);
                                }
                            }
                            for (i = 0; i < nbBoutonsSousMenu; ++i) {
                                if (EstDansLeBouton(boutonsSousMenu[i], event6.mouse.x, event6.mouse.y)) {
                                    dessinerBouton2(boutonsSousMenu[i], police, NOIR_TRANSPARENT, GRIS_CLAIR);
                                } else {
                                    dessinerBouton1(boutonsSousMenu[i], police, NOIR, BLANC);
                                }
                            }
                            al_flip_display();
                        }
                        if (!(strcmp(boutonsSousMenu[i].texte, "Volume"))) {
                            done = true;
                        }
                    }
                }

                break;
        }
    }
}

void menuScores(ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police, ALLEGRO_EVENT_QUEUE* queue1) {
    bool done = false;
    Bouton boutons[] = {
            {-10, 612, 130, 70, "<-"}
    };
    int nbBoutons = sizeof(boutons) / sizeof(boutons[0]);

    al_clear_to_color(NOIR);
    al_draw_bitmap(ImageMenu, 0, 0, 0);
    for (int i = 0; i < nbBoutons; ++i) {
        dessinerBouton1(boutons[i], police, NOIR, GRIS_CLAIR);
    }
    al_flip_display();

    while (!done) {
        ALLEGRO_EVENT event5;
        al_wait_for_event(queue1, &event5);
        al_clear_to_color(BLANC);
        al_draw_bitmap(ImageMenu, 0, 0, 0);
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
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], event5.mouse.x, event5.mouse.y)) {
                        if (!(strcmp(boutons[i].texte, "<-"))) {
                            done = true;
                        }
                    }
                }
                break;
        }
    }
}

void menu(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *ImageMenu, ALLEGRO_BITMAP *decor1, ALLEGRO_FONT *police, ALLEGRO_EVENT_QUEUE* queue1) {
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

    al_clear_to_color(BLANC);
    al_draw_bitmap(ImageMenu, 0, 0, 0);
    for (int i = 0; i < nbBoutons; ++i) {
        dessinerBouton1(boutons[i], police, NOIR, BLANC);
    }
    al_flip_display();

    while (!QuitterMenu) {
        ALLEGRO_EVENT event2;
        al_wait_for_event(queue1, &event2);

        switch (event2.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                QuitterMenu = true;
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                dessinerMenu(ImageMenu, nbBoutons, boutons, event2, police);
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], event2.mouse.x, event2.mouse.y)) {
                        if (!(strcmp(boutons[i].texte, "Play"))) {
                            ChoisirPseudo(&joueur1, &joueur2, display, ImageMenu, police, &LancerJeu);
                            if (LancerJeu) {
                                jeu(decor1, police, queue1);
                            }
                            dessinerMenu(ImageMenu, nbBoutons, boutons, event2, police);
                        }
                        if (!(strcmp(boutons[i].texte, "Options"))) {
                            menuOptions(ImageMenu, police, queue1);
                            dessinerMenu(ImageMenu, nbBoutons, boutons, event2, police);
                        }
                        if (!(strcmp(boutons[i].texte, "Scores"))) {
                            menuScores(ImageMenu, police, queue1);
                            dessinerMenu(ImageMenu, nbBoutons, boutons, event2, police);

                        }
                        if (!(strcmp(boutons[i].texte, "Exit"))) {
                            QuitterMenu = true;
                        }
                    }
                }
                break;
        }
    }
}