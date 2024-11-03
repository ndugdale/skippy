#pragma once

#include <SDL2/SDL.h>

#include "core/clock.h"
#include "core/renderer.h"
#include "core/texture_manager.h"
#include "core/window.h"
#include "event/event.h"
#include "game/player.h"
#include "game/turners.h"

typedef struct {
    Window window;
    Renderer renderer;
    TextureManager texture_manager;
    Clock clock;
    Player player;
    Turners turners;
    SDL_Color background;
} Application;

void application_init(Application* application);
void application_dispatch_events(Application* application);
void application_handle_event(Application* application, Event event);
void application_update(Application* application);
void application_render(Application* application);
void application_cleanup(Application* application);
