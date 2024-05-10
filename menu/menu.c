
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

void ArreterMusiqueFondDeMenu(Sons *son) {
    if (son->instanceDeMusqiue != NULL) {
        al_stop_sample_instance(son->instanceDeMusqiue);
    }
}

void JouerMusiqueFondDeMenu(Sons *son) {
    if (son->instanceDeMusqiue != NULL) {
        al_play_sample_instance(son->instanceDeMusqiue);
    }
}

void JouerMusiqueJeu(Sons *son) {
    if (son->instanceMusiqueJeu != NULL) {
        al_play_sample_instance(son->instanceMusiqueJeu);
    }
}

void ArreterMusiqueJeu(Sons *son) {
    if (son->instanceMusiqueJeu != NULL) {
        al_stop_sample_instance(son->instanceMusiqueJeu);
    }
}

void MenuRules(ComposantsJeu ***jeu, Sons **son) {
    ALLEGRO_EVENT event;
    bool fini = false;
    Bouton boutonRetour = {-10, 612, 130, 70, "<-"};
    float mouseX = 0, mouseY = 0;
    al_clear_to_color(NOIR);
    al_draw_bitmap((**jeu)->ImageMenu, 0, 0, 0);
    DessinerBouton1(boutonRetour, (**jeu)->police, NOIR, GRIS_CLAIR);

    al_draw_text((**jeu)->police, BLANC, 450, 200, ALLEGRO_ALIGN_LEFT, "Regles du jeu:");
    al_draw_text((**jeu)->policeRegle, NOIR, 290, 280, ALLEGRO_ALIGN_LEFT,
                 "Deux cuisiniers travaillent ensemble pour  ");
    al_draw_text((**jeu)->policeRegle, NOIR, 290, 320, ALLEGRO_ALIGN_LEFT,
                 "cuisiner des commmandes le plus rapidement    ");
    al_draw_text((**jeu)->policeRegle, NOIR, 290, 360, ALLEGRO_ALIGN_LEFT,
                 "possible dans un lieu qui peux rendre la tâche  ");
    al_draw_text((**jeu)->policeRegle, NOIR, 290, 400, ALLEGRO_ALIGN_LEFT,
                 "plus difficile que prévu. En binome ou seul  ");
    al_draw_text((**jeu)->policeRegle, NOIR, 290, 440, ALLEGRO_ALIGN_LEFT,
                 "vous devez récupérer les bon ingrédients,  ");
    al_draw_text((**jeu)->policeRegle, NOIR, 290, 480, ALLEGRO_ALIGN_LEFT,
                 "les préparer(decoupe/cuisson), les assembler  ");
    al_draw_text((**jeu)->policeRegle, NOIR, 290, 520, ALLEGRO_ALIGN_LEFT,
                 "et les faire sortir de cuisine avant le temps  ");
    al_draw_text((**jeu)->policeRegle, NOIR, 290, 560, ALLEGRO_ALIGN_LEFT, "imparti. Le décor oblige les joueurs à  ");
    al_draw_text((**jeu)->policeRegle, NOIR, 290, 600, ALLEGRO_ALIGN_LEFT, "communiquer. ");

    al_flip_display();

    while (!fini) {
        al_wait_for_event((**jeu)->file, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if (EstDansLeBouton(boutonRetour, mouseX, mouseY)) {
                    SonBoutonClique(*son);
                    fini = true;
                }
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                mouseX = event.mouse.x;
                mouseY = event.mouse.y;
                break;
            case ALLEGRO_EVENT_TIMER:
                if (EstDansLeBouton(boutonRetour, mouseX, mouseY)) {
                    DessinerBouton2(boutonRetour, (**jeu)->police, NOIR, BLANC);
                } else {
                    DessinerBouton1(boutonRetour, (**jeu)->police, NOIR, GRIS_CLAIR_TRANSPARENT);
                }
                al_flip_display();
                break;
        }
    }
}

