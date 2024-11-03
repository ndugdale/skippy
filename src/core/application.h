#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

#include "core/clock.h"
#include "core/renderer.h"
#include "core/texture_manager.h"
#include "core/window.h"
#include "player.h"
#include "turners.h"

typedef struct {
    Window window;
    Renderer renderer;
    TextureManager texture_manager;
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
