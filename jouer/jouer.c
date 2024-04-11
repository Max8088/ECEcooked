//
// Created by pierr on 03/04/2024.
//
#include "../constantes.h"

void jeu(ALLEGRO_BITMAP *decor1, ALLEGRO_FONT *police, ALLEGRO_EVENT_QUEUE* queue1) {
    bool fini = false;

    al_clear_to_color(BLANC);
    al_draw_bitmap(decor1, 0, 0, 0);
    //al_draw_text(police, al_map_rgba(0, 0, 0, 200), 640, 351, ALLEGRO_ALIGN_CENTRE, "GAME STARTING...");
    al_flip_display();

    while (!fini) {
        ALLEGRO_EVENT event4;
        al_wait_for_event(queue1, &event4);
        //al_clear_to_color(BLANC);
        al_draw_bitmap(decor1, 0, 0, 0);
        //al_draw_text(police, al_map_rgba(0, 0, 0, 200), 640, 351, ALLEGRO_ALIGN_CENTRE, "GAME STARTING...");
        al_flip_display();
        switch (event4.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;
        }
    }
}