void MenuOptions(ComposantsJeu **jeu, Sons **son) {
    ALLEGRO_EVENT event;
    bool fini = false;
    Bouton boutons[] = {
            {-10, 612, 130, 70, "<-"}
    };
    Bouton boutonsSousMenu[] = {
            {425, 435, 400, 70, "Credits"},
            {425, 235, 400, 70, "Volume"},
            {425, 335, 400, 70, "Rules"}

    };
    int nbBoutons = sizeof(boutons) / sizeof(boutons[0]);
    int nbBoutonsSousMenu = sizeof(boutonsSousMenu) / sizeof(boutonsSousMenu[0]);
    float mouseX = 0, mouseY = 0;

    al_clear_to_color(NOIR);
    al_draw_bitmap((*jeu)->ImageMenu, 0, 0, 0);
    for (int i = 0; i < nbBoutons; ++i) {
        DessinerBouton2(boutons[i], (*jeu)->police, NOIR, GRIS_CLAIR);
    }
    for (int i = 0; i < nbBoutonsSousMenu; ++i) {
        DessinerBouton1(boutonsSousMenu[i], (*jeu)->police, NOIR, BLANC);
    }
    al_flip_display();

    while (!fini) {
        al_wait_for_event((*jeu)->file, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], mouseX, mouseY)) {
                        if (!(strcmp(boutons[i].texte, "<-"))) {
                            SonBoutonClique(*son);
                            fini = true;
                            break;
                        }
                    }
                }
                for (int i = 0; i < nbBoutonsSousMenu; ++i) {
                    if (EstDansLeBouton(boutonsSousMenu[i], mouseX, mouseY)) {
                        if (!(strcmp(boutonsSousMenu[i].texte, "Volume"))) {
                            SonBoutonClique(*son);
                            MenuVolume(&son, &jeu);
                        }
                        if (!(strcmp(boutonsSousMenu[i].texte, "Credits"))) {
                            SonBoutonClique(*son);
                            MenuCredits(&jeu, &son);
                        }
                        if (!(strcmp(boutonsSousMenu[i].texte, "Rules"))) {
                            SonBoutonClique(*son);
                            MenuRules(&jeu, son);
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
                al_draw_bitmap((*jeu)->ImageMenu, 0, 0, 0);
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], mouseX, mouseY)) {
                        DessinerBouton2(boutons[i], (*jeu)->police, NOIR, BLANC);
                    } else {
                        DessinerBouton1(boutons[i], (*jeu)->police, NOIR, GRIS_CLAIR);
                    }
                }
                for (int i = 0; i < nbBoutonsSousMenu; ++i) {
                    if (EstDansLeBouton(boutonsSousMenu[i], mouseX, mouseY)) {
                        DessinerBouton2(boutonsSousMenu[i], (*jeu)->police, NOIR_TRANSPARENT, GRIS_CLAIR);
                    } else {
                        DessinerBouton1(boutonsSousMenu[i], (*jeu)->police, NOIR, BLANC);
                    }
                }
                al_flip_display();
                break;

        }
    }
}

void AfficherControls(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2) {
    ALLEGRO_EVENT event;
    bool fini = false;
    int countDown = 5, compteurTickDuTimer = 0;

    while (!fini) {
        al_wait_for_event(jeu->file, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;
            case ALLEGRO_EVENT_TIMER:
                if (++compteurTickDuTimer >= 60) {
                    countDown--;
                    compteurTickDuTimer = 0;
                }
                if (countDown <= 0) {
                    fini = true;
                }
                al_clear_to_color(NOIR);
                al_draw_text(jeu->police, BLANC, 228, 20, ALLEGRO_ALIGN_CENTER, joueur1->pseudo);
                al_draw_bitmap(joueur1->image, 198, 100, 0);
                al_draw_text(jeu->police, BLANC, 228, 180, ALLEGRO_ALIGN_CENTER, "Grab/Drop Keys");
                al_draw_bitmap(jeu->C, 134, 280, 0);
                al_draw_bitmap(jeu->V, 230, 280, 0);
                al_draw_text(jeu->police, BLANC, 228, 400, ALLEGRO_ALIGN_CENTER, "Moving Keys");
                al_draw_bitmap(jeu->Z, 180, 480, 0);
                al_draw_bitmap(jeu->S, 180, 570, 0);
                al_draw_bitmap(jeu->Q, 86, 570, 0);
                al_draw_bitmap(jeu->D, 276, 570, 0);

                al_draw_text(jeu->police, BLANC, 1020, 20, ALLEGRO_ALIGN_CENTER, joueur2->pseudo);
                al_draw_bitmap(joueur2->image, 990, 100, 0);
                al_draw_text(jeu->police, BLANC, 1020, 180, ALLEGRO_ALIGN_CENTER, "Grab/Drop Keys");
                al_draw_bitmap(jeu->L, 922, 280, 0);
                al_draw_bitmap(jeu->M, 1018, 280, 0);
                al_draw_text(jeu->police, BLANC, 1020, 400, ALLEGRO_ALIGN_CENTER, "Moving Keys");
                al_draw_text(jeu->police, BLANC, 614, 480, ALLEGRO_ALIGN_CENTER, "Pause mode");
                al_draw_bitmap(jeu->P, 560, 560, 0);
                al_draw_bitmap(jeu->FlecheHaut, 972, 480, 0);
                al_draw_bitmap(jeu->FlecheBas, 972, 580, 0);
                al_draw_bitmap(jeu->FlecheGauche, 872, 570, 0);
                al_draw_bitmap(jeu->FlecheDroite, 1072, 570, 0);
                al_draw_textf(jeu->police, BLANC, 624, 351, ALLEGRO_ALIGN_CENTER, "Starting in %d...", countDown);
                al_flip_display();
                break;
        }
    }
}

