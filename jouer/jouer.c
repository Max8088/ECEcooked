//
// Created by pierr on 03/04/2024.
//
#include "../constantes.h"

void jeu(ALLEGRO_DISPLAY *display, ALLEGRO_BITMAP *ImageMenu, ALLEGRO_FONT *police) {
    ALLEGRO_EVENT_QUEUE *queue4 = NULL;
    bool fini = false;

    queue4 = al_create_event_queue();
    assert(queue4);

    al_register_event_source(queue4, al_get_display_event_source(display));

    al_clear_to_color(BLANC);
    al_draw_bitmap(ImageMenu, 0, 0, 0);
    al_draw_text(police, al_map_rgba(0, 0, 0, 200), 640, 351, ALLEGRO_ALIGN_CENTRE, "GAME STARTING...");
    al_flip_display();

    while (!fini) {
        ALLEGRO_EVENT event4;
        al_wait_for_event(queue4, &event4);
        switch (event4.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                fini = true;
                break;
        }
    }
    al_destroy_event_queue(queue4);
    queue4 = NULL;
}