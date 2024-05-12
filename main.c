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

void ChargerImagesJeu(ComposantsJeu *jeu) {
    jeu->decor = al_load_bitmap("../images/decor1.png");
    jeu->sol1 = al_load_bitmap("../images/SOL 1.png");
    jeu->sol2 = al_load_bitmap("../images/SOL 2.png");
    jeu->planDeTravail = al_load_bitmap("../images/PLAN DE TRAVAIL.png");
    jeu->plaqueDeCuisson = al_load_bitmap("../images/PLAQUE DE CUISSON (2).png");
    jeu->stationDeDecoupe = al_load_bitmap("../images/STATION DE DECOUPE (2).png");
    jeu->presseAgrume = al_load_bitmap("../images/PRESSE-AGRUME (1).png");
    jeu->poubelle = al_load_bitmap("../images/POUBELLE.png");
    jeu->sortie = al_load_bitmap("../images/SORTIE.png");
    jeu->ImageMenu = al_load_bitmap("../images/fondmenuV2.jpg");
    jeu->ImageFondDeJeu = al_load_bitmap("../images/ImageFondDeJeu.png");
    jeu->Z = al_load_bitmap("../images/Z.png");
    jeu->Q = al_load_bitmap("../images/Q.png");
    jeu->S = al_load_bitmap("../images/S.png");
    jeu->D = al_load_bitmap("../images/D.png");
    jeu->C = al_load_bitmap("../images/C.png");
    jeu->V = al_load_bitmap("../images/V.png");
    jeu->P = al_load_bitmap("../images/P.png");
    jeu->L = al_load_bitmap("../images/L.png");
    jeu->M = al_load_bitmap("../images/M.png");
    jeu->FlecheHaut = al_load_bitmap("../images/UP.png");
    jeu->FlecheBas = al_load_bitmap("../images/DOWN.png");
    jeu->FlecheGauche = al_load_bitmap("../images/LEFT.png");
    jeu->FlecheDroite = al_load_bitmap("../images/RIGHT.png");
    jeu->sablier = al_load_bitmap("../images/MACARON TEMPS (1).png");
    jeu->tomate = al_load_bitmap("../images/tomate(1).png");
    jeu->citron = al_load_bitmap("../images/CITRON.png");
    jeu->menthe = al_load_bitmap("../images/MENTHE.png");
    jeu->limonade = al_load_bitmap("../images/LIMONADE.png");
    jeu->canneASucre = al_load_bitmap("../images/CanneASucre.png");
    jeu->frigoCitron = al_load_bitmap("../images/FRIGO _ CITRON (1).png");
    jeu->frigoLimonade = al_load_bitmap("../images/FRIGO _ LIMONADE (1).png");
    jeu->frigoMenthe = al_load_bitmap("../images/FRIGO _ MENTHE (1).png");
    jeu->frigoCanneASucre = al_load_bitmap("../images/FRIGO _ CANNE A SUCRE (1).png");
    jeu->mojito = al_load_bitmap("../images/mojito.png");
    jeu->caipirinha = al_load_bitmap("../images/caipirinha.png");
    jeu->hintzy = al_load_bitmap("../images/hintzy.png");
}

void ChargerPolices(ComposantsJeu *jeu) {
    jeu->police = al_load_ttf_font("../police/RubikDoodleShadow-Regular.ttf", 40, 0);
    jeu->policeTitre = al_load_ttf_font("../police/BungeeShade-Regular.ttf", 90, 0);
    jeu->policePseudo = al_load_ttf_font("../police/RubikDoodleShadow-Regular.ttf", 20, 0);
    jeu->policeRegle = al_load_ttf_font("../police/Kanit-Bold.ttf", 30, 0);
}

