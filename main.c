#include <stdio.h>
#include "constantes.h"
#include "./menu/menu.h"


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

void ChargerImages(ComposantsJeu *jeu) {
    jeu->decor = al_load_bitmap("../images/decor1.png");
    jeu->sol = al_load_bitmap("../images/sol(1).png");
    jeu->planDeTravail = al_load_bitmap("../images/plantravail.png");
    jeu->plaqueDeCuisson = al_load_bitmap("../images/cuisson(1).png");
    jeu->poubelle = al_load_bitmap("../images/poubelle.png");
    jeu->distributeurAssiette = al_load_bitmap("../images/distribassiettes.png");
    jeu->sortie = al_load_bitmap("../images/sortie(1).png");
    jeu->ImageMenu = al_load_bitmap("../images/fondmenuV2.jpg");
}

void ChargerPolices(ComposantsJeu *jeu) {
    jeu->police = al_load_ttf_font("../police/RubikDoodleShadow-Regular.ttf", 50, 0);
    jeu->policeTitre = al_load_ttf_font("../police/BungeeShade-Regular.ttf", 90, 0);
}

void InitialiserSon(Sons *son) {
    if (!al_reserve_samples(2)) {
        fprintf(stderr, "Erreur lors de la reservation des echantillons.\n");
    }
    son->mixer = al_get_default_mixer();
    son->musiqueDeFond = al_load_sample("../soundeffect/Elevator-music.wav");
    son->sonBoutonClique = al_load_sample("../soundeffect/click-sound.wav");
    son->instanceDeMusqiue = al_create_sample_instance(son->musiqueDeFond);
    al_set_sample_instance_playmode(son->instanceDeMusqiue, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(son->instanceDeMusqiue, 0.5);
    al_attach_sample_instance_to_mixer(son->instanceDeMusqiue, son->mixer);
    al_play_sample_instance(son->instanceDeMusqiue);
}

void PremierAffichageFenetre(ComposantsJeu *jeu) {
    al_set_window_title(jeu->fenetre, "TP2");
    al_set_window_position(jeu->fenetre, 130, 30);
    al_clear_to_color(NOIR);
    al_draw_bitmap(jeu->ImageMenu, 0, 0, 0);
    al_draw_text(jeu->policeTitre, NOIR, 624, 308, ALLEGRO_ALIGN_CENTER, "-ESCOOKED-");
    al_draw_text(jeu->police, NOIR, 624, 500, ALLEGRO_ALIGN_CENTRE, "PRESS ENTER");
    al_flip_display();
}

void LibererMemoire(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2) {
    al_destroy_display(jeu->fenetre);
    al_destroy_event_queue(jeu->file);
    al_destroy_timer(jeu->timer);

    al_destroy_bitmap(jeu->ImageMenu);
    al_destroy_bitmap(jeu->decor);
    al_destroy_bitmap(jeu->sol);
    al_destroy_bitmap(jeu->plaqueDeCuisson);
    al_destroy_bitmap(jeu->planDeDecoupe);
    al_destroy_bitmap(jeu->planDeTravail);
    al_destroy_bitmap(jeu->distributeurAssiette);
    al_destroy_bitmap(jeu->poubelle);
    al_destroy_bitmap(jeu->sortie);
    al_destroy_bitmap(joueur1->image);
    al_destroy_bitmap(joueur2->image);

    jeu->fenetre = NULL;
    jeu->file = NULL;
    jeu->timer = NULL;

    jeu->ImageMenu = NULL;
    jeu->decor = NULL;
    jeu->sol = NULL;
    jeu->plaqueDeCuisson = NULL;
    jeu->planDeDecoupe = NULL;
    jeu->planDeTravail = NULL;
    jeu->distributeurAssiette = NULL;
    jeu->poubelle = NULL;
    jeu->sortie = NULL;
    joueur1->image = NULL;
    joueur2->image = NULL;
}

int main(void) {
    InitialiserAllegro();
    bool fini = false;
    Joueur joueur1, joueur2;
    ComposantsJeu jeu;
    Sons son;
    ALLEGRO_EVENT event;

    InitialiserFenetreFileTimer(&jeu);
    ChargerImages(&jeu);
    ChargerPolices(&jeu);
    InitialiserJoueur(&joueur1, "../images/personnage(1).png", 100, 100);
    InitialiserJoueur(&joueur2, "../images/personnage(1).png", 300, 300);
    PremierAffichageFenetre(&jeu);
    InitialiserSon(&son);

    while (!fini) {
        al_wait_for_event(jeu.file, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;
            case ALLEGRO_EVENT_KEY_UP:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_ENTER:
                        Menu(&jeu, &joueur1, &joueur2, &son);
                        fini = true;
                        break;
                }
                break;
        }
    }

    LibererMemoire(&jeu, &joueur1, &joueur2);
    return 0;
}