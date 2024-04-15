//
// Created by pierr on 03/04/2024.
//

#ifndef ESCOOKED_CONSTANTES_H
#define ESCOOKED_CONSTANTES_H

#include <stdio.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5//allegro_font.h>
#include <allegro5//allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#define DISPLAY_WIDTH 1248
#define DISPLAY_HEIGHT 702
#define NOIR al_map_rgb(0, 0, 0)
#define BLANC al_map_rgba(255, 255, 255, 0)
#define NOIR_TRANSPARENT al_map_rgba(0, 0, 0, 150)
#define GRIS_CLAIR_TRANSPARENT al_map_rgba(150, 150, 150, 50)
#define GRIS_CLAIR al_map_rgb(150, 150, 150)
#define VERT_CLAIR al_map_rgb(0, 200, 0)
#define ROUGE al_map_rgb(150, 0, 0)

#endif //ESCOOKED_CONSTANTES_H
