#include <stdio.h>
#include "constantes.h"
#include "./menu/menu.h"

int main(void) {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_BITMAP *ImageMenu = NULL;
    ALLEGRO_EVENT_QUEUE *queue1 = NULL;
    ALLEGRO_FONT *police = NULL;
    bool fini = false;

    assert(al_init());
    assert(al_init_primitives_addon());
    assert(al_init_image_addon());
    assert(al_install_keyboard());
    al_init_font_addon();
    assert(al_init_ttf_addon());
    assert(al_install_mouse());

    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    assert(display);
    ImageMenu = al_load_bitmap("../images/fondmenuV2.jpg");
    assert(ImageMenu);
    queue1 = al_create_event_queue();
    assert(queue1);
    police = al_load_ttf_font("../police/RubikDoodleShadow-Regular.ttf", 50, 0);
    assert(police);

    al_register_event_source(queue1, al_get_display_event_source(display));
    al_register_event_source(queue1, al_get_keyboard_event_source());

    al_set_window_title(display, "Escooked");
    al_set_window_position(display, 130, 30);
    al_clear_to_color(BLANC);
    al_draw_bitmap(ImageMenu, 0, 0, 0);
    al_draw_text(police, BLANC, 640, 415, ALLEGRO_ALIGN_CENTRE, "PRESS ENTER");
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
                        menu(display, ImageMenu, police);
                        fini = true;
                        break;
                    case ALLEGRO_KEY_ESCAPE:
                        fini = true;
                        break;
                }
                break;
        }
    }
    al_destroy_display(display);
    al_destroy_bitmap(ImageMenu);
    al_destroy_event_queue(queue1);
    al_destroy_font(police);
    display = NULL;
    ImageMenu = NULL;
    queue1 = NULL;
    police = NULL;
    return 0;
}
