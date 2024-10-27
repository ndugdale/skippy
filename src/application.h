#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>
#include "clock.h"
#include "player.h"

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    Clock clock;
    Player player;
    SDL_Color background;
    uint16_t score;
    uint16_t hiscore;
} Application;

void application_init(Application* application);
void application_handle_input(Application* application);
void application_update(Application* application);
void application_render(Application* application);
void application_cleanup(Application* application);