void InitialiserSon(Sons *son) {
    if (!al_reserve_samples(4)) {
        fprintf(stderr, "Erreur lors de la reservation des echantillons.\n");
    }
    son->mixer = al_get_default_mixer();
    son->musiqueDeFondDeMenu = al_load_sample("../soundeffect/Menu.wav");
    son->sonBoutonClique = al_load_sample("../soundeffect/click-sound.wav");
    son->musiqueDeFondDeJeu = al_load_sample("../soundeffect/Niveau1.wav");

    son->instanceDeMusqiue = al_create_sample_instance(son->musiqueDeFondDeMenu);
    al_set_sample_instance_playmode(son->instanceDeMusqiue, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(son->instanceDeMusqiue, 0.5);
    al_attach_sample_instance_to_mixer(son->instanceDeMusqiue, son->mixer);
    al_play_sample_instance(son->instanceDeMusqiue);

    son->instanceEffetsSonores = al_create_sample_instance(son->sonBoutonClique);
    al_set_sample_instance_playmode(son->instanceEffetsSonores, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_gain(son->instanceEffetsSonores, 0.5);
    al_attach_sample_instance_to_mixer(son->instanceEffetsSonores, son->mixer);

    son->instanceMusiqueJeu = al_create_sample_instance(son->musiqueDeFondDeJeu);
    al_set_sample_instance_playmode(son->instanceMusiqueJeu, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(son->instanceMusiqueJeu, 0.5);
    al_attach_sample_instance_to_mixer(son->instanceMusiqueJeu, son->mixer);
}

void PremierAffichageFenetre(ComposantsJeu *jeu) {
    al_set_window_title(jeu->fenetre, "ECEcooked");
    al_set_window_position(jeu->fenetre, 130, 30);
    al_clear_to_color(NOIR);
    al_draw_bitmap(jeu->ImageMenu, 0, 0, 0);
    al_draw_text(jeu->policeTitre, NOIR, 624, 308, ALLEGRO_ALIGN_CENTER, "-ECEcooked-");
    al_draw_text(jeu->police, NOIR, 624, 500, ALLEGRO_ALIGN_CENTRE, "PRESS ENTER");
    al_flip_display();
}

void LibererMemoire(ComposantsJeu *jeu, Joueur *joueur1, Joueur *joueur2) {
    //Destruction des bitmaps
    if (jeu->ImageMenu != NULL) {
        al_destroy_bitmap(jeu->ImageMenu);
        jeu->ImageMenu = NULL;
    }
    if (jeu->ImageFondDeJeu != NULL) {
        al_destroy_bitmap(jeu->ImageFondDeJeu);
        jeu->ImageFondDeJeu = NULL;
    }
    if (jeu->decor != NULL) {
        al_destroy_bitmap(jeu->decor);
        jeu->decor = NULL;
    }
    if (jeu->sol1 != NULL) {
        al_destroy_bitmap(jeu->sol1);
        jeu->sol1 = NULL;
    }
    if (jeu->sol2 != NULL) {
        al_destroy_bitmap(jeu->sol2);
        jeu->sol2 = NULL;
    }
    if (jeu->planDeTravail != NULL) {
        al_destroy_bitmap(jeu->planDeTravail);
        jeu->planDeTravail = NULL;
    }
    if (jeu->plaqueDeCuisson != NULL) {
        al_destroy_bitmap(jeu->plaqueDeCuisson);
        jeu->plaqueDeCuisson = NULL;
    }
    if (jeu->poubelle != NULL) {
        al_destroy_bitmap(jeu->poubelle);
        jeu->poubelle = NULL;
    }
    if (jeu->sortie != NULL) {
        al_destroy_bitmap(jeu->sortie);
        jeu->sortie = NULL;
    }
    if (jeu->Z != NULL) {
        al_destroy_bitmap(jeu->Z);
        jeu->Z = NULL;
    }
    if (jeu->S != NULL) {
        al_destroy_bitmap(jeu->S);
        jeu->S = NULL;
    }
    if (jeu->Q != NULL) {
        al_destroy_bitmap(jeu->Q);
        jeu->Q = NULL;
    }
    if (jeu->D != NULL) {
        al_destroy_bitmap(jeu->D);
        jeu->D = NULL;
    }
    if (jeu->C != NULL) {
        al_destroy_bitmap(jeu->C);
        jeu->C = NULL;
    }
    if (jeu->V != NULL) {
        al_destroy_bitmap(jeu->V);
        jeu->V = NULL;
    }
    if (jeu->L != NULL) {
        al_destroy_bitmap(jeu->L);
        jeu->L = NULL;
    }
    if (jeu->M != NULL) {
        al_destroy_bitmap(jeu->M);
        jeu->M = NULL;
    }
    if (jeu->P != NULL) {
        al_destroy_bitmap(jeu->M);
        jeu->P = NULL;
    }
    if (jeu->FlecheHaut != NULL) {
        al_destroy_bitmap(jeu->FlecheHaut);
        jeu->FlecheHaut = NULL;
    }
    if (joueur1->image != NULL) {
        al_destroy_bitmap(joueur1->image);
        joueur1->image = NULL;
    }
    if (jeu->FlecheBas != NULL) {
        al_destroy_bitmap(jeu->FlecheBas);
        jeu->FlecheBas = NULL;
    }
    if (jeu->FlecheGauche != NULL) {
        al_destroy_bitmap(jeu->FlecheGauche);
        jeu->FlecheGauche = NULL;
    }
    if (jeu->FlecheDroite != NULL) {
        al_destroy_bitmap(jeu->FlecheDroite);
        jeu->FlecheDroite = NULL;
    }
    if (joueur2->image != NULL) {
        al_destroy_bitmap(joueur2->image);
        joueur2->image = NULL;
    }
    if (jeu->sablier != NULL) {
        al_destroy_bitmap(jeu->sablier);
        jeu->sablier = NULL;
    }
    if (jeu->frigoCitron != NULL) {
        al_destroy_bitmap(jeu->frigoCitron);
        jeu->frigoCitron = NULL;
    }

    // Libération des polices
    if (jeu->police != NULL) {
        al_destroy_font(jeu->police);
        jeu->police = NULL;
    }
    if (jeu->policeTitre != NULL) {
        al_destroy_font(jeu->policeTitre);
        jeu->policeTitre = NULL;
    }
    if (jeu->policePseudo != NULL) {
        al_destroy_font(jeu->policePseudo);
        jeu->policePseudo = NULL;
    }
    if (jeu->policeRegle != NULL) {
        al_destroy_font(jeu->policeRegle);
        jeu->policeRegle = NULL;
    }


    // Arrêt et destruction du timer
    if (jeu->timer != NULL) {
        al_stop_timer(jeu->timer);
        al_unregister_event_source(jeu->file, al_get_timer_event_source(jeu->timer));
        al_destroy_timer(jeu->timer);
        jeu->timer = NULL;
    }

    // Destruction de la file d'événements
    if (jeu->file != NULL) {
        al_destroy_event_queue(jeu->file);
        jeu->file = NULL;
    }

    // Destruction de la fenêtre d'affichage
    if (jeu->fenetre != NULL) {
        al_destroy_display(jeu->fenetre);
        jeu->fenetre = NULL;
    }
}

int main(void) {
    InitialiserAllegro();
    bool fini = false;
    Joueur joueur1, joueur2;
    ComposantsJeu jeu;
    Sons son;
    Scores scores;
    ALLEGRO_EVENT event;

    InitialiserFenetreFileTimer(&jeu);
    ChargerImagesJeu(&jeu);
    ChargerPolices(&jeu);
    ChargerScores(&scores);
    InitialiserJoueur(&joueur1, "../images/PERSO 1.png");
    InitialiserJoueur(&joueur2, "../images/PERSO 2.png");
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
                        Menu(&jeu, &joueur1, &joueur2, &son, &scores);
                        fini = true;
                        break;
                }
                break;
        }
    }

    LibererMemoire(&jeu, &joueur1, &joueur2);
    printf("\nTout marche bene chef\n");
    return 0;
}
