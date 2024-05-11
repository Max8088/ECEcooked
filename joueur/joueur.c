
#include "../constantes.h"
#include "../menu/menu.h"
#include "joueur.h"


void InitialiserJoueur(Joueur *joueur, const char *cheminVersImage) {
    joueur->vx = 0;
    joueur->vy = 0;
    joueur->angle = 3.0 * M_PI_2 ;
    joueur->score = 0;
    joueur->image = al_load_bitmap(cheminVersImage);
    strcpy(joueur->pseudo, "");
    joueur->element = NULL;
    assert(joueur->image);
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