void PremierAffichageMenu(ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police, int nbBoutons, Bouton *boutons) {
    al_clear_to_color(NOIR);
    al_draw_bitmap(ImageMenu, 0, 0, 0);
    for (int i = 0; i < nbBoutons; ++i) {
        DessinerBouton1(boutons[i], police, NOIR, BLANC);
    }
    al_flip_display();
}

void DessinerNiveauApercu(Bouton niveau, ComposantsJeu *jeu) {
    al_draw_filled_rounded_rectangle(niveau.x, niveau.y, niveau.x + niveau.width, niveau.y + niveau.height, 10, 10, NOIR);
    al_draw_bitmap(niveau.apercu, 375, 287, 0);
    float text_x = niveau.x + (niveau.width - al_get_text_width(jeu->police, niveau.texte)) / 2;
    float text_y = niveau.y + (niveau.height - al_get_font_ascent(jeu->police)) / 2;
    al_draw_text(jeu->police, BLANC, text_x, text_y - 5, 0, niveau.texte);
}

void ChoisirNiveau(ComposantsJeu *jeu, Niveau *niveau, bool *niveauChoisi) {
    bool fini = false;
    ALLEGRO_EVENT event;
    int niveauActuellementAffiche = 0;

    Bouton boutonNiveaux[] = {
            {425, 200, 400, 70, "Level 1", al_load_bitmap("../images/apercu map.png")},
            {425, 200, 400, 70, "Level 2", al_load_bitmap("../images/apercu map.png")},
            {425, 200, 400, 70, "Level 3", al_load_bitmap("../images/apercu map.png")}
    };
    int nbNiveaux = sizeof(boutonNiveaux) / sizeof(boutonNiveaux[0]);

    Bouton boutonRetour = {-10, 612, 130, 70, "<-"};
    Bouton flecheGauche = {300, 370, 50, 50, "<"};
    Bouton flecheDroite = {900, 370, 50, 50, ">"};
    Bouton Go = {425, 560, 400, 70, "GO !"};
    float mouseX = 0, mouseY = 0;

    al_clear_to_color(NOIR);
    al_draw_bitmap(jeu->ImageMenu, 0, 0, 0);
    DessinerNiveauApercu(boutonNiveaux[niveauActuellementAffiche], jeu);
    DessinerBouton1(boutonRetour, jeu->police, NOIR, GRIS_CLAIR);
    DessinerBouton1(flecheGauche, jeu->police, NOIR, BLANC);
    DessinerBouton1(flecheDroite, jeu->police, NOIR, BLANC);
    DessinerBouton1(Go, jeu->police, NOIR, BLANC);
    al_flip_display();

    while (!fini) {
        al_wait_for_event(jeu->file, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;
            case ALLEGRO_EVENT_MOUSE_AXES:
                mouseX = event.mouse.x;
                mouseY = event.mouse.y;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                if (EstDansLeBouton(boutonRetour, mouseX, mouseY)) {
                    *niveauChoisi = false;
                    fini = true;
                } else if (EstDansLeBouton(flecheGauche, event.mouse.x, event.mouse.y)) {
                    if (niveauActuellementAffiche > 0) niveauActuellementAffiche--;
                } else if (EstDansLeBouton(flecheDroite, event.mouse.x, event.mouse.y)) {
                    if (niveauActuellementAffiche < nbNiveaux - 1) niveauActuellementAffiche++;
                } else if (EstDansLeBouton(Go, event.mouse.x, event.mouse.y)) {
                    *niveau = niveauActuellementAffiche + 1;
                    *niveauChoisi = true;
                    fini = true;
                }
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if (event.keyboard.keycode == ALLEGRO_KEY_LEFT) {
                    if (niveauActuellementAffiche > 0) niveauActuellementAffiche--;
                } else if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT) {
                    if (niveauActuellementAffiche < nbNiveaux - 1) niveauActuellementAffiche++;
                } else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                    *niveau = niveauActuellementAffiche + 1;
                    *niveauChoisi = true;
                    fini = true;
                } else if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    *niveauChoisi = false;
                    fini = true;
                }
                break;
            case ALLEGRO_EVENT_TIMER:
                al_clear_to_color(NOIR);
                al_draw_bitmap(jeu->ImageMenu, 0, 0, 0);
                DessinerNiveauApercu(boutonNiveaux[niveauActuellementAffiche], jeu);
                if (EstDansLeBouton(boutonRetour, mouseX, mouseY)) {
                    DessinerBouton2(boutonRetour, jeu->police, NOIR, BLANC);
                } else {
                    DessinerBouton1(boutonRetour, jeu->police, NOIR, GRIS_CLAIR);
                }
                DessinerBouton1(flecheGauche, jeu->police, NOIR, BLANC);
                DessinerBouton1(flecheDroite, jeu->police, NOIR, BLANC);
                DessinerBouton1(Go, jeu->police, NOIR, BLANC);
                al_flip_display();
                break;
        }
    }
}

