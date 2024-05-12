
#include "../constantes.h"
#include "../jeu/jeu.h"
#include "menu.h"


void DessinerBouton1(Bouton bouton, ALLEGRO_FONT *police, ALLEGRO_COLOR couleurRectangle, ALLEGRO_COLOR couleurTexte) {
    al_draw_filled_rounded_rectangle(bouton.x, bouton.y, bouton.x + bouton.width, bouton.y + bouton.height, 10, 10,
                                     couleurRectangle);
    float text_x = bouton.x + (bouton.width - al_get_text_width(police, bouton.texte)) / 2;
    float text_y = bouton.y + (bouton.height - al_get_font_ascent(police)) / 2;
    text_y -= 5;
    al_draw_text(police, couleurTexte, text_x, text_y, 0, bouton.texte);
}

void DessinerBouton2(Bouton bouton, ALLEGRO_FONT *police, ALLEGRO_COLOR couleurRectangle, ALLEGRO_COLOR couleurTexte) {
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

void SonBoutonClique(Sons *son) {
    al_play_sample_instance(son->instanceEffetsSonores);
}

void MenuCredits(ComposantsJeu ***jeu, Sons ***son) {
    ALLEGRO_EVENT event;
    bool fini = false;
    Bouton boutons[] = {
            {-10, 612, 130, 70, "<-"}
    };
    int nbBoutons = sizeof(boutons) / sizeof(boutons[0]);
    float mouseX = 0, mouseY = 0;

    al_clear_to_color(BLANC);
    al_draw_bitmap((**jeu)->ImageMenu, 0, 0, 0);
    for (int i = 0; i < nbBoutons; ++i) {
        DessinerBouton1(boutons[i], (**jeu)->police, NOIR, GRIS_CLAIR_TRANSPARENT);
    }
    al_draw_text((**jeu)->police, NOIR, 624, 225, ALLEGRO_ALIGN_CENTRE, "-PIERRE-");
    al_draw_text((**jeu)->police, NOIR, 624, 325, ALLEGRO_ALIGN_CENTRE, "-MAXIME-");
    al_draw_text((**jeu)->police, NOIR, 624, 425, ALLEGRO_ALIGN_CENTRE, "-NIKITA-");
    al_draw_text((**jeu)->police, NOIR, 624, 525, ALLEGRO_ALIGN_CENTRE, "-FANIRY-");
    al_flip_display();

    while (!fini) {
        al_wait_for_event((**jeu)->file, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], mouseX, mouseY)) {
                        if (!(strcmp(boutons[i].texte, "<-"))) {
                            SonBoutonClique(**son);
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
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], mouseX, mouseY)) {
                        DessinerBouton2(boutons[i], (**jeu)->police, NOIR, BLANC);
                    } else {
                        DessinerBouton1(boutons[i], (**jeu)->police, NOIR, GRIS_CLAIR_TRANSPARENT);
                    }
                }
                al_flip_display();
                break;


        }
    }

}

void DessinerCurseur(const Curseur *curseur, ComposantsJeu ***jeu, float volume) {
    al_draw_filled_rounded_rectangle(curseur->x - 5, curseur->y, curseur->x + curseur->width + 5,
                                     curseur->y + curseur->height, 10, 10, GRIS_CLAIR_TRANSPARENT);
    float curseurPos = (volume - curseur->min) / (curseur->max - curseur->min) * curseur->width;
    al_draw_filled_circle(curseur->x + curseurPos, curseur->y + curseur->height / 2, curseur->height / 2, NOIR);
}

bool EstDansLeCurseurVolume(const Curseur *curseur, float mx, float my) {
    return (mx >= curseur->x && mx <= curseur->x + curseur->width && my >= curseur->y &&
            my <= curseur->y + curseur->height);
}

