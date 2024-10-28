#pragma once

#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>
#include "clock.h"
#include "player.h"
#include "turners.h"

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    Clock clock;
    Player player;
    Turners turners;
    SDL_Color background;
    uint16_t score;
    uint16_t hiscore;
    bool round_in_progress;
} Application;

void application_init(Application* application);
void application_handle_input(Application* application);
void application_update(Application* application);
void application_render(Application* application);
void application_cleanup(Application* application);
