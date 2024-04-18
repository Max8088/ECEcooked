#include <stdio.h>
#include "constantes.h"
#include "./menu/menu.h"
#include "./jouer/jouer.h"

void InitialiserAllegro() {
    assert(al_init());
    assert(al_init_primitives_addon());
    assert(al_init_image_addon());
    assert(al_install_keyboard());
    al_init_font_addon();
    assert(al_init_ttf_addon());
    assert(al_install_mouse());
    assert(al_install_audio());
    assert(al_init_acodec_addon());
}

void jouerMusiqueFond(ALLEGRO_SAMPLE **musiqueFond, ALLEGRO_SAMPLE_INSTANCE **instanceMusique, ALLEGRO_MIXER *mixer) {
    *musiqueFond = al_load_sample("../soundeffect/Elevator-music.wav");
    if (!*musiqueFond) {
        fprintf(stderr, "Impossible de charger la musique de fond.\n");
        return;
    }
    *instanceMusique = al_create_sample_instance(*musiqueFond);
    if (!*instanceMusique) {
        fprintf(stderr, "Impossible de créer une instance de musique.\n");
        return;
    }
    al_set_sample_instance_playmode(*instanceMusique, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(*instanceMusique, 0.5);
    al_attach_sample_instance_to_mixer(*instanceMusique, mixer);
    al_play_sample_instance(*instanceMusique);
}

void Liberation(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *ImageMenu, ALLEGRO_BITMAP *decor1, ALLEGRO_BITMAP *personnage,
                ALLEGRO_BITMAP *sol, ALLEGRO_BITMAP *cuisson, ALLEGRO_BITMAP *decoupe, ALLEGRO_BITMAP *planDeTravail,
                ALLEGRO_BITMAP *distrib_assiette, ALLEGRO_BITMAP *poubelle, ALLEGRO_BITMAP *sortie, ALLEGRO_EVENT_QUEUE
                *queue1, ALLEGRO_FONT *police, ALLEGRO_FONT *policeTitre, ALLEGRO_SAMPLE *musiqueFond,
                ALLEGRO_SAMPLE_INSTANCE *instanceMusique, ALLEGRO_MIXER *mixer, ALLEGRO_SAMPLE *sonBoutonClique) {
    if (display) {
        al_destroy_display(display);
        display = NULL;
    }
    if (ImageMenu) {
        al_destroy_bitmap(ImageMenu);
        ImageMenu = NULL;
    }
    if (decor1) {
        al_destroy_bitmap(decor1);
        decor1 = NULL;
    }
    if (personnage) {
        al_destroy_bitmap(personnage);
        personnage = NULL;
    }
    if (sol) {
        al_destroy_bitmap(sol);
        sol = NULL;
    }
    if (cuisson) {
        al_destroy_bitmap(cuisson);
        cuisson = NULL;
    }
    if (decoupe) {
        al_destroy_bitmap(decoupe);
        decoupe = NULL;
    }
    if (planDeTravail) {
        al_destroy_bitmap(planDeTravail);
        planDeTravail = NULL;
    }
    if (distrib_assiette) {
        al_destroy_bitmap(distrib_assiette);
        distrib_assiette = NULL;
    }
    if (poubelle) {
        al_destroy_bitmap(poubelle);
        poubelle = NULL;
    }
    if (sortie) {
        al_destroy_bitmap(sortie);
        sortie = NULL;
    }
    if (queue1) {
        al_destroy_event_queue(queue1);
        queue1 = NULL;
    }
    if (police) {
        al_destroy_font(police);
        police = NULL;
    }
    if (policeTitre) {
        al_destroy_font(policeTitre);
        policeTitre = NULL;
    }
    if (musiqueFond) {
        al_destroy_sample(musiqueFond);
        musiqueFond = NULL;
    }
    if (instanceMusique) {
        al_destroy_sample_instance(instanceMusique);
        instanceMusique = NULL;
    }
    if (mixer) {
        al_destroy_mixer(mixer);
        mixer = NULL;
    }
    if (sonBoutonClique) {
        al_destroy_sample(sonBoutonClique);
        sonBoutonClique = NULL;
    }
}

int main(void) {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *ImageMenu = NULL;
    ALLEGRO_BITMAP *decor1 = NULL;
    ALLEGRO_BITMAP *personnage = NULL;
    ALLEGRO_BITMAP *sol = NULL;
    ALLEGRO_BITMAP *cuisson = NULL;
    ALLEGRO_BITMAP *decoupe = NULL;
    ALLEGRO_BITMAP *planDeTravail = NULL;
    ALLEGRO_BITMAP *distrib_assiette = NULL;
    ALLEGRO_BITMAP *poubelle = NULL;
    ALLEGRO_BITMAP *sortie = NULL;
    ALLEGRO_EVENT_QUEUE *queue1 = NULL;
    ALLEGRO_FONT *police = NULL;
    ALLEGRO_FONT *policeTitre = NULL;
    ALLEGRO_SAMPLE *musiqueFond = NULL;
    ALLEGRO_SAMPLE_INSTANCE *instanceMusique = NULL;
    ALLEGRO_SAMPLE *sonBoutonClique = NULL;

    bool fini = false;

    InitialiserAllegro();

    if (!al_reserve_samples(2)) {
        fprintf(stderr, "Erreur lors de la reservation des echantillons.\n");
        return -1;
    }
    ALLEGRO_MIXER *mixer = al_get_default_mixer();

    jouerMusiqueFond(&musiqueFond, &instanceMusique, mixer);

    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    assert(display);
    ImageMenu = al_load_bitmap("../images/fondmenuV2.jpg");
    assert(ImageMenu);
    decor1 = al_load_bitmap("../images/decor2.png");
    assert(decor1);
    personnage = al_load_bitmap("../images/personnage(1).png");
    assert(personnage);
    sol = al_load_bitmap("../images/sol(1).png");
    assert(sol);
    cuisson = al_load_bitmap("../images/cuisson(1).png");
    assert(cuisson);
    decoupe = al_load_bitmap("../images/decoupe.png");
    assert(decoupe);
    planDeTravail = al_load_bitmap("../images/plantravail.png");
    assert(planDeTravail);
    distrib_assiette = al_load_bitmap("../images/distributeurassiettes.png");
    assert(distrib_assiette);
    poubelle = al_load_bitmap("../images/poubelle.png");
    assert(poubelle);
    sortie = al_load_bitmap("../images/sortie(1).png");
    assert(sortie);
    queue1 = al_create_event_queue();
    assert(queue1);
    police = al_load_ttf_font("../police/RubikDoodleShadow-Regular.ttf", 50, 0);
    assert(police);
    policeTitre = al_load_ttf_font("../police/BungeeShade-Regular.ttf", 90, 0);
    assert(policeTitre);
    sonBoutonClique = al_load_sample("../soundeffect/click-sound.wav");
    assert(sonBoutonClique);

    al_register_event_source(queue1, al_get_display_event_source(display));
    al_register_event_source(queue1, al_get_keyboard_event_source());
    al_register_event_source(queue1, al_get_mouse_event_source());

    al_set_window_title(display, "Escooked");
    al_set_window_position(display, 130, 30);
    al_clear_to_color(BLANC);
    al_draw_bitmap(ImageMenu, 0, 0, 0);
    al_draw_text(policeTitre, NOIR, 624, 308, ALLEGRO_ALIGN_CENTRE, "-ESCOOKED-");
    al_draw_text(police, NOIR, 624, 500, ALLEGRO_ALIGN_CENTRE, "PRESS ENTER");
    al_flip_display();

    while (!fini) {
        ALLEGRO_EVENT event1;
        al_wait_for_event(queue1, &event1);

        switch (event1.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                switch (event1.keyboard.keycode) {
                    case ALLEGRO_KEY_ENTER:
                        menu(display, ImageMenu, decor1, sol, personnage, cuisson, decoupe, planDeTravail,
                             distrib_assiette, poubelle, sortie, police, queue1, mixer, instanceMusique,
                             sonBoutonClique);
                        fini = true;
                        break;
                    case ALLEGRO_KEY_ESCAPE:
                        fini = true;
                        break;
                }
                break;
        }
    }

    Liberation(display, ImageMenu, decor1, personnage, sol, cuisson, decoupe, planDeTravail, distrib_assiette, poubelle,
               sortie, queue1, police, policeTitre, musiqueFond, instanceMusique, mixer, sonBoutonClique);

    return 0;
}