void lancerNiveau(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2, Niveau niveau) {
    switch (niveau) {
        case NIVEAU_1:
            Jeu(jeu, joueur1, joueur2);
            break;
        case NIVEAU_2:
            Jeu(jeu, joueur1, joueur2);
            break;
        case NIVEAU_3:
            Jeu(jeu, joueur1, joueur2);
            break;
        default:
            break;
    }
}

void DessinerMenu(ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police, float mouseX, float mouseY, Bouton boutons[],
                  int nbBoutons) {
    al_clear_to_color(NOIR);
    al_draw_bitmap(ImageMenu, 0, 0, 0);
    for (int i = 0; i < nbBoutons; ++i) {
        if (EstDansLeBouton(boutons[i], mouseX, mouseY)) {
            DessinerBouton2(boutons[i], police, NOIR_TRANSPARENT, GRIS_CLAIR_TRANSPARENT);
        } else {
            DessinerBouton1(boutons[i], police, NOIR, BLANC);
        }
    }
    al_flip_display();
}

void Menu(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2, Sons *son) {
    SonBoutonClique(son);
    bool fini = false, lancerJeu = false, niveauChoisi = false;
    Niveau niveau = NIVEAU_INCONNU;

    Bouton boutons[] = {
            {425, 235, 400, 70, "Play"},
            {425, 335, 400, 70, "Options"},
            {425, 435, 400, 70, "Scores"},
            {425, 535, 400, 70, "Exit"}
    };
    int nbBoutons = sizeof(boutons) / sizeof(boutons[0]);
    ALLEGRO_EVENT event;
    float mouseX = 0, mouseY = 0;

    PremierAffichageMenu(jeu->ImageMenu, jeu->police, nbBoutons, boutons);

    al_start_timer(jeu->timer);
    while (!fini) {
        al_wait_for_event(jeu->file, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
                for (int i = 0; i < nbBoutons; ++i) {
                    if (EstDansLeBouton(boutons[i], event.mouse.x, event.mouse.y)) {
                        if (!(strcmp(boutons[i].texte, "Play"))) {
                            SonBoutonClique(son);
                            do {
                                ChoisirNiveau(jeu, &niveau, &niveauChoisi);
                                SonBoutonClique(son);
                                if (!niveauChoisi) { break; }
                                ChoisirPseudos(jeu, joueur1, joueur2, &lancerJeu, son);
                            } while (!lancerJeu && niveauChoisi);

                            if (lancerJeu) {
                                ArreterMusiqueFondDeMenu(son);
                                AfficherControls(jeu, joueur1, joueur2);
                                JouerMusiqueJeu(son);
                                lancerNiveau(jeu, joueur1, joueur2, niveau);
                                ArreterMusiqueJeu(son);
                                JouerMusiqueFondDeMenu(son);
                                lancerJeu = false;
                            }
                        }
                        if (!(strcmp(boutons[i].texte, "Options"))) {
                            SonBoutonClique(son);
                            MenuOptions(&jeu, &son);
                        }
                        if (!(strcmp(boutons[i].texte, "Scores"))) {
                            SonBoutonClique(son);
                        }
                        if (!(strcmp(boutons[i].texte, "Exit"))) {
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
                DessinerMenu(jeu->ImageMenu, jeu->police, mouseX, mouseY, boutons, nbBoutons);
                break;
        }
    }
}