void MenuVolume(Sons ***son, ComposantsJeu ***jeu) {
    ALLEGRO_EVENT event;
    bool fini = false, draggingMusique = false, draggingEffetsSonores = false;
    float dernierX = 0;
    float mouseX = 0, mouseY = 0;
    char volMusiqueText[50];
    char volEffetsSonoresText[50];
    Bouton boutons[] = {
            {-10, 612, 130, 70, "<-"}
    };
    int nbBoutons = sizeof(boutons) / sizeof(boutons[0]);
    Curseur curseurVolumeMusique = {300, 300, 648, 30, 0.0, 1.0,
                                    al_get_sample_instance_gain((**son)->instanceDeMusqiue)};
    Curseur curseurEffetsSonores = {300, 400, 648, 30, 0.0, 1.0,
                                    al_get_sample_instance_gain((**son)->instanceEffetsSonores)};

    al_clear_to_color(NOIR);
    al_draw_bitmap((**jeu)->ImageMenu, 0, 0, 0);
    for (int i = 0; i < nbBoutons; ++i) {
        DessinerBouton1(boutons[i], (**jeu)->police, NOIR, GRIS_CLAIR);
    }
    DessinerCurseur(&curseurVolumeMusique, jeu, curseurVolumeMusique.value);
    sprintf(volMusiqueText, "Music Volume: %.0f%%", curseurVolumeMusique.value * 100);
    al_draw_text((**jeu)->police, NOIR, 624, curseurVolumeMusique.y + 30, ALLEGRO_ALIGN_CENTER, volMusiqueText);
    DessinerCurseur(&curseurEffetsSonores, jeu, curseurEffetsSonores.value);
    sprintf(volEffetsSonoresText, "Sound Effects Volume: %.0f%%", curseurEffetsSonores.value * 100);
    al_draw_text((**jeu)->police, NOIR, 624, curseurEffetsSonores.y + 30, ALLEGRO_ALIGN_CENTER, volEffetsSonoresText);


    al_flip_display();

    while (!fini) {
        al_wait_for_event((**jeu)->file, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
                if (EstDansLeCurseurVolume(&curseurVolumeMusique, mouseX, mouseY)) {
                    draggingMusique = true;
                    dernierX = mouseX;
                } else if (EstDansLeCurseurVolume(&curseurEffetsSonores, mouseX, mouseY)) {
                    draggingEffetsSonores = true;
                    dernierX = mouseX;
                }
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], mouseX, mouseY)) {
                        if (!(strcmp(boutons[i].texte, "<-"))) {
                            SonBoutonClique(**son);
                            fini = true;
                        }
                    }
                }
                draggingMusique = false;
                draggingEffetsSonores = false;
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                mouseX = event.mouse.x;
                mouseY = event.mouse.y;
                break;
            case ALLEGRO_EVENT_TIMER:
                al_clear_to_color(NOIR);
                al_draw_bitmap((**jeu)->ImageMenu, 0, 0, 0);
                DessinerCurseur(&curseurVolumeMusique, jeu, curseurVolumeMusique.value);
                sprintf(volMusiqueText, "Music: %.0f%%", curseurVolumeMusique.value * 100);
                al_draw_text((**jeu)->police, NOIR, 624, curseurVolumeMusique.y + 30, ALLEGRO_ALIGN_CENTER,
                             volMusiqueText);
                DessinerCurseur(&curseurEffetsSonores, jeu, curseurEffetsSonores.value);
                sprintf(volEffetsSonoresText, "Sound Effects: %.0f%%", curseurEffetsSonores.value * 100);
                al_draw_text((**jeu)->police, NOIR, 624, curseurEffetsSonores.y + 30, ALLEGRO_ALIGN_CENTER,
                             volEffetsSonoresText);

                if (draggingMusique) {
                    float dx = mouseX - dernierX;
                    dernierX = mouseX;
                    float nouvVolumeMusique = curseurVolumeMusique.value + (dx / curseurVolumeMusique.width) *
                                                                           (curseurVolumeMusique.max -
                                                                            curseurVolumeMusique.min);
                    if (nouvVolumeMusique < curseurVolumeMusique.min) { nouvVolumeMusique = curseurVolumeMusique.min; }
                    if (nouvVolumeMusique > curseurVolumeMusique.max) { nouvVolumeMusique = curseurVolumeMusique.max; }
                    curseurVolumeMusique.value = nouvVolumeMusique;
                    al_set_sample_instance_gain((**son)->instanceDeMusqiue, curseurVolumeMusique.value);
                    al_set_sample_instance_gain((**son)->instanceMusiqueJeu, curseurVolumeMusique.value);

                } else if (draggingEffetsSonores) {
                    float dx = mouseX - dernierX;
                    dernierX = mouseX;
                    float nouvVolumeEffetsSonores = curseurEffetsSonores.value + (dx / curseurEffetsSonores.width) *
                                                                                 (curseurEffetsSonores.max -
                                                                                  curseurEffetsSonores.min);
                    if (nouvVolumeEffetsSonores <
                        curseurEffetsSonores.min) { nouvVolumeEffetsSonores = curseurEffetsSonores.min; }
                    if (nouvVolumeEffetsSonores >
                        curseurEffetsSonores.max) { nouvVolumeEffetsSonores = curseurEffetsSonores.max; }
                    curseurEffetsSonores.value = nouvVolumeEffetsSonores;
                    al_set_sample_instance_gain((**son)->instanceEffetsSonores, curseurEffetsSonores.value);
                }
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], mouseX, mouseY)) {
                        DessinerBouton2(boutons[i], (**jeu)->police, NOIR, BLANC);
                    } else {
                        DessinerBouton1(boutons[i], (**jeu)->police, NOIR, GRIS_CLAIR_TRANSPARENT);
                    }
                }
                al_flip_display();
                break;
        }
    }

}
